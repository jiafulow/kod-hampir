#ifndef __EMTF_HLSLIB_TRKBUILDING_H__
#define __EMTF_HLSLIB_TRKBUILDING_H__

namespace emtf {

namespace detail {

constexpr static const int th_invalid = 0;

constexpr static const int th_window = 8;  // max - min + 1

constexpr static const int ph_diff_invalid = (1 << trkbuilding_ph_diff_t::width) - 1;
constexpr static const int th_diff_invalid = (1 << trkbuilding_th_diff_t::width) - 1;

constexpr static const int rows_zone_0[num_sites] = { 2, 2, 4, 5, 7, 2, 4, 6, 7, 1, 3, 0};
constexpr static const int rows_zone_1[num_sites] = { 1, 2, 4, 5, 7, 2, 4, 6, 7, 0, 3, 0};
constexpr static const int rows_zone_2[num_sites] = { 0, 0, 3, 4, 6, 1, 2, 5, 7, 0, 3, 0};

constexpr static const int chambers_10deg_chamber_order[8]      = {6, 7, 0, 1, 2, 3, 4, 5};
constexpr static const int chambers_20deg_chamber_order[4]      = {3, 0, 1, 2};
constexpr static const int chambers_20deg_ext_chamber_order[12] = {3, 10, 11, 0, 4, 5, 1, 6, 7, 2, 8, 9};

}  // namespace detail


// Round up to the nearest multiple of 4
template <unsigned int N>
struct CeilMultiple4
{
  static const unsigned int value = ((N + 3) / 4) * 4;
};

// Chamber tags
struct trkbuilding_10deg_chamber_tag {};
struct trkbuilding_20deg_chamber_tag {};
struct trkbuilding_20deg_ext_chamber_tag {};

// Site traits
template <typename Category>
struct trkbuilding_site_num_chambers {};

template <> struct trkbuilding_site_num_chambers<trkbuilding_10deg_chamber_tag> { static const int value = detail::chamber_10deg_nch; };
template <> struct trkbuilding_site_num_chambers<trkbuilding_20deg_chamber_tag> { static const int value = detail::chamber_20deg_nch; };
template <> struct trkbuilding_site_num_chambers<trkbuilding_20deg_ext_chamber_tag> { static const int value = detail::chamber_20deg_ext_nch; };

template <int Site>
struct trkbuilding_site_traits_helper {};

template <> struct trkbuilding_site_traits_helper<0> { typedef trkbuilding_10deg_chamber_tag chamber_category; };
template <> struct trkbuilding_site_traits_helper<1> { typedef trkbuilding_10deg_chamber_tag chamber_category; };
template <> struct trkbuilding_site_traits_helper<2> { typedef trkbuilding_20deg_ext_chamber_tag chamber_category; };
template <> struct trkbuilding_site_traits_helper<3> { typedef trkbuilding_20deg_ext_chamber_tag chamber_category; };
template <> struct trkbuilding_site_traits_helper<4> { typedef trkbuilding_20deg_ext_chamber_tag chamber_category; };
template <> struct trkbuilding_site_traits_helper<5> { typedef trkbuilding_10deg_chamber_tag chamber_category; };
template <> struct trkbuilding_site_traits_helper<6> { typedef trkbuilding_10deg_chamber_tag chamber_category; };
template <> struct trkbuilding_site_traits_helper<7> { typedef trkbuilding_20deg_ext_chamber_tag chamber_category; };
template <> struct trkbuilding_site_traits_helper<8> { typedef trkbuilding_20deg_ext_chamber_tag chamber_category; };
template <> struct trkbuilding_site_traits_helper<9> { typedef trkbuilding_10deg_chamber_tag chamber_category; };
template <> struct trkbuilding_site_traits_helper<10> { typedef trkbuilding_20deg_chamber_tag chamber_category; };
template <> struct trkbuilding_site_traits_helper<11> { typedef trkbuilding_10deg_chamber_tag chamber_category; };

template <int Site>
struct trkbuilding_site_traits {
  typedef typename trkbuilding_site_traits_helper<Site>::chamber_category chamber_category;
  static const int value = Site;
  static const int site_num_chambers = trkbuilding_site_num_chambers<chamber_category>::value;
  static const int site_num_chambers_round = CeilMultiple4<site_num_chambers>::value;
  static const int site_num_segments = site_num_chambers * num_segments;
  static const int site_num_segments_round = site_num_chambers_round * num_segments;
};

template <int Zone, int Site>
struct trkbuilding_get_chamber_op {
  inline int operator ()(int i) const {
    const int* array_ptr = nullptr;

    switch (Site) {
      case 0 : array_ptr = detail::chambers_endcap_row_0; break;
      case 1 : array_ptr = detail::chambers_endcap_row_1; break;
      case 2 : array_ptr = detail::chambers_endcap_row_2; break;
      case 3 : array_ptr = detail::chambers_endcap_row_3; break;
      case 4 : array_ptr = detail::chambers_endcap_row_4; break;
      case 5 : array_ptr = detail::chambers_endcap_row_5; break;
      case 6 : array_ptr = detail::chambers_endcap_row_6; break;
      case 7 : array_ptr = detail::chambers_endcap_row_7; break;
      case 8 : array_ptr = detail::chambers_endcap_row_8; break;
      case 9 : array_ptr = detail::chambers_endcap_row_9; break;
      case 10 : array_ptr = detail::chambers_endcap_row_10; break;
      case 11 : array_ptr = detail::chambers_endcap_row_11; break;
      default : break;
    }

    assert(array_ptr != nullptr);
    return array_ptr[i];
  }
};

template <typename Category>
struct trkbuilding_get_chamber_order_op {};

template <> struct trkbuilding_get_chamber_order_op<trkbuilding_10deg_chamber_tag> {
  inline int operator ()(int i) const { return detail::chambers_10deg_chamber_order[i]; }
};
template <> struct trkbuilding_get_chamber_order_op<trkbuilding_20deg_chamber_tag> {
  inline int operator ()(int i) const { return detail::chambers_20deg_chamber_order[i]; }
};
template <> struct trkbuilding_get_chamber_order_op<trkbuilding_20deg_ext_chamber_tag> {
  inline int operator ()(int i) const { return detail::chambers_20deg_ext_chamber_order[i]; }
};

template <typename Category>
struct trkbuilding_get_chamber_valid_op {
  inline bool operator ()(int i) const { return (i < (trkbuilding_site_num_chambers<Category>::value)); }
};

template <int Zone, int Site>
struct trkbuilding_get_segment_idx_op {
  typedef typename trkbuilding_site_traits<Site>::chamber_category chamber_category;

