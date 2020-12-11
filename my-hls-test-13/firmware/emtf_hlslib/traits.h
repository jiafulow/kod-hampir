#ifndef __EMTF_HLSLIB_TRAITS_H__
#define __EMTF_HLSLIB_TRAITS_H__

// Xilinx HLS
#include "ap_int.h"

namespace emtf {

// _____________________________________________________________________________
// Mock implementation of C++ type_traits for use in the HLS project

template <typename T, T v>
struct integral_constant { static const T value = v; };

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

template <bool B, typename T = void>
struct enable_if {};

template <typename T>
struct enable_if<true, T> { typedef T type; };

template <typename T, typename U>
struct is_same : false_type {};

template <typename T>
struct is_same<T, T> : true_type {};

// Check for ap datatype
template <typename T>
struct is_ap_int_type : false_type {};

template <int N> struct is_ap_int_type<ap_int<N> > : true_type {};  // toggle to true
template <int N> struct is_ap_int_type<ap_uint<N> > : true_type {};

// Make ap datatype - ap_int<N> or ap_uint<N>
template <int N, bool S>
struct make_ap_int_type { typedef ap_int<N> type; };  // signed

template <int N> struct make_ap_int_type<N, false> { typedef ap_uint<N> type; };  // unsigned

// Make signed ap datatype
template <typename T>
struct make_signed { typedef T type; };

template <int N> struct make_signed<ap_uint<N> > { typedef ap_int<N> type; };

// Make unsigned ap datatype
template <typename T>
struct make_unsigned { typedef T type; };

template <int N> struct make_unsigned<ap_int<N> > { typedef ap_uint<N> type; };

// Make wider ap datatype
template <typename T>
struct make_wider { typedef T type; };

template <int N> struct make_wider<ap_int<N> > { typedef ap_int<N+1> type; };
template <int N> struct make_wider<ap_uint<N> > { typedef ap_uint<N+1> type; };

// Make narrower ap datatype
template <typename T>
struct make_narrower { typedef T type; };

template <int N> struct make_narrower<ap_int<N> > { typedef ap_int<N-1> type; };
template <int N> struct make_narrower<ap_uint<N> > { typedef ap_uint<N-1> type; };

// Make concatenated ap datatype
template <typename T, typename U>
struct make_concat {};

template <int M, int N> struct make_concat<ap_int<M>, ap_int<N> > { typedef ap_int<M+N> type; };
template <int M, int N> struct make_concat<ap_uint<M>, ap_uint<N> > { typedef ap_uint<M+N> type; };

// Find max allowed value (for ap_uint<N>)
template <typename T>
struct find_ap_int_max_allowed {};

template <int N> struct find_ap_int_max_allowed<ap_uint<N> > { static const int value = (1 << N) - 1; };

// _____________________________________________________________________________
// Mock implementation of C++ iterator functions for use in the HLS project

// Iterator traits
template <typename Iterator>
struct iterator_traits {
  typedef typename Iterator::value_type      value_type;
  typedef typename Iterator::difference_type difference_type;
};

// Partial specialization for pointer types
template <typename T>
struct iterator_traits<T*> {
  typedef T   value_type;
  typedef int difference_type;
};

// Partial specialization for const pointer types
template <typename T>
struct iterator_traits<const T*> {
  typedef T   value_type;
  typedef int difference_type;
};

template <typename T>
using iter_value_t = typename iterator_traits<T>::value_type;

template <typename T>
using iter_difference_t = typename iterator_traits<T>::difference_type;

// Range access
template <typename T, unsigned int N>
T* stl_begin(T (&arr)[N]) {

#pragma HLS INLINE

  return arr;
}

template <typename T, unsigned int N>
T* stl_end(T (&arr)[N]) {

#pragma HLS INLINE

  return arr + N;
}

// Increment or decrement
template <typename RandomAccessIt>
RandomAccessIt stl_next(RandomAccessIt it, iter_difference_t<RandomAccessIt> n) {

#pragma HLS INLINE

  it += n;
  return it;
}

template <typename RandomAccessIt>
RandomAccessIt stl_prev(RandomAccessIt it, iter_difference_t<RandomAccessIt> n) {

#pragma HLS INLINE

  it -= n;
  return it;
}

template <typename RandomAccessIt>
iter_difference_t<RandomAccessIt> stl_distance(RandomAccessIt first, RandomAccessIt last) {

#pragma HLS INLINE

  return last - first;
}

}  // namespace emtf

#endif  // __EMTF_HLSLIB_TRAITS_H__ not defined
