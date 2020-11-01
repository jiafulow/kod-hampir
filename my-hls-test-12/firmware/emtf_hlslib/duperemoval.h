#ifndef __EMTF_HLSLIB_DUPEREMOVAL_H__
#define __EMTF_HLSLIB_DUPEREMOVAL_H__

namespace emtf {

template <typename T>
void duperemoval_copy_array(const T in0[num_features], T out[num_features]) {
  for (int i = 0; i < num_features; i++) {

#pragma HLS UNROLL

    out[i] = in0[i];
  }
}

template <typename T>
void duperemoval_zero_array(T out[num_features]) {
  for (int i = 0; i < num_features; i++) {

#pragma HLS UNROLL

    out[i] = 0;
  }
}

template <int Zone>
void duperemoval_preprocess(
    const track_seg_t track_seg[N_DUPEREMOVAL_IN * num_sites],
    const track_seg_v_t track_seg_v[N_DUPEREMOVAL_IN],
    track_seg_t track_seg_rm[N_DUPEREMOVAL_IN * num_sites_rm],
    track_seg_v_t track_seg_v_rm[N_DUPEREMOVAL_IN]
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE region

  // Loop over tracks
  for (int i = 0; i < num_tracks; i++) {

#pragma HLS UNROLL

    // Consider 6 sites for duplicate removal: ME1, ME2, ME3, ME4, ME0
    const track_seg_t* track_seg_rhs = track_seg + (i * num_sites);
    const track_seg_v_t& vld_rhs = track_seg_v[i];
    track_seg_t* track_seg_lhs = track_seg_rm + (i * num_sites_rm);
    track_seg_v_t& vld_lhs = track_seg_v_rm[i];

    int k = 0;
    track_seg_lhs[k++] = vld_rhs[0] ? track_seg_rhs[0] : (vld_rhs[9] ? track_seg_rhs[9] : (vld_rhs[1] ? track_seg_rhs[1] : (vld_rhs[5] ? track_seg_rhs[5] : (track_seg_t) N_MODEL_IN)));  // ME1/1 or GE1/1 or ME1/2 or RE1/2
    track_seg_lhs[k++] = vld_rhs[2] ? track_seg_rhs[2] : (vld_rhs[10] ? track_seg_rhs[10] : (vld_rhs[6] ? track_seg_rhs[6] : (track_seg_t) N_MODEL_IN));  // ME2 or GE2/1 or RE2/2
    track_seg_lhs[k++] = vld_rhs[3] ? track_seg_rhs[3] : (vld_rhs[7] ? track_seg_rhs[7] : (track_seg_t) N_MODEL_IN);  // ME3 or RE3
    track_seg_lhs[k++] = vld_rhs[4] ? track_seg_rhs[4] : (vld_rhs[8] ? track_seg_rhs[8] : (track_seg_t) N_MODEL_IN);  // ME4 or RE4
    track_seg_lhs[k++] = vld_rhs[11] ? track_seg_rhs[11] : (track_seg_t) N_MODEL_IN;  // ME0

    k = 0;
    vld_lhs[k++] = vld_rhs[0] or vld_rhs[9] or vld_rhs[1] or vld_rhs[5];
    vld_lhs[k++] = vld_rhs[2] or vld_rhs[10] or vld_rhs[6];
    vld_lhs[k++] = vld_rhs[3] or vld_rhs[7];
    vld_lhs[k++] = vld_rhs[4] or vld_rhs[8];
    vld_lhs[k++] = vld_rhs[11];
  }
}

template <int Zone>
void duperemoval_set_survivor(
    const track_seg_t track_seg_rm[N_DUPEREMOVAL_IN * num_sites_rm],
    const track_seg_v_t track_seg_v_rm[N_DUPEREMOVAL_IN],
    duperemoval_survivor_t survivor[N_DUPEREMOVAL_OUT]
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE region

  duperemoval_survivor_t removal = 0;  // initialize

  // Find duplicates and mark them for removal
  for (int i = 0; i < num_tracks; i++) {

#pragma HLS UNROLL

    for (int j = i + 1; j < num_tracks; j++) {

#pragma HLS UNROLL

      for (int k = 0; k < num_sites_rm; k++) {

#pragma HLS UNROLL

        const bool is_valid = track_seg_v_rm[i] and track_seg_v_rm[j];
        //const bool has_shared_seg = (track_seg_rm[(i * num_sites_rm) + k] == track_seg_rm[(j * num_sites_rm) + k]);
        const bool has_shared_seg = ((track_seg_rm[(i * num_sites_rm) + k] ^ track_seg_rm[(j * num_sites_rm) + k]) == 0);
        if (is_valid and has_shared_seg)
          removal[j] = true;
      }
    }
  }

  // Determine indices for output after removal
  for (int i = 0, j = 0; j < num_tracks; j++) {
    survivor[i] = 0;  // initialize

#pragma HLS UNROLL

    if (!removal[j]) {
      survivor[i][j] = 1;
      i++;
    }
  }
}

template <int Zone>
void duperemoval_set_features(
    const track_feat_t track_feat[N_DUPEREMOVAL_IN * num_features],
    const duperemoval_survivor_t survivor[N_DUPEREMOVAL_OUT],
    track_feat_t track_feat_rm[N_DUPEREMOVAL_OUT * num_features],
    track_valid_t track_valid_rm[N_DUPEREMOVAL_OUT]
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE region

  // Multiplex to output
  for (int i = 0; i < num_tracks; i++) {

#pragma HLS UNROLL

    track_valid_rm[i] = (bool) survivor[i];

    if (track_valid_rm[i]) {
      for (int j = i; j < num_tracks; j++) {

#pragma HLS UNROLL

        if (survivor[i][j]) {
          duperemoval_copy_array(track_feat + (j * num_features), track_feat_rm + (i * num_features));
        }
      }
    } else {
      // Invalid output
      duperemoval_zero_array(track_feat_rm + (i * num_features));
    }
  }
}


// _____________________________________________________________________________
template <int Zone>
void duperemoval_op(
    const track_seg_t track_seg[N_DUPEREMOVAL_IN * num_sites],
    const track_seg_v_t track_seg_v[N_DUPEREMOVAL_IN],
    const track_feat_t track_feat[N_DUPEREMOVAL_IN * num_features],
    const track_valid_t track_valid[N_DUPEREMOVAL_IN],
    track_feat_t track_feat_rm[N_DUPEREMOVAL_OUT * num_features],
    track_valid_t track_valid_rm[N_DUPEREMOVAL_OUT]
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE region

  track_seg_t track_seg_rm[N_DUPEREMOVAL_IN * num_sites_rm];
  track_seg_v_t track_seg_v_rm[N_DUPEREMOVAL_IN];
  duperemoval_survivor_t survivor[N_DUPEREMOVAL_OUT];

#pragma HLS ARRAY_PARTITION variable=track_seg_rm complete dim=0
#pragma HLS ARRAY_PARTITION variable=track_seg_v_rm complete dim=0
#pragma HLS ARRAY_PARTITION variable=survivor complete dim=0

  duperemoval_preprocess<Zone>(track_seg, track_seg_v, track_seg_rm, track_seg_v_rm);

  duperemoval_set_survivor<Zone>(track_seg_rm, track_seg_v_rm, survivor);

  duperemoval_set_features<Zone>(track_feat, survivor, track_feat_rm, track_valid_rm);
}


// _____________________________________________________________________________
// Entry point

template <int Zone>
void duperemoval_layer(
    const track_seg_t track_seg[N_DUPEREMOVAL_IN * num_sites],
    const track_seg_v_t track_seg_v[N_DUPEREMOVAL_IN],
    const track_feat_t track_feat[N_DUPEREMOVAL_IN * num_features],
    const track_valid_t track_valid[N_DUPEREMOVAL_IN],
    track_feat_t track_feat_rm[N_DUPEREMOVAL_OUT * num_features],
    track_valid_t track_valid_rm[N_DUPEREMOVAL_OUT]
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE region

  // Check assumptions
  static_assert(N_DUPEREMOVAL_IN == num_tracks, "N_DUPEREMOVAL_IN check failed");
  static_assert(N_DUPEREMOVAL_OUT == num_tracks, "N_DUPEREMOVAL_OUT check failed");
  static_assert(num_sites_rm == 5, "num_sites_rm must be 5");

  duperemoval_op<0>(track_seg, track_seg_v, track_feat, track_valid, track_feat_rm, track_valid_rm);
}

}  // namespace emtf

#endif  // __EMTF_HLSLIB_DUPEREMOVAL_H__ not defined
