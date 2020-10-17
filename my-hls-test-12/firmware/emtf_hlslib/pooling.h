#ifndef __EMTF_HLSLIB_POOLING_H__
#define __EMTF_HLSLIB_POOLING_H__

namespace emtf {

namespace detail {

constexpr static const int windows_col_reference = 55;

constexpr static const int windows_col_start_zone_0_patt_0[num_img_rows] = {51, 51, 52, 54, 54, 54, 54, 54};
constexpr static const int windows_col_start_zone_0_patt_1[num_img_rows] = {43, 43, 46, 53, 54, 55, 55, 55};
constexpr static const int windows_col_start_zone_0_patt_2[num_img_rows] = {57, 57, 56, 54, 54, 53, 53, 53};
constexpr static const int windows_col_start_zone_0_patt_3[num_img_rows] = {34, 35, 39, 53, 54, 54, 54, 53};
constexpr static const int windows_col_start_zone_0_patt_4[num_img_rows] = {61, 62, 59, 55, 54, 51, 50, 49};
constexpr static const int windows_col_start_zone_0_patt_5[num_img_rows] = {21, 23, 29, 52, 54, 52, 50, 46};
constexpr static const int windows_col_start_zone_0_patt_6[num_img_rows] = {65, 67, 62, 55, 54, 48, 47, 45};

constexpr static const int windows_col_start_zone_1_patt_0[num_img_rows] = {50, 51, 53, 54, 54, 54, 54, 54};
constexpr static const int windows_col_start_zone_1_patt_1[num_img_rows] = {39, 41, 48, 53, 54, 55, 55, 54};
constexpr static const int windows_col_start_zone_1_patt_2[num_img_rows] = {59, 58, 55, 55, 54, 53, 53, 53};
constexpr static const int windows_col_start_zone_1_patt_3[num_img_rows] = {27, 30, 44, 53, 54, 52, 51, 47};
constexpr static const int windows_col_start_zone_1_patt_4[num_img_rows] = {66, 64, 57, 55, 54, 52, 51, 51};
constexpr static const int windows_col_start_zone_1_patt_5[num_img_rows] = {18, 18, 41, 52, 54, 41, 34, 23};
constexpr static const int windows_col_start_zone_1_patt_6[num_img_rows] = {71, 68, 57, 53, 54, 51, 51, 52};

constexpr static const int windows_col_start_zone_2_patt_0[num_img_rows] = {53, 53, 54, 54, 54, 54, 54, 54};
constexpr static const int windows_col_start_zone_2_patt_1[num_img_rows] = {50, 50, 53, 54, 55, 54, 54, 54};
constexpr static const int windows_col_start_zone_2_patt_2[num_img_rows] = {56, 55, 54, 54, 54, 53, 54, 53};
constexpr static const int windows_col_start_zone_2_patt_3[num_img_rows] = {47, 48, 53, 54, 52, 51, 49, 48};
constexpr static const int windows_col_start_zone_2_patt_4[num_img_rows] = {57, 56, 54, 54, 53, 53, 53, 52};
constexpr static const int windows_col_start_zone_2_patt_5[num_img_rows] = {43, 45, 52, 54, 46, 40, 37, 31};
constexpr static const int windows_col_start_zone_2_patt_6[num_img_rows] = {57, 56, 53, 54, 53, 52, 52, 52};

constexpr static const int windows_col_stop_zone_0_patt_0[num_img_rows]  = {59, 59, 58, 56, 56, 56, 56, 56};
constexpr static const int windows_col_stop_zone_0_patt_1[num_img_rows]  = {53, 53, 54, 56, 56, 57, 57, 57};
constexpr static const int windows_col_stop_zone_0_patt_2[num_img_rows]  = {67, 67, 64, 57, 56, 55, 55, 55};
constexpr static const int windows_col_stop_zone_0_patt_3[num_img_rows]  = {49, 48, 51, 55, 56, 59, 60, 61};
constexpr static const int windows_col_stop_zone_0_patt_4[num_img_rows]  = {76, 75, 71, 57, 56, 56, 56, 57};
constexpr static const int windows_col_stop_zone_0_patt_5[num_img_rows]  = {45, 43, 48, 55, 56, 62, 63, 65};
constexpr static const int windows_col_stop_zone_0_patt_6[num_img_rows]  = {89, 87, 81, 58, 56, 58, 60, 64};

constexpr static const int windows_col_stop_zone_1_patt_0[num_img_rows]  = {60, 59, 57, 56, 56, 56, 56, 56};
constexpr static const int windows_col_stop_zone_1_patt_1[num_img_rows]  = {51, 52, 55, 55, 56, 57, 57, 57};
constexpr static const int windows_col_stop_zone_1_patt_2[num_img_rows]  = {71, 69, 62, 57, 56, 55, 55, 56};
constexpr static const int windows_col_stop_zone_1_patt_3[num_img_rows]  = {44, 46, 53, 55, 56, 58, 59, 59};
constexpr static const int windows_col_stop_zone_1_patt_4[num_img_rows]  = {83, 80, 66, 57, 56, 58, 59, 63};
constexpr static const int windows_col_stop_zone_1_patt_5[num_img_rows]  = {39, 42, 53, 57, 56, 59, 59, 58};
constexpr static const int windows_col_stop_zone_1_patt_6[num_img_rows]  = {92, 92, 69, 58, 56, 69, 76, 87};

constexpr static const int windows_col_stop_zone_2_patt_0[num_img_rows]  = {57, 57, 56, 56, 56, 56, 56, 56};
constexpr static const int windows_col_stop_zone_2_patt_1[num_img_rows]  = {54, 55, 56, 56, 56, 57, 56, 57};
constexpr static const int windows_col_stop_zone_2_patt_2[num_img_rows]  = {60, 60, 57, 56, 55, 56, 56, 56};
constexpr static const int windows_col_stop_zone_2_patt_3[num_img_rows]  = {53, 54, 56, 56, 57, 57, 57, 58};
constexpr static const int windows_col_stop_zone_2_patt_4[num_img_rows]  = {63, 62, 57, 56, 58, 59, 61, 62};
constexpr static const int windows_col_stop_zone_2_patt_5[num_img_rows]  = {53, 54, 57, 56, 57, 58, 58, 58};
constexpr static const int windows_col_stop_zone_2_patt_6[num_img_rows]  = {67, 65, 58, 56, 64, 70, 73, 79};

constexpr static const int paddings_zone_0[num_img_rows] = {34, 32, 26,  3,  1,  7,  8, 10};
constexpr static const int paddings_zone_1[num_img_rows] = {37, 37, 14,  3,  1, 14, 21, 32};
constexpr static const int paddings_zone_2[num_img_rows] = {12, 10,  3,  1,  9, 15, 18, 24};

constexpr static const int activations_zone_0[1u << num_img_rows] = {
   0, 22, 11, 26,  7, 31, 30, 38,  3, 42, 15, 44, 10, 50, 36, 53,  1, 23,
  13, 27,  9, 33, 31, 40,  5, 43, 17, 46, 16, 51, 39, 55,  0, 21, 12, 26,
   7, 31, 30, 38,  4, 42, 17, 45, 11, 50, 37, 54,  2, 23, 14, 27,  9, 34,
  34, 45,  6, 43, 20, 46, 20, 52, 49, 57,  0, 22, 12, 26,  8, 35, 30, 40,
   3, 42, 16, 45, 11, 53, 36, 56,  2, 24, 13, 28, 10, 38, 33, 49,  6, 45,
  18, 48, 20, 56, 40, 58,  1, 22, 13, 27,  8, 35, 32, 41,  5, 43, 18, 46,
  12, 54, 39, 56,  2, 25, 15, 28, 14, 41, 37, 53,  6, 47, 20, 49, 25, 58,
  52, 60,  0, 22, 13, 27,  7, 32, 31, 39,  3, 42, 17, 46, 11, 50, 37, 54,
   2, 25, 15, 29, 10, 49, 33, 55,  5, 44, 19, 48, 19, 57, 40, 59,  1, 24,
  14, 28,  8, 34, 33, 41,  4, 44, 19, 47, 12, 52, 39, 58,  3, 26, 16, 32,
  18, 58, 43, 60,  7, 50, 23, 52, 29, 61, 57, 62,  1, 23, 14, 28,  9, 37,
  32, 47,  5, 44, 18, 47, 15, 57, 38, 59,  4, 29, 16, 34, 19, 59, 36, 61,
   8, 55, 21, 56, 30, 62, 51, 63,  4, 25, 17, 29, 10, 48, 35, 55,  6, 51,
  21, 53, 24, 60, 48, 62,  9, 41, 24, 51, 36, 62, 59, 63, 21, 60, 35, 61,
  54, 63, 61, 63
};

constexpr static const int activations_zone_1[1u << num_img_rows] = {
   0,  2, 24, 29,  0,  2, 24, 29,  3,  7, 30, 37,  4,  8, 31, 38, 10, 13,
  38, 45, 10, 14, 38, 46, 17, 20, 48, 53, 17, 20, 49, 53,  0,  2, 25, 31,
   6,  7, 26, 33,  4,  8, 31, 40,  7, 11, 33, 42, 10, 15, 39, 48, 13, 16,
  41, 49, 18, 21, 50, 54, 19, 23, 50, 55,  0,  2, 25, 30,  1,  3, 25, 31,
   4,  8, 32, 40,  5,  9, 32, 40, 11, 15, 41, 46, 12, 15, 41, 47, 19, 23,
  51, 55, 20, 23, 51, 56,  1,  3, 27, 34, 12, 15, 28, 36,  5,  9, 34, 42,
  14, 18, 36, 45, 12, 16, 43, 51, 19, 22, 44, 52, 21, 28, 52, 58, 26, 29,
  53, 59,  1,  3, 25, 30,  7,  9, 27, 35,  5,  8, 32, 39,  9, 13, 33, 42,
  11, 14, 39, 47, 16, 18, 41, 49, 18, 22, 50, 57, 21, 26, 50, 57,  5,  6,
  27, 37, 38, 43, 46, 54,  6, 11, 34, 47, 39, 44, 48, 55, 13, 19, 44, 56,
  42, 45, 52, 60, 21, 28, 52, 61, 44, 48, 56, 62,  1,  4, 26, 33, 22, 24,
  35, 40,  6, 10, 34, 43, 23, 27, 36, 49, 12, 17, 43, 53, 28, 30, 46, 55,
  24, 35, 54, 62, 35, 37, 56, 63, 14, 17, 32, 45, 57, 58, 59, 61, 16, 20,
  37, 54, 57, 59, 59, 62, 22, 29, 51, 61, 58, 60, 61, 63, 36, 47, 60, 63,
  58, 60, 62, 63
};

constexpr static const int activations_zone_2[1u << num_img_rows] = {
   0, 11, 24, 43,  4, 20, 30, 52,  1, 13, 26, 45,  8, 22, 35, 55,  0, 11,
  25, 43,  5, 20, 31, 53,  3, 14, 27, 46, 10, 24, 37, 56,  3, 15, 29, 47,
   9, 28, 39, 57,  4, 17, 30, 48, 14, 35, 42, 59,  3, 16, 30, 48, 10, 29,
  40, 58,  7, 19, 32, 51, 19, 40, 43, 61,  0, 11, 25, 43,  4, 20, 31, 52,
   2, 13, 26, 45,  8, 23, 36, 56,  0, 12, 25, 44,  6, 21, 32, 54, 15, 23,
  34, 51, 34, 46, 47, 61,  3, 16, 29, 47, 10, 28, 40, 58,  5, 18, 31, 51,
  17, 39, 42, 61,  4, 17, 30, 49, 12, 37, 41, 60, 23, 39, 41, 59, 48, 59,
  58, 63,  1, 11, 25, 44,  6, 20, 33, 53,  2, 13, 27, 45,  9, 24, 36, 55,
   1, 12, 26, 45,  7, 22, 34, 54,  5, 16, 28, 47, 14, 33, 39, 57,  5, 16,
  31, 49, 13, 35, 41, 59,  7, 18, 33, 50, 19, 40, 44, 60,  6, 18, 32, 50,
  17, 38, 42, 60,  9, 22, 36, 54, 24, 51, 52, 62,  1, 12, 26, 44,  7, 21,
  33, 53,  2, 15, 27, 46, 10, 29, 38, 56,  2, 14, 27, 46,  9, 28, 36, 56,
  19, 37, 38, 57, 41, 57, 54, 63,  6, 18, 32, 49, 15, 37, 42, 60,  8, 22,
  35, 55, 23, 49, 50, 62,  8, 21, 34, 53, 21, 50, 48, 62, 38, 55, 52, 62,
  58, 63, 61, 63
};

}  // namespace detail


template <int ZONE, int ROW>
struct pooling_padding_traits {};

template <int ROW> struct pooling_padding_traits<0, ROW> { static const int value = detail::paddings_zone_0[ROW]; };
template <int ROW> struct pooling_padding_traits<1, ROW> { static const int value = detail::paddings_zone_1[ROW]; };
template <int ROW> struct pooling_padding_traits<2, ROW> { static const int value = detail::paddings_zone_2[ROW]; };

template <int ZONE, int ROW>
struct pooling_select_padding_type {
  static const int pad = pooling_padding_traits<ZONE, ROW>::value;
  typedef ap_uint<pad> type;
};

template <int ZONE, int ROW>
struct pooling_select_padded_type {
  static const int pad = pooling_padding_traits<ZONE, ROW>::value;
  typedef ap_uint<num_img_cols + (pad * 2)> type;
};

template <int ZONE, int ROW>
struct pooling_select_patch_type {
  static const int pad = pooling_padding_traits<ZONE, ROW>::value;
  typedef ap_uint<1 + (pad * 2)> type;
};

template <int ZONE>
struct pooling_get_col_start_op {};

template <> struct pooling_get_col_start_op<0> {  // zone 0
  inline int operator ()(int i, int j) const {    // patt i row j
    const int ref = detail::windows_col_reference;
    const int pad = detail::paddings_zone_0[j];
    switch (i) {
      case 0  : return (detail::windows_col_start_zone_0_patt_0[j] - ref + pad);
      case 1  : return (detail::windows_col_start_zone_0_patt_1[j] - ref + pad);
      case 2  : return (detail::windows_col_start_zone_0_patt_2[j] - ref + pad);
      case 3  : return (detail::windows_col_start_zone_0_patt_3[j] - ref + pad);
      case 4  : return (detail::windows_col_start_zone_0_patt_4[j] - ref + pad);
      case 5  : return (detail::windows_col_start_zone_0_patt_5[j] - ref + pad);
      case 6  : return (detail::windows_col_start_zone_0_patt_6[j] - ref + pad);
      default : return 0;
    }
  }
};

template <> struct pooling_get_col_start_op<1> {  // zone 1
  inline int operator ()(int i, int j) const {    // patt i row j
    const int ref = detail::windows_col_reference;
    const int pad = detail::paddings_zone_1[j];
    switch (i) {
      case 0  : return (detail::windows_col_start_zone_1_patt_0[j] - ref + pad);
      case 1  : return (detail::windows_col_start_zone_1_patt_1[j] - ref + pad);
      case 2  : return (detail::windows_col_start_zone_1_patt_2[j] - ref + pad);
      case 3  : return (detail::windows_col_start_zone_1_patt_3[j] - ref + pad);
      case 4  : return (detail::windows_col_start_zone_1_patt_4[j] - ref + pad);
      case 5  : return (detail::windows_col_start_zone_1_patt_5[j] - ref + pad);
      case 6  : return (detail::windows_col_start_zone_1_patt_6[j] - ref + pad);
      default : return 0;
    }
  }
};

template <> struct pooling_get_col_start_op<2> {  // zone 2
  inline int operator ()(int i, int j) const {    // patt i row j
    const int ref = detail::windows_col_reference;
    const int pad = detail::paddings_zone_2[j];
    switch (i) {
      case 0  : return (detail::windows_col_start_zone_2_patt_0[j] - ref + pad);
      case 1  : return (detail::windows_col_start_zone_2_patt_1[j] - ref + pad);
      case 2  : return (detail::windows_col_start_zone_2_patt_2[j] - ref + pad);
      case 3  : return (detail::windows_col_start_zone_2_patt_3[j] - ref + pad);
      case 4  : return (detail::windows_col_start_zone_2_patt_4[j] - ref + pad);
      case 5  : return (detail::windows_col_start_zone_2_patt_5[j] - ref + pad);
      case 6  : return (detail::windows_col_start_zone_2_patt_6[j] - ref + pad);
      default : return 0;
    }
  }
};

template <int ZONE>
struct pooling_get_col_stop_op {};

template <> struct pooling_get_col_stop_op<0> {  // zone 0
  inline int operator ()(int i, int j) const {   // patt i row j
    const int ref = detail::windows_col_reference;
    const int pad = detail::paddings_zone_0[j];
    switch (i) {
      case 0  : return (detail::windows_col_stop_zone_0_patt_0[j] - ref + pad);
      case 1  : return (detail::windows_col_stop_zone_0_patt_1[j] - ref + pad);
      case 2  : return (detail::windows_col_stop_zone_0_patt_2[j] - ref + pad);
      case 3  : return (detail::windows_col_stop_zone_0_patt_3[j] - ref + pad);
      case 4  : return (detail::windows_col_stop_zone_0_patt_4[j] - ref + pad);
      case 5  : return (detail::windows_col_stop_zone_0_patt_5[j] - ref + pad);
      case 6  : return (detail::windows_col_stop_zone_0_patt_6[j] - ref + pad);
      default : return 0;
    }
  }
};

template <> struct pooling_get_col_stop_op<1> {  // zone 1
  inline int operator ()(int i, int j) const {   // patt i row j
    const int ref = detail::windows_col_reference;
    const int pad = detail::paddings_zone_1[j];
    switch (i) {
      case 0  : return (detail::windows_col_stop_zone_1_patt_0[j] - ref + pad);
      case 1  : return (detail::windows_col_stop_zone_1_patt_1[j] - ref + pad);
      case 2  : return (detail::windows_col_stop_zone_1_patt_2[j] - ref + pad);
      case 3  : return (detail::windows_col_stop_zone_1_patt_3[j] - ref + pad);
      case 4  : return (detail::windows_col_stop_zone_1_patt_4[j] - ref + pad);
      case 5  : return (detail::windows_col_stop_zone_1_patt_5[j] - ref + pad);
      case 6  : return (detail::windows_col_stop_zone_1_patt_6[j] - ref + pad);
      default : return 0;
    }
  }
};

template <> struct pooling_get_col_stop_op<2> {  // zone 2
  inline int operator ()(int i, int j) const {   // patt i row j
    const int ref = detail::windows_col_reference;
    const int pad = detail::paddings_zone_2[j];
    switch (i) {
      case 0  : return (detail::windows_col_stop_zone_2_patt_0[j] - ref + pad);
      case 1  : return (detail::windows_col_stop_zone_2_patt_1[j] - ref + pad);
      case 2  : return (detail::windows_col_stop_zone_2_patt_2[j] - ref + pad);
      case 3  : return (detail::windows_col_stop_zone_2_patt_3[j] - ref + pad);
      case 4  : return (detail::windows_col_stop_zone_2_patt_4[j] - ref + pad);
      case 5  : return (detail::windows_col_stop_zone_2_patt_5[j] - ref + pad);
      case 6  : return (detail::windows_col_stop_zone_2_patt_6[j] - ref + pad);
      default : return 0;
    }
  }
};

template <int ZONE>
struct pooling_get_activation_op {};

template <> struct pooling_get_activation_op<0> { inline int operator ()(int i) const { return detail::activations_zone_0[i]; } };
template <> struct pooling_get_activation_op<1> { inline int operator ()(int i) const { return detail::activations_zone_1[i]; } };
template <> struct pooling_get_activation_op<2> { inline int operator ()(int i) const { return detail::activations_zone_2[i]; } };

// Function to init table
template <typename T, int N, class U>
void pooling_init_table(T (&arr)[N], U op) {
  for (int i = 0; i < N; i++) {
    arr[i] = op(i);
  }
}

// Function to init 2D table
template <typename T, int M, int N, class U>
void pooling_init_table_2d(T (&arr)[M][N], U op) {
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      arr[i][j] = op(i, j);
    }
  }
}

