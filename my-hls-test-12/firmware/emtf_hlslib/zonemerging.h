#ifndef __EMTF_HLSLIB_ZONEMERGING_H__
#define __EMTF_HLSLIB_ZONEMERGING_H__

namespace emtf {

// Zone merging op
template <int ZONE>
void zonemerging_op(
    const zonemerging_in_t zonemerging_0_in[N_ZONEMERGING_IN],
    const zonemerging_in_t zonemerging_1_in[N_ZONEMERGING_IN],
    const zonemerging_in_t zonemerging_2_in[N_ZONEMERGING_IN],
    zonemerging_out_t zonemerging_out[N_ZONEMERGING_OUT]
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

  // Check assumptions
  static_assert(N_ZONEMERGING_IN == num_out_tracks, "N_ZONEMERGING_IN check failed");
  static_assert(N_ZONEMERGING_OUT == num_out_tracks, "N_ZONEMERGING_OUT check failed");

  //FIXME - implement the merging
  for (int i = 0; i < num_out_tracks; i++) {
    zonemerging_out[i] = zonemerging_0_in[i];
  }
}


// _____________________________________________________________________________
// Entry point

template <int ZONE>
void zonemerging_layer(
    const zonemerging_in_t zonemerging_0_in[N_ZONEMERGING_IN],
    const zonemerging_in_t zonemerging_1_in[N_ZONEMERGING_IN],
    const zonemerging_in_t zonemerging_2_in[N_ZONEMERGING_IN],
    zonemerging_out_t zonemerging_out[N_ZONEMERGING_OUT]
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE region

  zonemerging_op<ZONE>(zonemerging_0_in, zonemerging_1_in, zonemerging_2_in, zonemerging_out);
}

}  // namespace emtf

#endif  // __EMTF_HLSLIB_ZONEMERGING_H__ not defined
