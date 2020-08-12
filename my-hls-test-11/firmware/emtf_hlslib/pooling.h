#ifndef __EMTF_HLSLIB_POOLING_H__
#define __EMTF_HLSLIB_POOLING_H__

#include <type_traits>

#include "ap_int.h"


namespace emtf {

// Definition of a pattern.
// 8 rows, 3 params per row. The params are (low, med, hi) of the pattern window.
template <int ZONE, int PATT>
struct Pattern {
  static constexpr int zone = ZONE;
  static constexpr int patt = PATT;
  static constexpr int col_offset = 55;  // offset used to encode the pattern window
  static constexpr int rows = 8;
  static constexpr int params = 3;  // per row
  static constexpr int size = rows * params;
  static const int data[size];  // need to be initialized before use
  static const int padding;  // need to be initialized before use
};

// Hardcoded pattern definitions
template <>
const int Pattern<0, 0>::data[size] =  {
  21, 36, 46, 23, 35, 43, 29, 41, 49, 52, 54, 55, 54, 55, 56, 52, 57, 62,
  50, 57, 63, 46, 57, 65
};
template <>
const int Pattern<0, 1>::data[size] =  {
  35, 44, 50, 35, 44, 48, 39, 47, 51, 53, 54, 55, 54, 55, 56, 54, 56, 59,
  54, 57, 60, 53, 57, 61
};
template <>
const int Pattern<0, 2>::data[size] =  {
  43, 51, 53, 43, 51, 53, 46, 52, 54, 53, 55, 56, 54, 55, 56, 55, 56, 57,
  55, 56, 57, 55, 56, 57
};
template <>
const int Pattern<0, 3>::data[size] =  {
  51, 55, 59, 51, 55, 59, 52, 55, 58, 54, 55, 56, 54, 55, 56, 54, 55, 56,
  54, 55, 56, 54, 55, 56
};
template <>
const int Pattern<0, 4>::data[size] =  {
  57, 59, 67, 57, 59, 67, 56, 58, 64, 54, 55, 57, 54, 55, 56, 53, 54, 55,
  53, 54, 55, 53, 54, 55
};
template <>
const int Pattern<0, 5>::data[size] =  {
  60, 66, 75, 62, 66, 75, 59, 63, 71, 55, 56, 57, 54, 55, 56, 51, 54, 56,
  50, 53, 56, 49, 53, 57
};
template <>
const int Pattern<0, 6>::data[size] =  {
  64, 74, 89, 67, 75, 87, 61, 69, 81, 55, 56, 58, 54, 55, 56, 48, 53, 58,
  47, 53, 60, 45, 53, 64
};

template <>
const int Pattern<0, 0>::padding = 34;
template <>
const int Pattern<0, 1>::padding = 20;
template <>
const int Pattern<0, 2>::padding = 12;
template <>
const int Pattern<0, 3>::padding = 4;
template <>
const int Pattern<0, 4>::padding = 12;
template <>
const int Pattern<0, 5>::padding = 20;
template <>
const int Pattern<0, 6>::padding = 34;

// TODO: move the pattern definitions somewhere else?


// _________________________________________________________________________________________________
// Perform ROI pooling - pool from the (low, hi)-range of each row in the input image.

template <int ROWS, int COLS, int PATTERNS, int ZONE, int PATT>
void roi_pooling(
    const ap_uint<ROWS> inputs[COLS],
    ap_uint<ROWS> outputs[COLS * PATTERNS]
) {
#pragma HLS INLINE

  typedef Pattern<ZONE, PATT> pattern_t;
  constexpr int PADDING = pattern_t::padding;
  constexpr int COLS_W_PADDING = COLS + (PADDING * 2);  // add padding on both sides

  static_assert(pattern_t::rows == ROWS, "pattern must have the same num of rows");
  static_assert(pattern_t::size == ROWS * 3, "pattern data array size must be num of rows * 3");
  static_assert(PADDING > 0, "padding must be greater than 0");

  // Create local buffer
  typedef ap_uint<COLS_W_PADDING> buffer_t;
  buffer_t buf[ROWS];
#pragma HLS ARRAY_PARTITION variable=buf complete dim=0

  // Initialize buffer
  buf_init_loop : for (int row = 0; row < ROWS; row++) {
#pragma HLS PIPELINE II=1

    buf_init_loop_inner : for (int ip_col = 0; ip_col < COLS_W_PADDING; ip_col++) {
      int col = (ip_col - PADDING);
      if (0 <= col && col < COLS) {
        buf[row][ip_col] = inputs[col][(ROWS - 1) - row];  // CUIDADO: bit order from the test bench is flipped
      } else {
        buf[row][ip_col] = 0;
      }
    }
  }

  // Do pooling
  pool_loop : for (int row = 0; row < ROWS; row++) {
#pragma HLS PIPELINE II=1

    const int offset = pattern_t::col_offset;
    const int low = pattern_t::data[row * 3 + 0];
    const int high = pattern_t::data[row * 3 + 2];

    pool_loop_inner : for (int col = 0; col < COLS; col++) {
      int ip_col = (col + PADDING);
      int start = ip_col + (low - offset);
      int stop = ip_col + (high - offset);
      outputs[col * PATTERNS + PATT][(ROWS - 1) - row] = buf[row](stop, start);  // CUIDADO: bit order from the test bench is flipped
    }
  }
  return;
}

// _________________________________________________________________________________________________
// Module

template <typename INPUT_T, typename OUTPUT_T, typename CONFIG_T>
void roi_pooling_module(
    const INPUT_T inputs[N_TOP_FN_IN],
    OUTPUT_T outputs[N_TOP_FN_OUT]
) {
  // Make sure types are correct
  static_assert(INPUT_T::width == OUTPUT_T::width, "inputs and outputs must have the same data width");
  static_assert(N_TOP_FN_OUT == N_TOP_FN_IN * num_patterns, "outputs array size must be inputs array size * num_patterns");

  // Deduce template arguments
  constexpr int ROWS = INPUT_T::width;
  constexpr int COLS = N_TOP_FN_IN;
  constexpr int PATTERNS = num_patterns;

  // Do pooling
  roi_pooling<ROWS, COLS, PATTERNS, 0, 0>(inputs, outputs);  // zone 0 patt 0
  roi_pooling<ROWS, COLS, PATTERNS, 0, 1>(inputs, outputs);  // zone 0 patt 1
  roi_pooling<ROWS, COLS, PATTERNS, 0, 2>(inputs, outputs);  // zone 0 patt 2
  roi_pooling<ROWS, COLS, PATTERNS, 0, 3>(inputs, outputs);  // zone 0 patt 3
  roi_pooling<ROWS, COLS, PATTERNS, 0, 4>(inputs, outputs);  // zone 0 patt 4
  roi_pooling<ROWS, COLS, PATTERNS, 0, 5>(inputs, outputs);  // zone 0 patt 5
  roi_pooling<ROWS, COLS, PATTERNS, 0, 6>(inputs, outputs);  // zone 0 patt 6
}

}  // namespace emtf

#endif  // __EMTF_HLSLIB_POOLING_H__ not defined
