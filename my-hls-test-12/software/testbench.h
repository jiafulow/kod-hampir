#ifndef __TESTBENCH_H__
#define __TESTBENCH_H__

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

namespace {

// 'Hits' contains 12 integer values.
// [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
struct HitsType {
  typedef int T;
  static const unsigned int N = 12;
};
typedef std::array<HitsType::T, HitsType::N> Hits;

// 'Event' contains a list of Hits objects.
// [[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
//  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
//  ...
//  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]]
typedef std::vector<Hits> Event;

// 'FPGAEvent' contains the full list of chambers.
// Currently, it assumes 115 chambers, max 8 segments per chamber,
// 10 variables per segment.
// Therefore, the data shape is (None, 115, 8, 10).
struct FPGAEvent {
  static const unsigned int CHAMBERS  = emtf::num_chambers;
  static const unsigned int SEGMENTS  = emtf::num_segments;
  static const unsigned int VARIABLES = emtf::num_variables;
  static const unsigned int LENGTH    = CHAMBERS * SEGMENTS;

  emtf::emtf_phi_t    emtf_phi[LENGTH];
  emtf::emtf_bend_t   emtf_bend[LENGTH];
  emtf::emtf_theta1_t emtf_theta1[LENGTH];
  emtf::emtf_theta2_t emtf_theta2[LENGTH];
  emtf::emtf_qual_t   emtf_qual[LENGTH];
  emtf::emtf_time_t   emtf_time[LENGTH];
  emtf::flags_zone_t  flags_zone[LENGTH];
  emtf::flags_tzone_t flags_tzone[LENGTH];
  emtf::bx_t          bx[LENGTH];
  emtf::valid_t       valid[LENGTH];

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

  explicit FPGAEvent(const Event& evt);  // constructor

  void serialize_into(emtf::model_in_t in0[N_MODEL_IN]) const;  // serialize data into a single array
};

FPGAEvent::FPGAEvent(const Event& evt) {
  // Initialize
  for (unsigned iseg = 0; iseg < LENGTH; iseg++) {
    emtf_phi[iseg]    = 0;
    emtf_bend[iseg]   = 0;
    emtf_theta1[iseg] = 0;
    emtf_theta2[iseg] = 0;
    emtf_qual[iseg]   = 0;
    emtf_time[iseg]   = 0;
    flags_zone[iseg]  = 0;
    flags_tzone[iseg] = 0;
    bx[iseg]          = 0;
    valid[iseg]       = 0;
  }

  // Fill values
  // This is basically converting sparsified data into unsparsified
  auto index_fn = ArrayIndex();

  for (unsigned ihit = 0; ihit < evt.size(); ihit++) {
    const int emtf_chamber = evt[ihit][0];
    const int emtf_segment = evt[ihit][1];
    const int iseg = index_fn(emtf_chamber, emtf_segment);

    emtf_phi[iseg]    = evt[ihit][2];
    emtf_bend[iseg]   = evt[ihit][3];
    emtf_theta1[iseg] = evt[ihit][4];
    emtf_theta2[iseg] = evt[ihit][5];
    emtf_qual[iseg]   = evt[ihit][6];
    emtf_time[iseg]   = evt[ihit][7];
    flags_zone[iseg]  = evt[ihit][8];
    flags_tzone[iseg] = evt[ihit][9];
    bx[iseg]          = evt[ihit][10];
    valid[iseg]       = evt[ihit][11];
  }
}

// Serialize data into a single array
void FPGAEvent::serialize_into(emtf::model_in_t in0[N_MODEL_IN]) const {
  for (unsigned iseg = 0; iseg < N_MODEL_IN; iseg++) {
    auto&& in0_tmp = in0[iseg];

    in0_tmp.range(emtf::emtf_phi_bits_hi   , emtf::emtf_phi_bits_lo)    = emtf_phi[iseg];
    in0_tmp.range(emtf::emtf_bend_bits_hi  , emtf::emtf_bend_bits_lo)   = emtf_bend[iseg];
    in0_tmp.range(emtf::emtf_theta1_bits_hi, emtf::emtf_theta1_bits_lo) = emtf_theta1[iseg];
    in0_tmp.range(emtf::emtf_theta2_bits_hi, emtf::emtf_theta2_bits_lo) = emtf_theta2[iseg];
    in0_tmp.range(emtf::emtf_qual_bits_hi  , emtf::emtf_qual_bits_lo)   = emtf_qual[iseg];
    in0_tmp.range(emtf::emtf_time_bits_hi  , emtf::emtf_time_bits_lo)   = emtf_time[iseg];
    in0_tmp.range(emtf::flags_zone_bits_hi , emtf::flags_zone_bits_lo)  = flags_zone[iseg];
    in0_tmp.range(emtf::flags_tzone_bits_hi, emtf::flags_tzone_bits_lo) = flags_tzone[iseg];
    in0_tmp.range(emtf::bx_bits_hi         , emtf::bx_bits_lo)          = bx[iseg];
    in0_tmp.range(emtf::valid_bits_hi      , emtf::valid_bits_lo)       = valid[iseg];
  }
}

// 'FPGAResult' contains the output, which is going to be sent to the NN.
// Assume 4 muon candidates and each muon candidate has 36 variables.
struct FPGAResult {
  static const unsigned int TRACKS = emtf::num_out_tracks;
  static const unsigned int VARIABLES = emtf::num_out_variables;
  static const unsigned int LENGTH = TRACKS * VARIABLES;

  emtf::model_out_t data[LENGTH];

  FPGAResult();  // constructor
};

FPGAResult::FPGAResult() {
  // Initialize
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

// Initialize array to zeros
template <typename T, size_t N>
void init_array_as_zeros(T (&arr)[N]) {
  std::fill(arr, arr + N, 0);
}

// Initialize array to ones
template <typename T, size_t N>
void init_array_as_ones(T (&arr)[N]) {
  std::fill(arr, arr + N, 1);
}

// Print plain array
template <typename T, size_t N>
void print_array(T const (&arr)[N]) {
  std::copy(arr, arr + N, std::ostream_iterator<T>(std::cout, ", "));
}

// Print std::array, std::vector
template <typename T>
void print_std_array(T const& arr) {
  std::copy(std::begin(arr), std::end(arr), std::ostream_iterator<typename T::value_type>(std::cout, ", "));
}

// Get array length
template <typename T, size_t N>
constexpr size_t get_array_length(T const (&arr)[N]) { return N; }

}  // anonymous namespace

#endif  // __TESTBENCH_H__ not defined
