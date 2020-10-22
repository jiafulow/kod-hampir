#ifndef __EMTF_HLSLIB_ZONING_H__
#define __EMTF_HLSLIB_ZONING_H__

namespace emtf {

namespace detail {

constexpr static const int chamber_10deg_chtype = 0;  // chamber type
constexpr static const int chamber_20deg_chtype = 1;
constexpr static const int chamber_20deg_ext_chtype = 2;

constexpr static const int chamber_10deg_nch = 7;  // num of chambers
constexpr static const int chamber_20deg_nch = 4;
constexpr static const int chamber_20deg_ext_nch = 11;

constexpr static const int chamber_img_bw = 90;          // 24 deg
constexpr static const int chamber_img_joined_bw = 315;  // 84 deg

// Full endcap region: 12 rows, 101 chambers
// Note: ME1/3 and RE1/3 are not included as they belong to the overlap region
constexpr static const int chambers_endcap_row_0[7]    = {  0,   1,   2,   9,  10,  11,  45};  // ME1/1
constexpr static const int chambers_endcap_row_1[7]    = {  3,   4,   5,  12,  13,  14,  46};  // ME1/2
constexpr static const int chambers_endcap_row_2[11]   = { 18,  19,  20,  48,  21,  22,  23,  24,  25,  26,  49};  // ME2/1 + ME2/2
constexpr static const int chambers_endcap_row_3[11]   = { 27,  28,  29,  50,  30,  31,  32,  33,  34,  35,  51};  // ME3/1 + ME3/2
constexpr static const int chambers_endcap_row_4[11]   = { 36,  37,  38,  52,  39,  40,  41,  42,  43,  44,  53};  // ME4/1 + ME4/2
constexpr static const int chambers_endcap_row_5[7]    = { 57,  58,  59,  66,  67,  68, 100};  // RE1/2
constexpr static const int chambers_endcap_row_6[7]    = { 75,  76,  77,  78,  79,  80, 103};  // RE2/2
constexpr static const int chambers_endcap_row_7[11]   = { 81,  82,  83, 104,  84,  85,  86,  87,  88,  89, 105};  // RE3/1 + RE3/2
constexpr static const int chambers_endcap_row_8[11]   = { 90,  91,  92, 106,  93,  94,  95,  96,  97,  98, 107};  // RE4/1 + RE4/2
constexpr static const int chambers_endcap_row_9[7]    = { 54,  55,  56,  63,  64,  65,  99};  // GE1/1
constexpr static const int chambers_endcap_row_10[4]   = { 72,  73,  74, 102};  // GE2/1
constexpr static const int chambers_endcap_row_11[7]   = {108, 109, 110, 111, 112, 113, 114};  // ME0

// Zone 0: 9 rows, 45 chambers
constexpr static const int chambers_zone_0_row_0[7]    = {108, 109, 110, 111, 112, 113, 114};  // ME0
constexpr static const int chambers_zone_0_row_1[7]    = { 54,  55,  56,  63,  64,  65,  99};  // GE1/1
constexpr static const int chambers_zone_0_row_2[7]    = {  0,   1,   2,   9,  10,  11,  45};  // ME1/1
constexpr static const int chambers_zone_0_row_3[4]    = { 72,  73,  74, 102};  // GE2/1
constexpr static const int chambers_zone_0_row_4[4]    = { 18,  19,  20,  48};  // ME2/1
constexpr static const int chambers_zone_0_row_5[4]    = { 27,  28,  29,  50};  // ME3/1
constexpr static const int chambers_zone_0_row_6[4]    = { 81,  82,  83, 104};  // RE3/1
constexpr static const int chambers_zone_0_row_7_0[4]  = { 36,  37,  38,  52};  // ME4/1
constexpr static const int chambers_zone_0_row_7_1[4]  = { 90,  91,  92, 106};  // RE4/1

// Zone 1: 14 rows, 80 chambers
constexpr static const int chambers_zone_1_row_0[7]    = { 54,  55,  56,  63,  64,  65,  99};  // GE1/1
constexpr static const int chambers_zone_1_row_1[7]    = {  0,   1,   2,   9,  10,  11,  45};  // ME1/1
constexpr static const int chambers_zone_1_row_2_0[7]  = {  3,   4,   5,  12,  13,  14,  46};  // ME1/2
constexpr static const int chambers_zone_1_row_2_1[7]  = { 57,  58,  59,  66,  67,  68, 100};  // RE1/2
constexpr static const int chambers_zone_1_row_3[4]    = { 72,  73,  74, 102};  // GE2/1
constexpr static const int chambers_zone_1_row_4[4]    = { 18,  19,  20,  48};  // ME2/1
constexpr static const int chambers_zone_1_row_5[11]   = { 27,  28,  29,  50,  30,  31,  32,  33,  34,  35,  51};  // ME3/1 + ME3/2
constexpr static const int chambers_zone_1_row_6[11]   = { 81,  82,  83, 104,  84,  85,  86,  87,  88,  89, 105};  // RE3/1 + RE3/2
constexpr static const int chambers_zone_1_row_7_0[11] = { 36,  37,  38,  52,  39,  40,  41,  42,  43,  44,  53};  // ME4/1 + ME4/2
constexpr static const int chambers_zone_1_row_7_1[11] = { 90,  91,  92, 106,  93,  94,  95,  96,  97,  98, 107};  // RE4/1 + RE4/2

// Zone 2: 8 rows, 56 chambers
constexpr static const int chambers_zone_2_row_0[7]    = {  3,   4,   5,  12,  13,  14,  46};  // ME1/2
constexpr static const int chambers_zone_2_row_1[7]    = { 57,  58,  59,  66,  67,  68, 100};  // RE1/2
constexpr static const int chambers_zone_2_row_2[7]    = { 75,  76,  77,  78,  79,  80, 103};  // RE2/2
constexpr static const int chambers_zone_2_row_3[7]    = { 21,  22,  23,  24,  25,  26,  49};  // ME2/2
constexpr static const int chambers_zone_2_row_4[7]    = { 30,  31,  32,  33,  34,  35,  51};  // ME3/2
constexpr static const int chambers_zone_2_row_5[7]    = { 84,  85,  86,  87,  88,  89, 105};  // RE3/2
constexpr static const int chambers_zone_2_row_6[7]    = { 39,  40,  41,  42,  43,  44,  53};  // ME4/2
constexpr static const int chambers_zone_2_row_7[7]    = { 93,  94,  95,  96,  97,  98, 107};  // RE4/2

// ph_init reference values:
// [0, 38, 75, 113, 150, 188, 225, 263] -> [0.0, 10.1333, 20.0, 30.1333, 40.0, 50.1333, 60.0, 70.1333] deg
constexpr static const int chambers_10deg_ph_init[7]       = { 75, 113, 150, 188, 225, 263,  38};
constexpr static const int chambers_20deg_ph_init[4]       = { 75, 150, 225,   0};
constexpr static const int chambers_20deg_ext_ph_init[11]  = { 75, 150, 225,   0,  75, 113, 150, 188, 225, 263,  38};

// ph_cover reference values:
// [52, 90, 127, 165, 202, 240, 277, 315] -> [13.8667, 24.0, 33.8667, 44.0, 53.8667, 64.0, 73.8667, 84.0] deg
constexpr static const int chambers_10deg_ph_cover[7]      = {127, 165, 202, 240, 277, 315,  90};
constexpr static const int chambers_20deg_ph_cover[4]      = {165, 240, 315,  90};
constexpr static const int chambers_20deg_ext_ph_cover[11] = {165, 240, 315,  90, 127, 165, 202, 240, 277, 315,  90};

constexpr static const int chamber_288unit_ph_init = chamber_img_joined_bw - 288; // 27; 7.2 deg
constexpr static const int chamber_288unit_ph_cover = chamber_img_joined_bw;      // 315; 84 deg

}  // namespace detail


struct zoning_base_chamber_traits {
  static const int chamber_img_bw = detail::chamber_img_bw;
  static const int chamber_img_joined_bw = detail::chamber_img_joined_bw;
  static const int chamber_img_joined_col_start = detail::chamber_288unit_ph_init;
  static const int chamber_img_joined_col_stop = (chamber_img_joined_bw - 1);
  typedef ap_uint<chamber_img_bw> chamber_img_t;
  typedef ap_uint<chamber_img_joined_bw> chamber_img_joined_t;
};

struct zoning_10deg_chamber_traits : zoning_base_chamber_traits {
  static const int chtype = detail::chamber_10deg_chtype;
  static const int nch = detail::chamber_10deg_nch;
};

struct zoning_20deg_chamber_traits : zoning_base_chamber_traits {
  static const int chtype = detail::chamber_20deg_chtype;
  static const int nch = detail::chamber_20deg_nch;
};

struct zoning_20deg_ext_chamber_traits : zoning_base_chamber_traits {
  static const int chtype = detail::chamber_20deg_ext_chtype;
  static const int nch = detail::chamber_20deg_ext_nch;
};

template <int ZONE>
struct zoning_num_rows_traits {};

template <> struct zoning_num_rows_traits<0> { static const int value = 1 + 1 + 1 + 1 + 1 + 1 + 1 + 2; };
template <> struct zoning_num_rows_traits<1> { static const int value = 1 + 1 + 2 + 1 + 1 + 1 + 1 + 2; };
template <> struct zoning_num_rows_traits<2> { static const int value = 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1; };

template <int ZONE, int ROW>
struct zoning_row_traits {};

template <> struct zoning_row_traits<0, 0> : zoning_10deg_chamber_traits {};
template <> struct zoning_row_traits<0, 1> : zoning_10deg_chamber_traits {};
template <> struct zoning_row_traits<0, 2> : zoning_10deg_chamber_traits {};
template <> struct zoning_row_traits<0, 3> : zoning_20deg_chamber_traits {};
template <> struct zoning_row_traits<0, 4> : zoning_20deg_chamber_traits {};
template <> struct zoning_row_traits<0, 5> : zoning_20deg_chamber_traits {};
template <> struct zoning_row_traits<0, 6> : zoning_20deg_chamber_traits {};
template <> struct zoning_row_traits<0, 7> : zoning_20deg_chamber_traits {};
template <> struct zoning_row_traits<0, 8> : zoning_20deg_chamber_traits {};

template <> struct zoning_row_traits<1, 0> : zoning_10deg_chamber_traits {};
template <> struct zoning_row_traits<1, 1> : zoning_10deg_chamber_traits {};
template <> struct zoning_row_traits<1, 2> : zoning_10deg_chamber_traits {};
template <> struct zoning_row_traits<1, 3> : zoning_10deg_chamber_traits {};
template <> struct zoning_row_traits<1, 4> : zoning_20deg_chamber_traits {};
template <> struct zoning_row_traits<1, 5> : zoning_20deg_chamber_traits {};
template <> struct zoning_row_traits<1, 6> : zoning_20deg_ext_chamber_traits {};
template <> struct zoning_row_traits<1, 7> : zoning_20deg_ext_chamber_traits {};
template <> struct zoning_row_traits<1, 8> : zoning_20deg_ext_chamber_traits {};
template <> struct zoning_row_traits<1, 9> : zoning_20deg_ext_chamber_traits {};

template <> struct zoning_row_traits<2, 0> : zoning_10deg_chamber_traits {};
template <> struct zoning_row_traits<2, 1> : zoning_10deg_chamber_traits {};
template <> struct zoning_row_traits<2, 2> : zoning_10deg_chamber_traits {};
template <> struct zoning_row_traits<2, 3> : zoning_10deg_chamber_traits {};
template <> struct zoning_row_traits<2, 4> : zoning_10deg_chamber_traits {};
template <> struct zoning_row_traits<2, 5> : zoning_10deg_chamber_traits {};
template <> struct zoning_row_traits<2, 6> : zoning_10deg_chamber_traits {};
template <> struct zoning_row_traits<2, 7> : zoning_10deg_chamber_traits {};

template <int ZONE, int ROW>
struct zoning_get_chamber_op {};

template <> struct zoning_get_chamber_op<0, 0> { inline int operator ()(int i) const { return detail::chambers_zone_0_row_0[i]; } };
template <> struct zoning_get_chamber_op<0, 1> { inline int operator ()(int i) const { return detail::chambers_zone_0_row_1[i]; } };
template <> struct zoning_get_chamber_op<0, 2> { inline int operator ()(int i) const { return detail::chambers_zone_0_row_2[i]; } };
template <> struct zoning_get_chamber_op<0, 3> { inline int operator ()(int i) const { return detail::chambers_zone_0_row_3[i]; } };
template <> struct zoning_get_chamber_op<0, 4> { inline int operator ()(int i) const { return detail::chambers_zone_0_row_4[i]; } };
template <> struct zoning_get_chamber_op<0, 5> { inline int operator ()(int i) const { return detail::chambers_zone_0_row_5[i]; } };
template <> struct zoning_get_chamber_op<0, 6> { inline int operator ()(int i) const { return detail::chambers_zone_0_row_6[i]; } };
template <> struct zoning_get_chamber_op<0, 7> { inline int operator ()(int i) const { return detail::chambers_zone_0_row_7_0[i]; } };
template <> struct zoning_get_chamber_op<0, 8> { inline int operator ()(int i) const { return detail::chambers_zone_0_row_7_1[i]; } };

template <> struct zoning_get_chamber_op<1, 0> { inline int operator ()(int i) const { return detail::chambers_zone_1_row_0[i]; } };
template <> struct zoning_get_chamber_op<1, 1> { inline int operator ()(int i) const { return detail::chambers_zone_1_row_1[i]; } };
template <> struct zoning_get_chamber_op<1, 2> { inline int operator ()(int i) const { return detail::chambers_zone_1_row_2_0[i]; } };
template <> struct zoning_get_chamber_op<1, 3> { inline int operator ()(int i) const { return detail::chambers_zone_1_row_2_1[i]; } };
template <> struct zoning_get_chamber_op<1, 4> { inline int operator ()(int i) const { return detail::chambers_zone_1_row_3[i]; } };
template <> struct zoning_get_chamber_op<1, 5> { inline int operator ()(int i) const { return detail::chambers_zone_1_row_4[i]; } };
template <> struct zoning_get_chamber_op<1, 6> { inline int operator ()(int i) const { return detail::chambers_zone_1_row_5[i]; } };
template <> struct zoning_get_chamber_op<1, 7> { inline int operator ()(int i) const { return detail::chambers_zone_1_row_6[i]; } };
template <> struct zoning_get_chamber_op<1, 8> { inline int operator ()(int i) const { return detail::chambers_zone_1_row_7_0[i]; } };
template <> struct zoning_get_chamber_op<1, 9> { inline int operator ()(int i) const { return detail::chambers_zone_1_row_7_1[i]; } };

template <> struct zoning_get_chamber_op<2, 0> { inline int operator ()(int i) const { return detail::chambers_zone_2_row_0[i]; } };
template <> struct zoning_get_chamber_op<2, 1> { inline int operator ()(int i) const { return detail::chambers_zone_2_row_1[i]; } };
template <> struct zoning_get_chamber_op<2, 2> { inline int operator ()(int i) const { return detail::chambers_zone_2_row_2[i]; } };
template <> struct zoning_get_chamber_op<2, 3> { inline int operator ()(int i) const { return detail::chambers_zone_2_row_3[i]; } };
template <> struct zoning_get_chamber_op<2, 4> { inline int operator ()(int i) const { return detail::chambers_zone_2_row_4[i]; } };
template <> struct zoning_get_chamber_op<2, 5> { inline int operator ()(int i) const { return detail::chambers_zone_2_row_5[i]; } };
template <> struct zoning_get_chamber_op<2, 6> { inline int operator ()(int i) const { return detail::chambers_zone_2_row_6[i]; } };
template <> struct zoning_get_chamber_op<2, 7> { inline int operator ()(int i) const { return detail::chambers_zone_2_row_7[i]; } };

template <int CHTYPE>
struct zoning_get_ph_init_op {};

template <> struct zoning_get_ph_init_op<0> { inline int operator ()(int i) const { return detail::chambers_10deg_ph_init[i]; } };
template <> struct zoning_get_ph_init_op<1> { inline int operator ()(int i) const { return detail::chambers_20deg_ph_init[i]; } };
template <> struct zoning_get_ph_init_op<2> { inline int operator ()(int i) const { return detail::chambers_20deg_ext_ph_init[i]; } };

template <int CHTYPE>
struct zoning_get_ph_cover_op {};

template <> struct zoning_get_ph_cover_op<0> { inline int operator ()(int i) const { return detail::chambers_10deg_ph_cover[i]; } };
template <> struct zoning_get_ph_cover_op<1> { inline int operator ()(int i) const { return detail::chambers_20deg_ph_cover[i]; } };
template <> struct zoning_get_ph_cover_op<2> { inline int operator ()(int i) const { return detail::chambers_20deg_ext_ph_cover[i]; } };

// Function to init table
template <typename T, int N, class U>
void zoning_init_table(T (&arr)[N], U op) {
  for (int i = 0; i < N; i++) {
    arr[i] = op(i);
  }
}


// _____________________________________________________________________________
// Perform loop over chambers and all the segments in the chambers

template <int ZONE, int ROW>
void zoning_row_op(
    const emtf_phi_t emtf_phi[N_MODEL_IN],
    const flags_zone_t flags_zone[N_MODEL_IN],
    const flags_tzone_t flags_tzone[N_MODEL_IN],
    const valid_t valid[N_MODEL_IN],
    zoning_out_t& zoning_out_row_k
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE region

  constexpr int TIMEZONE = 1;
  constexpr int CHTYPE = zoning_row_traits<ZONE, ROW>::chtype;
  constexpr int N = zoning_row_traits<ZONE, ROW>::nch;
  typedef typename zoning_row_traits<ZONE, ROW>::chamber_img_t chamber_img_t;
  typedef typename zoning_row_traits<ZONE, ROW>::chamber_img_joined_t chamber_img_joined_t;

  int chambers[N];
  zoning_init_table(chambers, zoning_get_chamber_op<ZONE, ROW>());

  int chambers_ph_init[N];
  zoning_init_table(chambers_ph_init, zoning_get_ph_init_op<CHTYPE>());

  int chambers_ph_cover[N];
  zoning_init_table(chambers_ph_cover, zoning_get_ph_cover_op<CHTYPE>());

  chamber_img_joined_t chamber_img_joined = 0;

  // Loop over chambers
  for (int i = 0; i < N; i++) {

#pragma HLS UNROLL

    //std::cout << "[DEBUG] z " << ZONE << " r " << ROW << " chamber: " << chambers[i] << " ph_init: " << chambers_ph_init[i] << std::endl;

    chamber_img_t chamber_img = 0;

    // Loop over segments
    for (int j = 0; j < num_segments; j++) {

#pragma HLS UNROLL

      const zoning_seg_t iseg = (chambers[i] * num_segments) + j;
      assert(chambers[i] < num_chambers);
      assert(iseg < N_MODEL_IN);

      // Fill the chamber image. A pixel at (row, col) is set to 1 if a segment is present.
      // Use condition: (valid && is_same_zone && is_same_timezone)
      if (
          (valid[iseg] == 1) and \
          (flags_zone[iseg][2-ZONE] == 1) and \
          (flags_tzone[iseg][2-TIMEZONE] == 1)
      ) {
        // truncate last 4 bits (i.e. divide by 16), subtract offset
        assert((emtf_phi[iseg] >> 4) >= chambers_ph_init[i]);
        const zoning_col_t offset = chambers_ph_init[i];
        const zoning_col_t col = (emtf_phi[iseg] >> 4) - offset;

        //std::cout << "[DEBUG] chamber: " << chambers[i] << " segment: " << j << " emtf_phi: " << emtf_phi[iseg] << " col: " << col << " offset: " << offset << std::endl;

        chamber_img.set(col, 1);  // set bit to 1
      }
    }  // end loop over segments

    // Join chamber images
    const zoning_col_t col_start_rhs = 0;
    const zoning_col_t col_stop_rhs = (chambers_ph_cover[i] - chambers_ph_init[i]) - 1;
    const zoning_col_t col_start_lhs = chambers_ph_init[i];
    const zoning_col_t col_stop_lhs = col_start_lhs + col_stop_rhs - col_start_rhs;

    //std::cout << "[DEBUG] start_l: " << col_start_lhs << " stop_l: " << col_stop_lhs << " start_r: " << col_start_rhs << " stop_r: " << col_stop_rhs << std::endl;

    // OR combined
    assert((col_stop_lhs - col_start_lhs) == (col_stop_rhs - col_start_rhs));
    chamber_img_joined.range(col_stop_lhs, col_start_lhs) = (
        chamber_img_joined.range(col_stop_lhs, col_start_lhs) |
        chamber_img.range(col_stop_rhs, col_start_rhs)
    );
  }  // end loop over chambers

  zoning_out_row_k = 0;  // initialize to zero

  // Adjust the size of chamber_img_joined
  const zoning_col_t col_start_rhs = zoning_row_traits<ZONE, ROW>::chamber_img_joined_col_start;
  const zoning_col_t col_stop_rhs = zoning_row_traits<ZONE, ROW>::chamber_img_joined_col_stop;
  const zoning_col_t col_start_lhs = 0;
  const zoning_col_t col_stop_lhs = (zoning_out_t::width - 1);

  //std::cout << "[DEBUG] start_l: " << col_start_lhs << " stop_l: " << col_stop_lhs << " start_r: " << col_start_rhs << " stop_r: " << col_stop_rhs << std::endl;

  assert((col_stop_lhs - col_start_lhs) == (col_stop_rhs - col_start_rhs));
  zoning_out_row_k = chamber_img_joined.range(col_stop_rhs, col_start_rhs);
}


// _____________________________________________________________________________
// Zoning op

// Customized for Zone 0
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

