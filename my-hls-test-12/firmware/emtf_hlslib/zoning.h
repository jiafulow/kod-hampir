#ifndef __EMTF_HLSLIB_ZONING_H__
#define __EMTF_HLSLIB_ZONING_H__

namespace emtf {

namespace detail {

constexpr static const int zoning_col_start = 27;
constexpr static const int zoning_col_stop = 315;

constexpr static const int chtype_10deg = 0;
constexpr static const int chtype_20deg = 1;

constexpr static const int chambers_10deg_bw = 52;        // 13.8667 deg
constexpr static const int chambers_20deg_bw = 90;        // 24 deg
constexpr static const int chambers_70deg_bw = 315 - 38;  // 73.8667 deg
constexpr static const int chambers_80deg_bw = 315;       // 84 deg

// ph_init reference values:
// [0, 38, 75, 113, 150, 188, 225, 263] -> [0.0, 10.1333, 20.0, 30.1333, 40.0, 50.1333, 60.0, 70.1333] deg
constexpr static const int chambers_10deg_ph_init[7] = {75, 113, 150, 188, 225, 263, 38};
constexpr static const int chambers_20deg_ph_init[4] = {75, 150, 225, 0};

// Zone 0 - 45 chambers
constexpr static const int chambers_zone_0_row_0[7]   = {108, 109, 110, 111, 112, 113, 114};  // ME0
constexpr static const int chambers_zone_0_row_1[7]   = { 54,  55,  56,  63,  64,  65,  99};  // GE1/1
constexpr static const int chambers_zone_0_row_2[7]   = {  0,   1,   2,   9,  10,  11,  45};  // ME1/1
constexpr static const int chambers_zone_0_row_3[4]   = { 72,  73,  74, 102};  // GE2/1
constexpr static const int chambers_zone_0_row_4[4]   = { 18,  19,  20,  48};  // ME2/1
constexpr static const int chambers_zone_0_row_5[4]   = { 27,  28,  29,  50};  // ME3/1
constexpr static const int chambers_zone_0_row_6[4]   = { 81,  82,  83, 104};  // RE3/1
constexpr static const int chambers_zone_0_row_7_0[4] = { 36,  37,  38,  52};  // ME4/1
constexpr static const int chambers_zone_0_row_7_1[4] = { 90,  91,  92, 106};  // RE4/1

}  // namespace detail

template <int ZONE>
struct find_zoning_num_rows {};

template <> struct find_zoning_num_rows<0> { static const int value = 1 + 1 + 1 + 1 + 1 + 1 + 1 + 2; };

template <int ZONE, int ROW>
struct chamber_type_traits {};

template <> struct chamber_type_traits<0, 0> { static const int value = detail::chtype_10deg; };
template <> struct chamber_type_traits<0, 1> { static const int value = detail::chtype_10deg; };
template <> struct chamber_type_traits<0, 2> { static const int value = detail::chtype_10deg; };
template <> struct chamber_type_traits<0, 3> { static const int value = detail::chtype_20deg; };
template <> struct chamber_type_traits<0, 4> { static const int value = detail::chtype_20deg; };
template <> struct chamber_type_traits<0, 5> { static const int value = detail::chtype_20deg; };
template <> struct chamber_type_traits<0, 6> { static const int value = detail::chtype_20deg; };
template <> struct chamber_type_traits<0, 7> { static const int value = detail::chtype_20deg; };
template <> struct chamber_type_traits<0, 8> { static const int value = detail::chtype_20deg; };

template <int ZONE, int ROW>
struct find_zoning_chamber {};

template <> struct find_zoning_chamber<0, 0> { inline int operator ()(int i) const { return detail::chambers_zone_0_row_0[i]; } };
template <> struct find_zoning_chamber<0, 1> { inline int operator ()(int i) const { return detail::chambers_zone_0_row_1[i]; } };
template <> struct find_zoning_chamber<0, 2> { inline int operator ()(int i) const { return detail::chambers_zone_0_row_2[i]; } };
template <> struct find_zoning_chamber<0, 3> { inline int operator ()(int i) const { return detail::chambers_zone_0_row_3[i]; } };
template <> struct find_zoning_chamber<0, 4> { inline int operator ()(int i) const { return detail::chambers_zone_0_row_4[i]; } };
template <> struct find_zoning_chamber<0, 5> { inline int operator ()(int i) const { return detail::chambers_zone_0_row_5[i]; } };
template <> struct find_zoning_chamber<0, 6> { inline int operator ()(int i) const { return detail::chambers_zone_0_row_6[i]; } };
template <> struct find_zoning_chamber<0, 7> { inline int operator ()(int i) const { return detail::chambers_zone_0_row_7_0[i]; } };
template <> struct find_zoning_chamber<0, 8> { inline int operator ()(int i) const { return detail::chambers_zone_0_row_7_1[i]; } };

template <int ZONE, int ROW>
struct find_zoning_ph_init {};

template <> struct find_zoning_ph_init<0, 0> { inline int operator ()(int i) const { return detail::chambers_10deg_ph_init[i]; } };
template <> struct find_zoning_ph_init<0, 1> { inline int operator ()(int i) const { return detail::chambers_10deg_ph_init[i]; } };
template <> struct find_zoning_ph_init<0, 2> { inline int operator ()(int i) const { return detail::chambers_10deg_ph_init[i]; } };
template <> struct find_zoning_ph_init<0, 3> { inline int operator ()(int i) const { return detail::chambers_20deg_ph_init[i]; } };
template <> struct find_zoning_ph_init<0, 4> { inline int operator ()(int i) const { return detail::chambers_20deg_ph_init[i]; } };
template <> struct find_zoning_ph_init<0, 5> { inline int operator ()(int i) const { return detail::chambers_20deg_ph_init[i]; } };
template <> struct find_zoning_ph_init<0, 6> { inline int operator ()(int i) const { return detail::chambers_20deg_ph_init[i]; } };
template <> struct find_zoning_ph_init<0, 7> { inline int operator ()(int i) const { return detail::chambers_20deg_ph_init[i]; } };
template <> struct find_zoning_ph_init<0, 8> { inline int operator ()(int i) const { return detail::chambers_20deg_ph_init[i]; } };


// Loop over chambers and all the segments in the chambers
template <int ZONE, int ROW>
void zoning_chambers_op(
    const emtf_phi_t emtf_phi[N_ZONING_IN],
    const flags_zone_t flags_zone[N_ZONING_IN],
    const flags_tzone_t flags_tzone[N_ZONING_IN],
    const valid_t valid[N_ZONING_IN],
    zoning_out_t& zoning_out_row_k
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

  zoning_out_row_k = 0;  // initialize

  auto find_chamber_op = find_zoning_chamber<ZONE, ROW>();
  auto find_chamber_ph_init = find_zoning_ph_init<ZONE, ROW>();

  constexpr int TIMEZONE = 0;
  constexpr int CHTYPE = chamber_type_traits<ZONE, ROW>::value;
  constexpr bool is_10deg = (CHTYPE == detail::chtype_10deg);

  constexpr int N = is_10deg ? 7 : 4;  // num of chambers in this row
  constexpr int chambers_img_joined_bw = is_10deg ? detail::chambers_70deg_bw : detail::chambers_80deg_bw;
  constexpr int chambers_img_bw = is_10deg ? detail::chambers_10deg_bw : detail::chambers_20deg_bw;
  typedef ap_uint<chambers_img_joined_bw> chambers_img_joined_t;
  typedef ap_uint<chambers_img_bw> chambers_img_t;

  chambers_img_joined_t chamber_img_joined;
  chambers_img_t chamber_img;

  chamber_img_joined = 0;  // initialize

  for (int i = 0; i < N; i++) {

#pragma HLS UNROLL

    chamber_img = 0;  // initialize

    for (int j = 0; j < num_segments; j++) {
      const unsigned iseg = (find_chamber_op(i) * num_segments) + j;
      assert(iseg < N_ZONING_IN);

      if (
          (valid[iseg] == 1) and \
          (flags_zone[iseg][2-ZONE] == 1) and \
          (flags_tzone[iseg][2-TIMEZONE] == 1)
      ) {
        // truncate last 4 bits (i.e. divide by 16), subtract offset
        assert((emtf_phi[iseg] >> 4) >= find_chamber_ph_init(i));
        zoning_col_t col = (emtf_phi[iseg] >> 4) - find_chamber_ph_init(i);

        chamber_img[col] = 1;
      }
    }  // end loop over segments

    zoning_col_t col_start = find_chamber_ph_init(i) - find_chamber_ph_init(N-1);
    zoning_col_t col_stop = col_start + chambers_img_bw - 1;

    //std::cout << "[DEBUG] " << col_start << " " << col_stop << std::endl;

    chamber_img_joined.range(col_stop, col_start) = chamber_img;
  }  // end loop over chambers

  assert(is_10deg ? (find_chamber_ph_init(N-1) >= detail::zoning_col_start) : (find_chamber_ph_init(N-1) < detail::zoning_col_start));
  zoning_col_t col_start_rhs = is_10deg ? 0 : detail::zoning_col_start;
  zoning_col_t col_stop_rhs = chambers_img_joined_bw - 1;
  zoning_col_t col_start_lhs = is_10deg ? find_chamber_ph_init(N-1) - detail::zoning_col_start : 0;
  zoning_col_t col_stop_lhs = col_start_lhs + (col_stop_rhs - col_start_rhs);

  //std::cout << "[DEBUG] " << col_start_lhs << " " << col_stop_lhs << " " << col_start_rhs << " " << col_stop_rhs << std::endl;

  zoning_out_row_k.range(col_stop_lhs, col_start_lhs) = chamber_img_joined.range(col_stop_rhs, col_start_rhs);
}

// Zoning op customized for zone 0
template <int ZONE, typename enable_if<ZONE == 0, int>::type = 0>
void zoning_op(
    const emtf_phi_t emtf_phi[N_ZONING_IN],
    const flags_zone_t flags_zone[N_ZONING_IN],
    const flags_tzone_t flags_tzone[N_ZONING_IN],
    const valid_t valid[N_ZONING_IN],
    zoning_out_t zoning_out[N_ZONING_OUT]
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE region

  zoning_out_t zoning_out_tmp[find_zoning_num_rows<ZONE>::value];

#pragma HLS ARRAY_PARTITION variable=zoning_out_tmp complete dim=0

  // Check assumptions
  static_assert(N_ZONING_IN == num_chambers * num_segments, "N_ZONING_IN check failed");
  static_assert(N_ZONING_OUT == num_img_rows, "N_ZONING_OUT check failed");

  // Loop over chambers-rows manually
  static_assert(find_zoning_num_rows<ZONE>::value == 9, "num_rows (zone 0) must be 9");

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
    const emtf_phi_t emtf_phi[N_ZONING_IN],
    const flags_zone_t flags_zone[N_ZONING_IN],
    const flags_tzone_t flags_tzone[N_ZONING_IN],
    const valid_t valid[N_ZONING_IN],
    zoning_out_t zoning_out[N_ZONING_OUT]
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE region

  zoning_op<ZONE>(emtf_phi, flags_zone, flags_tzone, valid, zoning_out);
}

}  // namespace emtf

#endif  // __EMTF_HLSLIB_ZONING_H__ not defined