  inline int operator ()(int i) const {
    auto get_chamber_op = trkbuilding_get_chamber_op<Zone, Site>();
    auto get_chamber_order_op = trkbuilding_get_chamber_order_op<chamber_category>();
    auto get_chamber_valid_op = trkbuilding_get_chamber_valid_op<chamber_category>();

    const int tmp_chm_0 = (i / num_segments);
    const int tmp_chm_1 = get_chamber_order_op(tmp_chm_0);
    const bool is_valid_chm = get_chamber_valid_op(tmp_chm_1);

    int iseg = N_MODEL_IN; // default is set to 'invalid'
    if (is_valid_chm) {
      const int tmp_chm = get_chamber_op(tmp_chm_1);
      const int tmp_seg = (i % num_segments);
      iseg = ((tmp_chm * num_segments) + tmp_seg);
      assert(iseg < N_MODEL_IN);
    }
    return iseg;
  }
};

template <int Zone, int Site>
struct trkbuilding_get_col_start_op {
  inline int operator ()(int i, int j) const {  // zone i patt j
    const int* array_ptr = nullptr;
    switch (i) {
      case 0:
        switch (j) {
          case 0 : array_ptr = detail::windows_col_start_zone_0_patt_0; break;
          case 1 : array_ptr = detail::windows_col_start_zone_0_patt_1; break;
          case 2 : array_ptr = detail::windows_col_start_zone_0_patt_2; break;
          case 3 : array_ptr = detail::windows_col_start_zone_0_patt_3; break;
          case 4 : array_ptr = detail::windows_col_start_zone_0_patt_4; break;
          case 5 : array_ptr = detail::windows_col_start_zone_0_patt_5; break;
          case 6 : array_ptr = detail::windows_col_start_zone_0_patt_6; break;
          default : break;
        }
        break;
      case 1:
        switch (j) {
          case 0 : array_ptr = detail::windows_col_start_zone_1_patt_0; break;
          case 1 : array_ptr = detail::windows_col_start_zone_1_patt_1; break;
          case 2 : array_ptr = detail::windows_col_start_zone_1_patt_2; break;
          case 3 : array_ptr = detail::windows_col_start_zone_1_patt_3; break;
          case 4 : array_ptr = detail::windows_col_start_zone_1_patt_4; break;
          case 5 : array_ptr = detail::windows_col_start_zone_1_patt_5; break;
          case 6 : array_ptr = detail::windows_col_start_zone_1_patt_6; break;
          default : break;
        }
        break;
      case 2:
        switch (j) {
          case 0 : array_ptr = detail::windows_col_start_zone_2_patt_0; break;
          case 1 : array_ptr = detail::windows_col_start_zone_2_patt_1; break;
          case 2 : array_ptr = detail::windows_col_start_zone_2_patt_2; break;
          case 3 : array_ptr = detail::windows_col_start_zone_2_patt_3; break;
          case 4 : array_ptr = detail::windows_col_start_zone_2_patt_4; break;
          case 5 : array_ptr = detail::windows_col_start_zone_2_patt_5; break;
          case 6 : array_ptr = detail::windows_col_start_zone_2_patt_6; break;
          default : break;
        }
        break;
      default:
        break;
    }
    assert(array_ptr != nullptr);

    int row = 0;
    switch (i) {
      case 0 : row = detail::rows_zone_0[Site]; break;
      case 1 : row = detail::rows_zone_1[Site]; break;
      case 2 : row = detail::rows_zone_2[Site]; break;
      default : break;
    }

    const int ref = detail::windows_col_reference;
    return (array_ptr[row] - ref);
  }
};

template <int Zone, int Site>
struct trkbuilding_get_col_mid_op {
  inline int operator ()(int i, int j) const {  // zone i patt j
    const int* array_ptr = nullptr;
    switch (i) {
      case 0:
        switch (j) {
          case 0 : array_ptr = detail::windows_col_mid_zone_0_patt_0; break;
          case 1 : array_ptr = detail::windows_col_mid_zone_0_patt_1; break;
          case 2 : array_ptr = detail::windows_col_mid_zone_0_patt_2; break;
          case 3 : array_ptr = detail::windows_col_mid_zone_0_patt_3; break;
          case 4 : array_ptr = detail::windows_col_mid_zone_0_patt_4; break;
          case 5 : array_ptr = detail::windows_col_mid_zone_0_patt_5; break;
          case 6 : array_ptr = detail::windows_col_mid_zone_0_patt_6; break;
          default : break;
        }
        break;
      case 1:
        switch (j) {
          case 0 : array_ptr = detail::windows_col_mid_zone_1_patt_0; break;
          case 1 : array_ptr = detail::windows_col_mid_zone_1_patt_1; break;
          case 2 : array_ptr = detail::windows_col_mid_zone_1_patt_2; break;
          case 3 : array_ptr = detail::windows_col_mid_zone_1_patt_3; break;
          case 4 : array_ptr = detail::windows_col_mid_zone_1_patt_4; break;
          case 5 : array_ptr = detail::windows_col_mid_zone_1_patt_5; break;
          case 6 : array_ptr = detail::windows_col_mid_zone_1_patt_6; break;
          default : break;
        }
        break;
      case 2:
        switch (j) {
          case 0 : array_ptr = detail::windows_col_mid_zone_2_patt_0; break;
          case 1 : array_ptr = detail::windows_col_mid_zone_2_patt_1; break;
          case 2 : array_ptr = detail::windows_col_mid_zone_2_patt_2; break;
          case 3 : array_ptr = detail::windows_col_mid_zone_2_patt_3; break;
          case 4 : array_ptr = detail::windows_col_mid_zone_2_patt_4; break;
          case 5 : array_ptr = detail::windows_col_mid_zone_2_patt_5; break;
          case 6 : array_ptr = detail::windows_col_mid_zone_2_patt_6; break;
          default : break;
        }
        break;
      default:
        break;
    }
    assert(array_ptr != nullptr);

    int row = 0;
    switch (i) {
      case 0 : row = detail::rows_zone_0[Site]; break;
      case 1 : row = detail::rows_zone_1[Site]; break;
      case 2 : row = detail::rows_zone_2[Site]; break;
      default : break;
    }

    const int ref = detail::windows_col_reference;
    return (array_ptr[row] - ref);
  }
};

template <int Zone, int Site>
struct trkbuilding_get_col_stop_op {
  inline int operator ()(int i, int j) const {  // zone i patt j
    const int* array_ptr = nullptr;
    switch (i) {
      case 0:
        switch (j) {
          case 0 : array_ptr = detail::windows_col_stop_zone_0_patt_0; break;
          case 1 : array_ptr = detail::windows_col_stop_zone_0_patt_1; break;
          case 2 : array_ptr = detail::windows_col_stop_zone_0_patt_2; break;
          case 3 : array_ptr = detail::windows_col_stop_zone_0_patt_3; break;
          case 4 : array_ptr = detail::windows_col_stop_zone_0_patt_4; break;
          case 5 : array_ptr = detail::windows_col_stop_zone_0_patt_5; break;
          case 6 : array_ptr = detail::windows_col_stop_zone_0_patt_6; break;
          default : break;
        }
        break;
      case 1:
        switch (j) {
          case 0 : array_ptr = detail::windows_col_stop_zone_1_patt_0; break;
          case 1 : array_ptr = detail::windows_col_stop_zone_1_patt_1; break;
          case 2 : array_ptr = detail::windows_col_stop_zone_1_patt_2; break;
          case 3 : array_ptr = detail::windows_col_stop_zone_1_patt_3; break;
          case 4 : array_ptr = detail::windows_col_stop_zone_1_patt_4; break;
          case 5 : array_ptr = detail::windows_col_stop_zone_1_patt_5; break;
          case 6 : array_ptr = detail::windows_col_stop_zone_1_patt_6; break;
          default : break;
        }
        break;
      case 2:
        switch (j) {
          case 0 : array_ptr = detail::windows_col_stop_zone_2_patt_0; break;
          case 1 : array_ptr = detail::windows_col_stop_zone_2_patt_1; break;
          case 2 : array_ptr = detail::windows_col_stop_zone_2_patt_2; break;
          case 3 : array_ptr = detail::windows_col_stop_zone_2_patt_3; break;
          case 4 : array_ptr = detail::windows_col_stop_zone_2_patt_4; break;
          case 5 : array_ptr = detail::windows_col_stop_zone_2_patt_5; break;
          case 6 : array_ptr = detail::windows_col_stop_zone_2_patt_6; break;
          default : break;
        }
        break;
      default:
        break;
    }
    assert(array_ptr != nullptr);

    int row = 0;
    switch (i) {
      case 0 : row = detail::rows_zone_0[Site]; break;
      case 1 : row = detail::rows_zone_1[Site]; break;
      case 2 : row = detail::rows_zone_2[Site]; break;
      default : break;
    }

    const int ref = detail::windows_col_reference;
    return (array_ptr[row] - ref);
  }
};

// Function to calculate abs difference
template <typename T>
T trkbuilding_calc_abs_diff(const T& lhs, const T& rhs) {
  return (lhs >= rhs) ? (lhs - rhs) : (rhs - lhs);
}

// Function to calculate signed difference
template <typename T, typename R=typename make_signed<typename make_wider<T>::type>::type>
R trkbuilding_calc_signed_diff(const T& lhs, const T& rhs) {
  return (static_cast<R>(lhs) - static_cast<R>(rhs));
}

// Function to suppress value if condition is false
template <typename T>
T trkbuilding_take_value_if(bool cond, const T& in0) {
  return cond ? in0 : static_cast<T>(0);
}

// Function to init table
template <typename T, int N, class U>
void trkbuilding_init_table(T (&arr)[N], U op) {
  for (int i = 0; i < N; i++) {
    arr[i] = op(i);
  }
}

// Function to init 2D table
template <typename T, int M, int N, class U>
void trkbuilding_init_table_2d(T (&arr)[M][N], U op) {
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      arr[i][j] = op(i, j);
    }
  }
}