// Function to set bits in preactivation
template <typename T0, typename T1, typename T2, typename T3,
          typename T4, typename T5, typename T6, typename T7,
          typename T_OUT>
void pooling_set_preactivation(
    const T0& in0, const T1& in1, const T2& in2, const T3& in3,
    const T4& in4, const T5& in5, const T6& in6, const T7& in7,
    T_OUT& out
) {
  static_assert(is_same<T_OUT, pooling_preactivation_t>::value, "T_OUT type check failed");

  out[0] = (bool) in0;
  out[1] = (bool) in1;
  out[2] = (bool) in2;
  out[3] = (bool) in3;
  out[4] = (bool) in4;
  out[5] = (bool) in5;
  out[6] = (bool) in6;
  out[7] = (bool) in7;
}

// Function to apply activation
template <typename T_IN, typename T_OUT, class U>
void pooling_apply_activation(const T_IN& in0, T_OUT& out, U op) {
  static_assert(is_same<T_IN, pooling_preactivation_t>::value, "T_IN type check failed");
  static_assert(is_same<T_OUT, pooling_activation_t>::value, "T_OUT type check failed");

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

// Keep this as a separate module
#pragma HLS INLINE off

#if !defined(__SYNTHESIS__)
  static bool initialized = false;
  static int lookup_table[1u << num_img_rows];
#else
  bool initialized = false;
  int lookup_table[1u << num_img_rows];
#endif

  if (!initialized) {
    pooling_init_table(lookup_table, op);
    initialized = true;
  }

  out = (T_OUT) lookup_table[in0];
}

