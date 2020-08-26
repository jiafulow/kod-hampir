#ifndef __MYPROJECT_H__
#define __MYPROJECT_H__

// Xilinx HLS
#include "ap_int.h"
#include "ap_fixed.h"
//#include "hls_stream.h"

// Project definitions
#include "defines.h"

//FIXME
//constexpr int N_TOP_FN_IN = FPGAEvent::LENGTH;
//constexpr int N_TOP_FN_OUT = FPGAResult::LENGTH;

constexpr unsigned int N_TOP_FN_IN = num_emtf_chambers * num_emtf_segments;
constexpr unsigned int N_TOP_FN_OUT = num_emtf_out_tracks * num_emtf_out_variables;

// Top-level function prototype
void myproject(
    const emtf_phi_t   in_emtf_phi[N_TOP_FN_IN],
    const emtf_bend_t  in_emtf_bend[N_TOP_FN_IN],
    const emtf_theta_t in_emtf_theta[N_TOP_FN_IN],
    const emtf_theta_t in_emtf_theta_alt[N_TOP_FN_IN],
    const emtf_qual_t  in_emtf_qual[N_TOP_FN_IN],
    const emtf_time_t  in_emtf_time[N_TOP_FN_IN],
    const zones_t      in_zones[N_TOP_FN_IN],
    const timezones_t  in_timezones[N_TOP_FN_IN],
    const bx_t         in_bx[N_TOP_FN_IN],
    const valid_t      in_valid[N_TOP_FN_IN],
    model_default_t    out[N_TOP_FN_OUT]
);

#endif  // __MYPROJECT_H__ not defined