  zoning_out_t zoning_out_row_7_0;
  zoning_out_t zoning_out_row_7_1;

  // Loop over chamber_rows manually
  zoning_row_op<ZONE, 0>(emtf_phi, flags_zone, flags_tzone, valid, zoning_out[0]);
  zoning_row_op<ZONE, 1>(emtf_phi, flags_zone, flags_tzone, valid, zoning_out[1]);
  zoning_row_op<ZONE, 2>(emtf_phi, flags_zone, flags_tzone, valid, zoning_out[2]);
  zoning_row_op<ZONE, 3>(emtf_phi, flags_zone, flags_tzone, valid, zoning_out[3]);
  zoning_row_op<ZONE, 4>(emtf_phi, flags_zone, flags_tzone, valid, zoning_out[4]);
  zoning_row_op<ZONE, 5>(emtf_phi, flags_zone, flags_tzone, valid, zoning_out[5]);
  zoning_row_op<ZONE, 6>(emtf_phi, flags_zone, flags_tzone, valid, zoning_out[6]);
  zoning_row_op<ZONE, 7>(emtf_phi, flags_zone, flags_tzone, valid, zoning_out_row_7_0);
  zoning_row_op<ZONE, 8>(emtf_phi, flags_zone, flags_tzone, valid, zoning_out_row_7_1);

