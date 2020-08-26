#include "myproject.h"

//#include "emtf_hlslib/all.h"

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
) {
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_vld port=in_emtf_phi
#pragma HLS INTERFACE ap_vld port=in_emtf_bend
#pragma HLS INTERFACE ap_vld port=in_emtf_theta
#pragma HLS INTERFACE ap_vld port=in_emtf_theta_alt
#pragma HLS INTERFACE ap_vld port=in_emtf_qual
#pragma HLS INTERFACE ap_vld port=in_emtf_time
#pragma HLS INTERFACE ap_vld port=in_zones
#pragma HLS INTERFACE ap_vld port=in_timezones
#pragma HLS INTERFACE ap_vld port=in_bx
#pragma HLS INTERFACE ap_vld port=in_valid
#pragma HLS INTERFACE ap_vld port=out

//#pragma HLS ARRAY_PARTITION variable=in_emtf_phi complete dim=0
//#pragma HLS ARRAY_PARTITION variable=in_emtf_bend complete dim=0
//#pragma HLS ARRAY_PARTITION variable=in_emtf_theta complete dim=0
//#pragma HLS ARRAY_PARTITION variable=in_emtf_theta_alt complete dim=0
//#pragma HLS ARRAY_PARTITION variable=in_emtf_qual complete dim=0
//#pragma HLS ARRAY_PARTITION variable=in_emtf_time complete dim=0
//#pragma HLS ARRAY_PARTITION variable=in_zones complete dim=0
//#pragma HLS ARRAY_PARTITION variable=in_timezones complete dim=0
//#pragma HLS ARRAY_PARTITION variable=in_bx complete dim=0
//#pragma HLS ARRAY_PARTITION variable=in_valid complete dim=0
//#pragma HLS ARRAY_PARTITION variable=out complete dim=0

  // Dummy loop - FIXME
  for (unsigned i = 0; i < N_TOP_FN_OUT; i++) {
    out[i] = in_valid[i];
  }

}
