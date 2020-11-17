#ifndef __EMTF_HLSLIB_POOLING_H__
#define __EMTF_HLSLIB_POOLING_H__

namespace emtf {

namespace detail {

constexpr static const int windows_col_reference = 55;

constexpr static const int windows_col_start_zone_0_patt_0[num_img_rows] = {51, 51, 52, 54, 54, 54, 54, 54};
constexpr static const int windows_col_start_zone_0_patt_1[num_img_rows] = {43, 43, 46, 53, 54, 55, 55, 55};
constexpr static const int windows_col_start_zone_0_patt_2[num_img_rows] = {57, 57, 56, 54, 54, 53, 53, 53};
constexpr static const int windows_col_start_zone_0_patt_3[num_img_rows] = {34, 35, 39, 53, 54, 54, 54, 53};
constexpr static const int windows_col_start_zone_0_patt_4[num_img_rows] = {61, 62, 59, 54, 54, 51, 50, 49};
constexpr static const int windows_col_start_zone_0_patt_5[num_img_rows] = {21, 23, 29, 52, 54, 52, 50, 46};
constexpr static const int windows_col_start_zone_0_patt_6[num_img_rows] = {65, 67, 62, 54, 54, 48, 47, 45};
constexpr static const int windows_col_start_zone_1_patt_0[num_img_rows] = {50, 51, 53, 54, 54, 54, 54, 54};
constexpr static const int windows_col_start_zone_1_patt_1[num_img_rows] = {39, 41, 48, 53, 54, 55, 55, 54};
constexpr static const int windows_col_start_zone_1_patt_2[num_img_rows] = {59, 58, 55, 54, 54, 53, 53, 53};
constexpr static const int windows_col_start_zone_1_patt_3[num_img_rows] = {27, 30, 44, 53, 54, 52, 51, 47};
constexpr static const int windows_col_start_zone_1_patt_4[num_img_rows] = {66, 64, 57, 54, 54, 52, 51, 51};
constexpr static const int windows_col_start_zone_1_patt_5[num_img_rows] = {19, 19, 41, 52, 54, 41, 34, 23};
constexpr static const int windows_col_start_zone_1_patt_6[num_img_rows] = {71, 68, 57, 53, 54, 51, 51, 52};
constexpr static const int windows_col_start_zone_2_patt_0[num_img_rows] = {53, 53, 54, 54, 54, 54, 54, 54};
constexpr static const int windows_col_start_zone_2_patt_1[num_img_rows] = {50, 50, 53, 54, 54, 54, 54, 54};
constexpr static const int windows_col_start_zone_2_patt_2[num_img_rows] = {55, 55, 54, 54, 54, 53, 54, 53};
constexpr static const int windows_col_start_zone_2_patt_3[num_img_rows] = {47, 48, 53, 54, 52, 51, 49, 48};
constexpr static const int windows_col_start_zone_2_patt_4[num_img_rows] = {57, 56, 54, 54, 53, 53, 53, 52};
constexpr static const int windows_col_start_zone_2_patt_5[num_img_rows] = {43, 45, 52, 54, 46, 40, 37, 31};
constexpr static const int windows_col_start_zone_2_patt_6[num_img_rows] = {57, 56, 53, 54, 53, 52, 52, 52};

constexpr static const int windows_col_mid_zone_0_patt_0[num_img_rows]   = {55, 55, 55, 55, 55, 55, 55, 55};
constexpr static const int windows_col_mid_zone_0_patt_1[num_img_rows]   = {49, 49, 50, 55, 55, 56, 56, 56};
constexpr static const int windows_col_mid_zone_0_patt_2[num_img_rows]   = {61, 61, 60, 55, 55, 54, 54, 54};
constexpr static const int windows_col_mid_zone_0_patt_3[num_img_rows]   = {42, 42, 45, 54, 55, 57, 57, 57};
constexpr static const int windows_col_mid_zone_0_patt_4[num_img_rows]   = {68, 68, 65, 56, 55, 53, 53, 53};
constexpr static const int windows_col_mid_zone_0_patt_5[num_img_rows]   = {33, 33, 39, 54, 55, 57, 56, 55};
constexpr static const int windows_col_mid_zone_0_patt_6[num_img_rows]   = {77, 77, 71, 56, 55, 53, 54, 55};
constexpr static const int windows_col_mid_zone_1_patt_0[num_img_rows]   = {55, 55, 55, 55, 55, 55, 55, 55};
constexpr static const int windows_col_mid_zone_1_patt_1[num_img_rows]   = {46, 47, 52, 55, 55, 56, 56, 56};
constexpr static const int windows_col_mid_zone_1_patt_2[num_img_rows]   = {64, 63, 58, 55, 55, 54, 54, 54};
constexpr static const int windows_col_mid_zone_1_patt_3[num_img_rows]   = {35, 39, 49, 54, 55, 55, 55, 53};
constexpr static const int windows_col_mid_zone_1_patt_4[num_img_rows]   = {75, 71, 61, 56, 55, 55, 55, 57};
constexpr static const int windows_col_mid_zone_1_patt_5[num_img_rows]   = {28, 31, 47, 55, 55, 50, 45, 40};
constexpr static const int windows_col_mid_zone_1_patt_6[num_img_rows]   = {82, 79, 63, 55, 55, 60, 65, 70};
constexpr static const int windows_col_mid_zone_2_patt_0[num_img_rows]   = {55, 55, 55, 55, 55, 55, 55, 55};
constexpr static const int windows_col_mid_zone_2_patt_1[num_img_rows]   = {52, 53, 55, 55, 55, 55, 55, 55};
constexpr static const int windows_col_mid_zone_2_patt_2[num_img_rows]   = {58, 57, 55, 55, 55, 55, 55, 55};
constexpr static const int windows_col_mid_zone_2_patt_3[num_img_rows]   = {50, 51, 54, 55, 55, 54, 54, 53};
constexpr static const int windows_col_mid_zone_2_patt_4[num_img_rows]   = {60, 59, 56, 55, 55, 56, 56, 57};
constexpr static const int windows_col_mid_zone_2_patt_5[num_img_rows]   = {48, 49, 55, 55, 53, 49, 48, 45};
constexpr static const int windows_col_mid_zone_2_patt_6[num_img_rows]   = {62, 61, 55, 55, 57, 61, 62, 65};

constexpr static const int windows_col_stop_zone_0_patt_0[num_img_rows]  = {59, 59, 58, 56, 56, 56, 56, 56};
constexpr static const int windows_col_stop_zone_0_patt_1[num_img_rows]  = {53, 53, 54, 56, 56, 57, 57, 57};
constexpr static const int windows_col_stop_zone_0_patt_2[num_img_rows]  = {67, 67, 64, 57, 56, 55, 55, 55};
constexpr static const int windows_col_stop_zone_0_patt_3[num_img_rows]  = {49, 48, 51, 56, 56, 59, 60, 61};
constexpr static const int windows_col_stop_zone_0_patt_4[num_img_rows]  = {76, 75, 71, 57, 56, 56, 56, 57};
constexpr static const int windows_col_stop_zone_0_patt_5[num_img_rows]  = {45, 43, 48, 56, 56, 62, 63, 65};
constexpr static const int windows_col_stop_zone_0_patt_6[num_img_rows]  = {89, 87, 81, 58, 56, 58, 60, 64};
constexpr static const int windows_col_stop_zone_1_patt_0[num_img_rows]  = {60, 59, 57, 56, 56, 56, 56, 56};
constexpr static const int windows_col_stop_zone_1_patt_1[num_img_rows]  = {51, 52, 55, 56, 56, 57, 57, 57};
constexpr static const int windows_col_stop_zone_1_patt_2[num_img_rows]  = {71, 69, 62, 57, 56, 55, 55, 56};
constexpr static const int windows_col_stop_zone_1_patt_3[num_img_rows]  = {44, 46, 53, 56, 56, 58, 59, 59};
constexpr static const int windows_col_stop_zone_1_patt_4[num_img_rows]  = {83, 80, 66, 57, 56, 58, 59, 63};
constexpr static const int windows_col_stop_zone_1_patt_5[num_img_rows]  = {39, 42, 53, 57, 56, 59, 59, 58};
constexpr static const int windows_col_stop_zone_1_patt_6[num_img_rows]  = {91, 91, 69, 58, 56, 69, 76, 87};
constexpr static const int windows_col_stop_zone_2_patt_0[num_img_rows]  = {57, 57, 56, 56, 56, 56, 56, 56};
constexpr static const int windows_col_stop_zone_2_patt_1[num_img_rows]  = {55, 55, 56, 56, 56, 57, 56, 57};
constexpr static const int windows_col_stop_zone_2_patt_2[num_img_rows]  = {60, 60, 57, 56, 56, 56, 56, 56};
constexpr static const int windows_col_stop_zone_2_patt_3[num_img_rows]  = {53, 54, 56, 56, 57, 57, 57, 58};
constexpr static const int windows_col_stop_zone_2_patt_4[num_img_rows]  = {63, 62, 57, 56, 58, 59, 61, 62};
constexpr static const int windows_col_stop_zone_2_patt_5[num_img_rows]  = {53, 54, 57, 56, 57, 58, 58, 58};
constexpr static const int windows_col_stop_zone_2_patt_6[num_img_rows]  = {67, 65, 58, 56, 64, 70, 73, 79};

constexpr static const int paddings_zone_0[num_img_rows] = {34, 32, 26,  3,  1,  7,  8, 10};
constexpr static const int paddings_zone_1[num_img_rows] = {36, 36, 14,  3,  1, 14, 21, 32};
constexpr static const int paddings_zone_2[num_img_rows] = {12, 10,  3,  1,  9, 15, 18, 24};

constexpr static const int activations_zone_0[1u << num_img_rows] = {
   0, 18, 14, 26,  7, 33, 26, 38,  3, 39, 20, 45, 10, 49, 36, 54,  1, 19,
  15, 27,  9, 34, 30, 43,  5, 41, 22, 46, 12, 51, 38, 55,  0, 18, 14, 27,
   8, 33, 28, 38,  4, 41, 22, 45, 11, 50, 37, 54,  2, 20, 16, 29,  9, 34,
  32, 46,  6, 41, 24, 47, 14, 52, 47, 57,  0, 18, 14, 27,  8, 35, 28, 43,
   4, 40, 21, 45, 11, 53, 37, 56,  2, 20, 15, 29, 10, 37, 31, 49,  5, 44,
  23, 48, 13, 56, 40, 58,  1, 19, 15, 27,  9, 35, 30, 43,  5, 42, 23, 46,
  12, 54, 39, 57,  2, 21, 17, 30, 11, 44, 36, 53,  6, 45, 25, 50, 22, 58,
  52, 60,  0, 19, 15, 28,  8, 34, 29, 40,  4, 41, 22, 46, 11, 51, 37, 55,
   2, 21, 16, 31, 10, 49, 32, 55,  6, 44, 24, 48, 13, 57, 42, 59,  1, 20,
  16, 30,  8, 34, 31, 44,  5, 43, 24, 48, 12, 52, 40, 58,  3, 24, 18, 33,
  13, 58, 39, 60,  7, 49, 32, 53, 26, 61, 56, 62,  1, 19, 16, 29,  9, 36,
  31, 47,  4, 42, 23, 47, 12, 57, 38, 59,  3, 25, 17, 35, 13, 59, 36, 61,
   7, 54, 25, 56, 28, 62, 51, 63,  3, 23, 17, 32, 10, 48, 33, 55,  6, 50,
  25, 52, 21, 60, 50, 62,  7, 39, 26, 51, 35, 62, 59, 63, 17, 60, 42, 61,
  53, 63, 61, 63
};

constexpr static const int activations_zone_1[1u << num_img_rows] = {
   0,  2, 24, 29,  0,  2, 24, 29,  3,  7, 31, 38,  4,  8, 31, 39, 10, 13,
  38, 45, 10, 14, 38, 46, 17, 20, 48, 53, 17, 20, 49, 53,  0,  2, 25, 31,
   6,  7, 26, 33,  4,  8, 31, 40,  7, 11, 32, 42, 10, 14, 39, 48, 13, 16,
  40, 49, 18, 21, 50, 55, 19, 23, 50, 55,  0,  2, 25, 30,  1,  3, 25, 30,
   4,  8, 32, 41,  5,  9, 33, 41, 11, 15, 40, 47, 11, 15, 41, 47, 19, 23,
  51, 55, 20, 23, 51, 56,  1,  3, 27, 34, 12, 15, 28, 36,  5,  9, 34, 43,
  14, 18, 36, 45, 12, 16, 43, 51, 19, 22, 44, 52, 21, 28, 52, 58, 26, 29,
  53, 59,  1,  3, 25, 30,  7,  9, 27, 35,  5,  8, 32, 40,  9, 13, 33, 42,
  11, 14, 39, 47, 16, 18, 41, 49, 18, 22, 50, 57, 21, 26, 50, 57,  5,  6,
  27, 37, 37, 42, 46, 54,  6, 12, 34, 47, 38, 43, 48, 55, 13, 19, 44, 56,
  42, 45, 52, 60, 21, 28, 52, 61, 44, 48, 56, 62,  1,  4, 26, 33, 22, 24,
  35, 39,  6, 10, 34, 44, 23, 27, 36, 49, 12, 17, 43, 53, 28, 30, 46, 54,
  24, 35, 54, 62, 35, 37, 56, 63, 15, 17, 32, 45, 57, 58, 59, 61, 16, 20,
  37, 54, 57, 59, 59, 62, 22, 29, 51, 61, 58, 60, 61, 63, 36, 46, 60, 63,
  58, 60, 62, 63
};

constexpr static const int activations_zone_2[1u << num_img_rows] = {
   0, 11, 24, 43,  4, 20, 30, 52,  1, 13, 26, 45,  8, 22, 35, 55,  0, 11,
  25, 43,  5, 20, 31, 53,  3, 14, 27, 46, 10, 24, 37, 56,  3, 15, 29, 47,
   9, 28, 39, 57,  4, 17, 30, 48, 14, 35, 42, 59,  3, 16, 30, 48, 10, 29,
  40, 58,  7, 19, 32, 51, 19, 40, 43, 61,  0, 11, 25, 43,  4, 20, 31, 52,
   2, 13, 26, 45,  8, 23, 36, 56,  0, 12, 25, 44,  6, 21, 33, 54, 15, 23,
  34, 51, 34, 46, 46, 61,  3, 16, 29, 47, 10, 28, 40, 58,  5, 18, 31, 51,
  17, 39, 42, 61,  4, 17, 30, 49, 12, 37, 41, 60, 23, 39, 41, 59, 48, 59,
  58, 63,  1, 11, 25, 44,  6, 20, 33, 53,  2, 13, 27, 45,  9, 24, 37, 55,
   1, 12, 26, 45,  7, 22, 34, 54,  5, 16, 28, 47, 14, 32, 39, 57,  5, 16,
  31, 49, 13, 35, 41, 59,  7, 18, 33, 50, 19, 40, 44, 60,  6, 18, 32, 50,
  17, 38, 42, 60,  9, 22, 36, 54, 24, 51, 52, 62,  1, 12, 26, 44,  7, 21,
  33, 53,  2, 15, 27, 47, 10, 29, 38, 56,  2, 14, 27, 46,  9, 28, 36, 56,
  19, 36, 38, 57, 41, 57, 54, 63,  6, 18, 32, 49, 15, 37, 42, 60,  8, 22,
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
struct pooling_get_activation_op {};

template <> struct pooling_get_activation_op<0> { inline int operator ()(int i) const { return detail::activations_zone_0[i]; } };
template <> struct pooling_get_activation_op<1> { inline int operator ()(int i) const { return detail::activations_zone_1[i]; } };
template <> struct pooling_get_activation_op<2> { inline int operator ()(int i) const { return detail::activations_zone_2[i]; } };

template <int ZONE>
struct pooling_get_col_start_op {};

template <int ZONE>
struct pooling_get_col_mid_op {};

template <int ZONE>
struct pooling_get_col_stop_op {};

// Implement the pooling_get_blah_op by using text replacement macros ("token pasting")
// It defines the following for 'col_start':
//     template <> struct pooling_get_col_start_op<0> { inline int operator ()(int i, int j) const { ... } };
//     template <> struct pooling_get_col_start_op<1> { inline int operator ()(int i, int j) const { ... } };
//     template <> struct pooling_get_col_start_op<2> { inline int operator ()(int i, int j) const { ... } };
// and similarly for 'col_mid' and 'col_stop'.
// The operator ()(int i, int j) takes patt 'i' and row 'j'.
#define DEFINE_NICE_OPS_POOLING(ZONE, NAME) \
    template <> struct pooling_get_##NAME##_op<ZONE> { \
      inline int operator ()(int i, int j) const { \
        const int ref = detail::windows_col_reference; \
        const int pad = detail::paddings_zone_##ZONE[j]; \
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

DEFINE_NICE_OPS_POOLING(0, col_start)
DEFINE_NICE_OPS_POOLING(1, col_start)
DEFINE_NICE_OPS_POOLING(2, col_start)
DEFINE_NICE_OPS_POOLING(0, col_mid)
DEFINE_NICE_OPS_POOLING(1, col_mid)
DEFINE_NICE_OPS_POOLING(2, col_mid)
DEFINE_NICE_OPS_POOLING(0, col_stop)
DEFINE_NICE_OPS_POOLING(1, col_stop)
DEFINE_NICE_OPS_POOLING(2, col_stop)
#undef DEFINE_NICE_OPS_POOLING

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
  static_assert(T_OUT::width == 8, "T_OUT type check failed");

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
