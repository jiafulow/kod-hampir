#ifndef __EMTF_HLSLIB_HELPER_H__
#define __EMTF_HLSLIB_HELPER_H__

#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <type_traits>

#ifndef __SYNTHESIS__
#define emtf_assert(expr) (assert(expr))
#else
#define emtf_assert(expr) ((void)(expr))
#endif

namespace emtf {

// Check for ap datatype
template <typename T>
struct is_ap_int_type : std::false_type {};
template <int N>
struct is_ap_int_type<ap_int<N> > : std::true_type {};
template <int N>
struct is_ap_int_type<ap_uint<N> > : std::true_type {};

// A helper function for use in the serialize function.
// It copies N bits from src into dst. The starting bit position for src is 0, and
// the starting bit position for dst is 'i'.
template <typename T1, typename T2>
int copy_bits(T1& dst, const T2& src, int N, int i) {
  static_assert(is_ap_int_type<T1>::value, "input must be ap datatype");
  static_assert(is_ap_int_type<T2>::value, "input must be ap datatype");
  for (int j = 0; j < N; i++, j++) {
    dst[i] = src[j];
  }
  return i;
}

// A helper function for use in the deserialize function.
// It copies N bits from src into dst. Note that it differs from the previous function
// as 'src' is the first argument and 'dst' is the second argument here. The starting
// bit position for src is 'i', and the starting bit position for src in 0.
template <typename T1, typename T2>
int copy_bits_from(const T1& src, T2& dst, int N, int i) {
  static_assert(is_ap_int_type<T1>::value, "input must be ap datatype");
  static_assert(is_ap_int_type<T2>::value, "input must be ap datatype");
  for (int j = 0; j < N; i++, j++) {
    dst[j] = src[i];
  }
  return i;
}

}  // namespace emtf

#endif  // __EMTF_HLSLIB_HELPER_H__ not defined