// Function to find max activation, keeping pattern number
template <typename T_IN, typename T_OUT>
void pooling_reduce_max_activation(const T_IN in0[num_patterns], T_OUT& out) {
  static_assert(is_same<T_IN, pooling_activation_t>::value, "T_IN type check failed");
  static_assert(is_same<T_OUT, pooling_out_t>::value, "T_OUT type check failed");

  typedef pooling_activation_t value_t;
  constexpr unsigned int bits_lo = 0;
  constexpr unsigned int bits_hi = (value_t::width - 1);

  // Stage 0: prepend patt number to the input value
  const T_OUT tmp_0_0 = (pooling_patt_t(0), in0[0]);
  const T_OUT tmp_0_1 = (pooling_patt_t(1), in0[1]);
  const T_OUT tmp_0_2 = (pooling_patt_t(2), in0[2]);
  const T_OUT tmp_0_3 = (pooling_patt_t(3), in0[3]);
  const T_OUT tmp_0_4 = (pooling_patt_t(4), in0[4]);
  const T_OUT tmp_0_5 = (pooling_patt_t(5), in0[5]);
  const T_OUT tmp_0_6 = (pooling_patt_t(6), in0[6]);

  // Stage 1
  const T_OUT tmp_1_0 = tmp_0_0;
  const T_OUT tmp_1_1 = (tmp_0_1.range(bits_hi, bits_lo) >= tmp_0_2.range(bits_hi, bits_lo)) ? tmp_0_1 : tmp_0_2;
  const T_OUT tmp_1_2 = (tmp_0_3.range(bits_hi, bits_lo) >= tmp_0_4.range(bits_hi, bits_lo)) ? tmp_0_3 : tmp_0_4;
  const T_OUT tmp_1_3 = (tmp_0_5.range(bits_hi, bits_lo) >= tmp_0_6.range(bits_hi, bits_lo)) ? tmp_0_5 : tmp_0_6;

  // Stage 2
  const T_OUT tmp_2_0 = (tmp_1_0.range(bits_hi, bits_lo) >= tmp_1_1.range(bits_hi, bits_lo)) ? tmp_1_0 : tmp_1_1;
  const T_OUT tmp_2_1 = (tmp_1_2.range(bits_hi, bits_lo) >= tmp_1_3.range(bits_hi, bits_lo)) ? tmp_1_2 : tmp_1_3;

  // Stage 3
  out = (tmp_2_0.range(bits_hi, bits_lo) >= tmp_2_1.range(bits_hi, bits_lo)) ? tmp_2_0 : tmp_2_1;
}

