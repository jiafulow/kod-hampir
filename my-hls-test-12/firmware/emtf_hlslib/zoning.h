#ifndef __EMTF_HLSLIB_ZONING_H__
#define __EMTF_HLSLIB_ZONING_H__

namespace emtf {

namespace detail {

// Zone 0 - 45 chambers
constexpr static const int chambers_zone_0_row_0[7]   = {108, 109, 110, 111, 112, 113, 114};
constexpr static const int chambers_zone_0_row_1[7]   = { 54,  55,  56,  63,  64,  65,  99};
constexpr static const int chambers_zone_0_row_2[7]   = {  0,   1,   2,   9,  10,  11,  45};
constexpr static const int chambers_zone_0_row_3[4]   = { 72,  73,  74, 102};
constexpr static const int chambers_zone_0_row_4[4]   = { 18,  19,  20,  48};
constexpr static const int chambers_zone_0_row_5[4]   = { 27,  28,  29,  50};
constexpr static const int chambers_zone_0_row_6[4]   = { 81,  82,  83, 104};
constexpr static const int chambers_zone_0_row_7_0[4] = { 36,  37,  38,  52};
constexpr static const int chambers_zone_0_row_7_1[4] = { 90,  91,  92, 106};

//TODO - include chamber start phi

}  // namespace detail

template <int ZONE>
struct find_num_rows {};  // not to be confused with emtf::num_img_rows

template <> struct find_num_rows<0> { static const int value = 9; };

template <int ZONE, int ROW>
struct find_num_chambers {};  // not to be confused with emtf::num_chambers

template <> struct find_num_chambers<0, 0> { static const int value = 7; };
template <> struct find_num_chambers<0, 1> { static const int value = 7; };
template <> struct find_num_chambers<0, 2> { static const int value = 7; };
template <> struct find_num_chambers<0, 3> { static const int value = 4; };
template <> struct find_num_chambers<0, 4> { static const int value = 4; };
template <> struct find_num_chambers<0, 5> { static const int value = 4; };
template <> struct find_num_chambers<0, 6> { static const int value = 4; };
template <> struct find_num_chambers<0, 7> { static const int value = 4; };
template <> struct find_num_chambers<0, 8> { static const int value = 4; };

template <int ZONE, int ROW>
struct find_chamber {};

template <> struct find_chamber<0, 0> { inline int operator ()(int i) const { return detail::chambers_zone_0_row_0[i]; } };
template <> struct find_chamber<0, 1> { inline int operator ()(int i) const { return detail::chambers_zone_0_row_1[i]; } };
template <> struct find_chamber<0, 2> { inline int operator ()(int i) const { return detail::chambers_zone_0_row_2[i]; } };
template <> struct find_chamber<0, 3> { inline int operator ()(int i) const { return detail::chambers_zone_0_row_3[i]; } };
template <> struct find_chamber<0, 4> { inline int operator ()(int i) const { return detail::chambers_zone_0_row_4[i]; } };
template <> struct find_chamber<0, 5> { inline int operator ()(int i) const { return detail::chambers_zone_0_row_5[i]; } };
template <> struct find_chamber<0, 6> { inline int operator ()(int i) const { return detail::chambers_zone_0_row_6[i]; } };
template <> struct find_chamber<0, 7> { inline int operator ()(int i) const { return detail::chambers_zone_0_row_7_0[i]; } };
template <> struct find_chamber<0, 8> { inline int operator ()(int i) const { return detail::chambers_zone_0_row_7_1[i]; } };


// Given a segment with (emtf_phi, flags_zone, flags_tzone, and valid), set bit in zoning_out_row_k
template <int ZONE, int TIMEZONE=0>
void zoning_row_op(
    const emtf_phi_t emtf_phi_iseg,
    const flags_zone_t flags_zone_iseg,
    const flags_tzone_t flags_tzone_iseg,
    const valid_t valid_iseg,
    zoning_out_t& zoning_out_row_k
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

  static const emtf_phi_t coarse_emtf_strip = 8 * 2;  // 'doublestrip' unit; doublestrip = 2x full-strip unit in 10 deg chamber
  static const emtf_phi_t min_emtf_strip = 27 * coarse_emtf_strip;  // 7.2 deg
  static const emtf_phi_t max_emtf_strip = 315 * coarse_emtf_strip;  // 84 deg

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

// Loop over chambers and all the segments in the chambers
template <int ZONE, int ROW>
void zoning_chambers_op(
    const emtf_phi_t emtf_phi[N_MODEL_IN],
    const flags_zone_t flags_zone[N_MODEL_IN],
    const flags_tzone_t flags_tzone[N_MODEL_IN],
    const valid_t valid[N_MODEL_IN],
    zoning_out_t& zoning_out_row_k
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE region

  zoning_out_row_k = 0;  // initialize

  constexpr int N = find_num_chambers<ZONE, ROW>::value;
  auto find_chamber_op = find_chamber<ZONE, ROW>();

  for (int i = 0; i < N; i++) {

#pragma HLS UNROLL

    for (int j = 0; j < num_segments; j++) {
      const unsigned iseg = (find_chamber_op(i) * num_segments) + j;
      assert(iseg < N_MODEL_IN);
      zoning_row_op<ZONE>(emtf_phi[iseg], flags_zone[iseg], flags_tzone[iseg], valid[iseg], zoning_out_row_k);
    }
  }
}

// Zoning op customized for zone 0
template <int ZONE, typename enable_if<ZONE == 0, int>::type = 0>
void zoning_op(
    const emtf_phi_t emtf_phi[N_MODEL_IN],
    const flags_zone_t flags_zone[N_MODEL_IN],
    const flags_tzone_t flags_tzone[N_MODEL_IN],
    const valid_t valid[N_MODEL_IN],
    zoning_out_t zoning_out[N_ZONING_OUT]
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE region

  zoning_out_t zoning_out_tmp[find_num_rows<ZONE>::value];

#pragma HLS ARRAY_PARTITION variable=zoning_out_tmp complete dim=0

  // Loop over chambers-rows manually
  static_assert(find_num_rows<ZONE>::value == 9, "num_rows (zone 0) must be 9");

  zoning_chambers_op<ZONE, 0>(emtf_phi, flags_zone, flags_tzone, valid, zoning_out_tmp[0]);
  zoning_chambers_op<ZONE, 1>(emtf_phi, flags_zone, flags_tzone, valid, zoning_out_tmp[1]);
  zoning_chambers_op<ZONE, 2>(emtf_phi, flags_zone, flags_tzone, valid, zoning_out_tmp[2]);
  zoning_chambers_op<ZONE, 3>(emtf_phi, flags_zone, flags_tzone, valid, zoning_out_tmp[3]);
  zoning_chambers_op<ZONE, 4>(emtf_phi, flags_zone, flags_tzone, valid, zoning_out_tmp[4]);
  zoning_chambers_op<ZONE, 5>(emtf_phi, flags_zone, flags_tzone, valid, zoning_out_tmp[5]);
  zoning_chambers_op<ZONE, 6>(emtf_phi, flags_zone, flags_tzone, valid, zoning_out_tmp[6]);
  zoning_chambers_op<ZONE, 7>(emtf_phi, flags_zone, flags_tzone, valid, zoning_out_tmp[7]);
  zoning_chambers_op<ZONE, 8>(emtf_phi, flags_zone, flags_tzone, valid, zoning_out_tmp[8]);

  // Loop over rows manually
  static_assert(num_img_rows == 8, "num_img_rows must be 8");

  zoning_out[0] = zoning_out_tmp[0];
  zoning_out[1] = zoning_out_tmp[1];
  zoning_out[2] = zoning_out_tmp[2];
  zoning_out[3] = zoning_out_tmp[3];
  zoning_out[4] = zoning_out_tmp[4];
  zoning_out[5] = zoning_out_tmp[5];
  zoning_out[6] = zoning_out_tmp[6];
  zoning_out[7] = (zoning_out_tmp[7] | zoning_out_tmp[8]);
}


// _____________________________________________________________________________
// Entry point

template <int ZONE>
void zoning_layer(
    const emtf_phi_t emtf_phi[N_MODEL_IN],
    const flags_zone_t flags_zone[N_MODEL_IN],
    const flags_tzone_t flags_tzone[N_MODEL_IN],
    const valid_t valid[N_MODEL_IN],
    zoning_out_t zoning_out[N_ZONING_OUT]
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

  zoning_op<ZONE>(emtf_phi, flags_zone, flags_tzone, valid, zoning_out);
}

}  // namespace emtf

#endif  // __EMTF_HLSLIB_ZONING_H__ not defined
