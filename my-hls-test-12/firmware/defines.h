#ifndef __DEFINES_H__
#define __DEFINES_H__

// Define data lengths
constexpr int num_emtf_chambers      = 115;
constexpr int num_emtf_segments      = 2;  //FIXME - need to accommodate GEM & ME0
constexpr int num_emtf_variables     = 10;
constexpr int num_emtf_out_tracks    = 4;
constexpr int num_emtf_out_variables = 36;

// Define data widths
constexpr int bw_emtf_phi      = 13;
constexpr int bw_emtf_bend     = 10;
constexpr int bw_emtf_theta    = 8;
constexpr int bw_emtf_qual     = 6;
constexpr int bw_emtf_time     = 6;
constexpr int bw_zones         = 5;
constexpr int bw_timezones     = 5;
constexpr int bw_bx            = 2;
constexpr int bw_valid         = 1;
constexpr int bw_model_default = 13;

// Typedefs
typedef ap_uint<bw_emtf_phi>     emtf_phi_t;
typedef ap_int<bw_emtf_bend>     emtf_bend_t;      // IMPORTANT: signed
typedef ap_uint<bw_emtf_theta>   emtf_theta_t;
typedef ap_int<bw_emtf_qual>     emtf_qual_t;      // IMPORTANT: signed
typedef ap_int<bw_emtf_time>     emtf_time_t;      // IMPORTANT: signed
typedef ap_uint<bw_zones>        zones_t;
typedef ap_uint<bw_timezones>    timezones_t;
typedef ap_int<bw_bx>            bx_t;             // IMPORTANT: signed
typedef ap_uint<bw_valid>        valid_t;
typedef ap_int<bw_model_default> model_default_t;  // IMPORTANT: signed

#endif  // __DEFINES_H__ not defined
