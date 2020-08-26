#include "myproject.h"

// Top-level function implementation
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
) {
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_vld port=in_emtf_phi
#pragma HLS INTERFACE ap_vld port=in_emtf_bend
#pragma HLS INTERFACE ap_vld port=in_emtf_theta1
#pragma HLS INTERFACE ap_vld port=in_emtf_theta2
#pragma HLS INTERFACE ap_vld port=in_emtf_qual
#pragma HLS INTERFACE ap_vld port=in_emtf_time
#pragma HLS INTERFACE ap_vld port=in_zones
#pragma HLS INTERFACE ap_vld port=in_timezones
#pragma HLS INTERFACE ap_vld port=in_bx
#pragma HLS INTERFACE ap_vld port=in_valid
#pragma HLS INTERFACE ap_vld port=out

//#pragma HLS ARRAY_PARTITION variable=in_emtf_phi complete dim=0
//#pragma HLS ARRAY_PARTITION variable=in_emtf_bend complete dim=0
//#pragma HLS ARRAY_PARTITION variable=in_emtf_theta1 complete dim=0
//#pragma HLS ARRAY_PARTITION variable=in_emtf_theta2 complete dim=0
//#pragma HLS ARRAY_PARTITION variable=in_emtf_qual complete dim=0
//#pragma HLS ARRAY_PARTITION variable=in_emtf_time complete dim=0
//#pragma HLS ARRAY_PARTITION variable=in_zones complete dim=0
//#pragma HLS ARRAY_PARTITION variable=in_timezones complete dim=0
//#pragma HLS ARRAY_PARTITION variable=in_bx complete dim=0
//#pragma HLS ARRAY_PARTITION variable=in_valid complete dim=0
//#pragma HLS ARRAY_PARTITION variable=out complete dim=0

  //FIXME - dummy loop
  for (unsigned i = 0; i < N_TOP_FN_OUT; i++) {
    out[i] = in_valid[i];
  }

}