template <typename T0, typename T1, typename T_OUT>
void trkbuilding_reduce_min_ph_diff(const T0 in0[4], const T1 in1[4], T_OUT& out, bool& vld, trkbuilding_20deg_chamber_tag tag) {
  static_assert(is_same<T0, trkbuilding_ph_diff_t>::value, "T0 type check failed");
  static_assert(is_same<T1, track_seg_t>::value, "T1 type check failed");
  static_assert(is_same<T_OUT, track_seg_t>::value, "T_OUT type check failed");

  typedef T0 value_t;
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
  const idx_t idx = tmp_2_0.range(index_bits_hi, index_bits_lo);
  out = in1[idx];
  vld = (in0[idx] != detail::ph_diff_invalid);
}

template <typename T0, typename T1, typename T_OUT>
void trkbuilding_reduce_min_ph_diff(const T0 in0[8], const T1 in1[8], T_OUT& out, bool& vld, trkbuilding_10deg_chamber_tag tag) {
  static_assert(is_same<T0, trkbuilding_ph_diff_t>::value, "T0 type check failed");
  static_assert(is_same<T1, track_seg_t>::value, "T1 type check failed");
  static_assert(is_same<T_OUT, track_seg_t>::value, "T_OUT type check failed");

  typedef T0 value_t;
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
  const idx_t idx = tmp_3_0.range(index_bits_hi, index_bits_lo);
  out = in1[idx];
  vld = (in0[idx] != detail::ph_diff_invalid);
}

template <typename T0, typename T1, typename T_OUT>
void trkbuilding_reduce_min_ph_diff(const T0 in0[12], const T1 in1[12], T_OUT& out, bool& vld, trkbuilding_20deg_ext_chamber_tag tag) {
  static_assert(is_same<T0, trkbuilding_ph_diff_t>::value, "T0 type check failed");
  static_assert(is_same<T1, track_seg_t>::value, "T1 type check failed");
  static_assert(is_same<T_OUT, track_seg_t>::value, "T_OUT type check failed");

  typedef T0 value_t;
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
  const idx_t idx = tmp_4_0.range(index_bits_hi, index_bits_lo);
  out = in1[idx];
  vld = (in0[idx] != detail::ph_diff_invalid);
}

template <typename T_IN, typename T_OUT, typename T=T_OUT>
void trkbuilding_sort_three(const T_IN in0[3], T_OUT& out0, T_OUT& out1, T_OUT& out2) {
  static_assert(is_same<T_IN, T_OUT>::value, "T_OUT type check failed");

  // The following implements the bubble sorting network, which is a stable sort algo.
  // There are 3 wires (0,1,2 from top to bottom), and there are 3 stages.
  // In each stage, compare a pair of wires (connected by a vertical line in the diagram).
  // If the value of the top wire is less than that of the bottom wire, swap the wires.
  // Thus, the smallest value moves to the bottom. At the end, all the values are sorted
  // (descending from top to bottom).
  //
  // 0   1   2   3
  // ----o-------o----
  //     |       |
  // ----o---o---o----
  //         |
  // --------o--------

  // Stage 0: if there are invalid theta values, try to set them to valid theta values
  const T tmp_0_0 = (in0[0] != detail::th_invalid) ? in0[0] : ((in0[1] != detail::th_invalid) ? in0[1] : in0[2]);
  const T tmp_0_1 = (in0[1] != detail::th_invalid) ? in0[1] : ((in0[2] != detail::th_invalid) ? in0[2] : in0[0]);
  const T tmp_0_2 = (in0[2] != detail::th_invalid) ? in0[2] : ((in0[0] != detail::th_invalid) ? in0[0] : in0[1]);

  // Stage 1: compare-swap if (wire[i] < wire[j]) swap(wire[j], wire[i])
  const T tmp_1_0 = (tmp_0_0 < tmp_0_1) ? tmp_0_1 : tmp_0_0;
  const T tmp_1_1 = (tmp_0_0 < tmp_0_1) ? tmp_0_0 : tmp_0_1;

  // Stage 2
  const T tmp_2_1 = (tmp_1_1 < tmp_0_2) ? tmp_0_2 : tmp_1_1;
  const T tmp_2_2 = (tmp_1_1 < tmp_0_2) ? tmp_1_1 : tmp_0_2;

  // Stage 3
  const T tmp_3_0 = (tmp_1_0 < tmp_2_1) ? tmp_2_1 : tmp_1_0;
  const T tmp_3_1 = (tmp_1_0 < tmp_2_1) ? tmp_1_0 : tmp_2_1;

  // Output
  out0 = tmp_3_0;
  out1 = tmp_3_1;
  out2 = tmp_2_2;
}

