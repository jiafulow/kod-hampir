#ifndef __EMTF_HLSLIB_POOLING_H__
#define __EMTF_HLSLIB_POOLING_H__

#include <type_traits>

#include "ap_int.h"


namespace emtf {

// Configuration

struct default_pooling_config {
  static const unsigned patt_constants_nrows = 8;
  static const unsigned patt_constants_nparams = 3;  // per row
  static const unsigned patt_constants_len = patt_constants_nrows * patt_constants_nparams;
  static const unsigned patt_constants[patt_constants_len];
  static const unsigned patt_window_max_size = 40;  // 10.667 deg
  static const unsigned patt_window_col_offset = 55;  // (111-1)/2 = 55
  static const unsigned zone = 0;
  static const unsigned patt = 0;
};

template <class INPUT_T, class OUTPUT_T, int ROWS, int COLS, int WIN_SIZE, class window_t, class pixel_t>
void pooling_kernel(
    const INPUT_T inputs[COLS],
    OUTPUT_T outputs[COLS],
    const window_t windows_low[ROWS],
    const window_t windows_hi[ROWS],
    const window_t window_col_offset,
    pixel_t buf[ROWS]
) {
#pragma HLS INLINE

  const unsigned col_offset = window_col_offset;

  pooling_col_loop : for (unsigned col = 0; col < COLS; col++) {
    pooling_row_loop : for (unsigned row = 0; row < ROWS; row++) {
      unsigned start = col + windows_low[row];
      unsigned stop = col + windows_hi[row] + 1;
      start = (start < window_col_offset) ? 0 : (start - col_offset);
      stop = (stop < window_col_offset) ? 0 : (stop - col_offset);
      stop = (stop < COLS) ? stop : COLS;

      pixel_t result = 0;

      pooling_win_loop : for (; start != stop; start++) {
#pragma HLS LOOP_TRIPCOUNT min=WIN_SIZE max=WIN_SIZE
#pragma HLS PIPELINE II=1
        buf[row] = inputs[start][(ROWS - 1) - row];  // XXX bit order from the test bench is flipped
        result = (result | buf[row]);  // or_reduce
      }  // end of pooling_win_loop

      outputs[col][(ROWS - 1) - row] = result;  // XXX bit order from the test bench is flipped
    }  // end of pooling_row_loop
  }  // end of pooling_col_loop
}

// Perform pooling - pool from the (low, hi)-range for each row in the input image.

template <class INPUT_T, class OUTPUT_T, typename CONFIG_T>
void pooling_module(
    const INPUT_T inputs[N_TOP_FN_IN],
    OUTPUT_T outputs[N_TOP_FN_OUT]
) {
  // Make sure types are correct
  static_assert(INPUT_T::width == OUTPUT_T::width, "inputs and outputs must have the same data width");
  static_assert(N_TOP_FN_IN == N_TOP_FN_OUT, "inputs and outputs must have the same array size");

  // Make sure the pattern is valid
  static_assert(CONFIG_T::patt_constants_nrows == 8, "pattern has invalid num of rows");  // 8 rows
  static_assert(CONFIG_T::patt_constants_nparams == 3, "pattern has invalid num of params");  // (low, med, hi) in each row
  static_assert(CONFIG_T::patt_constants_len == CONFIG_T::patt_constants_nrows * CONFIG_T::patt_constants_nparams, "pattern has invalid array size");
  static_assert(get_array_length(CONFIG_T::patt_constants) == CONFIG_T::patt_constants_len, "pattern has invalid array size");
  static_assert(CONFIG_T::patt_constants_nrows == INPUT_T::width, "pattern num of rows different from input data width");

  // Deduce template arguments
  constexpr int ROWS = INPUT_T::width;
  constexpr int COLS = N_TOP_FN_IN;
  constexpr int WIN_SIZE = CONFIG_T::patt_window_max_size;

  // Get the window params (low, med, hi)
  typedef ap_uint<emtf::ceillog2(COLS)> window_t;
  window_t windows_low[ROWS], windows_med[ROWS], windows_hi[ROWS];
  const window_t window_col_offset = CONFIG_T::patt_window_col_offset;

  for (unsigned row = 0; row < ROWS; row++) {
    const unsigned low = CONFIG_T::patt_constants[row * 3 + 0];
    const unsigned med = CONFIG_T::patt_constants[row * 3 + 1];
    const unsigned hi = CONFIG_T::patt_constants[row * 3 + 2];
    emtf_assert((hi > low) && (hi - low) < CONFIG_T::patt_window_max_size);
    emtf_assert((hi > med) && (hi - med) < CONFIG_T::patt_window_max_size);
    emtf_assert((med > low) && (med - low) < CONFIG_T::patt_window_max_size);
    //std::cout << row << " " << low << " " << med << " " << hi << std::endl;

    windows_low[row] = low;
    windows_med[row] = med;
    windows_hi[row] = hi;
  }

  // Create buffer
  typedef ap_uint<1> pixel_t;  // 1-bit pixel
  pixel_t buf[ROWS];

  // Do work
  pooling_kernel<INPUT_T, OUTPUT_T, ROWS, COLS, WIN_SIZE, window_t, pixel_t>(inputs, outputs, windows_low, windows_hi, window_col_offset, buf);
}

}  // namespace emtf

#endif  // __EMTF_HLSLIB_POOLING_H__ not defined
