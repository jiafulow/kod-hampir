#ifndef __MYPROJECT_H__
#define __MYPROJECT_H__

// Xilinx HLS
#include "ap_int.h"
#include "ap_fixed.h"
//#include "hls_stream.h"

// EMTF HLS
#include "emtf_hlslib/all.h"

// Input and output shapes
constexpr unsigned int N_TOP_FN_IN = emtf::num_chambers * emtf::num_segments;
constexpr unsigned int N_TOP_FN_OUT = emtf::num_out_tracks * emtf::num_out_variables;

// Top-level function prototype
void myproject(
    const emtf::emtf_phi_t    in_emtf_phi[N_TOP_FN_IN],
    const emtf::emtf_bend_t   in_emtf_bend[N_TOP_FN_IN],
    const emtf::emtf_theta1_t in_emtf_theta1[N_TOP_FN_IN],
    const emtf::emtf_theta2_t in_emtf_theta2[N_TOP_FN_IN],
    const emtf::emtf_qual_t   in_emtf_qual[N_TOP_FN_IN],
    const emtf::emtf_time_t   in_emtf_time[N_TOP_FN_IN],
    const emtf::zones_t       in_zones[N_TOP_FN_IN],
    const emtf::timezones_t   in_timezones[N_TOP_FN_IN],
    const emtf::bx_t          in_bx[N_TOP_FN_IN],
    const emtf::valid_t       in_valid[N_TOP_FN_IN],
    emtf::model_default_t     out[N_TOP_FN_OUT]
);

#endif  // __MYPROJECT_H__ not defined
