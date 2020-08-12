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
  static const int win_size;  // max pattern window size - need to be initialized before use
};

// Hardcoded pattern definitions
template <>
const int Pattern<0, 3>::data[size] =  {
  51, 55, 59, 51, 55, 59, 52, 55, 58, 54, 55, 56, 54, 55, 56, 54, 55, 56,
  54, 55, 56, 54, 55, 56
};

template <>
const int Pattern<0, 3>::win_size = 9;

typedef Pattern<0, 3> pattern_z0p3;


// _________________________________________________________________________________________________
// Perform ROI pooling - pool from the (low, hi)-range of each row in the input image.

template <int ROWS, int COLS>
void roi_pooling(
    const ap_uint<ROWS> inputs[COLS],
    ap_uint<ROWS> outputs[COLS]
) {
#pragma HLS INLINE

  constexpr int cols = COLS;
  constexpr int rows = ROWS;
  constexpr int win_size = pattern_z0p3::win_size;
  constexpr int padding = (win_size / 2);  // win_size: 3,4,5,6,7,... -> padding: 1,2,2,3,3,...
  constexpr int cols_w_padding = cols + (padding * 2);  // add padding on both sides

  // Create local buffer
  ap_uint<cols_w_padding> buf[ROWS];
#pragma HLS ARRAY_PARTITION variable=buf complete dim=0

  // Initialize buffer
  buf_init_loop : for (int row = 0; row < rows; row++) {
#pragma HLS PIPELINE II=1

    buf_init_loop_inner : for (int ip_col = 0; ip_col < cols_w_padding; ip_col++) {
      int col = (ip_col - padding);
      if (0 <= col && col < cols) {
        buf[row][ip_col] = inputs[col][(rows - 1) - row];  // CUIDADO: bit order from the test bench is flipped
      } else {
        buf[row][ip_col] = 0;
      }
    }
  }

  // Do pooling
  pool_loop : for (int row = 0; row < rows; row++) {
#pragma HLS PIPELINE II=1

    const int offset = pattern_z0p3::col_offset;
    const int low = pattern_z0p3::data[row * 3 + 0];
    const int high = pattern_z0p3::data[row * 3 + 2];

    pool_loop_inner : for (int col = 0; col < cols; col++) {
      int ip_col = (col + padding);
      int start = ip_col + (low - offset);
      int stop = ip_col + (high - offset);
      outputs[col][(rows - 1) - row] = buf[row](stop, start);  // CUIDADO: bit order from the test bench is flipped
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
  static_assert(N_TOP_FN_IN == N_TOP_FN_OUT, "inputs and outputs must have the same array size");

  // Deduce template arguments
  constexpr int ROWS = INPUT_T::width;
  constexpr int COLS = N_TOP_FN_IN;

  // Do pooling
  roi_pooling<ROWS, COLS>(inputs, outputs);
}

}  // namespace emtf

#endif  // __EMTF_HLSLIB_POOLING_H__ not defined
