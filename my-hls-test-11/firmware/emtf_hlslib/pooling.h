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

// Get the window params (low, center, high) of the specified row from the pattern.

template <typename CONFIG_T>
int_triple get_window_params(unsigned row) {
  assert(row < CONFIG_T::patt_constants_nrows);
  unsigned index0 = row * CONFIG_T::patt_constants_nparams + 0;
  unsigned index1 = row * CONFIG_T::patt_constants_nparams + 1;
  unsigned index2 = row * CONFIG_T::patt_constants_nparams + 2;
  int_triple params(
      CONFIG_T::patt_constants[index0],
      CONFIG_T::patt_constants[index1],
      CONFIG_T::patt_constants[index2]
  );
  return params;
}

// Perform pooling - pool from the (low, high)-range for each row in the input image.

template <class INPUT_T, class OUTPUT_T, typename CONFIG_T>
void pooling_module(
    const INPUT_T inputs[CONFIG_T::input_shape_w],
    OUTPUT_T outputs[CONFIG_T::output_shape_w]
) {
  // Make sure types are correct
  static_assert(std::is_same<INPUT_T, ap_uint<CONFIG_T::input_shape_h> >::value);
  static_assert(std::is_same<OUTPUT_T, ap_uint<CONFIG_T::output_shape_h> >::value);

  // Make sure the pattern is valid
  static_assert(CONFIG_T::patt_constants_nparams == 3);
  static_assert(CONFIG_T::patt_constants_len == CONFIG_T::patt_constants_nrows * CONFIG_T::patt_constants_nparams);
  static_assert(get_array_length(CONFIG_T::patt_constants) == CONFIG_T::patt_constants_len);

  for (unsigned row = 0; row < CONFIG_T::input_shape_h; row++) {
    int_triple window_params = get_window_params<CONFIG_T>(row);
    unsigned window_size = window_params.third - window_params.first + 1;
    std::cout << row << " " << window_params.first << " " << window_params.second << " " << window_params.third << std::endl;
    assert(0 < window_size && window_size < CONFIG_T::patt_window_max_size);
  }

}

}  // namespace emtf

#endif  // __EMTF_HLSLIB_POOLING_H__ not defined