template <typename T_IN, typename T_OUT, typename T=T_OUT>
void trkbuilding_reduce_median_theta(const T_IN in0[9], T_OUT& out) {
  static_assert(is_same<T_IN, T_OUT>::value, "T_OUT type check failed");

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE region

  // See https://stackoverflow.com/a/46801450 regarding this median-of-9 sorting network.
  T tmp_0[9];
  T tmp_1[9];
  T tmp_2[3];

#pragma HLS ARRAY_PARTITION variable=tmp_0 complete dim=0
#pragma HLS ARRAY_PARTITION variable=tmp_1 complete dim=0
#pragma HLS ARRAY_PARTITION variable=tmp_2 complete dim=0

  // Stage 0
  trkbuilding_sort_three(in0 + 0, tmp_0[0], tmp_0[3], tmp_0[6]);
  trkbuilding_sort_three(in0 + 3, tmp_0[1], tmp_0[4], tmp_0[7]);
  trkbuilding_sort_three(in0 + 6, tmp_0[2], tmp_0[5], tmp_0[8]);

  // Stage 1
  trkbuilding_sort_three(tmp_0 + 0, tmp_1[5], tmp_1[8], tmp_1[2]);
  trkbuilding_sort_three(tmp_0 + 3, tmp_1[7], tmp_1[1], tmp_1[4]);
  trkbuilding_sort_three(tmp_0 + 6, tmp_1[0], tmp_1[3], tmp_1[6]);

  // Stage 2
  trkbuilding_sort_three(tmp_1 + 0, tmp_2[0], tmp_2[1], tmp_2[2]);

  // Output
  out = tmp_2[1];
}

template <typename T_IN, typename T_OUT, typename T=T_OUT>
void trkbuilding_reduce_median_theta_s1(const T_IN in0[3], T_OUT& out) {
  static_assert(is_same<T_IN, T_OUT>::value, "T_OUT type check failed");

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE region

  T tmp_0[3];

#pragma HLS ARRAY_PARTITION variable=tmp_0 complete dim=0

  // Stage 0
  trkbuilding_sort_three(in0 + 0, tmp_0[0], tmp_0[1], tmp_0[2]);

  // Output
  out = tmp_0[1];
}

template <typename T_IN, typename T_OUT, typename T=T_OUT>
void trkbuilding_select_best_theta(const T_IN& in0, const T_IN& in1, const T_IN& theta_median, T_OUT& out, bool& vld) {
  static_assert(is_same<T_IN, T_OUT>::value, "T_OUT type check failed");

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE region

  const T th_diff_tmp_0 = trkbuilding_calc_abs_diff(in0, theta_median);
  const T th_diff_tmp_1 = trkbuilding_calc_abs_diff(in1, theta_median);
  const bool valid_tmp_0 = (in0 != detail::th_invalid) and (th_diff_tmp_0 < detail::th_window);
  const bool valid_tmp_1 = (in1 != detail::th_invalid) and (th_diff_tmp_1 < detail::th_window);

  // Output
  if (valid_tmp_0 and valid_tmp_1) {
    out = (th_diff_tmp_0 < th_diff_tmp_1) ? in0 : in1;
    vld = true;
  } else if (valid_tmp_0) {
    out = in0;
    vld = true;
  } else if (valid_tmp_1) {
    out = in1;
    vld = true;
  } else {
    out = (T_OUT) detail::th_invalid;
    vld = false;
  }
}

template <typename T_IN, typename T_OUT, typename T=T_OUT>
void trkbuilding_select_best_theta(const T_IN& in0, const T_IN& theta_median, T_OUT& out, bool& vld) {
  static_assert(is_same<T_IN, T_OUT>::value, "T_OUT type check failed");

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE region

  const T th_diff_tmp_0 = trkbuilding_calc_abs_diff(in0, theta_median);
  const bool valid_tmp_0 = (in0 != detail::th_invalid) and (th_diff_tmp_0 < detail::th_window);

  // Output
  if (valid_tmp_0) {
    out = in0;
    vld = true;
  } else {
    out = (T_OUT) detail::th_invalid;
    vld = false;
  }
}

template <typename T_IN, typename T_OUT>
void trkbuilding_set_seg_valid_flag(const T_IN in0[num_sites], T_OUT& out) {
  static_assert(is_same<T_IN, bool>::value, "T_IN type check failed");
  static_assert(T_OUT::width == num_sites, "T_OUT type check failed");

  for (int i = 0; i < num_sites; i++) {

#pragma HLS UNROLL

    out[i] = in0[i];
  }
}


// _____________________________________________________________________________
// Perform loop over chambers and all the segments in the chambers

