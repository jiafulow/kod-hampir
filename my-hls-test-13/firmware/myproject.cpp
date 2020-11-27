#include "myproject.h"

using namespace emtf;

// Top-level function implementation
void myproject(
    const emtf::model_in_t in0[emtf::N_MODEL_IN],
    emtf::model_out_t out[emtf::N_MODEL_OUT]
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_vld port=in0
#pragma HLS INTERFACE ap_vld port=out
#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS ARRAY_RESHAPE variable=in0 complete dim=0
#pragma HLS ARRAY_PARTITION variable=out complete dim=0

  // Unpack from in0
  emtf_phi_t    emtf_phi    [N_MODEL_IN];
  emtf_bend_t   emtf_bend   [N_MODEL_IN];
  emtf_theta1_t emtf_theta1 [N_MODEL_IN];
  emtf_theta2_t emtf_theta2 [N_MODEL_IN];
  emtf_qual1_t  emtf_qual1  [N_MODEL_IN];
  emtf_qual2_t  emtf_qual2  [N_MODEL_IN];
  emtf_time_t   emtf_time   [N_MODEL_IN];
  seg_zones_t   seg_zones   [N_MODEL_IN];
  seg_tzones_t  seg_tzones  [N_MODEL_IN];
  seg_fr_t      seg_fr      [N_MODEL_IN];
  seg_dl_t      seg_dl      [N_MODEL_IN];
  seg_bx_t      seg_bx      [N_MODEL_IN];
  seg_valid_t   seg_valid   [N_MODEL_IN];

#pragma HLS ARRAY_PARTITION variable=emtf_phi complete dim=0
#pragma HLS ARRAY_PARTITION variable=emtf_bend complete dim=0
#pragma HLS ARRAY_PARTITION variable=emtf_theta1 complete dim=0
#pragma HLS ARRAY_PARTITION variable=emtf_theta2 complete dim=0
#pragma HLS ARRAY_PARTITION variable=emtf_qual1 complete dim=0
#pragma HLS ARRAY_PARTITION variable=emtf_qual2 complete dim=0
#pragma HLS ARRAY_PARTITION variable=emtf_time complete dim=0
#pragma HLS ARRAY_PARTITION variable=seg_zones complete dim=0
#pragma HLS ARRAY_PARTITION variable=seg_tzones complete dim=0
#pragma HLS ARRAY_PARTITION variable=seg_fr complete dim=0
#pragma HLS ARRAY_PARTITION variable=seg_dl complete dim=0
#pragma HLS ARRAY_PARTITION variable=seg_bx complete dim=0
#pragma HLS ARRAY_PARTITION variable=seg_valid complete dim=0

top_fn_loop_in0:

  for (unsigned iseg = 0; iseg < N_MODEL_IN; iseg++) {

#pragma HLS UNROLL

    emtf_phi[iseg]    = in0[iseg].emtf_phi;
    emtf_bend[iseg]   = in0[iseg].emtf_bend;
    emtf_theta1[iseg] = in0[iseg].emtf_theta1;
    emtf_theta2[iseg] = in0[iseg].emtf_theta2;
    emtf_qual1[iseg]  = in0[iseg].emtf_qual1;
    emtf_qual2[iseg]  = in0[iseg].emtf_qual2;
    emtf_time[iseg]   = in0[iseg].emtf_time;
    seg_zones[iseg]   = in0[iseg].seg_zones;
    seg_tzones[iseg]  = in0[iseg].seg_tzones;
    seg_fr[iseg]      = in0[iseg].seg_fr;
    seg_dl[iseg]      = in0[iseg].seg_dl;
    seg_bx[iseg]      = in0[iseg].seg_bx;
    seg_valid[iseg]   = in0[iseg].seg_valid;
  }  // end top_fn_loop_in0

  // This macro is defined in emtf_hlslib/helper.h
  PRINT_TOP_FN_ARRAYS_IN0

  // Intermediate arrays (1)
  zoning_out_t      zoning_0_out      [N_ZONING_OUT];
  zoning_out_t      zoning_1_out      [N_ZONING_OUT];
  zoning_out_t      zoning_2_out      [N_ZONING_OUT];
  pooling_out_t     pooling_0_out     [N_POOLING_OUT];
  pooling_out_t     pooling_1_out     [N_POOLING_OUT];
  pooling_out_t     pooling_2_out     [N_POOLING_OUT];
  suppression_out_t suppression_0_out [N_SUPPRESSION_OUT];
  suppression_out_t suppression_1_out [N_SUPPRESSION_OUT];
  suppression_out_t suppression_2_out [N_SUPPRESSION_OUT];
  zonesorting_out_t zonesorting_0_out [N_ZONESORTING_OUT];
  zonesorting_out_t zonesorting_1_out [N_ZONESORTING_OUT];
  zonesorting_out_t zonesorting_2_out [N_ZONESORTING_OUT];
  zonemerging_out_t zonemerging_0_out [N_ZONEMERGING_OUT];

#pragma HLS ARRAY_PARTITION variable=zoning_0_out complete dim=0
#pragma HLS ARRAY_PARTITION variable=zoning_1_out complete dim=0
#pragma HLS ARRAY_PARTITION variable=zoning_2_out complete dim=0
#pragma HLS ARRAY_PARTITION variable=pooling_0_out complete dim=0
#pragma HLS ARRAY_PARTITION variable=pooling_1_out complete dim=0
#pragma HLS ARRAY_PARTITION variable=pooling_2_out complete dim=0
#pragma HLS ARRAY_PARTITION variable=suppression_0_out complete dim=0
#pragma HLS ARRAY_PARTITION variable=suppression_1_out complete dim=0
#pragma HLS ARRAY_PARTITION variable=suppression_2_out complete dim=0
#pragma HLS ARRAY_PARTITION variable=zonesorting_0_out complete dim=0
#pragma HLS ARRAY_PARTITION variable=zonesorting_1_out complete dim=0
#pragma HLS ARRAY_PARTITION variable=zonesorting_2_out complete dim=0
#pragma HLS ARRAY_PARTITION variable=zonemerging_0_out complete dim=0

  // Unpack from zonemerging_0_out (a.k.a. in1)
  trk_qual_t  trk_qual [N_ZONEMERGING_OUT];
  trk_patt_t  trk_patt [N_ZONEMERGING_OUT];
  trk_col_t   trk_col  [N_ZONEMERGING_OUT];
  trk_zone_t  trk_zone [N_ZONEMERGING_OUT];

#pragma HLS ARRAY_PARTITION variable=trk_qual complete dim=0
#pragma HLS ARRAY_PARTITION variable=trk_patt complete dim=0
#pragma HLS ARRAY_PARTITION variable=trk_col complete dim=0
#pragma HLS ARRAY_PARTITION variable=trk_zone complete dim=0

top_fn_loop_in1:

  for (unsigned itrk = 0; itrk < N_ZONEMERGING_OUT; itrk++) {

#pragma HLS UNROLL

    zonemerging_out_t in1_tmp = zonemerging_0_out[itrk];  // read input
  }  // end top_fn_loop_in1

  // This macro is defined in emtf_hlslib/helper.h
  PRINT_TOP_FN_ARRAYS_IN1

  // Intermediate arrays (2)
  trk_seg_t   trk_seg      [N_TRKBUILDING_OUT * num_emtf_sites];
  trk_feat_t  trk_feat     [N_TRKBUILDING_OUT * num_emtf_features];
  trk_valid_t trk_valid    [N_TRKBUILDING_OUT];
  trk_feat_t  trk_feat_rm  [N_DUPEREMOVAL_OUT * num_emtf_features];
  trk_valid_t trk_valid_rm [N_DUPEREMOVAL_OUT];

#pragma HLS ARRAY_PARTITION variable=trk_seg complete dim=0
#pragma HLS ARRAY_PARTITION variable=trk_feat complete dim=0
#pragma HLS ARRAY_PARTITION variable=trk_valid complete dim=0
#pragma HLS ARRAY_PARTITION variable=trk_feat_rm complete dim=0
#pragma HLS ARRAY_PARTITION variable=trk_valid_rm complete dim=0

top_fn_loop_out:

  for (unsigned i = 0; i < (N_DUPEREMOVAL_OUT * num_emtf_features); i++) {

#pragma HLS UNROLL

    out[i] = trk_feat_rm[i];
  }  // end top_fn_loop_out

  // This macro is defined in emtf_hlslib/helper.h
  PRINT_TOP_FN_ARRAYS_OTHER
}
