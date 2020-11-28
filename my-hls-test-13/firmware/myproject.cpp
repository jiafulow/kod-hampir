#include "myproject.h"

using namespace emtf;

// Top-level function implementation
void myproject(
    const emtf::model_in_t in0[emtf::model_config::n_in],
    emtf::model_out_t out[emtf::model_config::n_out]
) {

#pragma HLS PIPELINE II=model_config::target_ii

#pragma HLS INTERFACE ap_vld port=in0
#pragma HLS INTERFACE ap_vld port=out
#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS ARRAY_RESHAPE variable=in0 complete dim=0
#pragma HLS ARRAY_PARTITION variable=out complete dim=0

  // Unpack from in0
  emtf_phi_t    emtf_phi    [model_config::n_in];
  emtf_bend_t   emtf_bend   [model_config::n_in];
  emtf_theta1_t emtf_theta1 [model_config::n_in];
  emtf_theta2_t emtf_theta2 [model_config::n_in];
  emtf_qual1_t  emtf_qual1  [model_config::n_in];
  emtf_qual2_t  emtf_qual2  [model_config::n_in];
  emtf_time_t   emtf_time   [model_config::n_in];
  seg_zones_t   seg_zones   [model_config::n_in];
  seg_tzones_t  seg_tzones  [model_config::n_in];
  seg_fr_t      seg_fr      [model_config::n_in];
  seg_dl_t      seg_dl      [model_config::n_in];
  seg_bx_t      seg_bx      [model_config::n_in];
  seg_valid_t   seg_valid   [model_config::n_in];

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

  for (unsigned iseg = 0; iseg < model_config::n_in; iseg++) {

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
  zoning_out_t      zoning_0_out      [zoning_config::n_out];
  zoning_out_t      zoning_1_out      [zoning_config::n_out];
  zoning_out_t      zoning_2_out      [zoning_config::n_out];
  pooling_out_t     pooling_0_out     [pooling_config::n_out];
  pooling_out_t     pooling_1_out     [pooling_config::n_out];
  pooling_out_t     pooling_2_out     [pooling_config::n_out];
  suppression_out_t suppression_0_out [suppression_config::n_out];
  suppression_out_t suppression_1_out [suppression_config::n_out];
  suppression_out_t suppression_2_out [suppression_config::n_out];
  zonesorting_out_t zonesorting_0_out [zonesorting_config::n_out];
  zonesorting_out_t zonesorting_1_out [zonesorting_config::n_out];
  zonesorting_out_t zonesorting_2_out [zonesorting_config::n_out];
  zonemerging_out_t zonemerging_0_out [zonemerging_config::n_out];

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

  // Layer 0 - zoning

  zoning_layer<m_zone_0_tag>(emtf_phi, seg_zones, seg_tzones, seg_valid, zoning_0_out);
  zoning_layer<m_zone_1_tag>(emtf_phi, seg_zones, seg_tzones, seg_valid, zoning_1_out);
  zoning_layer<m_zone_2_tag>(emtf_phi, seg_zones, seg_tzones, seg_valid, zoning_2_out);

  // Layer 1 - pooling

  pooling_layer<m_zone_0_tag>(zoning_0_out, pooling_0_out);
  pooling_layer<m_zone_1_tag>(zoning_1_out, pooling_1_out);
  pooling_layer<m_zone_2_tag>(zoning_2_out, pooling_2_out);

  // Layer 2 - non-max suppression

  suppression_layer<m_zone_0_tag>(pooling_0_out, suppression_0_out);
  suppression_layer<m_zone_1_tag>(pooling_1_out, suppression_1_out);
  suppression_layer<m_zone_2_tag>(pooling_2_out, suppression_2_out);

  // ...

  // Unpack from zonemerging_0_out (a.k.a. in1)
  trk_qual_t  trk_qual [zonemerging_config::n_out];
  trk_patt_t  trk_patt [zonemerging_config::n_out];
  trk_col_t   trk_col  [zonemerging_config::n_out];
  trk_zone_t  trk_zone [zonemerging_config::n_out];

#pragma HLS ARRAY_PARTITION variable=trk_qual complete dim=0
#pragma HLS ARRAY_PARTITION variable=trk_patt complete dim=0
#pragma HLS ARRAY_PARTITION variable=trk_col complete dim=0
#pragma HLS ARRAY_PARTITION variable=trk_zone complete dim=0

top_fn_loop_in1:

  for (unsigned itrk = 0; itrk < zonemerging_config::n_out; itrk++) {

#pragma HLS UNROLL

    zonemerging_out_t in1_tmp = zonemerging_0_out[itrk];  // read input
  }  // end top_fn_loop_in1

  // This macro is defined in emtf_hlslib/helper.h
  PRINT_TOP_FN_ARRAYS_IN1

  // Intermediate arrays (2)
  trk_seg_t   trk_seg      [trkbuilding_config::n_out * num_emtf_sites];
  trk_feat_t  trk_feat     [trkbuilding_config::n_out * num_emtf_features];
  trk_valid_t trk_valid    [trkbuilding_config::n_out];
  trk_feat_t  trk_feat_rm  [duperemoval_config::n_out * num_emtf_features];
  trk_valid_t trk_valid_rm [duperemoval_config::n_out];

#pragma HLS ARRAY_PARTITION variable=trk_seg complete dim=0
#pragma HLS ARRAY_PARTITION variable=trk_feat complete dim=0
#pragma HLS ARRAY_PARTITION variable=trk_valid complete dim=0
#pragma HLS ARRAY_PARTITION variable=trk_feat_rm complete dim=0
#pragma HLS ARRAY_PARTITION variable=trk_valid_rm complete dim=0

top_fn_loop_out:

  for (unsigned i = 0; i < (duperemoval_config::n_out * num_emtf_features); i++) {

#pragma HLS UNROLL

    out[i] = trk_feat_rm[i];
  }  // end top_fn_loop_out

  // This macro is defined in emtf_hlslib/helper.h
  PRINT_TOP_FN_ARRAYS_OTHER
}
