#ifndef __EMTF_HLSLIB_ZONING_H__
#define __EMTF_HLSLIB_ZONING_H__

namespace emtf {

// Given a segment (TP) with (emtf_phi, flags_zone, flags_tzone, and valid), set bit in zoning_out_row_k
template <int ZONE, int TIMEZONE=0>
void zoning_row_op(
    const emtf::emtf_phi_t emtf_phi_iseg,
    const emtf::flags_zone_t flags_zone_iseg,
    const emtf::flags_tzone_t flags_tzone_iseg,
    const emtf::valid_t valid_iseg,
    emtf::zoning_out_t& zoning_out_row_k
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

  static const emtf::emtf_phi_t coarse_emtf_strip = 8 * 2;  // 'doublestrip' unit; doublestrip = 2x full-strip unit in 10 deg chamber
  static const emtf::emtf_phi_t min_emtf_strip = 27 * coarse_emtf_strip;  // 7.2 deg
  static const emtf::emtf_phi_t max_emtf_strip = 315 * coarse_emtf_strip;  // 84 deg

  if (
      (valid_iseg == 1) and \
      (flags_zone_iseg[2-ZONE] == 1) and \
      (flags_tzone_iseg[2-TIMEZONE] == 1) and \
      (min_emtf_strip <= emtf_phi_iseg) and \
      (emtf_phi_iseg < max_emtf_strip)
  ) {
    const ap_uint<emtf_phi_t::width - 4> col = (emtf_phi_iseg - min_emtf_strip) >> 4;  // truncate last 4 bits (i.e. divide by 16)
    assert(0 <= col && col < num_img_cols);
    zoning_out_row_k[col] = 1;
  }
}

// Zoning op for zone 0
template <int ZONE, typename enable_if<ZONE == 0, int>::type = 0>
void zoning_op(
    const emtf::emtf_phi_t emtf_phi[N_MODEL_IN],
    const emtf::flags_zone_t flags_zone[N_MODEL_IN],
    const emtf::flags_tzone_t flags_tzone[N_MODEL_IN],
    const emtf::valid_t valid[N_MODEL_IN],
    emtf::zoning_out_t zoning_out[N_ZONING_OUT]
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE region

  static const int chambers_row_0[7]   = {108, 109, 110, 111, 112, 113, 114};
  static const int chambers_row_1[7]   = { 54,  55,  56,  63,  64,  65,  99};
  static const int chambers_row_2[7]   = {  0,   1,   2,   9,  10,  11,  45};
  static const int chambers_row_3[4]   = { 72,  73,  74, 102};
  static const int chambers_row_4[4]   = { 18,  19,  20,  48};
  static const int chambers_row_5[4]   = { 27,  28,  29,  50};
  static const int chambers_row_6[4]   = { 81,  82,  83, 104};
  static const int chambers_row_7_0[4] = { 36,  37,  38,  52};
  static const int chambers_row_7_1[4] = { 90,  91,  92, 106};

  static const int N = 7 + 7 + 7 + 4 + 4 + 4 + 4 + 4 + 4;

  static const int chambers_fused[N] = {
    chambers_row_0[0], chambers_row_0[1], chambers_row_0[2], chambers_row_0[3], chambers_row_0[4], chambers_row_0[5], chambers_row_0[6],
    chambers_row_1[0], chambers_row_1[1], chambers_row_1[2], chambers_row_1[3], chambers_row_1[4], chambers_row_1[5], chambers_row_1[6],
    chambers_row_2[0], chambers_row_2[1], chambers_row_2[2], chambers_row_2[3], chambers_row_2[4], chambers_row_2[5], chambers_row_2[6],
    chambers_row_3[0], chambers_row_3[1], chambers_row_3[2], chambers_row_3[3],
    chambers_row_4[0], chambers_row_4[1], chambers_row_4[2], chambers_row_4[3],
    chambers_row_5[0], chambers_row_5[1], chambers_row_5[2], chambers_row_5[3],
    chambers_row_6[0], chambers_row_6[1], chambers_row_6[2], chambers_row_6[3],
    chambers_row_7_0[0], chambers_row_7_0[1], chambers_row_7_0[2], chambers_row_7_0[3],
    chambers_row_7_1[0], chambers_row_7_1[1], chambers_row_7_1[2], chambers_row_7_1[3]
  };

  static const int rows_fused[N] = {
    0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 2,
    3, 3, 3, 3,
    4, 4, 4, 4,
    5, 5, 5, 5,
    6, 6, 6, 6,
    7, 7, 7, 7,
    7, 7, 7, 7
  };

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < emtf::num_segments; j++) {

#pragma HLS UNROLL

      const unsigned iseg = (chambers_fused[i] * emtf::num_segments) + j;
      zoning_row_op<ZONE>(emtf_phi[iseg], flags_zone[iseg], flags_tzone[iseg], valid[iseg], zoning_out[rows_fused[i]]);
    }
  }
}


// _____________________________________________________________________________
// Entry point

template <int ZONE>
void zoning_layer(
    const emtf::emtf_phi_t emtf_phi[N_MODEL_IN],
    const emtf::flags_zone_t flags_zone[N_MODEL_IN],
    const emtf::flags_tzone_t flags_tzone[N_MODEL_IN],
    const emtf::valid_t valid[N_MODEL_IN],
    emtf::zoning_out_t zoning_out[N_ZONING_OUT]
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

  zoning_op<ZONE>(emtf_phi, flags_zone, flags_tzone, valid, zoning_out);
}

}  // namespace emtf

#endif  // __EMTF_HLSLIB_ZONING_H__ not defined