template <int Zone, int Site>
void trkbuilding_match_ph_op(
    const emtf_phi_t emtf_phi[N_MODEL_IN],
    const flags_zone_t flags_zone[N_MODEL_IN],
    const valid_t valid[N_MODEL_IN],
    const track_qual_t& track_qual_trk_i,
    const track_patt_t& track_patt_trk_i,
    const track_col_t& track_col_trk_i,
    const track_zone_t& track_zone_trk_i,
    track_seg_t& track_seg_trk_i_site_j,
    bool& track_seg_v_trk_i_site_j
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE region

  typedef typename trkbuilding_site_traits<Site>::chamber_category chamber_category;
  const int N = trkbuilding_site_traits<Site>::site_num_segments_round;  // rounded up to multiple of 4

  int segment_indices[N];
  trkbuilding_init_table(segment_indices, trkbuilding_get_segment_idx_op<Zone, Site>());

  int windows_col_start[num_zones][num_patterns];
  trkbuilding_init_table_2d(windows_col_start, trkbuilding_get_col_start_op<Zone, Site>());

  int windows_col_mid[num_zones][num_patterns];
  trkbuilding_init_table_2d(windows_col_mid, trkbuilding_get_col_mid_op<Zone, Site>());

  int windows_col_stop[num_zones][num_patterns];
  trkbuilding_init_table_2d(windows_col_stop, trkbuilding_get_col_stop_op<Zone, Site>());


  // Find segments matched to the pattern
  trkbuilding_ph_diff_t trkbuilding_ph_diff[N];
  track_seg_t trkbuilding_segment[N];

#pragma HLS ARRAY_PARTITION variable=trkbuilding_ph_diff complete dim=0

  const int col_patt = (int) track_col_trk_i + detail::chamber_288unit_ph_init;
  const int col_start = col_patt + windows_col_start[track_zone_trk_i][track_patt_trk_i];
  const int col_mid = col_patt + windows_col_mid[track_zone_trk_i][track_patt_trk_i];
  const int col_stop = col_patt + windows_col_stop[track_zone_trk_i][track_patt_trk_i];

  // Loop over segments (including fake chambers)
  for (int i = 0; i < N; i++) {

#pragma HLS UNROLL

    const int iseg = segment_indices[i];
    const bool is_valid_chm = (iseg < N_MODEL_IN);

    if (is_valid_chm) {
      //FIXME - remove int
      const int col = (emtf_phi[iseg] >> 4);
      const bool is_valid_seg = (valid[iseg] == 1) and \
                                (flags_zone[iseg][2 - track_zone_trk_i] == 1) and \
                                (col_start <= col) and (col <= col_stop);

      if (is_valid_seg) {
        // Calculate the difference
        const emtf_phi_t ph_seg = emtf_phi[iseg];
        const emtf_phi_t ph_patt = (col_mid << 4) + (1 << 3);
        const emtf_phi_t ph_diff_tmp_0 = trkbuilding_calc_abs_diff(ph_seg, ph_patt);
        const bool valid_tmp_0 = (ph_diff_tmp_0 < detail::ph_diff_invalid);
        const emtf_phi_t ph_diff_tmp_1 = valid_tmp_0 ? ph_diff_tmp_0 : (emtf_phi_t) detail::ph_diff_invalid;
        trkbuilding_ph_diff[i] = (trkbuilding_ph_diff_t) ph_diff_tmp_1;

      } else {
        // Invalid segment
        trkbuilding_ph_diff[i] = (trkbuilding_ph_diff_t) detail::ph_diff_invalid;
      }
    } else {
      // Invalid chamber
      trkbuilding_ph_diff[i] = (trkbuilding_ph_diff_t) detail::ph_diff_invalid;
    }

    // Keep track of segment idx
    trkbuilding_segment[i] = (track_seg_t) iseg;
  }  // end loop over segments

  // Select an area (40 deg = 2x 20 deg chambers)
  bool vld_area_0 = (col_patt < (detail::chambers_20deg_ph_cover[0]));
  bool vld_area_1 = (col_patt < (detail::chambers_20deg_ph_cover[1]));
  bool vld_area_2 = (col_patt < (detail::chambers_20deg_ph_cover[2]));

  const trkbuilding_area_t area = vld_area_0 ? 0 : (vld_area_1 ? 1 : (vld_area_2 ? 2 : num_img_areas));
  assert(area != num_img_areas);

  // Select min activation
  const int area_begin = area * (N / (num_img_areas + 1));
  trkbuilding_reduce_min_ph_diff(
      trkbuilding_ph_diff + area_begin,
      trkbuilding_segment + area_begin,
      track_seg_trk_i_site_j,
      track_seg_v_trk_i_site_j,
      chamber_category()
  );
}

