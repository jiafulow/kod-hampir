#ifndef __EMTF_HLSLIB_TRKBUILDING_H__
#define __EMTF_HLSLIB_TRKBUILDING_H__

namespace emtf {

// Track building op

template <int ZONE>
void trkbuilding_op(
    const emtf_phi_t emtf_phi[N_MODEL_IN],
    const emtf_bend_t emtf_bend[N_MODEL_IN],
    const emtf_theta1_t emtf_theta1[N_MODEL_IN],
    const emtf_theta2_t emtf_theta2[N_MODEL_IN],
    const emtf_qual_t emtf_qual[N_MODEL_IN],
    const emtf_time_t emtf_time[N_MODEL_IN],
    const valid_t valid[N_MODEL_IN],
    const track_qual_t track_qual[N_TRKBUILDING_IN],
    const track_patt_t track_patt[N_TRKBUILDING_IN],
    const track_col_t track_col[N_TRKBUILDING_IN],
    const track_zone_t track_zone[N_TRKBUILDING_IN],
    trkbuilding_out_t trkbuilding_out[N_TRKBUILDING_OUT]
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

  // Check assumptions
  static_assert(N_TRKBUILDING_IN == num_out_tracks, "N_TRKBUILDING_IN check failed");
  static_assert(N_TRKBUILDING_OUT == num_out_tracks * num_out_variables, "N_TRKBUILDING_OUT check failed");

  //FIXME - implement the track building
  for (int i = 0; i < num_out_tracks; i++) {
    trkbuilding_out[i] = track_qual[i];
  }
}


// _____________________________________________________________________________
// Entry point

template <int ZONE>
void trkbuilding_layer(
    const emtf_phi_t emtf_phi[N_MODEL_IN],
    const emtf_bend_t emtf_bend[N_MODEL_IN],
    const emtf_theta1_t emtf_theta1[N_MODEL_IN],
    const emtf_theta2_t emtf_theta2[N_MODEL_IN],
    const emtf_qual_t emtf_qual[N_MODEL_IN],
    const emtf_time_t emtf_time[N_MODEL_IN],
    const valid_t valid[N_MODEL_IN],
    const track_qual_t track_qual[N_TRKBUILDING_IN],
    const track_patt_t track_patt[N_TRKBUILDING_IN],
    const track_col_t track_col[N_TRKBUILDING_IN],
    const track_zone_t track_zone[N_TRKBUILDING_IN],
    trkbuilding_out_t trkbuilding_out[N_TRKBUILDING_OUT]
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE region

  trkbuilding_op<ZONE>(emtf_phi, emtf_bend, emtf_theta1, emtf_theta2, emtf_qual, emtf_time, valid,
                       track_qual, track_patt, track_col, track_zone, trkbuilding_out);
}

}  // namespace emtf

#endif  // __EMTF_HLSLIB_TRKBUILDING_H__ not defined
