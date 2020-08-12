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
     657,  664,  671,  678,  685,  692,  699,  706,  713,  720,  727,  734,
     741,  748,  754,  755,  761,  762,  768,  769,  775,  776,  782,  783,
     789,  790,  796,  797,  803,  804,  809,  810,  811,  816,  817,  818,
     823,  824,  825,  830,  831,  832,  837,  838,  839,  844,  845,  846,
     851,  852,  853,  858,  859,  860,  864,  865,  866,  867,  871,  872,
     873,  874,  878,  879,  880,  881,  885,  886,  887,  888,  892,  893,
     894,  899,  900,  901,  905,  906,  907,  912,  913,  914,  919,  920,
     921,  925,  926,  927,  932,  933,  934,  938,  939,  940,  941,  945,
     946,  947,  948,  951,  952,  953,  954,  958,  959,  960,  961,  965,
     966,  967,  968,  970,  971,  972,  973,  974,  975,  976,  977,  978,
     979,  980,  981,  982,  983,  984,  985,  986,  987,  988,  989,  990,
     991,  992,  993,  994,  995,  996,  997,  998,  999, 1000, 1001, 1002,
    1003, 1004, 1005, 1006, 1007, 1008, 1009, 1010, 1011, 1012, 1013, 1014,
    1015, 1016, 1018, 1019, 1020, 1021, 1022, 1023, 1026, 1027, 1028, 1029,
    1030, 1031, 1034, 1035, 1036, 1037, 1038, 1039, 1041, 1042, 1043, 1044,
    1045, 1046, 1047, 1048, 1049, 1050, 1051, 1053, 1054, 1055, 1056, 1057,
    1058, 1059, 1061, 1062, 1063, 1064, 1065, 1066, 1067, 1069, 1070, 1071,
    1072, 1073, 1074, 1075, 1076, 1077, 1078, 1079, 1081, 1082, 1083, 1084,
    1085, 1089, 1090, 1091, 1092, 1097, 1098, 1099, 1104, 1105, 1106, 1111,
    1112, 1113, 1119, 1120, 1126, 1127, 1133
  };
  std::vector<unsigned> values = {
    128, 128, 128, 128, 192, 192, 192, 192, 192, 192, 192, 192, 192, 224, 128,
    224, 128, 224, 192, 224, 192, 224, 192, 224, 192, 224, 192, 224, 192, 224,
    128, 192, 224, 128, 224, 224, 192, 224, 224, 192, 224, 160, 192, 224,  32,
    192, 224,  32, 192, 224,  32, 192, 224,  32, 128, 224,  32,  32, 128, 224,
     32,  32, 192, 224,  32,  32, 192,  96,  32,  32, 192,  96,  32, 192,  32,
     32, 128, 224,  32, 128, 224,  32, 192, 224,  32, 128, 192,  96, 128, 224,
     96,   3, 128, 224,  32,   3, 128, 224,  32,   1, 135, 224, 224,   1, 135,
    226, 224,  19, 167, 227, 224,  16,  16,  19, 175, 239, 248,  24,  24,  24,
     27, 191, 255, 122,  24,  24,  24,  31, 255, 255, 126,  26,  24,  10,  15,
    247, 247,  23,   6,   2,   7,   7, 247, 231,   5,   7,   6,   7,   7, 231,
    229,   1,   5,   7,   7,   7, 231, 229,   1,   5,   7,   7, 231, 229,   1,
      7,   7, 231, 228,   4,   7,   7, 231, 102,   4,   4,   5,   7, 231,  70,
      4,   4,   4,   5,   7, 231,   6,   4,   4,   5,   7, 231,   2,   2,   4,
      4,   7, 231,   2,   2,   2,   6,   7, 227,   2,   2,   2,   2,   6,   7,
    226,   2,   2,   2,   2,   7, 226,   2,   2,   6, 226,   2,   6, 226,   2,
      2, 226,   2,   2, 192,   2, 192,   2, 192,   2
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