template <int Zone>
void trkbuilding_match_th_op(
    const emtf_theta1_t emtf_theta1[N_MODEL_IN],
    const emtf_theta2_t emtf_theta2[N_MODEL_IN],
    const track_seg_t track_seg_trk_i[num_sites],
    const bool track_seg_v_trk_i_ph[num_sites],
    emtf_theta1_t& theta_median_trk_i,
    emtf_theta1_t emtf_theta_best[num_sites],
    bool track_seg_v_trk_i_th[num_sites]
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE region

  emtf_theta1_t theta_values[9];
  emtf_theta1_t theta_values_s1[3];  // special case for ME0/ME1-only tracks

#pragma HLS ARRAY_PARTITION variable=theta_values complete dim=0
#pragma HLS ARRAY_PARTITION variable=theta_values_s1 complete dim=0

  // Loop over the theta values manually
  const emtf_theta1_t theta_value_0_0 = track_seg_v_trk_i_ph[0] ? emtf_theta1[track_seg_trk_i[0]] : (emtf_theta1_t) detail::th_invalid;
  const emtf_theta1_t theta_value_0_1 = track_seg_v_trk_i_ph[0] ? emtf_theta2[track_seg_trk_i[0]] : (emtf_theta1_t) detail::th_invalid;
  const emtf_theta1_t theta_value_1_0 = track_seg_v_trk_i_ph[1] ? emtf_theta1[track_seg_trk_i[1]] : (emtf_theta1_t) detail::th_invalid;
  const emtf_theta1_t theta_value_1_1 = track_seg_v_trk_i_ph[1] ? emtf_theta2[track_seg_trk_i[1]] : (emtf_theta1_t) detail::th_invalid;
  const emtf_theta1_t theta_value_2_0 = track_seg_v_trk_i_ph[2] ? emtf_theta1[track_seg_trk_i[2]] : (emtf_theta1_t) detail::th_invalid;
  const emtf_theta1_t theta_value_2_1 = track_seg_v_trk_i_ph[2] ? emtf_theta2[track_seg_trk_i[2]] : (emtf_theta1_t) detail::th_invalid;
  const emtf_theta1_t theta_value_3_0 = track_seg_v_trk_i_ph[3] ? emtf_theta1[track_seg_trk_i[3]] : (emtf_theta1_t) detail::th_invalid;
  const emtf_theta1_t theta_value_3_1 = track_seg_v_trk_i_ph[3] ? emtf_theta2[track_seg_trk_i[3]] : (emtf_theta1_t) detail::th_invalid;
  const emtf_theta1_t theta_value_4_0 = track_seg_v_trk_i_ph[4] ? emtf_theta1[track_seg_trk_i[4]] : (emtf_theta1_t) detail::th_invalid;
  const emtf_theta1_t theta_value_4_1 = track_seg_v_trk_i_ph[4] ? emtf_theta2[track_seg_trk_i[4]] : (emtf_theta1_t) detail::th_invalid;
  const emtf_theta1_t theta_value_5_0 = track_seg_v_trk_i_ph[5] ? emtf_theta1[track_seg_trk_i[5]] : (emtf_theta1_t) detail::th_invalid;
  const emtf_theta1_t theta_value_6_0 = track_seg_v_trk_i_ph[6] ? emtf_theta1[track_seg_trk_i[6]] : (emtf_theta1_t) detail::th_invalid;
  const emtf_theta1_t theta_value_7_0 = track_seg_v_trk_i_ph[7] ? emtf_theta1[track_seg_trk_i[7]] : (emtf_theta1_t) detail::th_invalid;
  const emtf_theta1_t theta_value_8_0 = track_seg_v_trk_i_ph[8] ? emtf_theta1[track_seg_trk_i[8]] : (emtf_theta1_t) detail::th_invalid;
  const emtf_theta1_t theta_value_9_0 = track_seg_v_trk_i_ph[9] ? emtf_theta1[track_seg_trk_i[9]] : (emtf_theta1_t) detail::th_invalid;
  const emtf_theta1_t theta_value_10_0 = track_seg_v_trk_i_ph[10] ? emtf_theta1[track_seg_trk_i[10]] : (emtf_theta1_t) detail::th_invalid;
  const emtf_theta1_t theta_value_11_0 = track_seg_v_trk_i_ph[11] ? emtf_theta1[track_seg_trk_i[11]] : (emtf_theta1_t) detail::th_invalid;

  theta_values[0] = theta_value_2_0;  // ME2 theta 1
  theta_values[1] = theta_value_3_0;  // ME3 theta 1
  theta_values[2] = theta_value_4_0;  // ME4 theta 1
  theta_values[3] = theta_value_2_1;  // ME2 theta 2
  theta_values[4] = theta_value_3_1;  // ME3 theta 2
  theta_values[5] = theta_value_4_1;  // ME4 theta 2
  theta_values[6] = (theta_value_6_0 != detail::th_invalid) ? theta_value_6_0 : theta_value_10_0;  // RE2 or GE2/1 theta
  theta_values[7] = theta_value_7_0;  // RE3 theta
  theta_values[8] = theta_value_8_0;  // RE4 theta

  theta_values_s1[0] = (theta_value_0_0 != detail::th_invalid) ? theta_value_0_0 : theta_value_1_0;  // ME1/1 or ME1/2 theta 1
  theta_values_s1[1] = (theta_value_0_1 != detail::th_invalid) ? theta_value_0_1 : theta_value_1_1;  // ME1/1 or ME1/2 theta 2
  theta_values_s1[2] = (theta_value_11_0 != detail::th_invalid) ? theta_value_11_0 : (theta_value_9_0 != detail::th_invalid) ? theta_value_9_0 : theta_value_5_0;  // ME0 or GE1/1 or RE1/2

  emtf_theta1_t theta_median = 0;
  emtf_theta1_t theta_median_s1 = 0;

  // Find theta_median
  trkbuilding_reduce_median_theta(theta_values, theta_median);
  trkbuilding_reduce_median_theta_s1(theta_values_s1, theta_median_s1);

  theta_median_trk_i = (theta_median != detail::th_invalid) ? theta_median : theta_median_s1;

  // Find the most compatible theta values
  trkbuilding_select_best_theta(theta_value_0_0, theta_value_0_1, theta_median_trk_i, emtf_theta_best[0], track_seg_v_trk_i_th[0]);
  trkbuilding_select_best_theta(theta_value_1_0, theta_value_1_1, theta_median_trk_i, emtf_theta_best[1], track_seg_v_trk_i_th[1]);
  trkbuilding_select_best_theta(theta_value_2_0, theta_value_2_1, theta_median_trk_i, emtf_theta_best[2], track_seg_v_trk_i_th[2]);
  trkbuilding_select_best_theta(theta_value_3_0, theta_value_3_1, theta_median_trk_i, emtf_theta_best[3], track_seg_v_trk_i_th[3]);
  trkbuilding_select_best_theta(theta_value_4_0, theta_value_4_1, theta_median_trk_i, emtf_theta_best[4], track_seg_v_trk_i_th[4]);
  trkbuilding_select_best_theta(theta_value_5_0, theta_median_trk_i, emtf_theta_best[5], track_seg_v_trk_i_th[5]);
  trkbuilding_select_best_theta(theta_value_6_0, theta_median_trk_i, emtf_theta_best[6], track_seg_v_trk_i_th[6]);
  trkbuilding_select_best_theta(theta_value_7_0, theta_median_trk_i, emtf_theta_best[7], track_seg_v_trk_i_th[7]);
  trkbuilding_select_best_theta(theta_value_8_0, theta_median_trk_i, emtf_theta_best[8], track_seg_v_trk_i_th[8]);
  trkbuilding_select_best_theta(theta_value_9_0, theta_median_trk_i, emtf_theta_best[9], track_seg_v_trk_i_th[9]);
  trkbuilding_select_best_theta(theta_value_10_0, theta_median_trk_i, emtf_theta_best[10], track_seg_v_trk_i_th[10]);
  trkbuilding_select_best_theta(theta_value_11_0, theta_median_trk_i, emtf_theta_best[11], track_seg_v_trk_i_th[11]);
}

