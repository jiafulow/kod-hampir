#ifndef __EMTF_HLSLIB_TYPES_H__
#define __EMTF_HLSLIB_TYPES_H__

// Xilinx HLS
#include "ap_int.h"
#include "ap_fixed.h"

// EMTF HLS
#include "common.h"

namespace emtf {

// Enums
enum segment_type {
  VI_EMTF_CHAMBER = 0,
  VI_EMTF_SEGMENT = 1
};

enum variable_type {
  VI_EMTF_PHI     = 0,
  VI_EMTF_BEND    = 1,
  VI_EMTF_THETA1  = 2,
  VI_EMTF_THETA2  = 3,
  VI_EMTF_QUAL    = 4,
  VI_EMTF_TIME    = 5,
  VI_FLAGS_ZONE   = 6,
  VI_FLAGS_TZONE  = 7,
  VI_BX           = 8,
  VI_VALID        = 9  // try to keep 'valid' as the last
};

enum track_variable_type {
  VI_TRACK_QUAL   = 0,
  VI_TRACK_PATT   = 1,
  VI_TRACK_COL    = 2,
  VI_TRACK_ZONE   = 3
};

// Bit width
template <int T> struct variable_bw_traits {};
template <> struct variable_bw_traits<VI_EMTF_PHI>    { static const int value = 13; };
template <> struct variable_bw_traits<VI_EMTF_BEND>   { static const int value = 10; };
template <> struct variable_bw_traits<VI_EMTF_THETA1> { static const int value = 8; };
template <> struct variable_bw_traits<VI_EMTF_THETA2> { static const int value = 8; };
template <> struct variable_bw_traits<VI_EMTF_QUAL>   { static const int value = 6; };
template <> struct variable_bw_traits<VI_EMTF_TIME>   { static const int value = 6; };
template <> struct variable_bw_traits<VI_FLAGS_ZONE>  { static const int value = 3; };
template <> struct variable_bw_traits<VI_FLAGS_TZONE> { static const int value = 3; };
template <> struct variable_bw_traits<VI_BX>          { static const int value = 2; };
template <> struct variable_bw_traits<VI_VALID>       { static const int value = 1; };

template <int T> struct track_variable_bw_traits {};
template <> struct track_variable_bw_traits<VI_TRACK_QUAL> { static const int value = 6; };
template <> struct track_variable_bw_traits<VI_TRACK_PATT> { static const int value = 3; };
template <> struct track_variable_bw_traits<VI_TRACK_COL>  { static const int value = 9; };
template <> struct track_variable_bw_traits<VI_TRACK_ZONE> { static const int value = 2; };

// Is signed
template <int T> struct variable_sign_traits {};
template <> struct variable_sign_traits<VI_EMTF_PHI>    { static const bool value = 0; };
template <> struct variable_sign_traits<VI_EMTF_BEND>   { static const bool value = 1; };
template <> struct variable_sign_traits<VI_EMTF_THETA1> { static const bool value = 0; };
template <> struct variable_sign_traits<VI_EMTF_THETA2> { static const bool value = 0; };
template <> struct variable_sign_traits<VI_EMTF_QUAL>   { static const bool value = 1; };
template <> struct variable_sign_traits<VI_EMTF_TIME>   { static const bool value = 1; };
template <> struct variable_sign_traits<VI_FLAGS_ZONE>  { static const bool value = 0; };
template <> struct variable_sign_traits<VI_FLAGS_TZONE> { static const bool value = 0; };
template <> struct variable_sign_traits<VI_BX>          { static const bool value = 1; };
template <> struct variable_sign_traits<VI_VALID>       { static const bool value = 0; };

template <int T> struct track_variable_sign_traits {};
template <> struct track_variable_sign_traits<VI_TRACK_QUAL> { static const bool value = 0; };
template <> struct track_variable_sign_traits<VI_TRACK_PATT> { static const bool value = 0; };
template <> struct track_variable_sign_traits<VI_TRACK_COL>  { static const bool value = 0; };
template <> struct track_variable_sign_traits<VI_TRACK_ZONE> { static const bool value = 0; };


// _____________________________________________________________________________
// Import stuff from <type_traits>
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

template <int N> struct is_ap_int_type<ap_int<N> > : true_type {};   // toggle to true
template <int N> struct is_ap_int_type<ap_uint<N> > : true_type {};  // toggle to true

// Select ap datatype - ap_int<N> or ap_uint<N>
template <int N, bool S>
struct select_ap_int_type {};

template <int N> struct select_ap_int_type<N, true> { typedef ap_int<N> type; };    // signed
template <int N> struct select_ap_int_type<N, false> { typedef ap_uint<N> type; };  // unsigned


// _____________________________________________________________________________
// Get bw and sign, then find the ap datatype
// For example, enum VI_EMTF_PHI has bw = 13, sign = 0, so the datatype is ap_uint<13>.
template <int T> struct find_variable_datatype {
  typedef typename select_ap_int_type<
      variable_bw_traits<T>::value, variable_sign_traits<T>::value>::type type;
};

template <int T> struct find_track_variable_datatype {
  typedef typename select_ap_int_type<
      track_variable_bw_traits<T>::value, track_variable_sign_traits<T>::value>::type type;
};

// Find the range of bits when the variables are serialized
template <int T>
struct find_variable_range_of_bits {
  static const int begin = find_variable_range_of_bits<T - 1>::end;
  static const int end = begin + variable_bw_traits<T>::value;
};

template <>
struct find_variable_range_of_bits<0> {  // specialize when T=0
  static const int begin = 0;
  static const int end = begin + variable_bw_traits<0>::value;
};

template <int T>
struct find_track_variable_range_of_bits {
  static const int begin = find_track_variable_range_of_bits<T - 1>::end;
  static const int end = begin + track_variable_bw_traits<T>::value;
};

template <>
struct find_track_variable_range_of_bits<0> {  // specialize when T=0
  static const int begin = 0;
  static const int end = begin + track_variable_bw_traits<0>::value;
};

// Translate enums into nicer names by using text replacement macros ("token pasting")
// For example, take enum VI_EMTF_PHI and define emtf_phi_t, emtf_phi_bits_lo, emtf_phi_bits_hi:
//     typedef find_variable_datatype<VI_EMTF_PHI>::type emtf_phi_t;
//     constexpr int emtf_phi_bits_lo = find_variable_range_of_bits<VI_EMTF_PHI>::begin;
//     constexpr int emtf_phi_bits_hi = find_variable_range_of_bits<VI_EMTF_PHI>::end - 1;
#define DEFINE_NICE_NAMES(T, NAME) \
    typedef find_variable_datatype<T>::type NAME##_t; \
    constexpr int NAME##_bits_lo = find_variable_range_of_bits<T>::begin; \
    constexpr int NAME##_bits_hi = find_variable_range_of_bits<T>::end - 1;

DEFINE_NICE_NAMES(VI_EMTF_PHI, emtf_phi)
DEFINE_NICE_NAMES(VI_EMTF_BEND, emtf_bend)
DEFINE_NICE_NAMES(VI_EMTF_THETA1, emtf_theta1)
DEFINE_NICE_NAMES(VI_EMTF_THETA2, emtf_theta2)
DEFINE_NICE_NAMES(VI_EMTF_QUAL, emtf_qual)
DEFINE_NICE_NAMES(VI_EMTF_TIME, emtf_time)
DEFINE_NICE_NAMES(VI_FLAGS_ZONE, flags_zone)
DEFINE_NICE_NAMES(VI_FLAGS_TZONE, flags_tzone)
DEFINE_NICE_NAMES(VI_BX, bx)
DEFINE_NICE_NAMES(VI_VALID, valid)
#undef DEFINE_NICE_NAMES

#define DEFINE_NICE_NAMES_TRACK(T, NAME) \
    typedef find_track_variable_datatype<T>::type NAME##_t; \
    constexpr int NAME##_bits_lo = find_track_variable_range_of_bits<T>::begin; \
    constexpr int NAME##_bits_hi = find_track_variable_range_of_bits<T>::end - 1;

DEFINE_NICE_NAMES_TRACK(VI_TRACK_QUAL, track_qual)
DEFINE_NICE_NAMES_TRACK(VI_TRACK_PATT, track_patt)
DEFINE_NICE_NAMES_TRACK(VI_TRACK_COL,  track_col)
DEFINE_NICE_NAMES_TRACK(VI_TRACK_ZONE, track_zone)
#undef DEFINE_NICE_NAMES_TRACK


// _____________________________________________________________________________
// Model input and output lengths
enum model_length_type {
  N_MODEL_IN = num_chambers * num_segments,
  N_MODEL_OUT = num_tracks * num_features
};

// Bit width of model_in_t is the sum of the bit widths
struct model_in_bw_traits {
  static const int value = find_variable_range_of_bits<VI_VALID>::end;  // 'valid' should be the last variable
};

// Bit width of model_out_t is arbitrary for now
struct model_out_bw_traits {
  static const int value = variable_bw_traits<VI_EMTF_PHI>::value;
};

// Model input and output datatypes
typedef ap_uint<model_in_bw_traits::value> model_in_t;
typedef ap_int<model_out_bw_traits::value> model_out_t;

// Layer output lengths
enum layer_length_type {
  N_ZONING_OUT = num_img_rows,
  N_POOLING_OUT = num_img_cols,
  N_ZONESORTING_OUT = num_tracks,
  // Synonyms
  N_POOLING_IN = N_ZONING_OUT,
  N_SUPPRESSION_IN = N_POOLING_OUT,
  N_SUPPRESSION_OUT = N_SUPPRESSION_IN,
  N_ZONESORTING_IN = N_SUPPRESSION_OUT,
  N_ZONEMERGING_IN = N_ZONESORTING_OUT,
  N_ZONEMERGING_OUT = N_ZONEMERGING_IN,
  N_TRKBUILDING_IN = N_ZONEMERGING_OUT,
  N_TRKBUILDING_OUT = N_MODEL_OUT
};

// Layer typedefs
typedef ap_uint<11>           zoning_seg_t;             // bw: ceil(log2(num_chambers * 10))
typedef ap_uint<9>            zoning_col_t;             // bw: ceil(log2(80/coarse_emtf_strip))
typedef ap_uint<num_img_cols> zoning_out_t;             // bw: num_img_cols
typedef ap_uint<num_img_rows> pooling_preactivation_t;  // bw: num_img_rows
typedef ap_uint<6>            pooling_activation_t;     // bw: preactivation bw - 2
typedef ap_uint<3>            pooling_patt_t;           // bw: ceil(log2(num_patterns))
typedef ap_uint<9>            pooling_col_t;            // bw: ceil(log2(num_img_cols))
typedef ap_uint<2>            pooling_zone_t;           // bw: ceil(log2(num_zones))
typedef ap_uint<6+3>          pooling_out_t;            // bw: activation bw + patt bw
typedef ap_uint<6+3+9>        zonesorting_out_t;        // bw: activation bw + patt bw + col bw
typedef ap_uint<6+3+9+2>      zonemerging_out_t;        // bw: activation bw + patt bw + col bw + zone bw
// Synonyms
typedef zoning_out_t          pooling_in_t;
typedef pooling_out_t         suppression_in_t;
typedef suppression_in_t      suppression_out_t;
typedef suppression_out_t     zonesorting_in_t;
typedef zonesorting_out_t     zonemerging_in_t;
typedef model_out_t           trkbuilding_out_t;


// _____________________________________________________________________________
// Misc definitions
constexpr static const int pooling_reuse_factor = 4;  //FIXME - not yet implemented
constexpr static const int pooling_fusion_factor = 8; //FIXME - not yet implemented

}  // namespace emtf

// The following are frequently used, so get rid of namespace
using emtf::N_MODEL_IN;
using emtf::N_MODEL_OUT;
using emtf::N_ZONING_OUT;
using emtf::N_POOLING_IN;
using emtf::N_POOLING_OUT;
using emtf::N_SUPPRESSION_IN;
using emtf::N_SUPPRESSION_OUT;
using emtf::N_ZONESORTING_IN;
using emtf::N_ZONESORTING_OUT;
using emtf::N_ZONEMERGING_IN;
using emtf::N_ZONEMERGING_OUT;
using emtf::N_TRKBUILDING_IN;
using emtf::N_TRKBUILDING_OUT;


#endif  // __EMTF_HLSLIB_TYPES_H__ not defined