// _____________________________________________________________________________
// Apply the patterns at a particular column

template <int ZONE>
void pooling_col_op(
    const typename pooling_select_patch_type<ZONE, 0>::type patch_row_0,
    const typename pooling_select_patch_type<ZONE, 1>::type patch_row_1,
    const typename pooling_select_patch_type<ZONE, 2>::type patch_row_2,
    const typename pooling_select_patch_type<ZONE, 3>::type patch_row_3,
    const typename pooling_select_patch_type<ZONE, 4>::type patch_row_4,
    const typename pooling_select_patch_type<ZONE, 5>::type patch_row_5,
    const typename pooling_select_patch_type<ZONE, 6>::type patch_row_6,
    const typename pooling_select_patch_type<ZONE, 7>::type patch_row_7,
    pooling_out_t& pooling_out_col_l
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE region

  int windows_col_start[num_patterns][num_img_rows];
  pooling_init_table_2d(windows_col_start, pooling_get_col_start_op<ZONE>());

  int windows_col_stop[num_patterns][num_img_rows];
  pooling_init_table_2d(windows_col_stop, pooling_get_col_stop_op<ZONE>());

  pooling_preactivation_t pooling_preactivations[num_patterns];
  pooling_activation_t pooling_activations[num_patterns];

#pragma HLS ARRAY_PARTITION variable=pooling_preactivations complete dim=0
#pragma HLS ARRAY_PARTITION variable=pooling_activations complete dim=0

  // Loop over patterns
  for (unsigned patt = 0; patt < num_patterns; patt++) {

#pragma HLS UNROLL

    // Check pattern windows in each row
    pooling_set_preactivation(
        patch_row_0.range(windows_col_stop[patt][0], windows_col_start[patt][0]),
        patch_row_1.range(windows_col_stop[patt][1], windows_col_start[patt][1]),
        patch_row_2.range(windows_col_stop[patt][2], windows_col_start[patt][2]),
        patch_row_3.range(windows_col_stop[patt][3], windows_col_start[patt][3]),
        patch_row_4.range(windows_col_stop[patt][4], windows_col_start[patt][4]),
        patch_row_5.range(windows_col_stop[patt][5], windows_col_start[patt][5]),
        patch_row_6.range(windows_col_stop[patt][6], windows_col_start[patt][6]),
        patch_row_7.range(windows_col_stop[patt][7], windows_col_start[patt][7]),
        pooling_preactivations[patt]
    );

    // Activation
    pooling_apply_activation(
        pooling_preactivations[patt],
        pooling_activations[patt],
        pooling_get_activation_op<ZONE>()
    );
  }  // end loop over patterns

  // Select max activation
  pooling_reduce_max_activation(pooling_activations, pooling_out_col_l);
}