template <int Zone>
void trkbuilding_extract_op(
    const emtf_phi_t emtf_phi[N_MODEL_IN],
    const emtf_bend_t emtf_bend[N_MODEL_IN],
    const emtf_qual_t emtf_qual[N_MODEL_IN],
    const emtf_time_t emtf_time[N_MODEL_IN],
    const emtf_phi_t& phi_median_trk_i,
    const emtf_theta1_t& theta_median_trk_i,
    const emtf_theta1_t emtf_theta_best[num_sites],
    const track_seg_t track_seg_trk_i[num_sites],
    const track_seg_v_t& track_seg_v_trk_i,
    track_feat_t track_feat_trk_i[num_features],
    track_valid_t& track_valid_trk_i
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE region

  // Table showing the 36 features sent to NN
  //
  // feat       | ME1/1 | ME1/2 |  ME2  |  ME3  |  ME4  |  RE1  |  RE2  |  RE3  |  RE4  | GE1/1 | GE2/1 |  ME0
  // -----------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------
  // emtf_phi   |   *   |   *   |   *   |   *   |   *   |   *   |   *   |   *   |   *   |   *   |   *   |   *
  // emtf_theta |   *   |   *   |   *   |   *   |   *   |   *   |   *   |   *   |   *   |   *   |   *   |   *
  // emtf_bend  |   *   |   *   |   *   |   *   |   *   |       |       |       |       |       |       |   *
  // emtf_qual  |   *   |   *   |   *   |   *   |   *   |       |       |       |       |       |       |   *
  // emtf_time  |       |       |       |       |       |       |       |       |       |       |       |

  // If a track is valid, theta_median must not be zero
  assert(!track_valid_trk_i || (track_valid_trk_i && (theta_median_trk_i != detail::th_invalid)));

  int k = 0;

  // emtf_phi
  track_feat_trk_i[k++] = trkbuilding_take_value_if(track_seg_v_trk_i[0], trkbuilding_calc_signed_diff(emtf_phi[track_seg_trk_i[0]], phi_median_trk_i));
  track_feat_trk_i[k++] = trkbuilding_take_value_if(track_seg_v_trk_i[1], trkbuilding_calc_signed_diff(emtf_phi[track_seg_trk_i[1]], phi_median_trk_i));
  track_feat_trk_i[k++] = trkbuilding_take_value_if(track_seg_v_trk_i[2], trkbuilding_calc_signed_diff(emtf_phi[track_seg_trk_i[2]], phi_median_trk_i));
  track_feat_trk_i[k++] = trkbuilding_take_value_if(track_seg_v_trk_i[3], trkbuilding_calc_signed_diff(emtf_phi[track_seg_trk_i[3]], phi_median_trk_i));
  track_feat_trk_i[k++] = trkbuilding_take_value_if(track_seg_v_trk_i[4], trkbuilding_calc_signed_diff(emtf_phi[track_seg_trk_i[4]], phi_median_trk_i));
  track_feat_trk_i[k++] = trkbuilding_take_value_if(track_seg_v_trk_i[5], trkbuilding_calc_signed_diff(emtf_phi[track_seg_trk_i[5]], phi_median_trk_i));
  track_feat_trk_i[k++] = trkbuilding_take_value_if(track_seg_v_trk_i[6], trkbuilding_calc_signed_diff(emtf_phi[track_seg_trk_i[6]], phi_median_trk_i));
  track_feat_trk_i[k++] = trkbuilding_take_value_if(track_seg_v_trk_i[7], trkbuilding_calc_signed_diff(emtf_phi[track_seg_trk_i[7]], phi_median_trk_i));
  track_feat_trk_i[k++] = trkbuilding_take_value_if(track_seg_v_trk_i[8], trkbuilding_calc_signed_diff(emtf_phi[track_seg_trk_i[8]], phi_median_trk_i));
  track_feat_trk_i[k++] = trkbuilding_take_value_if(track_seg_v_trk_i[9], trkbuilding_calc_signed_diff(emtf_phi[track_seg_trk_i[9]], phi_median_trk_i));
  track_feat_trk_i[k++] = trkbuilding_take_value_if(track_seg_v_trk_i[10], trkbuilding_calc_signed_diff(emtf_phi[track_seg_trk_i[10]], phi_median_trk_i));
  track_feat_trk_i[k++] = trkbuilding_take_value_if(track_seg_v_trk_i[11], trkbuilding_calc_signed_diff(emtf_phi[track_seg_trk_i[11]], phi_median_trk_i));

  // emtf_theta
  track_feat_trk_i[k++] = trkbuilding_take_value_if(track_seg_v_trk_i[0], trkbuilding_calc_signed_diff(emtf_theta_best[0], theta_median_trk_i));
  track_feat_trk_i[k++] = trkbuilding_take_value_if(track_seg_v_trk_i[1], trkbuilding_calc_signed_diff(emtf_theta_best[1], theta_median_trk_i));
  track_feat_trk_i[k++] = trkbuilding_take_value_if(track_seg_v_trk_i[2], trkbuilding_calc_signed_diff(emtf_theta_best[2], theta_median_trk_i));
  track_feat_trk_i[k++] = trkbuilding_take_value_if(track_seg_v_trk_i[3], trkbuilding_calc_signed_diff(emtf_theta_best[3], theta_median_trk_i));
  track_feat_trk_i[k++] = trkbuilding_take_value_if(track_seg_v_trk_i[4], trkbuilding_calc_signed_diff(emtf_theta_best[4], theta_median_trk_i));
  track_feat_trk_i[k++] = trkbuilding_take_value_if(track_seg_v_trk_i[5], trkbuilding_calc_signed_diff(emtf_theta_best[5], theta_median_trk_i));
  track_feat_trk_i[k++] = trkbuilding_take_value_if(track_seg_v_trk_i[6], trkbuilding_calc_signed_diff(emtf_theta_best[6], theta_median_trk_i));
  track_feat_trk_i[k++] = trkbuilding_take_value_if(track_seg_v_trk_i[7], trkbuilding_calc_signed_diff(emtf_theta_best[7], theta_median_trk_i));
  track_feat_trk_i[k++] = trkbuilding_take_value_if(track_seg_v_trk_i[8], trkbuilding_calc_signed_diff(emtf_theta_best[8], theta_median_trk_i));
  track_feat_trk_i[k++] = trkbuilding_take_value_if(track_seg_v_trk_i[9], trkbuilding_calc_signed_diff(emtf_theta_best[9], theta_median_trk_i));
  track_feat_trk_i[k++] = trkbuilding_take_value_if(track_seg_v_trk_i[10], trkbuilding_calc_signed_diff(emtf_theta_best[10], theta_median_trk_i));
  track_feat_trk_i[k++] = trkbuilding_take_value_if(track_seg_v_trk_i[11], trkbuilding_calc_signed_diff(emtf_theta_best[11], theta_median_trk_i));

  // emtf_bend
  track_feat_trk_i[k++] = trkbuilding_take_value_if(track_seg_v_trk_i[0], emtf_bend[track_seg_trk_i[0]]);
  track_feat_trk_i[k++] = trkbuilding_take_value_if(track_seg_v_trk_i[1], emtf_bend[track_seg_trk_i[1]]);
  track_feat_trk_i[k++] = trkbuilding_take_value_if(track_seg_v_trk_i[2], emtf_bend[track_seg_trk_i[2]]);
  track_feat_trk_i[k++] = trkbuilding_take_value_if(track_seg_v_trk_i[3], emtf_bend[track_seg_trk_i[3]]);
  track_feat_trk_i[k++] = trkbuilding_take_value_if(track_seg_v_trk_i[4], emtf_bend[track_seg_trk_i[4]]);
  track_feat_trk_i[k++] = trkbuilding_take_value_if(track_seg_v_trk_i[11], emtf_bend[track_seg_trk_i[11]]);

  // emtf_qual
  track_feat_trk_i[k++] = trkbuilding_take_value_if(track_seg_v_trk_i[0], emtf_qual[track_seg_trk_i[0]]);
  track_feat_trk_i[k++] = trkbuilding_take_value_if(track_seg_v_trk_i[1], emtf_qual[track_seg_trk_i[1]]);
  track_feat_trk_i[k++] = trkbuilding_take_value_if(track_seg_v_trk_i[2], emtf_qual[track_seg_trk_i[2]]);
  track_feat_trk_i[k++] = trkbuilding_take_value_if(track_seg_v_trk_i[3], emtf_qual[track_seg_trk_i[3]]);
  track_feat_trk_i[k++] = trkbuilding_take_value_if(track_seg_v_trk_i[4], emtf_qual[track_seg_trk_i[4]]);
  track_feat_trk_i[k++] = trkbuilding_take_value_if(track_seg_v_trk_i[11], emtf_qual[track_seg_trk_i[11]]);
  assert(k == num_features);
}


// _____________________________________________________________________________
// Track building op

