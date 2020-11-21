#ifndef __EMTF_HLSLIB_TRAITS_H__
#define __EMTF_HLSLIB_TRAITS_H__

// Xilinx HLS
#include "ap_int.h"

namespace emtf {

// Mock implementation of C++ type_traits for use in the HLS project

template <class T, T v>
struct integral_constant { static const T value = v; };

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

template <bool B, class T = void>
struct enable_if {};

template <class T>
struct enable_if<true, T> { typedef T type; };

template <class T, class U>
struct is_same : false_type {};

template <class T>
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
template <class T>
struct make_signed { typedef T type; };

template <int N> struct make_signed<ap_uint<N> > { typedef ap_int<N> type; };

// Make unsigned ap datatype
template <class T>
struct make_unsigned { typedef T type; };

template <int N> struct make_unsigned<ap_int<N> > { typedef ap_uint<N> type; };

// Make wider ap datatype
template <class T>
struct make_wider { typedef T type; };

template <int N> struct make_wider<ap_int<N> > { typedef ap_int<N+1> type; };
template <int N> struct make_wider<ap_uint<N> > { typedef ap_uint<N+1> type; };

// Make narrower ap datatype
template <class T>
struct make_narrower { typedef T type; };

template <int N> struct make_narrower<ap_int<N> > { typedef ap_int<N-1> type; };
template <int N> struct make_narrower<ap_uint<N> > { typedef ap_uint<N-1> type; };

}  // namespace emtf

#endif  // __EMTF_HLSLIB_TRAITS_H__ not defined
