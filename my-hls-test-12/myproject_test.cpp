#include <cassert>
#include <cstdint>
#include <array>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>

#include "firmware/myproject.h"


namespace {

// Hits contains 12 integer values.
// [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
struct HitsType {
  typedef int T;
  static const unsigned int N = 12;
};
typedef std::array<HitsType::T, HitsType::N> Hits;

// Event contains a list of Hits objects.
// [[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
//  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
//  ...
//  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]]
typedef std::vector<Hits> Event;

// FPGAEvent contains the full list of chambers.
// Currently, it assumes 115 chambers, max 8 segments per chamber,
// 10 variables per segment.
// Therefore, the data shape is (None, 115, 8, 10).
struct FPGAEvent {
  static const unsigned int CHAMBERS  = num_emtf_chambers;
  static const unsigned int SEGMENTS  = num_emtf_segments;
  static const unsigned int VARIABLES = num_emtf_variables;
  static const unsigned int LENGTH    = CHAMBERS * SEGMENTS;

  emtf_phi_t   emtf_phi[LENGTH];
  emtf_bend_t  emtf_bend[LENGTH];
  emtf_theta_t emtf_theta[LENGTH];
  emtf_theta_t emtf_theta_alt[LENGTH];
  emtf_qual_t  emtf_qual[LENGTH];
  emtf_time_t  emtf_time[LENGTH];
  zones_t      zones[LENGTH];
  timezones_t  timezones[LENGTH];
  bx_t         bx[LENGTH];
  valid_t      valid[LENGTH];

  explicit FPGAEvent(const Event& evt);  // constructor

  struct ArrayIndex {
    inline unsigned operator ()(unsigned emtf_chamber, unsigned emtf_segment) const {
      assert(emtf_chamber < CHAMBERS);
      assert(emtf_segment < SEGMENTS);
      return (emtf_chamber * SEGMENTS) + emtf_segment;
    }
    inline int operator ()(int emtf_chamber, int emtf_segment) const {
      assert(static_cast<unsigned>(emtf_chamber) < CHAMBERS);
      assert(static_cast<unsigned>(emtf_segment) < SEGMENTS);
      return (emtf_chamber * SEGMENTS) + emtf_segment;
    }
  };
};

FPGAEvent::FPGAEvent(const Event& evt) {
  static_assert(VARIABLES + 2 == HitsType::N, "Num of variables + 2 != num of elements in Hits");

  // Initialize
  for (unsigned i = 0; i < LENGTH; i++) {
    emtf_phi[i]       = 0;
    emtf_bend[i]      = 0;
    emtf_theta[i]     = 0;
    emtf_theta_alt[i] = 0;
    emtf_qual[i]      = 0;
    emtf_time[i]      = 0;
    zones[i]          = 0;
    timezones[i]      = 0;
    bx[i]             = 0;
    valid[i]          = 0;
  }

  // Fill values
  auto index_fn = ArrayIndex();

  for (unsigned ievt = 0; ievt < evt.size(); ievt++) {
    int emtf_chamber = evt[ievt][0];
    int emtf_segment = evt[ievt][1];
    int i = index_fn(emtf_chamber, emtf_segment);

    emtf_phi[i]       = evt[ievt][2];
    emtf_bend[i]      = evt[ievt][3];
    emtf_theta[i]     = evt[ievt][4];
    emtf_theta_alt[i] = evt[ievt][5];
    emtf_qual[i]      = evt[ievt][6];
    emtf_time[i]      = evt[ievt][7];
    zones[i]          = evt[ievt][8];
    timezones[i]      = evt[ievt][9];
    bx[i]             = evt[ievt][10];
    valid[i]          = evt[ievt][11];
  }
  return;
}

struct FPGAResult {
  static const unsigned int TRACKS = num_emtf_out_tracks;
  static const unsigned int VARIABLES = num_emtf_out_variables;
  static const unsigned int LENGTH = TRACKS * VARIABLES;

  model_default_t data[LENGTH];  // IMPORTANT: signed

  FPGAResult();  // constructor
};

FPGAResult::FPGAResult() {
  for (unsigned i = 0; i < LENGTH; i++) {
    data[i] = 0;
  }
}


// Read test bench event file
int read_tb_event(const std::string filename, Event& evt) {
  std::array<HitsType::T, HitsType::N> line_buf;

  std::string line;  // line in file
  char c;  // delimiter in line
  bool first_line = true;
  bool debug = false;

  std::ifstream infile(filename);

  if (infile.is_open()) {
    while (std::getline(infile, line)) {  // split by line break
      // This is how an input line looks like
      // [   2,    0, 2548,    5,   18,   17,   -6,    0,    4,    3,    0,    1],
      std::istringstream ss(line);

      // Parsing the line
      if (first_line) {
        ss >> c;  // get rid of '['
        first_line = false;
      }
      ss >> c;  // get rid of '['
      for (unsigned i = 0; i < line_buf.size(); ++i)  // extract int, then get rid of ','
        ss >> line_buf[i] >> c;
      ss >> c;  // get rid of ']'
      ss >> c;  // get rid of ','

      // Append
      evt.emplace_back(line_buf);

      // Debug
      if (debug) {
        std::cout << "Line: " << line << std::endl;
        std::cout << "Parsed line: ";
        for (unsigned i = 0; i < line_buf.size(); ++i)
          std::cout << line_buf[i] << " ";
        std::cout << std::endl;
      }
    }
  } else {
    std::cerr << "Failed to open file: " << filename << std::endl;
  }
  infile.close();
  return 0;
}

template <typename T, size_t N>
void print_array(T const (&arr)[N]) {
  std::copy(arr, arr + N, std::ostream_iterator<T>(std::cout, ", "));
}

template <typename T>
void print_std_array(T const& arr) {
  std::copy(std::begin(arr), std::end(arr), std::ostream_iterator<typename T::value_type>(std::cout, ", "));
}

}  // anonymous namespace


// _____________________________________________________________________________
// Main

int main(int argc, char **argv)
{
  // Create Event
  Event event_0;
  read_tb_event("tb_data/event_0.txt", event_0);

  // Create FPGAEvent
  const FPGAEvent fw_event_0(event_0);
  FPGAResult fw_result_0;
  FPGAResult fw_gold_0;

  // Run
  myproject(
      fw_event_0.emtf_phi,
      fw_event_0.emtf_bend,
      fw_event_0.emtf_theta,
      fw_event_0.emtf_theta_alt,
      fw_event_0.emtf_qual,
      fw_event_0.emtf_time,
      fw_event_0.zones,
      fw_event_0.timezones,
      fw_event_0.bx,
      fw_event_0.valid,
      fw_result_0.data
  );

  // Check for mismatches
  int err = 0;  // error code
  for (unsigned i = 0; i < N_TOP_FN_OUT; i++) {
    if (fw_result_0.data[i] != fw_gold_0.data[i])
      err++;
  }

  if (err) {
    // Print error info
    std::string clr_error = "\033[1;31m";  // red
    std::string clr_reset = "\033[0m";     // reset
    std::cout << clr_error << "FAILED!" << clr_reset << std::endl;
    std::cout << "Got:" << std::endl;
    print_array(fw_result_0.data);
    std::cout << std::endl;
    std::cout << "Expected:" << std::endl;
    print_array(fw_gold_0.data);
    std::cout << std::endl;
  }
  return 0;  //FIXME
}