// _____________________________________________________________________________
// Pooling op

template <int ZONE>
void pooling_op(
    const pooling_in_t pooling_in[N_POOLING_IN],
    pooling_out_t pooling_out[N_POOLING_OUT]
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

//#pragma HLS INLINE region

  typedef typename pooling_select_padding_type<ZONE, 0>::type padding_row_0_t;
  typedef typename pooling_select_padding_type<ZONE, 1>::type padding_row_1_t;
  typedef typename pooling_select_padding_type<ZONE, 2>::type padding_row_2_t;
  typedef typename pooling_select_padding_type<ZONE, 3>::type padding_row_3_t;
  typedef typename pooling_select_padding_type<ZONE, 4>::type padding_row_4_t;
  typedef typename pooling_select_padding_type<ZONE, 5>::type padding_row_5_t;
  typedef typename pooling_select_padding_type<ZONE, 6>::type padding_row_6_t;
  typedef typename pooling_select_padding_type<ZONE, 7>::type padding_row_7_t;

  typedef typename pooling_select_padded_type<ZONE, 0>::type padded_row_0_t;
  typedef typename pooling_select_padded_type<ZONE, 1>::type padded_row_1_t;
  typedef typename pooling_select_padded_type<ZONE, 2>::type padded_row_2_t;
  typedef typename pooling_select_padded_type<ZONE, 3>::type padded_row_3_t;
  typedef typename pooling_select_padded_type<ZONE, 4>::type padded_row_4_t;
  typedef typename pooling_select_padded_type<ZONE, 5>::type padded_row_5_t;
  typedef typename pooling_select_padded_type<ZONE, 6>::type padded_row_6_t;
  typedef typename pooling_select_padded_type<ZONE, 7>::type padded_row_7_t;

  const padded_row_0_t padded_row_0 = (padding_row_0_t(0), pooling_in[0], padding_row_0_t(0));
  const padded_row_1_t padded_row_1 = (padding_row_1_t(0), pooling_in[1], padding_row_1_t(0));
  const padded_row_2_t padded_row_2 = (padding_row_2_t(0), pooling_in[2], padding_row_2_t(0));
  const padded_row_3_t padded_row_3 = (padding_row_3_t(0), pooling_in[3], padding_row_3_t(0));
  const padded_row_4_t padded_row_4 = (padding_row_4_t(0), pooling_in[4], padding_row_4_t(0));
  const padded_row_5_t padded_row_5 = (padding_row_5_t(0), pooling_in[5], padding_row_5_t(0));
  const padded_row_6_t padded_row_6 = (padding_row_6_t(0), pooling_in[6], padding_row_6_t(0));
  const padded_row_7_t padded_row_7 = (padding_row_7_t(0), pooling_in[7], padding_row_7_t(0));

  // Loop over columns
  for (unsigned col = 0; col < num_img_cols; col++) {

#pragma HLS UNROLL factor=num_img_cols/pooling_reuse_factor

    pooling_col_op<ZONE>(
      padded_row_0.range(col + (padding_row_0_t::width * 2), col),
      padded_row_1.range(col + (padding_row_1_t::width * 2), col),
      padded_row_2.range(col + (padding_row_2_t::width * 2), col),
      padded_row_3.range(col + (padding_row_3_t::width * 2), col),
      padded_row_4.range(col + (padding_row_4_t::width * 2), col),
      padded_row_5.range(col + (padding_row_5_t::width * 2), col),
      padded_row_6.range(col + (padding_row_6_t::width * 2), col),
      padded_row_7.range(col + (padding_row_7_t::width * 2), col),
      pooling_out[col]
    );
  }  // end loop over columns
}


// _____________________________________________________________________________
// Entry point

template <int ZONE>
void pooling_layer(
    const pooling_in_t pooling_in[N_POOLING_IN],
    pooling_out_t pooling_out[N_POOLING_OUT]
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE region

  // Check assumptions
  static_assert(N_POOLING_IN == num_img_rows, "N_POOLING_IN check failed");
  static_assert(N_POOLING_OUT == num_img_cols, "N_POOLING_OUT check failed");
  static_assert(num_img_rows == 8, "num_img_rows must be 8");
  static_assert(num_patterns == 7, "num_patterns must be 7");

  pooling_op<ZONE>(pooling_in, pooling_out);
}

}  // namespace emtf

#endif  // __EMTF_HLSLIB_POOLING_H__ not defined
