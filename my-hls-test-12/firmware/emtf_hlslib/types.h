#ifndef __EMTF_HLSLIB_TYPES_H__
#define __EMTF_HLSLIB_TYPES_H__

// Xilinx HLS
#include "ap_int.h"
#include "ap_fixed.h"

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
  VI_ZONES        = 6,
  VI_TIMEZONES    = 7,
  VI_BX           = 8,
  VI_VALID        = 9
};

// Bit width
template <int T> struct variable_bw_traits {};
template <> struct variable_bw_traits<VI_EMTF_PHI>    { static const int bw = 13; };
template <> struct variable_bw_traits<VI_EMTF_BEND>   { static const int bw = 10; };
template <> struct variable_bw_traits<VI_EMTF_THETA1> { static const int bw = 8; };
template <> struct variable_bw_traits<VI_EMTF_THETA2> { static const int bw = 8; };
template <> struct variable_bw_traits<VI_EMTF_QUAL>   { static const int bw = 6; };
template <> struct variable_bw_traits<VI_EMTF_TIME>   { static const int bw = 6; };
template <> struct variable_bw_traits<VI_ZONES>       { static const int bw = 3; };
template <> struct variable_bw_traits<VI_TIMEZONES>   { static const int bw = 3; };
template <> struct variable_bw_traits<VI_BX>          { static const int bw = 2; };
template <> struct variable_bw_traits<VI_VALID>       { static const int bw = 1; };

// Is signed
template <int T> struct variable_sg_traits {};
template <> struct variable_sg_traits<VI_EMTF_PHI>    { static const bool sg = 0; };
template <> struct variable_sg_traits<VI_EMTF_BEND>   { static const bool sg = 1; };
template <> struct variable_sg_traits<VI_EMTF_THETA1> { static const bool sg = 0; };
template <> struct variable_sg_traits<VI_EMTF_THETA2> { static const bool sg = 0; };
template <> struct variable_sg_traits<VI_EMTF_QUAL>   { static const bool sg = 1; };
template <> struct variable_sg_traits<VI_EMTF_TIME>   { static const bool sg = 1; };
template <> struct variable_sg_traits<VI_ZONES>       { static const bool sg = 0; };
template <> struct variable_sg_traits<VI_TIMEZONES>   { static const bool sg = 0; };
template <> struct variable_sg_traits<VI_BX>          { static const bool sg = 1; };
template <> struct variable_sg_traits<VI_VALID>       { static const bool sg = 0; };

// Datatype - ap_int<N> or ap_uint<N>
template <int N, bool S> struct select_ap_int_type {};
template <int N> struct select_ap_int_type<N, true>  { typedef ap_int<N>  datatype; };  // signed
template <int N> struct select_ap_int_type<N, false> { typedef ap_uint<N> datatype; };  // unsigned

// Get 'bw' and 'sg', then get the datatype
// For example, enum VI_EMTF_PHI has bw = 13, sg = 0, so the datatype is ap_uint<13>.
template <int T> struct variable_datatype {
  typedef typename select_ap_int_type<
      variable_bw_traits<T>::bw, variable_sg_traits<T>::sg>::datatype datatype;
};

// Typedefs
typedef variable_datatype<VI_EMTF_PHI>::datatype     emtf_phi_t;
typedef variable_datatype<VI_EMTF_BEND>::datatype    emtf_bend_t;
typedef variable_datatype<VI_EMTF_THETA1>::datatype  emtf_theta1_t;
typedef variable_datatype<VI_EMTF_THETA2>::datatype  emtf_theta2_t;
typedef variable_datatype<VI_EMTF_QUAL>::datatype    emtf_qual_t;
typedef variable_datatype<VI_EMTF_TIME>::datatype    emtf_time_t;
typedef variable_datatype<VI_ZONES>::datatype        zones_t;
typedef variable_datatype<VI_TIMEZONES>::datatype    timezones_t;
typedef variable_datatype<VI_BX>::datatype           bx_t;
typedef variable_datatype<VI_VALID>::datatype        valid_t;

// Additional typedefs
typedef ap_int<13> model_default_t;

}  // namespace emtf

#endif  // __EMTF_HLSLIB_TYPES_H__ not defined
