#ifndef __EMTF_HLSLIB_TRKBUILDING_H__
#define __EMTF_HLSLIB_TRKBUILDING_H__

namespace emtf {

namespace detail {

constexpr static const int ph_invalid = (1 << trkbuilding_ph_diff_t::width) - 1;
constexpr static const int th_invalid = (1 << trkbuilding_th_diff_t::width) - 1;

constexpr static const int groups_zone_0_rows[num_feature_groups] = { 2, 2, 4, 5, 7, 2, 4, 6, 7, 1, 3, 0};
constexpr static const int groups_zone_1_rows[num_feature_groups] = { 1, 2, 4, 5, 7, 2, 4, 6, 7, 0, 3, 0};
constexpr static const int groups_zone_2_rows[num_feature_groups] = { 0, 0, 3, 4, 6, 1, 2, 5, 7, 0, 3, 0};

}  // namespace detail


// Round up to the nearest multiple of 4
template <unsigned int N>
struct CeilMultiple4
{
  static const unsigned int value = ((N + 3) / 4) * 4;
};

struct trkbuilding_base_chamber_traits {};

struct trkbuilding_10deg_chamber_traits : trkbuilding_base_chamber_traits {
  static const int chtype = detail::chamber_10deg_chtype;
  static const int nch = detail::chamber_10deg_nch;
  static const int ndiff = CeilMultiple4<nch * num_segments>::value;
};

struct trkbuilding_20deg_chamber_traits : trkbuilding_base_chamber_traits {
  static const int chtype = detail::chamber_20deg_chtype;
  static const int nch = detail::chamber_20deg_nch;
  static const int ndiff = CeilMultiple4<nch * num_segments>::value;
};

struct trkbuilding_20deg_ext_chamber_traits : trkbuilding_base_chamber_traits {
  static const int chtype = detail::chamber_20deg_ext_chtype;
  static const int nch = detail::chamber_20deg_ext_nch;
  static const int ndiff = CeilMultiple4<nch * num_segments>::value;
};

template <int ZONE, int ROW>
struct trkbuilding_row_traits {};

template <int ZONE> struct trkbuilding_row_traits<ZONE, 0>  : trkbuilding_10deg_chamber_traits {};
template <int ZONE> struct trkbuilding_row_traits<ZONE, 1>  : trkbuilding_10deg_chamber_traits {};
template <int ZONE> struct trkbuilding_row_traits<ZONE, 2>  : trkbuilding_20deg_ext_chamber_traits {};
template <int ZONE> struct trkbuilding_row_traits<ZONE, 3>  : trkbuilding_20deg_ext_chamber_traits {};
template <int ZONE> struct trkbuilding_row_traits<ZONE, 4>  : trkbuilding_20deg_ext_chamber_traits {};
template <int ZONE> struct trkbuilding_row_traits<ZONE, 5>  : trkbuilding_10deg_chamber_traits {};
template <int ZONE> struct trkbuilding_row_traits<ZONE, 6>  : trkbuilding_10deg_chamber_traits {};
template <int ZONE> struct trkbuilding_row_traits<ZONE, 7>  : trkbuilding_20deg_ext_chamber_traits {};
template <int ZONE> struct trkbuilding_row_traits<ZONE, 8>  : trkbuilding_20deg_ext_chamber_traits {};
template <int ZONE> struct trkbuilding_row_traits<ZONE, 9>  : trkbuilding_10deg_chamber_traits {};
template <int ZONE> struct trkbuilding_row_traits<ZONE, 10> : trkbuilding_20deg_chamber_traits {};
template <int ZONE> struct trkbuilding_row_traits<ZONE, 11> : trkbuilding_10deg_chamber_traits {};

template <int ZONE, int ROW>
struct trkbuilding_get_chamber_op {};

template <int ZONE> struct trkbuilding_get_chamber_op<ZONE, 0>  { inline int operator ()(int i) const { return detail::chambers_endcap_row_0[i]; } };
template <int ZONE> struct trkbuilding_get_chamber_op<ZONE, 1>  { inline int operator ()(int i) const { return detail::chambers_endcap_row_1[i]; } };
template <int ZONE> struct trkbuilding_get_chamber_op<ZONE, 2>  { inline int operator ()(int i) const { return detail::chambers_endcap_row_2[i]; } };
template <int ZONE> struct trkbuilding_get_chamber_op<ZONE, 3>  { inline int operator ()(int i) const { return detail::chambers_endcap_row_3[i]; } };
template <int ZONE> struct trkbuilding_get_chamber_op<ZONE, 4>  { inline int operator ()(int i) const { return detail::chambers_endcap_row_4[i]; } };
template <int ZONE> struct trkbuilding_get_chamber_op<ZONE, 5>  { inline int operator ()(int i) const { return detail::chambers_endcap_row_5[i]; } };
template <int ZONE> struct trkbuilding_get_chamber_op<ZONE, 6>  { inline int operator ()(int i) const { return detail::chambers_endcap_row_6[i]; } };
template <int ZONE> struct trkbuilding_get_chamber_op<ZONE, 7>  { inline int operator ()(int i) const { return detail::chambers_endcap_row_7[i]; } };
template <int ZONE> struct trkbuilding_get_chamber_op<ZONE, 8>  { inline int operator ()(int i) const { return detail::chambers_endcap_row_8[i]; } };
template <int ZONE> struct trkbuilding_get_chamber_op<ZONE, 9>  { inline int operator ()(int i) const { return detail::chambers_endcap_row_9[i]; } };
template <int ZONE> struct trkbuilding_get_chamber_op<ZONE, 10> { inline int operator ()(int i) const { return detail::chambers_endcap_row_10[i]; } };
template <int ZONE> struct trkbuilding_get_chamber_op<ZONE, 11> { inline int operator ()(int i) const { return detail::chambers_endcap_row_11[i]; } };

template <int ZONE, int ROW>
struct trkbuilding_get_col_mid_op {};

// Implement the trkbuilding_get_blah_op by using text replacement macros ("token pasting")
// It defines the following for 'col_mid':
//     template <> struct trkbuilding_get_col_mid_op<0, j> { inline int operator ()(int i) const { ... } };
//     template <> struct trkbuilding_get_col_mid_op<1, j> { inline int operator ()(int i) const { ... } };
//     template <> struct trkbuilding_get_col_mid_op<2, j> { inline int operator ()(int i) const { ... } };
// The operator ()(int i) takes patt 'i'.
// Note the differences in 'pad' and 'j' compared to the version in emtf_hlslib/pooling.h
#define DEFINE_NICE_OPS_TRKBUILDING(ZONE, ROW, NAME) \
    template <> struct trkbuilding_get_##NAME##_op<ZONE, ROW> { \
      inline int operator ()(int i) const { \
        const int ref = detail::windows_col_reference; \
        const int pad = detail::chamber_288unit_ph_init; \
        const int j = detail::groups_zone_##ZONE##_rows[ROW]; \
        switch (i) { \
          case 0  : return (detail::windows_##NAME##_zone_##ZONE##_patt_0[j] - ref + pad); \
          case 1  : return (detail::windows_##NAME##_zone_##ZONE##_patt_1[j] - ref + pad); \
          case 2  : return (detail::windows_##NAME##_zone_##ZONE##_patt_2[j] - ref + pad); \
          case 3  : return (detail::windows_##NAME##_zone_##ZONE##_patt_3[j] - ref + pad); \
          case 4  : return (detail::windows_##NAME##_zone_##ZONE##_patt_4[j] - ref + pad); \
          case 5  : return (detail::windows_##NAME##_zone_##ZONE##_patt_5[j] - ref + pad); \
          case 6  : return (detail::windows_##NAME##_zone_##ZONE##_patt_6[j] - ref + pad); \
          default : return 0; \
        } \
      } \
    };

DEFINE_NICE_OPS_TRKBUILDING(0, 0, col_mid)
DEFINE_NICE_OPS_TRKBUILDING(0, 1, col_mid)
DEFINE_NICE_OPS_TRKBUILDING(0, 2, col_mid)
DEFINE_NICE_OPS_TRKBUILDING(0, 3, col_mid)
DEFINE_NICE_OPS_TRKBUILDING(0, 4, col_mid)
DEFINE_NICE_OPS_TRKBUILDING(0, 5, col_mid)
DEFINE_NICE_OPS_TRKBUILDING(0, 6, col_mid)
DEFINE_NICE_OPS_TRKBUILDING(0, 7, col_mid)
DEFINE_NICE_OPS_TRKBUILDING(0, 8, col_mid)
DEFINE_NICE_OPS_TRKBUILDING(0, 9, col_mid)
DEFINE_NICE_OPS_TRKBUILDING(0, 10, col_mid)
DEFINE_NICE_OPS_TRKBUILDING(0, 11, col_mid)
DEFINE_NICE_OPS_TRKBUILDING(1, 0, col_mid)
DEFINE_NICE_OPS_TRKBUILDING(1, 1, col_mid)
DEFINE_NICE_OPS_TRKBUILDING(1, 2, col_mid)
DEFINE_NICE_OPS_TRKBUILDING(1, 3, col_mid)
DEFINE_NICE_OPS_TRKBUILDING(1, 4, col_mid)
DEFINE_NICE_OPS_TRKBUILDING(1, 5, col_mid)
DEFINE_NICE_OPS_TRKBUILDING(1, 6, col_mid)
DEFINE_NICE_OPS_TRKBUILDING(1, 7, col_mid)
DEFINE_NICE_OPS_TRKBUILDING(1, 8, col_mid)
DEFINE_NICE_OPS_TRKBUILDING(1, 9, col_mid)
DEFINE_NICE_OPS_TRKBUILDING(1, 10, col_mid)
DEFINE_NICE_OPS_TRKBUILDING(1, 11, col_mid)
DEFINE_NICE_OPS_TRKBUILDING(2, 0, col_mid)
DEFINE_NICE_OPS_TRKBUILDING(2, 1, col_mid)
DEFINE_NICE_OPS_TRKBUILDING(2, 2, col_mid)
DEFINE_NICE_OPS_TRKBUILDING(2, 3, col_mid)
DEFINE_NICE_OPS_TRKBUILDING(2, 4, col_mid)
DEFINE_NICE_OPS_TRKBUILDING(2, 5, col_mid)
DEFINE_NICE_OPS_TRKBUILDING(2, 6, col_mid)
DEFINE_NICE_OPS_TRKBUILDING(2, 7, col_mid)
DEFINE_NICE_OPS_TRKBUILDING(2, 8, col_mid)
DEFINE_NICE_OPS_TRKBUILDING(2, 9, col_mid)
DEFINE_NICE_OPS_TRKBUILDING(2, 10, col_mid)
DEFINE_NICE_OPS_TRKBUILDING(2, 11, col_mid)
#undef DEFINE_NICE_OPS_TRKBUILDING


// Function to init table
template <typename T, int N, class U>
void trkbuilding_init_table(T (&arr)[N], U op) {
  for (int i = 0; i < N; i++) {
    arr[i] = op(i);
  }
}

// Function to determine ph_patt (given patt, col) and then calculate ph_diff
template <typename T_IN, typename T_OUT, class U>
void trkbuilding_get_ph_diff(
    const T_IN& in0,
    const track_patt_t& patt,
    const track_col_t& col,
    T_OUT& out,
    U op
) {
  static_assert(is_same<T_IN, emtf_phi_t>::value, "T_IN type check failed");
  static_assert(is_same<T_OUT, trkbuilding_ph_diff_t>::value, "T_OUT type check failed");

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

// Keep this as a separate module
#pragma HLS INLINE off

#if !defined(__SYNTHESIS__)
  static bool initialized = false;
  static int lookup_table[num_patterns];
#else
  bool initialized = false;
  int lookup_table[num_patterns];
#endif

  if (!initialized) {
    trkbuilding_init_table(lookup_table, op);
    initialized = true;
  }

  const track_col_t offset = lookup_table[patt];
  const T_IN invalid = (T_IN) detail::ph_diff_invalid;
  const T_IN ph_patt = ((col + offset) << 4) + (1 << 3);
  const T_IN ph_diff_tmp_0 = (in0 >= ph_patt) ? (in0 - ph_patt) : (ph_patt - in0);
  const T_IN ph_diff_tmp_1 = (ph_diff_tmp_0 < invalid) ? ph_diff_tmp_0 : invalid;
  out = (T_OUT) ph_diff_tmp_1;
}

template <int CHTYPE, int N, typename enable_if<N == 8, int>::type = 0>
void trkbuilding_reorder_ph_diff_array(
    const trkbuilding_ph_diff_t in0[N],
    trkbuilding_ph_diff_t out[N]
) {
  static const int indices[N] = { 6,  7,  0,  1,  2,  3,  4,  5};
  for (int i = 0; i < N; i++) {
    out[i] = in0[indices[i]];
  }
}

template <int CHTYPE, int N, typename enable_if<N == 16, int>::type = 0>
void trkbuilding_reorder_ph_diff_array(
    const trkbuilding_ph_diff_t in0[N],
    trkbuilding_ph_diff_t out[N]
) {
  static const int indices[N] = {12, 13, 14, 15,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11};
  for (int i = 0; i < N; i++) {
    out[i] = in0[indices[i]];
  }
}

template <int CHTYPE, int N, typename enable_if<N == 24, int>::type = 0>
void trkbuilding_reorder_ph_diff_array(
    const trkbuilding_ph_diff_t in0[N],
    trkbuilding_ph_diff_t out[N]
) {
  static const int indices[N] = { 6,  7, 20, 21, 22, 23,  0,  1,  8,  9, 10, 11,  2,  3, 12, 13, 14, 15,  4,  5, 16, 17, 18, 19};
  for (int i = 0; i < N; i++) {
    out[i] = in0[indices[i]];
  }
}

template <int CHTYPE, int N, typename enable_if<N == 8, int>::type = 0>
void trkbuilding_retrieve_ph_diff_index(
    const trkbuilding_ph_diff_idx_t& in0,
    trkbuilding_ph_diff_idx_t& out
) {
  static const int indices[N] = { 6,  7,  0,  1,  2,  3,  4,  5};
  out = (trkbuilding_ph_diff_idx_t) indices[in0];
}

template <int CHTYPE, int N, typename enable_if<N == 16, int>::type = 0>
void trkbuilding_retrieve_ph_diff_index(
    const trkbuilding_ph_diff_idx_t& in0,
    trkbuilding_ph_diff_idx_t& out
) {
  static const int indices[N] = {12, 13, 14, 15,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11};
  out = (trkbuilding_ph_diff_idx_t) indices[in0];
}

template <int CHTYPE, int N, typename enable_if<N == 24, int>::type = 0>
void trkbuilding_retrieve_ph_diff_index(
    const trkbuilding_ph_diff_idx_t& in0,
    trkbuilding_ph_diff_idx_t& out
) {
  static const int indices[N] = { 6,  7, 20, 21, 22, 23,  0,  1,  8,  9, 10, 11,  2,  3, 12, 13, 14, 15,  4,  5, 16, 17, 18, 19};
  out = (trkbuilding_ph_diff_idx_t) indices[in0];
}

template <int CHTYPE, int N, typename enable_if<N == 8, int>::type = 0>
void trkbuilding_reduce_min_ph_diff(const trkbuilding_ph_diff_t in0[N/2], trkbuilding_ph_diff_idx_t& out) {
  typedef trkbuilding_ph_diff_t value_t;
  constexpr unsigned int bits_lo = 0;
  constexpr unsigned int bits_hi = (value_t::width - 1);

  typedef ap_uint<2> idx_t;  // 0..3
  constexpr unsigned int index_bits_lo = value_t::width;
  constexpr unsigned int index_bits_hi = (idx_t::width + value_t::width - 1);

  typedef ap_uint<idx_t::width + value_t::width> T;

  // Stage 0: concatenate index and value
  const T tmp_0_0 = (idx_t(0), in0[0].range(bits_hi, bits_lo));
  const T tmp_0_1 = (idx_t(1), in0[1].range(bits_hi, bits_lo));
  const T tmp_0_2 = (idx_t(2), in0[2].range(bits_hi, bits_lo));
  const T tmp_0_3 = (idx_t(3), in0[3].range(bits_hi, bits_lo));

  // Stage 1
  const T tmp_1_0 = (tmp_0_0.range(bits_hi, bits_lo) < tmp_0_1.range(bits_hi, bits_lo)) ? tmp_0_0 : tmp_0_1;
  const T tmp_1_1 = (tmp_0_2.range(bits_hi, bits_lo) < tmp_0_3.range(bits_hi, bits_lo)) ? tmp_0_2 : tmp_0_3;

  // Stage 2
  const T tmp_2_0 = (tmp_1_0.range(bits_hi, bits_lo) < tmp_1_1.range(bits_hi, bits_lo)) ? tmp_1_0 : tmp_1_1;

  // Output
  out = tmp_2_0.range(index_bits_hi, index_bits_lo);
}

template <int CHTYPE, int N, typename enable_if<N == 16, int>::type = 0>
void trkbuilding_reduce_min_ph_diff(const trkbuilding_ph_diff_t in0[N/2], trkbuilding_ph_diff_idx_t& out) {
  typedef trkbuilding_ph_diff_t value_t;
  constexpr unsigned int bits_lo = 0;
  constexpr unsigned int bits_hi = (value_t::width - 1);

  typedef ap_uint<3> idx_t;  // 0..7
  constexpr unsigned int index_bits_lo = value_t::width;
  constexpr unsigned int index_bits_hi = (idx_t::width + value_t::width - 1);

  typedef ap_uint<idx_t::width + value_t::width> T;

  // Stage 0: concatenate index and value
  const T tmp_0_0 = (idx_t(0), in0[0].range(bits_hi, bits_lo));
  const T tmp_0_1 = (idx_t(1), in0[1].range(bits_hi, bits_lo));
  const T tmp_0_2 = (idx_t(2), in0[2].range(bits_hi, bits_lo));
  const T tmp_0_3 = (idx_t(3), in0[3].range(bits_hi, bits_lo));
  const T tmp_0_4 = (idx_t(4), in0[4].range(bits_hi, bits_lo));
  const T tmp_0_5 = (idx_t(5), in0[5].range(bits_hi, bits_lo));
  const T tmp_0_6 = (idx_t(6), in0[6].range(bits_hi, bits_lo));
  const T tmp_0_7 = (idx_t(7), in0[7].range(bits_hi, bits_lo));

  // Stage 1
  const T tmp_1_0 = (tmp_0_0.range(bits_hi, bits_lo) < tmp_0_1.range(bits_hi, bits_lo)) ? tmp_0_0 : tmp_0_1;
  const T tmp_1_1 = (tmp_0_2.range(bits_hi, bits_lo) < tmp_0_3.range(bits_hi, bits_lo)) ? tmp_0_2 : tmp_0_3;
  const T tmp_1_2 = (tmp_0_4.range(bits_hi, bits_lo) < tmp_0_5.range(bits_hi, bits_lo)) ? tmp_0_4 : tmp_0_5;
  const T tmp_1_3 = (tmp_0_6.range(bits_hi, bits_lo) < tmp_0_7.range(bits_hi, bits_lo)) ? tmp_0_6 : tmp_0_7;

  // Stage 2
  const T tmp_2_0 = (tmp_1_0.range(bits_hi, bits_lo) < tmp_1_1.range(bits_hi, bits_lo)) ? tmp_1_0 : tmp_1_1;
  const T tmp_2_1 = (tmp_1_2.range(bits_hi, bits_lo) < tmp_1_3.range(bits_hi, bits_lo)) ? tmp_1_2 : tmp_1_3;

  // Stage 3
  const T tmp_3_0 = (tmp_2_0.range(bits_hi, bits_lo) < tmp_2_1.range(bits_hi, bits_lo)) ? tmp_2_0 : tmp_2_1;

  // Output
  out = tmp_3_0.range(index_bits_hi, index_bits_lo);
}

template <int CHTYPE, int N, typename enable_if<N == 24, int>::type = 0>
void trkbuilding_reduce_min_ph_diff(const trkbuilding_ph_diff_t in0[N/2], trkbuilding_ph_diff_idx_t& out) {
  typedef trkbuilding_ph_diff_t value_t;
  constexpr unsigned int bits_lo = 0;
  constexpr unsigned int bits_hi = (value_t::width - 1);

  typedef ap_uint<4> idx_t;  // 0..11
  constexpr unsigned int index_bits_lo = value_t::width;
  constexpr unsigned int index_bits_hi = (idx_t::width + value_t::width - 1);

  typedef ap_uint<idx_t::width + value_t::width> T;

  // Stage 0: concatenate index and value
  const T tmp_0_0 = (idx_t(0), in0[0].range(bits_hi, bits_lo));
  const T tmp_0_1 = (idx_t(1), in0[1].range(bits_hi, bits_lo));
  const T tmp_0_2 = (idx_t(2), in0[2].range(bits_hi, bits_lo));
  const T tmp_0_3 = (idx_t(3), in0[3].range(bits_hi, bits_lo));
  const T tmp_0_4 = (idx_t(4), in0[4].range(bits_hi, bits_lo));
  const T tmp_0_5 = (idx_t(5), in0[5].range(bits_hi, bits_lo));
  const T tmp_0_6 = (idx_t(6), in0[6].range(bits_hi, bits_lo));
  const T tmp_0_7 = (idx_t(7), in0[7].range(bits_hi, bits_lo));
  const T tmp_0_8 = (idx_t(8), in0[8].range(bits_hi, bits_lo));
  const T tmp_0_9 = (idx_t(9), in0[9].range(bits_hi, bits_lo));
  const T tmp_0_10 = (idx_t(10), in0[10].range(bits_hi, bits_lo));
  const T tmp_0_11 = (idx_t(11), in0[11].range(bits_hi, bits_lo));

  // Stage 1
  const T tmp_1_0 = (tmp_0_0.range(bits_hi, bits_lo) < tmp_0_1.range(bits_hi, bits_lo)) ? tmp_0_0 : tmp_0_1;
  const T tmp_1_1 = (tmp_0_2.range(bits_hi, bits_lo) < tmp_0_3.range(bits_hi, bits_lo)) ? tmp_0_2 : tmp_0_3;
  const T tmp_1_2 = (tmp_0_4.range(bits_hi, bits_lo) < tmp_0_5.range(bits_hi, bits_lo)) ? tmp_0_4 : tmp_0_5;
  const T tmp_1_3 = (tmp_0_6.range(bits_hi, bits_lo) < tmp_0_7.range(bits_hi, bits_lo)) ? tmp_0_6 : tmp_0_7;
  const T tmp_1_4 = (tmp_0_8.range(bits_hi, bits_lo) < tmp_0_9.range(bits_hi, bits_lo)) ? tmp_0_8 : tmp_0_9;
  const T tmp_1_5 = (tmp_0_10.range(bits_hi, bits_lo) < tmp_0_11.range(bits_hi, bits_lo)) ? tmp_0_10 : tmp_0_11;

  // Stage 2
  const T tmp_2_0 = (tmp_1_0.range(bits_hi, bits_lo) < tmp_1_1.range(bits_hi, bits_lo)) ? tmp_1_0 : tmp_1_1;
  const T tmp_2_1 = (tmp_1_2.range(bits_hi, bits_lo) < tmp_1_3.range(bits_hi, bits_lo)) ? tmp_1_2 : tmp_1_3;
  const T tmp_2_2 = (tmp_1_4.range(bits_hi, bits_lo) < tmp_1_5.range(bits_hi, bits_lo)) ? tmp_1_4 : tmp_1_5;

  // Stage 3
  const T tmp_3_0 = (tmp_2_0.range(bits_hi, bits_lo) < tmp_2_1.range(bits_hi, bits_lo)) ? tmp_2_0 : tmp_2_1;
  const T tmp_3_1 = tmp_2_2;

  // Stage 4
  const T tmp_4_0 = (tmp_3_0.range(bits_hi, bits_lo) < tmp_3_1.range(bits_hi, bits_lo)) ? tmp_3_0 : tmp_3_1;

  // Output
  out = tmp_4_0.range(index_bits_hi, index_bits_lo);
}


// _____________________________________________________________________________
// Perform loop over chambers and all the segments in the chambers

template <int ZONE, int ROW>
void trkbuilding_row_op(
    const emtf_phi_t emtf_phi[N_MODEL_IN],
    const flags_zone_t flags_zone[N_MODEL_IN],
    const valid_t valid[N_MODEL_IN],
    const track_qual_t track_qual_trk_i,
    const track_patt_t track_patt_trk_i,
    const track_col_t track_col_trk_i,
    const track_zone_t track_zone_trk_i,
    trkbuilding_seg_t& trkbuilding_idx_out_row_k
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE region

  //constexpr int TIMEZONE = 1;
  constexpr int CHTYPE = trkbuilding_row_traits<ZONE, ROW>::chtype;
  constexpr int N = trkbuilding_row_traits<ZONE, ROW>::nch;

  int chambers[N];
  trkbuilding_init_table(chambers, trkbuilding_get_chamber_op<ZONE, ROW>());

  const unsigned int n_ph_diff = trkbuilding_row_traits<ZONE, ROW>::ndiff;

  trkbuilding_ph_diff_t trkbuilding_ph_diff_zone_0[n_ph_diff];
  trkbuilding_ph_diff_t trkbuilding_ph_diff_zone_1[n_ph_diff];
  trkbuilding_ph_diff_t trkbuilding_ph_diff_zone_2[n_ph_diff];
  trkbuilding_ph_diff_t trkbuilding_ph_diff[n_ph_diff];
  trkbuilding_ph_diff_t trkbuilding_ph_diff_reordered[n_ph_diff];

#pragma HLS ARRAY_PARTITION variable=trkbuilding_ph_diff_zone_0 complete dim=0
#pragma HLS ARRAY_PARTITION variable=trkbuilding_ph_diff_zone_1 complete dim=0
#pragma HLS ARRAY_PARTITION variable=trkbuilding_ph_diff_zone_2 complete dim=0
#pragma HLS ARRAY_PARTITION variable=trkbuilding_ph_diff complete dim=0
#pragma HLS ARRAY_PARTITION variable=trkbuilding_ph_diff_reordered complete dim=0

  unsigned int idiff = 0;  // index into trkbuilding_ph_diff

  // Loop over chambers
  for (int i = 0; i < N; i++) {

#pragma HLS UNROLL

    // Loop over segments
    for (int j = 0; j < num_segments; j++) {

#pragma HLS UNROLL

      const trkbuilding_seg_t iseg = (chambers[i] * num_segments) + j;
      assert(chambers[i] < num_chambers);
      assert(iseg < N_MODEL_IN);

      trkbuilding_get_ph_diff(emtf_phi[iseg], track_patt_trk_i, track_col_trk_i, trkbuilding_ph_diff_zone_0[idiff], trkbuilding_get_col_mid_op<0, ROW>());
      trkbuilding_get_ph_diff(emtf_phi[iseg], track_patt_trk_i, track_col_trk_i, trkbuilding_ph_diff_zone_1[idiff], trkbuilding_get_col_mid_op<1, ROW>());
      trkbuilding_get_ph_diff(emtf_phi[iseg], track_patt_trk_i, track_col_trk_i, trkbuilding_ph_diff_zone_2[idiff], trkbuilding_get_col_mid_op<2, ROW>());

      bool vld_zone_0 = (valid[iseg] == 1) and (track_zone_trk_i == 0) and (flags_zone[iseg][2-0] == 1);
      bool vld_zone_1 = (valid[iseg] == 1) and (track_zone_trk_i == 1) and (flags_zone[iseg][2-1] == 1);
      bool vld_zone_2 = (valid[iseg] == 1) and (track_zone_trk_i == 2) and (flags_zone[iseg][2-2] == 1);

      if (vld_zone_0) {
        trkbuilding_ph_diff[idiff] = trkbuilding_ph_diff_zone_0[idiff];
      } else if (vld_zone_1) {
        trkbuilding_ph_diff[idiff] = trkbuilding_ph_diff_zone_1[idiff];
      } else if (vld_zone_2) {
        trkbuilding_ph_diff[idiff] = trkbuilding_ph_diff_zone_2[idiff];
      } else {
        trkbuilding_ph_diff[idiff] = detail::ph_invalid;
      }

      idiff++;
    }  // end loop over segments
  }  // end loop over chambers

  // Fill the rest of ph_diff values
  for (; idiff < n_ph_diff; idiff++) {

#pragma HLS UNROLL

    trkbuilding_ph_diff[idiff] = detail::ph_invalid;
  }

  trkbuilding_reorder_ph_diff_array<CHTYPE, n_ph_diff>(trkbuilding_ph_diff, trkbuilding_ph_diff_reordered);

  bool vld_area_0 = (track_col_trk_i < (detail::chambers_20deg_ph_cover[0] - detail::chamber_288unit_ph_init));
  bool vld_area_1 = (track_col_trk_i < (detail::chambers_20deg_ph_cover[1] - detail::chamber_288unit_ph_init));
  bool vld_area_2 = (track_col_trk_i < (detail::chambers_20deg_ph_cover[2] - detail::chamber_288unit_ph_init));

  const trkbuilding_area_t area = vld_area_0 ? 0 : (vld_area_1 ? 1 : (vld_area_2 ? 2 : num_img_areas));
  assert(area != num_img_areas);

  // Select min activation
  trkbuilding_ph_diff_idx_t ph_diff_idx_reordered;
  trkbuilding_reduce_min_ph_diff<CHTYPE, n_ph_diff>(trkbuilding_ph_diff_reordered + (area * (n_ph_diff / (num_img_areas + 1))), ph_diff_idx_reordered);

  trkbuilding_ph_diff_idx_t ph_diff_idx;
  trkbuilding_retrieve_ph_diff_index<CHTYPE, n_ph_diff>(ph_diff_idx_reordered + (area * (n_ph_diff / (num_img_areas + 1))), ph_diff_idx);

  constexpr unsigned int num_segments_bits_lo = 0;
  constexpr unsigned int num_segments_bits_hi = (1 - 1);  // ceil(log2(num_segments))
  constexpr unsigned int num_chambers_bits_lo = 1;
  constexpr unsigned int num_chambers_bits_hi = (4 + 1 - 1);  // ceil(log2(N))
  ap_uint<1> segment_idx = ph_diff_idx.range(num_segments_bits_hi, num_segments_bits_lo);
  ap_uint<4> chamber_idx = ph_diff_idx.range(num_chambers_bits_hi, num_chambers_bits_lo);

  trkbuilding_idx_out_row_k = (chambers[chamber_idx] * num_segments) + segment_idx;
  assert(trkbuilding_idx_out_row_k < N_MODEL_IN);
}


// _____________________________________________________________________________
// Track building op

template <int ZONE>
void trkbuilding_op(
    const emtf_phi_t emtf_phi[N_MODEL_IN],
    const emtf_bend_t emtf_bend[N_MODEL_IN],
    const emtf_theta1_t emtf_theta1[N_MODEL_IN],
    const emtf_theta2_t emtf_theta2[N_MODEL_IN],
    const emtf_qual_t emtf_qual[N_MODEL_IN],
    const emtf_time_t emtf_time[N_MODEL_IN],
    const flags_zone_t flags_zone[N_MODEL_IN],
    const flags_tzone_t flags_tzone[N_MODEL_IN],
    const bx_t bx[N_MODEL_IN],
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

  trkbuilding_seg_t trkbuilding_idx_out[num_feature_groups];

#pragma HLS ARRAY_PARTITION variable=trkbuilding_idx_out complete dim=0

  // Loop over tracks
  for (int i = 0; i < num_tracks; i++) {

#pragma HLS UNROLL

    // Loop over chamber_rows manually
    trkbuilding_row_op<ZONE, 0> (emtf_phi, flags_zone, valid, track_qual[i], track_patt[i], track_col[i], track_zone[i], trkbuilding_idx_out[0]);
    trkbuilding_row_op<ZONE, 1> (emtf_phi, flags_zone, valid, track_qual[i], track_patt[i], track_col[i], track_zone[i], trkbuilding_idx_out[1]);
    trkbuilding_row_op<ZONE, 2> (emtf_phi, flags_zone, valid, track_qual[i], track_patt[i], track_col[i], track_zone[i], trkbuilding_idx_out[2]);
    trkbuilding_row_op<ZONE, 3> (emtf_phi, flags_zone, valid, track_qual[i], track_patt[i], track_col[i], track_zone[i], trkbuilding_idx_out[3]);
    trkbuilding_row_op<ZONE, 4> (emtf_phi, flags_zone, valid, track_qual[i], track_patt[i], track_col[i], track_zone[i], trkbuilding_idx_out[4]);
    trkbuilding_row_op<ZONE, 5> (emtf_phi, flags_zone, valid, track_qual[i], track_patt[i], track_col[i], track_zone[i], trkbuilding_idx_out[5]);
    trkbuilding_row_op<ZONE, 6> (emtf_phi, flags_zone, valid, track_qual[i], track_patt[i], track_col[i], track_zone[i], trkbuilding_idx_out[6]);
    trkbuilding_row_op<ZONE, 7> (emtf_phi, flags_zone, valid, track_qual[i], track_patt[i], track_col[i], track_zone[i], trkbuilding_idx_out[7]);
    trkbuilding_row_op<ZONE, 8> (emtf_phi, flags_zone, valid, track_qual[i], track_patt[i], track_col[i], track_zone[i], trkbuilding_idx_out[8]);
    trkbuilding_row_op<ZONE, 9> (emtf_phi, flags_zone, valid, track_qual[i], track_patt[i], track_col[i], track_zone[i], trkbuilding_idx_out[9]);
    trkbuilding_row_op<ZONE, 10>(emtf_phi, flags_zone, valid, track_qual[i], track_patt[i], track_col[i], track_zone[i], trkbuilding_idx_out[10]);
    trkbuilding_row_op<ZONE, 11>(emtf_phi, flags_zone, valid, track_qual[i], track_patt[i], track_col[i], track_zone[i], trkbuilding_idx_out[11]);

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
    const flags_zone_t flags_zone[N_MODEL_IN],
    const flags_tzone_t flags_tzone[N_MODEL_IN],
    const bx_t bx[N_MODEL_IN],
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

  // Check assumptions
  static_assert(N_TRKBUILDING_IN == num_tracks, "N_TRKBUILDING_IN check failed");
  static_assert(N_TRKBUILDING_OUT == num_tracks * num_features, "N_TRKBUILDING_OUT check failed");
  static_assert(num_feature_groups == 12, "num_feature_groups must be 12");

  trkbuilding_op<ZONE>(emtf_phi, emtf_bend, emtf_theta1, emtf_theta2, emtf_qual, emtf_time,
                       flags_zone, flags_tzone, bx, valid, track_qual, track_patt,
                       track_col, track_zone, trkbuilding_out);
}

}  // namespace emtf

#endif  // __EMTF_HLSLIB_TRKBUILDING_H__ not defined
