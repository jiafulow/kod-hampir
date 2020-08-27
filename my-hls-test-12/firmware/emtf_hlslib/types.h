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
  VI_VALID        = 9,
  NUM_VARIABLES   = 10
};

// Bit width
template <int T> struct variable_bw_traits {};
template <> struct variable_bw_traits<VI_EMTF_PHI>    { static const int value = 13; };
template <> struct variable_bw_traits<VI_EMTF_BEND>   { static const int value = 10; };
template <> struct variable_bw_traits<VI_EMTF_THETA1> { static const int value = 8; };
template <> struct variable_bw_traits<VI_EMTF_THETA2> { static const int value = 8; };
template <> struct variable_bw_traits<VI_EMTF_QUAL>   { static const int value = 6; };
template <> struct variable_bw_traits<VI_EMTF_TIME>   { static const int value = 6; };
template <> struct variable_bw_traits<VI_ZONES>       { static const int value = 3; };
template <> struct variable_bw_traits<VI_TIMEZONES>   { static const int value = 3; };
template <> struct variable_bw_traits<VI_BX>          { static const int value = 2; };
template <> struct variable_bw_traits<VI_VALID>       { static const int value = 1; };

// Is signed
template <int T> struct variable_sign_traits {};
template <> struct variable_sign_traits<VI_EMTF_PHI>    { static const bool value = 0; };
template <> struct variable_sign_traits<VI_EMTF_BEND>   { static const bool value = 1; };
template <> struct variable_sign_traits<VI_EMTF_THETA1> { static const bool value = 0; };
template <> struct variable_sign_traits<VI_EMTF_THETA2> { static const bool value = 0; };
template <> struct variable_sign_traits<VI_EMTF_QUAL>   { static const bool value = 1; };
template <> struct variable_sign_traits<VI_EMTF_TIME>   { static const bool value = 1; };
template <> struct variable_sign_traits<VI_ZONES>       { static const bool value = 0; };
template <> struct variable_sign_traits<VI_TIMEZONES>   { static const bool value = 0; };
template <> struct variable_sign_traits<VI_BX>          { static const bool value = 1; };
template <> struct variable_sign_traits<VI_VALID>       { static const bool value = 0; };

// Datatype - ap_int<N> or ap_uint<N>
template <int N, bool S> struct select_ap_int_type {};
template <int N> struct select_ap_int_type<N, true>  { typedef ap_int<N>  type; };  // signed
template <int N> struct select_ap_int_type<N, false> { typedef ap_uint<N> type; };  // unsigned

// Get 'bw' and 'sg', then get the datatype
// For example, enum VI_EMTF_PHI has bw = 13, sign = 0, so the datatype is ap_uint<13>.
template <int T> struct variable_datatype {
  typedef typename select_ap_int_type<
      variable_bw_traits<T>::value, variable_sign_traits<T>::value>::type type;
};

// Typedefs
typedef variable_datatype<VI_EMTF_PHI>::type     emtf_phi_t;
typedef variable_datatype<VI_EMTF_BEND>::type    emtf_bend_t;
typedef variable_datatype<VI_EMTF_THETA1>::type  emtf_theta1_t;
typedef variable_datatype<VI_EMTF_THETA2>::type  emtf_theta2_t;
typedef variable_datatype<VI_EMTF_QUAL>::type    emtf_qual_t;
typedef variable_datatype<VI_EMTF_TIME>::type    emtf_time_t;
typedef variable_datatype<VI_ZONES>::type        zones_t;
typedef variable_datatype<VI_TIMEZONES>::type    timezones_t;
typedef variable_datatype<VI_BX>::type           bx_t;
typedef variable_datatype<VI_VALID>::type        valid_t;

// Model inputs and outputs
enum length_type {
  N_MODEL_INPUT = emtf::num_chambers * emtf::num_segments,
  N_MODEL_OUTPUT = emtf::num_out_tracks * emtf::num_out_variables
};

// Model typedefs

// Count total number of bits.
// Should be equal to 60 bits, but subject to change.
struct count_model_input_bw {
  static const int value = emtf_phi_t::width     + \
                           emtf_bend_t::width    + \
                           emtf_theta1_t::width  + \
                           emtf_theta2_t::width  + \
                           emtf_qual_t::width    + \
                           emtf_time_t::width    + \
                           zones_t::width        + \
                           timezones_t::width    + \
                           bx_t::width           + \
                           valid_t::width;
};

// model_output_t is also subject to change
typedef ap_uint<13>                          model_default_t;
typedef ap_uint<count_model_input_bw::value> model_input_t;
typedef model_default_t                      model_output_t;

}  // namespace emtf

#endif  // __EMTF_HLSLIB_TYPES_H__ not defined
