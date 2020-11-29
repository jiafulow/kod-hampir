#ifndef __EMTF_HLSLIB_DUPEREMOVAL_H__
#define __EMTF_HLSLIB_DUPEREMOVAL_H__

namespace emtf {

template <typename T=void>
void duperemoval_preprocess_op(
    const trk_seg_t trk_seg[duperemoval_config::n_in * num_emtf_sites],
    const trk_seg_v_t trk_seg_v[duperemoval_config::n_in],
    trk_seg_t trk_seg_rm[duperemoval_config::n_in * num_emtf_sites_rm],
    trk_seg_v_t trk_seg_v_rm[duperemoval_config::n_in]
) {

#pragma HLS PIPELINE II=duperemoval_config::target_ii

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE

duperemoval_preprocess_op_loop:

  // Loop over tracks
  for (unsigned itrk = 0; itrk < duperemoval_config::n_in; itrk++) {

#pragma HLS UNROLL

    // Consider 5 sites for duplicate removal: ME1, ME2, ME3, ME4, ME0
    auto trk_seg_rhs = stl_next(trk_seg, itrk * num_emtf_sites);
    const trk_seg_v_t& vld_rhs = trk_seg_v[itrk];

    auto trk_seg_lhs = stl_next(trk_seg_rm, itrk * num_emtf_sites_rm);
    trk_seg_v_t& vld_lhs = trk_seg_v_rm[itrk];

    // site (out) | site (in)
    // -----------|-------------------------------------------
    // ME1        | ME1/1, GE1/1, ME1/2, RE1/2
    // ME2        | ME2, GE2/1, RE2/2
    // ME3        | ME3, RE3
    // ME4        | ME4, RE4
    // ME0        | ME0

    int k = 0;
    trk_seg_lhs[k++] = vld_rhs[0] ? trk_seg_rhs[0] : (vld_rhs[9] ? trk_seg_rhs[9] : (vld_rhs[1] ? trk_seg_rhs[1] : trk_seg_rhs[5]));
    trk_seg_lhs[k++] = vld_rhs[2] ? trk_seg_rhs[2] : (vld_rhs[10] ? trk_seg_rhs[10] : trk_seg_rhs[6]);
    trk_seg_lhs[k++] = vld_rhs[3] ? trk_seg_rhs[3] : trk_seg_rhs[7];
    trk_seg_lhs[k++] = vld_rhs[4] ? trk_seg_rhs[4] : trk_seg_rhs[8];
    trk_seg_lhs[k++] = trk_seg_rhs[11];
    assert(k == num_emtf_sites_rm);

    int l = 0;
    vld_lhs[l++] = vld_rhs[0] or vld_rhs[9] or vld_rhs[1] or vld_rhs[5];
    vld_lhs[l++] = vld_rhs[2] or vld_rhs[10] or vld_rhs[6];
    vld_lhs[l++] = vld_rhs[3] or vld_rhs[7];
    vld_lhs[l++] = vld_rhs[4] or vld_rhs[8];
    vld_lhs[l++] = vld_rhs[11];
    assert(l == num_emtf_sites_rm);
  }
}

template <typename T=void>
void duperemoval_set_survivors_op(
    const trk_valid_t trk_valid[duperemoval_config::n_in],
    const trk_seg_t trk_seg_rm[duperemoval_config::n_in * num_emtf_sites_rm],
    const trk_seg_v_t trk_seg_v_rm[duperemoval_config::n_in],
    duperemoval_survivor_t survivors[duperemoval_config::n_out]
) {

#pragma HLS PIPELINE II=duperemoval_config::target_ii

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE

  duperemoval_survivor_t removal = 0;  // initialize

duperemoval_set_survivors_op_loop_i:

  // Find duplicates and mark them for removal
  for (unsigned i = 0; i < (num_emtf_tracks - 1); i++) {

#pragma HLS UNROLL

  duperemoval_set_survivors_op_loop_j:

    for (unsigned j = i + 1; j < num_emtf_tracks; j++) {

#pragma HLS UNROLL

    duperemoval_set_survivors_op_loop_k:

      for (unsigned k = 0; k < num_emtf_sites_rm; k++) {

#pragma HLS UNROLL

        const bool is_valid = trk_valid[i] and trk_valid[j] and trk_seg_v_rm[i][k] and trk_seg_v_rm[j][k];
        const bool has_shared_seg = (trk_seg_rm[(i * num_emtf_sites_rm) + k] == trk_seg_rm[(j * num_emtf_sites_rm) + k]);
        if (is_valid and has_shared_seg) {
          removal[j] = true;
        }
      }
    }
  }

duperemoval_set_survivors_op_loop_i_1:

  // Determine indices for output after removal
  for (unsigned i = 0, j = 0; j < num_emtf_tracks; j++) {

#pragma HLS UNROLL

    survivors[i] = 0;  // initialize

    if (!removal[j]) {
      survivors[i][j] = 1;
      i++;
    }
  }
}

template <typename T=void>
void duperemoval_set_features_op(
    const trk_feat_t trk_feat[duperemoval_config::n_in * num_emtf_features],
    const duperemoval_survivor_t survivors[duperemoval_config::n_out],
    trk_feat_t trk_feat_rm[duperemoval_config::n_out * num_emtf_features],
    trk_valid_t trk_valid_rm[duperemoval_config::n_out]
) {

#pragma HLS PIPELINE II=duperemoval_config::target_ii

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE

duperemoval_set_features_op_loop_i:

  // Multiplex to output
  for (unsigned i = 0; i < num_emtf_tracks; i++) {

#pragma HLS UNROLL

    trk_valid_rm[i] = (bool) survivors[i];

    if (trk_valid_rm[i]) {

    duperemoval_set_features_op_loop_j:

      for (unsigned j = i; j < num_emtf_tracks; j++) {

#pragma HLS UNROLL

        if (survivors[i][j]) {  // only one survives

        duperemoval_set_features_op_loop_k:

          // Simple copy
          for (unsigned k = 0; k < num_emtf_features; k++) {

#pragma HLS UNROLL

            trk_feat_rm[(i * num_emtf_features) + k] = trk_feat[(j * num_emtf_features) + k];
          }
        }
      }
    } else {
      // Invalid track

    duperemoval_set_features_op_loop_j_else:

      // Fill with zero
      for (unsigned k = 0; k < num_emtf_features; k++) {

#pragma HLS UNROLL

        trk_feat_rm[(i * num_emtf_features) + k] = 0;
      }
    }
  }
}

// _____________________________________________________________________________
// Dupe removal op

template <typename Zone>
void duperemoval_op(
    const trk_seg_t   trk_seg      [duperemoval_config::n_in * num_emtf_sites],
    const trk_seg_v_t trk_seg_v    [duperemoval_config::n_in],
    const trk_feat_t  trk_feat     [duperemoval_config::n_in * num_emtf_features],
    const trk_valid_t trk_valid    [duperemoval_config::n_in],
    trk_feat_t        trk_feat_rm  [duperemoval_config::n_out * num_emtf_features],
    trk_valid_t       trk_valid_rm [duperemoval_config::n_out]
) {

#pragma HLS PIPELINE II=duperemoval_config::target_ii

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE

  trk_seg_t trk_seg_rm[duperemoval_config::n_in * num_emtf_sites_rm];
  trk_seg_v_t trk_seg_v_rm[duperemoval_config::n_in];
  duperemoval_survivor_t survivors[duperemoval_config::n_out];

#pragma HLS ARRAY_PARTITION variable=trk_seg_rm complete dim=0
#pragma HLS ARRAY_PARTITION variable=trk_seg_v_rm complete dim=0
#pragma HLS ARRAY_PARTITION variable=survivors complete dim=0

  duperemoval_preprocess_op(trk_seg, trk_seg_v, trk_seg_rm, trk_seg_v_rm);

  duperemoval_set_survivors_op(trk_valid, trk_seg_rm, trk_seg_v_rm, survivors);

  duperemoval_set_features_op(trk_feat, survivors, trk_feat_rm, trk_valid_rm);
}

// _____________________________________________________________________________
// Entry point

template <typename Zone>
void duperemoval_layer(
    const trk_seg_t   trk_seg      [duperemoval_config::n_in * num_emtf_sites],
    const trk_seg_v_t trk_seg_v    [duperemoval_config::n_in],
    const trk_feat_t  trk_feat     [duperemoval_config::n_in * num_emtf_features],
    const trk_valid_t trk_valid    [duperemoval_config::n_in],
    trk_feat_t        trk_feat_rm  [duperemoval_config::n_out * num_emtf_features],
    trk_valid_t       trk_valid_rm [duperemoval_config::n_out]
) {

#pragma HLS PIPELINE II=duperemoval_config::target_ii

#pragma HLS INTERFACE ap_ctrl_none port=return

  // Check assumptions
  static_assert(duperemoval_config::n_in == num_emtf_tracks, "duperemoval_config::n_in check failed");
  static_assert(duperemoval_config::n_out == num_emtf_tracks, "duperemoval_config::n_out check failed");
  static_assert(num_emtf_sites == 12, "num_emtf_sites must be 12");
  static_assert(num_emtf_sites_rm == 5, "num_emtf_sites_rm must be 5");

  duperemoval_op<Zone>(trk_seg, trk_seg_v, trk_feat, trk_valid, trk_feat_rm, trk_valid_rm);
}

}  // namespace emtf

#endif  // __EMTF_HLSLIB_DUPEREMOVAL_H__ not defined
