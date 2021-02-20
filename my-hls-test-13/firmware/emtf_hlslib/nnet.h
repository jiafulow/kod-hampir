#ifndef __EMTF_HLSLIB_NNET_H__
#define __EMTF_HLSLIB_NNET_H__

namespace emtf {

// _____________________________________________________________________________
// Entry point

template <typename Zone>
void nnet_layer(
    const trk_feat_t  trk_feat  [nnet_config::n_in * num_emtf_features],
    const trk_valid_t trk_valid [nnet_config::n_in],
    trk_invpt_t       trk_invpt [nnet_config::n_out],
    trk_phi_t         trk_phi   [nnet_config::n_out],
    trk_eta_t         trk_eta   [nnet_config::n_out],
    trk_d0_t          trk_d0    [nnet_config::n_out],
    trk_z0_t          trk_z0    [nnet_config::n_out],
    trk_beta_t        trk_beta  [nnet_config::n_out]
) {

#pragma HLS PIPELINE II=nnet_config::layer_target_ii

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS LATENCY max=nnet_config::target_lat

  // Check assumptions
  static_assert(nnet_config::n_in == num_emtf_tracks, "nnet_config::n_in check failed");
  static_assert(nnet_config::n_out == num_emtf_tracks, "nnet_config::n_out check failed");
  static_assert(num_emtf_features == 40, "num_emtf_features must be 40");

  // Loop over tracks
  LOOP_TRK: for (unsigned itrk = 0; itrk < nnet_config::n_in; itrk++) {
    //FIXME
  }
}

}  // namespace emtf

#endif  // __EMTF_HLSLIB_NNET_H__ not defined
