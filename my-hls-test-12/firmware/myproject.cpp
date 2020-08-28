#include "myproject.h"

// Top-level function implementation
void myproject(
    const emtf::model_in_t in0[N_MODEL_IN],
    emtf::model_out_t out[N_MODEL_OUT]
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_vld port=in0
#pragma HLS INTERFACE ap_vld port=out
#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS ARRAY_RESHAPE variable=in0 complete dim=0
#pragma HLS ARRAY_PARTITION variable=out complete dim=0

  // Deserialize from in0
  emtf::emtf_phi_t    emtf_phi[N_MODEL_IN];
  emtf::emtf_bend_t   emtf_bend[N_MODEL_IN];
  emtf::emtf_theta1_t emtf_theta1[N_MODEL_IN];
  emtf::emtf_theta2_t emtf_theta2[N_MODEL_IN];
  emtf::emtf_qual_t   emtf_qual[N_MODEL_IN];
  emtf::emtf_time_t   emtf_time[N_MODEL_IN];
  emtf::zones_t       zones[N_MODEL_IN];
  emtf::timezones_t   timezones[N_MODEL_IN];
  emtf::bx_t          bx[N_MODEL_IN];
  emtf::valid_t       valid[N_MODEL_IN];

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

  emtf::model_in_t in0_tmp = 0;

  for (unsigned iseg = 0; iseg < N_MODEL_IN; iseg++) {
    in0_tmp = in0[iseg];  // read input

    emtf_phi[iseg]    = in0_tmp.range(emtf::emtf_phi_bits_hi   , emtf::emtf_phi_bits_lo);
    emtf_bend[iseg]   = in0_tmp.range(emtf::emtf_bend_bits_hi  , emtf::emtf_bend_bits_lo);
    emtf_theta1[iseg] = in0_tmp.range(emtf::emtf_theta1_bits_hi, emtf::emtf_theta1_bits_lo);
    emtf_theta2[iseg] = in0_tmp.range(emtf::emtf_theta2_bits_hi, emtf::emtf_theta2_bits_lo);
    emtf_qual[iseg]   = in0_tmp.range(emtf::emtf_qual_bits_hi  , emtf::emtf_qual_bits_lo);
    emtf_time[iseg]   = in0_tmp.range(emtf::emtf_time_bits_hi  , emtf::emtf_time_bits_lo);
    zones[iseg]       = in0_tmp.range(emtf::zones_bits_hi      , emtf::zones_bits_lo);
    timezones[iseg]   = in0_tmp.range(emtf::timezones_bits_hi  , emtf::timezones_bits_lo);
    bx[iseg]          = in0_tmp.range(emtf::bx_bits_hi         , emtf::bx_bits_lo);
    valid[iseg]       = in0_tmp.range(emtf::valid_bits_hi      , emtf::valid_bits_lo);
  }

  // This is a macro defined in emtf_hlslib/helper.h. To be removed in the final version.
  PRINT_TOP_FN_ARRAYS

  // Layer 1 - zoning
  emtf::zoning_out_t zoning_out[N_ZONING_OUT];
#pragma HLS ARRAY_PARTITION variable=zoning_out complete dim=0

  emtf::zoning_layer<0>(emtf_phi, zones, timezones, valid, zoning_out);

  // Layer 2 - pooling
  emtf::pooling_out_t pooling_out[N_POOLING_OUT];
#pragma HLS ARRAY_PARTITION variable=pooling_out complete dim=0

  emtf::pooling_layer<0>(zoning_out, pooling_out);





  //FIXME - dummy loop
  for (unsigned i = 0; i < N_MODEL_OUT; i++) {
    out[i] = valid[i];
  }

}