template <int Zone>
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
    const track_qual_t& track_qual_trk_i,
    const track_patt_t& track_patt_trk_i,
    const track_col_t& track_col_trk_i,
    const track_zone_t& track_zone_trk_i,
    track_seg_t track_seg_trk_i[num_sites],
    track_seg_v_t& track_seg_v_trk_i,
    track_feat_t track_feat_trk_i[num_features],
    track_valid_t& track_valid_trk_i
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

//#pragma HLS INLINE region

  emtf_phi_t phi_median_trk_i = 0;
  emtf_theta1_t theta_median_trk_i = 0;

  emtf_theta1_t emtf_theta_best[num_sites];
  bool track_seg_v_trk_i_ph[num_sites];
  bool track_seg_v_trk_i_th[num_sites];

#pragma HLS ARRAY_PARTITION variable=emtf_theta_best complete dim=0
#pragma HLS ARRAY_PARTITION variable=track_seg_v_trk_i_ph complete dim=0
#pragma HLS ARRAY_PARTITION variable=track_seg_v_trk_i_th complete dim=0

  // Find phi_median, select best segment indices (closest to phi_median)
  {
    // Loop over sites manually
    trkbuilding_match_ph_op<Zone, 0> (emtf_phi, flags_zone, valid, track_qual_trk_i, track_patt_trk_i, track_col_trk_i, track_zone_trk_i, track_seg_trk_i[0], track_seg_v_trk_i_ph[0]);
    trkbuilding_match_ph_op<Zone, 1> (emtf_phi, flags_zone, valid, track_qual_trk_i, track_patt_trk_i, track_col_trk_i, track_zone_trk_i, track_seg_trk_i[1], track_seg_v_trk_i_ph[1]);
    trkbuilding_match_ph_op<Zone, 2> (emtf_phi, flags_zone, valid, track_qual_trk_i, track_patt_trk_i, track_col_trk_i, track_zone_trk_i, track_seg_trk_i[2], track_seg_v_trk_i_ph[2]);
    trkbuilding_match_ph_op<Zone, 3> (emtf_phi, flags_zone, valid, track_qual_trk_i, track_patt_trk_i, track_col_trk_i, track_zone_trk_i, track_seg_trk_i[3], track_seg_v_trk_i_ph[3]);
    trkbuilding_match_ph_op<Zone, 4> (emtf_phi, flags_zone, valid, track_qual_trk_i, track_patt_trk_i, track_col_trk_i, track_zone_trk_i, track_seg_trk_i[4], track_seg_v_trk_i_ph[4]);
    trkbuilding_match_ph_op<Zone, 5> (emtf_phi, flags_zone, valid, track_qual_trk_i, track_patt_trk_i, track_col_trk_i, track_zone_trk_i, track_seg_trk_i[5], track_seg_v_trk_i_ph[5]);
    trkbuilding_match_ph_op<Zone, 6> (emtf_phi, flags_zone, valid, track_qual_trk_i, track_patt_trk_i, track_col_trk_i, track_zone_trk_i, track_seg_trk_i[6], track_seg_v_trk_i_ph[6]);
    trkbuilding_match_ph_op<Zone, 7> (emtf_phi, flags_zone, valid, track_qual_trk_i, track_patt_trk_i, track_col_trk_i, track_zone_trk_i, track_seg_trk_i[7], track_seg_v_trk_i_ph[7]);
    trkbuilding_match_ph_op<Zone, 8> (emtf_phi, flags_zone, valid, track_qual_trk_i, track_patt_trk_i, track_col_trk_i, track_zone_trk_i, track_seg_trk_i[8], track_seg_v_trk_i_ph[8]);
    trkbuilding_match_ph_op<Zone, 9> (emtf_phi, flags_zone, valid, track_qual_trk_i, track_patt_trk_i, track_col_trk_i, track_zone_trk_i, track_seg_trk_i[9], track_seg_v_trk_i_ph[9]);
    trkbuilding_match_ph_op<Zone, 10>(emtf_phi, flags_zone, valid, track_qual_trk_i, track_patt_trk_i, track_col_trk_i, track_zone_trk_i, track_seg_trk_i[10], track_seg_v_trk_i_ph[10]);
    trkbuilding_match_ph_op<Zone, 11>(emtf_phi, flags_zone, valid, track_qual_trk_i, track_patt_trk_i, track_col_trk_i, track_zone_trk_i, track_seg_trk_i[11], track_seg_v_trk_i_ph[11]);

    // Set phi_median
    const int col_patt = (int) track_col_trk_i + detail::chamber_288unit_ph_init;
    phi_median_trk_i = (col_patt << 4) + (1 << 3);
  }

  // Find theta_median, select best theta values (closest to theta_median)
  {

#pragma HLS INLINE region

    trkbuilding_match_th_op<Zone>(emtf_theta1, emtf_theta2, track_seg_trk_i, track_seg_v_trk_i_ph,
                                  theta_median_trk_i, emtf_theta_best, track_seg_v_trk_i_th);

    // Set segment valid flag and track valid flag
    trkbuilding_set_seg_valid_flag(track_seg_v_trk_i_th, track_seg_v_trk_i);
    track_valid_trk_i = (bool) track_seg_v_trk_i;
  }

  // Extract features
  {

#pragma HLS INLINE region

    trkbuilding_extract_op<Zone>(emtf_phi, emtf_bend, emtf_qual, emtf_time, phi_median_trk_i, theta_median_trk_i,
                                 emtf_theta_best, track_seg_trk_i, track_seg_v_trk_i, track_feat_trk_i, track_valid_trk_i);
  }
}


// _____________________________________________________________________________
// Entry point

template <int Zone>
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
    track_seg_t track_seg[N_TRKBUILDING_OUT * num_sites],
    track_seg_v_t track_seg_v[N_TRKBUILDING_OUT],
    track_feat_t track_feat[N_TRKBUILDING_OUT * num_features],
    track_valid_t track_valid[N_TRKBUILDING_OUT]
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE region

  // Check assumptions
  static_assert(N_TRKBUILDING_IN == num_tracks, "N_TRKBUILDING_IN check failed");
  static_assert(N_TRKBUILDING_OUT == num_tracks, "N_TRKBUILDING_OUT check failed");
  static_assert(num_sites == 12, "num_sites must be 12");

  // Loop over tracks
  for (int i = 0; i < num_tracks; i++) {

#pragma HLS UNROLL

    trkbuilding_op<Zone>(emtf_phi, emtf_bend, emtf_theta1, emtf_theta2, emtf_qual, emtf_time,
                         flags_zone, flags_tzone, bx, valid, track_qual[i], track_patt[i],
                         track_col[i], track_zone[i], &(track_seg[i * num_sites]), track_seg_v[i],
                         &(track_feat[i * num_features]), track_valid[i]);
  }  // end loop over tracks
}

}  // namespace emtf

#endif  // __EMTF_HLSLIB_TRKBUILDING_H__ not defined
