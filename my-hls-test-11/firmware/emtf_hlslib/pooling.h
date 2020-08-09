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
  static const unsigned input_shape_h = 1;
  static const unsigned input_shape_w = 1;
  static const unsigned output_shape_h = 1;
  static const unsigned output_shape_w = 1;
};

template <class INPUT_T, class OUTPUT_T, int ROWS, int COLS, class window_t, class pixel_t>
void pooling_kernel(
    const INPUT_T inputs[COLS],
    OUTPUT_T outputs[COLS],
    const window_t windows_low[ROWS],
    const window_t windows_hi[ROWS],
    pixel_t buf[ROWS]
) {
#pragma HLS INLINE

  pooling_row_loop : for (unsigned row = 0; row < ROWS; row++) {

  }


}

// Perform pooling - pool from the (low, hi)-range for each row in the input image.

template <class INPUT_T, class OUTPUT_T, typename CONFIG_T>
void pooling_module(
    const INPUT_T inputs[CONFIG_T::input_shape_w],
    OUTPUT_T outputs[CONFIG_T::output_shape_w]
) {
  // Make sure types are correct
  static_assert(std::is_same<INPUT_T, ap_uint<CONFIG_T::input_shape_h> >::value);
  static_assert(std::is_same<OUTPUT_T, ap_uint<CONFIG_T::output_shape_h> >::value);
  static_assert(CONFIG_T::input_shape_h == CONFIG_T::output_shape_h);  // only supports same image size currently
  static_assert(CONFIG_T::input_shape_w == CONFIG_T::output_shape_w);  // only supports same image size currently

  // Make sure the pattern is valid
  static_assert(CONFIG_T::patt_constants_nrows == 8);  // 8 rows
  static_assert(CONFIG_T::patt_constants_nparams == 3);  // (low, med, hi) in each row
  static_assert(CONFIG_T::patt_constants_len == CONFIG_T::patt_constants_nrows * CONFIG_T::patt_constants_nparams);
  static_assert(get_array_length(CONFIG_T::patt_constants) == CONFIG_T::patt_constants_len);

  // Deduce template arguments
  constexpr int ROWS = CONFIG_T::input_shape_h;
  constexpr int COLS = CONFIG_T::input_shape_w;
  static_assert(CONFIG_T::patt_constants_nrows == ROWS);  // input type should be 8-bit, each bit represents a row.

  // Get the window params (low, med, hi)
  typedef ap_uint<emtf::ceillog2(COLS)> window_t;
  window_t windows_low[ROWS], windows_med[ROWS], windows_hi[ROWS];

  for (unsigned row = 0; row < ROWS; row++) {
    const unsigned low = CONFIG_T::patt_constants[row * 3 + 0];
    const unsigned med = CONFIG_T::patt_constants[row * 3 + 1];
    const unsigned hi = CONFIG_T::patt_constants[row * 3 + 2];
    assert((hi > low) && (hi - low) < CONFIG_T::patt_window_max_size);
    assert((hi > med) && (hi - med) < CONFIG_T::patt_window_max_size);
    assert((med > low) && (med - low) < CONFIG_T::patt_window_max_size);
    std::cout << row << " " << low << " " << med << " " << hi << std::endl;

    windows_low[row] = low;
    windows_med[row] = med;
    windows_hi[row] = hi;
  }

  // Create buffer
  typedef ap_uint<1> pixel_t;  // 1-bit pixel
  pixel_t buf[ROWS];

  // Do work
  pooling_kernel<INPUT_T, OUTPUT_T, ROWS, COLS, window_t, pixel_t>(inputs, outputs, windows_low, windows_hi, buf);
}

}  // namespace emtf

#endif  // __EMTF_HLSLIB_POOLING_H__ not defined
