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
  // Note: the following are currently unused and will be synthesized away - emtf_qual2, emtf_time, seg_fr, seg_dl, seg_bx.
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

  // Loop over in0
  LOOP_IN0: for (unsigned iseg = 0; iseg < model_config::n_in; iseg++) {

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
  }  // end loop over in0

  // This macro is defined in emtf_hlslib/helper.h
  PRINT_TOP_FN_ARRAYS_IN0

  // Check assumptions
  constexpr int num_trk_cols_with_safety = (((80 * 64) / emtf_img_col_factor) + (max_emtf_img_col_pad * 2));
  static_assert(trk_qual_t::width == max_emtf_pattern_activation_log2, "trk_qual_t type check failed");
  static_assert(trk_patt_t::width == details::ceil_log2<num_emtf_patterns>::value, "trk_patt_t type check failed");
  static_assert(trk_col_t::width == details::ceil_log2<num_trk_cols_with_safety>::value, "trk_col_t type check failed");
  static_assert(trk_zone_t::width == details::ceil_log2<num_emtf_zones>::value, "trk_zone_t type check failed");
  static_assert(trk_tzone_t::width == details::ceil_log2<num_emtf_timezones>::value, "trk_tzone_t type check failed");
  static_assert(trk_seg_t::width == details::ceil_log2<num_emtf_chambers * num_emtf_segments>::value, "trk_seg_t type check failed");
  static_assert(trk_seg_v_t::width == num_emtf_sites, "trk_seg_v_t type check failed");
  static_assert(trk_feat_t::width == emtf_phi_t::width, "trk_feat_t type check failed");
  static_assert(trk_valid_t::width == 1, "trk_valid_t type check failed");

  // Intermediate arrays (for layers 0..4)
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

  suppression_layer<m_zone_any_tag>(pooling_0_out, suppression_0_out);
  suppression_layer<m_zone_any_tag>(pooling_1_out, suppression_1_out);
  suppression_layer<m_zone_any_tag>(pooling_2_out, suppression_2_out);

  // Layer 3 - zone sorting

  zonesorting_layer<m_zone_any_tag>(suppression_0_out, zonesorting_0_out);
  zonesorting_layer<m_zone_any_tag>(suppression_1_out, zonesorting_1_out);
  zonesorting_layer<m_zone_any_tag>(suppression_2_out, zonesorting_2_out);

  // Layer 4 - zone merging

  zonemerging_layer<m_zone_any_tag>(
      zonesorting_0_out, zonesorting_1_out, zonesorting_2_out, zonemerging_0_out
  );

  // Unpack from in1 (a.k.a. zonemerging_0_out)
  trk_qual_t trk_qual [trkbuilding_config::n_in];
  trk_patt_t trk_patt [trkbuilding_config::n_in];
  trk_col_t  trk_col  [trkbuilding_config::n_in];
  trk_zone_t trk_zone [trkbuilding_config::n_in];

#pragma HLS ARRAY_PARTITION variable=trk_qual complete dim=0
#pragma HLS ARRAY_PARTITION variable=trk_patt complete dim=0
#pragma HLS ARRAY_PARTITION variable=trk_col complete dim=0
#pragma HLS ARRAY_PARTITION variable=trk_zone complete dim=0

  constexpr int in1_0_bits_lo = 0;
  constexpr int in1_0_bits_hi = (in1_0_bits_lo + trk_qual_t::width - 1);
  constexpr int in1_1_bits_lo = (in1_0_bits_hi + 1);
  constexpr int in1_1_bits_hi = (in1_1_bits_lo + trk_patt_t::width - 1);
  constexpr int in1_2_bits_lo = (in1_1_bits_hi + 1);
  constexpr int in1_2_bits_hi = (in1_2_bits_lo + trk_col_t::width - 1);
  constexpr int in1_3_bits_lo = (in1_2_bits_hi + 1);
  constexpr int in1_3_bits_hi = (in1_3_bits_lo + trk_zone_t::width - 1);

  // Loop over in1
  LOOP_IN1: for (unsigned itrk = 0; itrk < trkbuilding_config::n_in; itrk++) {

#pragma HLS UNROLL

    trk_qual[itrk] = zonemerging_0_out[itrk].range(in1_0_bits_hi, in1_0_bits_lo);
    trk_patt[itrk] = zonemerging_0_out[itrk].range(in1_1_bits_hi, in1_1_bits_lo);
    trk_col[itrk]  = zonemerging_0_out[itrk].range(in1_2_bits_hi, in1_2_bits_lo);
    trk_zone[itrk] = zonemerging_0_out[itrk].range(in1_3_bits_hi, in1_3_bits_lo);
  }  // end loop over in1

  // This macro is defined in emtf_hlslib/helper.h
  PRINT_TOP_FN_ARRAYS_IN1

  // Intermediate arrays (for layers 5..6)
  trk_seg_t   trk_seg      [trkbuilding_config::n_out * num_emtf_sites];
  trk_seg_v_t trk_seg_v    [trkbuilding_config::n_out];
  trk_feat_t  trk_feat     [trkbuilding_config::n_out * num_emtf_features];
  trk_valid_t trk_valid    [trkbuilding_config::n_out];
  trk_feat_t  trk_feat_rm  [duperemoval_config::n_out * num_emtf_features];
  trk_valid_t trk_valid_rm [duperemoval_config::n_out];

#pragma HLS ARRAY_PARTITION variable=trk_seg complete dim=0
#pragma HLS ARRAY_PARTITION variable=trk_seg_v complete dim=0
#pragma HLS ARRAY_PARTITION variable=trk_feat complete dim=0
#pragma HLS ARRAY_PARTITION variable=trk_valid complete dim=0
#pragma HLS ARRAY_PARTITION variable=trk_feat_rm complete dim=0
#pragma HLS ARRAY_PARTITION variable=trk_valid_rm complete dim=0

  // Layer 5 - track building

  trkbuilding_layer<m_zone_any_tag>(
      emtf_phi, emtf_bend, emtf_theta1, emtf_theta2, emtf_qual1, emtf_qual2,
      emtf_time, seg_zones, seg_tzones, seg_fr, seg_dl, seg_bx,
      seg_valid, trk_qual, trk_patt, trk_col, trk_zone, trk_seg,
      trk_seg_v, trk_feat, trk_valid
  );

  // Layer 6 - dupe removal

  duperemoval_layer<m_zone_any_tag>(
      trk_seg, trk_seg_v, trk_feat, trk_valid, trk_feat_rm, trk_valid_rm
  );

  // Copy to output
  LOOP_OUT: for (unsigned i = 0; i < model_config::n_out; i++) {

#pragma HLS UNROLL

    out[i] = trk_feat_rm[i];
  }

  // This macro is defined in emtf_hlslib/helper.h
  PRINT_TOP_FN_ARRAYS_OTHER
}
