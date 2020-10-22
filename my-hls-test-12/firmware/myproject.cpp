#include "myproject.h"

// EMTF HLS
#include "emtf_hlslib/all.h"

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
  emtf::emtf_phi_t    emtf_phi    [N_MODEL_IN];
  emtf::emtf_bend_t   emtf_bend   [N_MODEL_IN];
  emtf::emtf_theta1_t emtf_theta1 [N_MODEL_IN];
  emtf::emtf_theta2_t emtf_theta2 [N_MODEL_IN];
  emtf::emtf_qual_t   emtf_qual   [N_MODEL_IN];
  emtf::emtf_time_t   emtf_time   [N_MODEL_IN];
  emtf::flags_zone_t  flags_zone  [N_MODEL_IN];
  emtf::flags_tzone_t flags_tzone [N_MODEL_IN];
  emtf::bx_t          bx          [N_MODEL_IN];
  emtf::valid_t       valid       [N_MODEL_IN];

#pragma HLS ARRAY_PARTITION variable=emtf_phi complete dim=0
#pragma HLS ARRAY_PARTITION variable=emtf_bend complete dim=0
#pragma HLS ARRAY_PARTITION variable=emtf_theta1 complete dim=0
#pragma HLS ARRAY_PARTITION variable=emtf_theta2 complete dim=0
#pragma HLS ARRAY_PARTITION variable=emtf_qual complete dim=0
#pragma HLS ARRAY_PARTITION variable=emtf_time complete dim=0
#pragma HLS ARRAY_PARTITION variable=flags_zone complete dim=0
#pragma HLS ARRAY_PARTITION variable=flags_tzone complete dim=0
#pragma HLS ARRAY_PARTITION variable=bx complete dim=0
#pragma HLS ARRAY_PARTITION variable=valid complete dim=0

  emtf::model_in_t in0_tmp;

  top_fn_loop_in0 : for (unsigned iseg = 0; iseg < N_MODEL_IN; iseg++) {

#pragma HLS UNROLL

    in0_tmp = in0[iseg];  // read input

    emtf_phi[iseg]    = in0_tmp.range(emtf::emtf_phi_bits_hi   , emtf::emtf_phi_bits_lo);
    emtf_bend[iseg]   = in0_tmp.range(emtf::emtf_bend_bits_hi  , emtf::emtf_bend_bits_lo);
    emtf_theta1[iseg] = in0_tmp.range(emtf::emtf_theta1_bits_hi, emtf::emtf_theta1_bits_lo);
    emtf_theta2[iseg] = in0_tmp.range(emtf::emtf_theta2_bits_hi, emtf::emtf_theta2_bits_lo);
    emtf_qual[iseg]   = in0_tmp.range(emtf::emtf_qual_bits_hi  , emtf::emtf_qual_bits_lo);
    emtf_time[iseg]   = in0_tmp.range(emtf::emtf_time_bits_hi  , emtf::emtf_time_bits_lo);
    flags_zone[iseg]  = in0_tmp.range(emtf::flags_zone_bits_hi , emtf::flags_zone_bits_lo);
    flags_tzone[iseg] = in0_tmp.range(emtf::flags_tzone_bits_hi, emtf::flags_tzone_bits_lo);
    bx[iseg]          = in0_tmp.range(emtf::bx_bits_hi         , emtf::bx_bits_lo);
    valid[iseg]       = in0_tmp.range(emtf::valid_bits_hi      , emtf::valid_bits_lo);
  }

  // This macro is defined in emtf_hlslib/helper.h
  PRINT_TOP_FN_ARRAYS_IN0

  // Intermediate arrays
  emtf::zoning_out_t      zoning_0_out      [N_ZONING_OUT];
  emtf::zoning_out_t      zoning_1_out      [N_ZONING_OUT];
  emtf::zoning_out_t      zoning_2_out      [N_ZONING_OUT];
  emtf::pooling_out_t     pooling_0_out     [N_POOLING_OUT];
  emtf::pooling_out_t     pooling_1_out     [N_POOLING_OUT];
  emtf::pooling_out_t     pooling_2_out     [N_POOLING_OUT];
  emtf::suppression_out_t suppression_0_out [N_SUPPRESSION_OUT];
  emtf::suppression_out_t suppression_1_out [N_SUPPRESSION_OUT];
  emtf::suppression_out_t suppression_2_out [N_SUPPRESSION_OUT];
  emtf::zonesorting_out_t zonesorting_0_out [N_ZONESORTING_OUT];
  emtf::zonesorting_out_t zonesorting_1_out [N_ZONESORTING_OUT];
  emtf::zonesorting_out_t zonesorting_2_out [N_ZONESORTING_OUT];
  emtf::zonemerging_out_t zonemerging_0_out [N_ZONEMERGING_OUT];

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

  emtf::zoning_layer<0>(emtf_phi, flags_zone, flags_tzone, valid, zoning_0_out);
  emtf::zoning_layer<1>(emtf_phi, flags_zone, flags_tzone, valid, zoning_1_out);
  emtf::zoning_layer<2>(emtf_phi, flags_zone, flags_tzone, valid, zoning_2_out);

  // Layer 1 - pooling

  emtf::pooling_layer<0>(zoning_0_out, pooling_0_out);
  emtf::pooling_layer<1>(zoning_1_out, pooling_1_out);
  emtf::pooling_layer<2>(zoning_2_out, pooling_2_out);

  // Layer 2 - non-max suppression

  emtf::suppression_layer<0>(pooling_0_out, suppression_0_out);
  emtf::suppression_layer<1>(pooling_1_out, suppression_1_out);
  emtf::suppression_layer<2>(pooling_2_out, suppression_2_out);

  // Layer 3 - zone sorting

  emtf::zonesorting_layer<0>(suppression_0_out, zonesorting_0_out);
  emtf::zonesorting_layer<1>(suppression_1_out, zonesorting_1_out);
  emtf::zonesorting_layer<2>(suppression_2_out, zonesorting_2_out);

  // Layer 4 - zone merging

  emtf::zonemerging_layer<0>(zonesorting_0_out, zonesorting_1_out, zonesorting_2_out,
                             zonemerging_0_out);

  // Deserialize from zonemerging_0_out
  emtf::track_qual_t track_qual [N_ZONEMERGING_OUT];
  emtf::track_patt_t track_patt [N_ZONEMERGING_OUT];
  emtf::track_col_t  track_col  [N_ZONEMERGING_OUT];
  emtf::track_zone_t track_zone [N_ZONEMERGING_OUT];

