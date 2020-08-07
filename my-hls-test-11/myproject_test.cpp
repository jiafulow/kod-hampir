#include <cassert>
#include <cstdint>
#include <array>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <iterator>
#include <algorithm>

#include "firmware/myproject.h"


// Lambdas
auto create_event = [](const std::vector<unsigned>& indices, const std::vector<unsigned>& values) {
  assert(indices.size() == values.size());
  std::array<unsigned, N_TOP_FN_IN> arr = {0};
  for (unsigned i = 0; i < indices.size(); i++) {
    arr.at(indices.at(i)) = values.at(i);
  }
  return arr;
};

auto create_gold = [](const std::vector<unsigned>& indices, const std::vector<unsigned>& values) {
  assert(indices.size() == values.size());
  std::array<unsigned, N_TOP_FN_OUT> arr = {0};
  for (unsigned i = 0; i < indices.size(); i++) {
    arr.at(indices.at(i)) = values.at(i);
  }
  return arr;
};

auto create_event_0 = []() {
  std::vector<unsigned> indices = {
      127, 129, 132, 140, 142, 143, 144, 149, 153
  };
  std::vector<unsigned> values = {
      128,  64,  32,  24,   2,   4,   1,   4,   2
  };
  return create_event(indices, values);
};

auto create_gold_0 = []() {
  std::vector<unsigned> indices = {
      123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 139, 140,
      141, 142, 143, 144, 145, 148, 149, 150, 152, 153, 154
  };
  std::vector<unsigned> values = {
      128, 128, 192, 192, 192, 192, 224, 224, 224,  96,  96,  32,  32,  24,  24,
       26,   6,   7,   5,   1,   4,   4,   4,   2,   2,   2
  };
  return create_gold(indices, values);
};

// Global functions
template <typename T, size_t N>
void print_array(T const (&arr)[N]) {
  std::copy(arr, arr + N, std::ostream_iterator<T>(std::cout, ", "));
}

template <typename T>
void print_std_array(T const& arr) {
  std::copy(std::begin(arr), std::end(arr), std::ostream_iterator<typename T::value_type>(std::cout, ", "));
}


// _________________________________________________________________________________________________
// Main

int main(int argc, char **argv)
{
  // Allocate arrays
  top_fn_in_t inputs[N_TOP_FN_IN];
  top_fn_out_t outputs[N_TOP_FN_OUT];
  top_fn_out_t gold_outputs[N_TOP_FN_OUT];

  // Initialize
  auto event_0 = create_event_0();
  auto gold_0 = create_gold_0();

  for (unsigned i = 0; i < N_TOP_FN_IN; i++) {
    inputs[i] = event_0.at(i);
  }
  for (unsigned i = 0; i < N_TOP_FN_OUT; i++) {
    outputs[i] = 0;
  }
  for (unsigned i = 0; i < N_TOP_FN_OUT; i++) {
    gold_outputs[i] = gold_0.at(i);
  }

  // Run
  myproject(inputs, outputs);

  // Check for mismatches
  int err = 0;  // error code
  for (unsigned i = 0; i < N_TOP_FN_OUT; i++) {
    if (outputs[i] != gold_outputs[i])
      err++;
  }

  if (err) {
    // Print error info
    std::string clr_error = "\033[1;31m";  // red
    std::string clr_reset = "\033[0m";     // reset
    std::cout << clr_error << "FAILED!" << clr_reset << std::endl;
    std::cout << "Got:" << std::endl;
    print_array(outputs);
    std::cout << std::endl;
    std::cout << "Expected:" << std::endl;
    print_array(gold_outputs);
    std::cout << std::endl;
  }
  return err;
}