  // Combine certain rows
  zoning_out[7] = (zoning_out_row_7_0 | zoning_out_row_7_1);
}

// Customized for Zone 1
template <int ZONE, typename enable_if<ZONE == 1, int>::type = 0>
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

  zoning_out_t zoning_out_row_2_0;
  zoning_out_t zoning_out_row_2_1;
  zoning_out_t zoning_out_row_7_0;
  zoning_out_t zoning_out_row_7_1;

  // Loop over the rows manually
  zoning_row_op<ZONE, 0>(emtf_phi, flags_zone, flags_tzone, valid, zoning_out[0]);
  zoning_row_op<ZONE, 1>(emtf_phi, flags_zone, flags_tzone, valid, zoning_out[1]);
  zoning_row_op<ZONE, 2>(emtf_phi, flags_zone, flags_tzone, valid, zoning_out_row_2_0);
  zoning_row_op<ZONE, 3>(emtf_phi, flags_zone, flags_tzone, valid, zoning_out_row_2_1);
  zoning_row_op<ZONE, 4>(emtf_phi, flags_zone, flags_tzone, valid, zoning_out[3]);
  zoning_row_op<ZONE, 5>(emtf_phi, flags_zone, flags_tzone, valid, zoning_out[4]);
  zoning_row_op<ZONE, 6>(emtf_phi, flags_zone, flags_tzone, valid, zoning_out[5]);
  zoning_row_op<ZONE, 7>(emtf_phi, flags_zone, flags_tzone, valid, zoning_out[6]);
  zoning_row_op<ZONE, 8>(emtf_phi, flags_zone, flags_tzone, valid, zoning_out_row_7_0);
  zoning_row_op<ZONE, 9>(emtf_phi, flags_zone, flags_tzone, valid, zoning_out_row_7_1);

  // Combine certain rows
  zoning_out[2] = (zoning_out_row_2_0 | zoning_out_row_2_1);
  zoning_out[7] = (zoning_out_row_7_0 | zoning_out_row_7_1);
}