#pragma HLS ARRAY_PARTITION variable=track_qual complete dim=0
#pragma HLS ARRAY_PARTITION variable=track_patt complete dim=0
#pragma HLS ARRAY_PARTITION variable=track_col complete dim=0
#pragma HLS ARRAY_PARTITION variable=track_zone complete dim=0

  emtf::zonemerging_out_t in1_tmp;

  top_fn_loop_in1 : for (unsigned itrk = 0; itrk < N_ZONEMERGING_OUT; itrk++) {

#pragma HLS UNROLL

    in1_tmp = zonemerging_0_out[itrk];  // read input

    track_qual[itrk] = in1_tmp.range(emtf::track_qual_bits_hi, emtf::track_qual_bits_lo);
    track_patt[itrk] = in1_tmp.range(emtf::track_patt_bits_hi, emtf::track_patt_bits_lo);
    track_col[itrk]  = in1_tmp.range(emtf::track_col_bits_hi , emtf::track_col_bits_lo);
    track_zone[itrk] = in1_tmp.range(emtf::track_zone_bits_hi, emtf::track_zone_bits_lo);
  }

  // This macro is defined in emtf_hlslib/helper.h
  PRINT_TOP_FN_ARRAYS_IN1

  // Layer 5 - track building

  emtf::trkbuilding_layer<0>(emtf_phi, emtf_bend, emtf_theta1, emtf_theta2, emtf_qual, emtf_time,
                             flags_zone, flags_tzone, bx, valid, track_qual, track_patt,
                             track_col, track_zone, out);

  // This macro is defined in emtf_hlslib/helper.h
  PRINT_TOP_FN_ARRAYS_OTHER
}
