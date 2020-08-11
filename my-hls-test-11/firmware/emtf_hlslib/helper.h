#ifndef __EMTF_HLSLIB_HELPER_H__
#define __EMTF_HLSLIB_HELPER_H__

#include <cassert>
#include <cstdint>
#include <cstdlib>

#ifndef __SYNTHESIS__
#define emtf_assert(expr) (assert(expr))
#else
#define emtf_assert(expr) ((void)(expr))
#endif

#include "helper_from_opencv.h"

#include "helper_from_xfopencv.h"

namespace emtf {

// Get array length
template <typename T, size_t N>
constexpr size_t get_array_length(T const (&arr)[N]) { return N; }

}  // namespace emtf

#endif  // __EMTF_HLSLIB_HELPER_H__ not defined