// Customized for Zone 2
template <int ZONE, typename enable_if<ZONE == 2, int>::type = 0>
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

  // Loop over chamber_rows manually
  zoning_row_op<ZONE, 0>(emtf_phi, flags_zone, flags_tzone, valid, zoning_out[0]);
  zoning_row_op<ZONE, 1>(emtf_phi, flags_zone, flags_tzone, valid, zoning_out[1]);
  zoning_row_op<ZONE, 2>(emtf_phi, flags_zone, flags_tzone, valid, zoning_out[2]);
  zoning_row_op<ZONE, 3>(emtf_phi, flags_zone, flags_tzone, valid, zoning_out[3]);
  zoning_row_op<ZONE, 4>(emtf_phi, flags_zone, flags_tzone, valid, zoning_out[4]);
  zoning_row_op<ZONE, 5>(emtf_phi, flags_zone, flags_tzone, valid, zoning_out[5]);
  zoning_row_op<ZONE, 6>(emtf_phi, flags_zone, flags_tzone, valid, zoning_out[6]);
  zoning_row_op<ZONE, 7>(emtf_phi, flags_zone, flags_tzone, valid, zoning_out[7]);
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

#pragma HLS INLINE region

  // Check assumptions
  static_assert(N_ZONING_OUT == num_img_rows, "N_ZONING_OUT check failed");
  static_assert(num_img_rows == 8, "num_img_rows must be 8");
  static_assert(num_img_cols == 288, "num_img_cols must be 288");
  static_assert(zoning_num_rows_traits<0>::value == 9, "num_rows (zone 0) must be 9");
  static_assert(zoning_num_rows_traits<1>::value == 10, "num_rows (zone 1) must be 10");
  static_assert(zoning_num_rows_traits<2>::value == 8, "num_rows (zone 2) must be 8");

  zoning_op<ZONE>(emtf_phi, flags_zone, flags_tzone, valid, zoning_out);
}

}  // namespace emtf

#endif  // __EMTF_HLSLIB_ZONING_H__ not defined
