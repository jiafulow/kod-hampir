#ifndef __EMTF_HLSLIB_POOLING_H__
#define __EMTF_HLSLIB_POOLING_H__

#include <type_traits>

#include "ap_int.h"


namespace emtf {

struct default_pooling_config {
  static const unsigned patt_constants_len = 24;  // 8 * 3
  static const unsigned patt_constants[patt_constants_len];
  static const unsigned zone = 0;
  static const unsigned patt = 0;
  static const unsigned input_shape_h = 1;
  static const unsigned input_shape_w = 1;
  static const unsigned output_shape_h = 1;
  static const unsigned output_shape_w = 1;
};

template <class INPUT_T, class OUTPUT_T, typename CONFIG_T>
void pooling_module(
    const INPUT_T inputs[CONFIG_T::input_shape_w],
    OUTPUT_T outputs[CONFIG_T::output_shape_w]
) {
  // Make sure types are correct
  static_assert(std::is_same<INPUT_T, ap_uint<CONFIG_T::input_shape_h> >::value);
  static_assert(std::is_same<OUTPUT_T, ap_uint<CONFIG_T::output_shape_h> >::value);

}

}  // namespace emtf

#endif  // __EMTF_HLSLIB_POOLING_H__ not defined
