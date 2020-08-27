#include "myproject.h"

// Top-level function implementation
void myproject(
    const emtf::model_input_t in0[N_MODEL_INPUT],
    emtf::model_output_t out[N_MODEL_OUTPUT]
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_vld port=in0
#pragma HLS INTERFACE ap_vld port=out
#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS ARRAY_RESHAPE variable=in0 complete dim=0
#pragma HLS ARRAY_PARTITION variable=out complete dim=0

  // Deserialize from in0
  emtf::emtf_phi_t    emtf_phi[N_MODEL_INPUT];
  emtf::emtf_bend_t   emtf_bend[N_MODEL_INPUT];
  emtf::emtf_theta1_t emtf_theta1[N_MODEL_INPUT];
  emtf::emtf_theta2_t emtf_theta2[N_MODEL_INPUT];
  emtf::emtf_qual_t   emtf_qual[N_MODEL_INPUT];
  emtf::emtf_time_t   emtf_time[N_MODEL_INPUT];
  emtf::zones_t       zones[N_MODEL_INPUT];
  emtf::timezones_t   timezones[N_MODEL_INPUT];
  emtf::bx_t          bx[N_MODEL_INPUT];
  emtf::valid_t       valid[N_MODEL_INPUT];

#pragma HLS ARRAY_PARTITION variable=emtf_phi complete dim=0
#pragma HLS ARRAY_PARTITION variable=emtf_bend complete dim=0
#pragma HLS ARRAY_PARTITION variable=emtf_theta1 complete dim=0
#pragma HLS ARRAY_PARTITION variable=emtf_theta2 complete dim=0
#pragma HLS ARRAY_PARTITION variable=emtf_qual complete dim=0
#pragma HLS ARRAY_PARTITION variable=emtf_time complete dim=0
#pragma HLS ARRAY_PARTITION variable=zones complete dim=0
#pragma HLS ARRAY_PARTITION variable=timezones complete dim=0
#pragma HLS ARRAY_PARTITION variable=bx complete dim=0
#pragma HLS ARRAY_PARTITION variable=valid complete dim=0

  for (unsigned iseg = 0; iseg < N_MODEL_INPUT; iseg++) {
    int i = 0;
    i = emtf::copy_bits_from(in0[iseg], emtf_phi[iseg]   , emtf::emtf_phi_t::width   , i);
    i = emtf::copy_bits_from(in0[iseg], emtf_bend[iseg]  , emtf::emtf_bend_t::width  , i);
    i = emtf::copy_bits_from(in0[iseg], emtf_theta1[iseg], emtf::emtf_theta1_t::width, i);
    i = emtf::copy_bits_from(in0[iseg], emtf_theta2[iseg], emtf::emtf_theta2_t::width, i);
    i = emtf::copy_bits_from(in0[iseg], emtf_qual[iseg]  , emtf::emtf_qual_t::width  , i);
    i = emtf::copy_bits_from(in0[iseg], emtf_time[iseg]  , emtf::emtf_time_t::width  , i);
    i = emtf::copy_bits_from(in0[iseg], zones[iseg]      , emtf::zones_t::width      , i);
    i = emtf::copy_bits_from(in0[iseg], timezones[iseg]  , emtf::timezones_t::width  , i);
    i = emtf::copy_bits_from(in0[iseg], bx[iseg]         , emtf::bx_t::width         , i);
    i = emtf::copy_bits_from(in0[iseg], valid[iseg]      , emtf::valid_t::width      , i);
    emtf_assert(i == emtf::model_input_t::width);
  }



  //FIXME - dummy loop
  for (unsigned i = 0; i < N_MODEL_OUTPUT; i++) {
    out[i] = valid[i];
  }

}
