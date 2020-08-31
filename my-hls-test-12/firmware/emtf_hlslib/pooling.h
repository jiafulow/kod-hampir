#ifndef __EMTF_HLSLIB_POOLING_H__
#define __EMTF_HLSLIB_POOLING_H__

namespace emtf {

namespace detail {

constexpr static const int windows_col_offset = 55;

constexpr static const int windows_col_start_zone_0_row_0[num_patterns] = {51, 43, 57, 34, 61, 21, 65};
constexpr static const int windows_col_start_zone_0_row_1[num_patterns] = {51, 43, 57, 35, 62, 23, 67};
constexpr static const int windows_col_start_zone_0_row_2[num_patterns] = {52, 46, 56, 39, 59, 29, 62};
constexpr static const int windows_col_start_zone_0_row_3[num_patterns] = {54, 53, 54, 53, 55, 52, 55};
constexpr static const int windows_col_start_zone_0_row_4[num_patterns] = {54, 54, 54, 54, 54, 54, 54};
constexpr static const int windows_col_start_zone_0_row_5[num_patterns] = {54, 55, 53, 54, 51, 52, 48};
constexpr static const int windows_col_start_zone_0_row_6[num_patterns] = {54, 55, 53, 54, 50, 50, 47};
constexpr static const int windows_col_start_zone_0_row_7[num_patterns] = {54, 55, 53, 53, 49, 46, 45};

constexpr static const int windows_col_stop_zone_0_row_0[num_patterns] = {59, 53, 67, 49, 76, 45, 89};
constexpr static const int windows_col_stop_zone_0_row_1[num_patterns] = {59, 53, 67, 48, 75, 43, 87};
constexpr static const int windows_col_stop_zone_0_row_2[num_patterns] = {58, 54, 64, 51, 71, 48, 81};
constexpr static const int windows_col_stop_zone_0_row_3[num_patterns] = {56, 56, 57, 55, 57, 55, 58};
constexpr static const int windows_col_stop_zone_0_row_4[num_patterns] = {56, 56, 56, 56, 56, 56, 56};
constexpr static const int windows_col_stop_zone_0_row_5[num_patterns] = {56, 57, 55, 59, 56, 62, 58};
constexpr static const int windows_col_stop_zone_0_row_6[num_patterns] = {56, 57, 55, 60, 56, 63, 60};
constexpr static const int windows_col_stop_zone_0_row_7[num_patterns] = {56, 57, 55, 61, 57, 65, 64};

}  // namespace detail

template <int ZONE, int ROW, int PATT>
struct find_window_col_start {};

template <int PATT> struct find_window_col_start<0, 0, PATT> { static const int value = detail::windows_col_start_zone_0_row_0[PATT] - detail::windows_col_offset; };
template <int PATT> struct find_window_col_start<0, 1, PATT> { static const int value = detail::windows_col_start_zone_0_row_1[PATT] - detail::windows_col_offset; };
template <int PATT> struct find_window_col_start<0, 2, PATT> { static const int value = detail::windows_col_start_zone_0_row_2[PATT] - detail::windows_col_offset; };
template <int PATT> struct find_window_col_start<0, 3, PATT> { static const int value = detail::windows_col_start_zone_0_row_3[PATT] - detail::windows_col_offset; };
template <int PATT> struct find_window_col_start<0, 4, PATT> { static const int value = detail::windows_col_start_zone_0_row_4[PATT] - detail::windows_col_offset; };
template <int PATT> struct find_window_col_start<0, 5, PATT> { static const int value = detail::windows_col_start_zone_0_row_5[PATT] - detail::windows_col_offset; };
template <int PATT> struct find_window_col_start<0, 6, PATT> { static const int value = detail::windows_col_start_zone_0_row_6[PATT] - detail::windows_col_offset; };
template <int PATT> struct find_window_col_start<0, 7, PATT> { static const int value = detail::windows_col_start_zone_0_row_7[PATT] - detail::windows_col_offset; };

template <int ZONE, int ROW, int PATT>
struct find_window_col_stop {};

template <int PATT> struct find_window_col_stop<0, 0, PATT> { static const int value = detail::windows_col_stop_zone_0_row_0[PATT] - detail::windows_col_offset; };
template <int PATT> struct find_window_col_stop<0, 1, PATT> { static const int value = detail::windows_col_stop_zone_0_row_1[PATT] - detail::windows_col_offset; };
template <int PATT> struct find_window_col_stop<0, 2, PATT> { static const int value = detail::windows_col_stop_zone_0_row_2[PATT] - detail::windows_col_offset; };
template <int PATT> struct find_window_col_stop<0, 3, PATT> { static const int value = detail::windows_col_stop_zone_0_row_3[PATT] - detail::windows_col_offset; };
template <int PATT> struct find_window_col_stop<0, 4, PATT> { static const int value = detail::windows_col_stop_zone_0_row_4[PATT] - detail::windows_col_offset; };
template <int PATT> struct find_window_col_stop<0, 5, PATT> { static const int value = detail::windows_col_stop_zone_0_row_5[PATT] - detail::windows_col_offset; };
template <int PATT> struct find_window_col_stop<0, 6, PATT> { static const int value = detail::windows_col_stop_zone_0_row_6[PATT] - detail::windows_col_offset; };
template <int PATT> struct find_window_col_stop<0, 7, PATT> { static const int value = detail::windows_col_stop_zone_0_row_7[PATT] - detail::windows_col_offset; };

template <int ZONE, unsigned int N=256>
struct find_activation {
  static const unsigned int size = N;
  static const unsigned int array[size];
};

template <>
const unsigned int find_activation<0>::array[size] = {
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

template <int ZONE>
struct activation_fn {
  inline pooling_activation_t operator ()(const pooling_preactivation_trans_t& x) const {
    assert(0 <= x && x < find_activation<ZONE>::size);
    return find_activation<ZONE>::array[x];
  }
};


template <typename T_IN, typename T_OUT, int N_IN, int N_OUT>
void transpose_array(T_IN const (&in0)[N_IN], T_OUT (&out)[N_OUT]) {

#pragma HLS INLINE

  for (int i = 0; i < N_IN; i++) {
    for (int j = 0; j < N_OUT; j++) {
      out[j][i] = in0[i][j];
    }
  }
}

template <typename T_IN, typename T_OUT, int N_IN, int N_OUT, class OP>
void apply_activation(T_IN const (&in0)[N_IN], T_OUT (&out)[N_OUT], OP op) {

#pragma HLS INLINE

  for (int i = 0; i < N_IN; i++) {
    out[i] = op(in0[i]);
  }
}


template <int ZONE, int ROW, int PATT>
void pooling_patt_op(
    const pooling_in_t& pooling_in_row_k,
    pooling_preactivation_t& pooling_preactivation_row_k,
    const int col
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

//#pragma HLS function_instantiate variable=col

  constexpr int START = find_window_col_start<ZONE, ROW, PATT>::value;
  constexpr int STOP = find_window_col_stop<ZONE, ROW, PATT>::value;
  constexpr int PAD_START = (START < 0) ? -START : 1;
  constexpr int PAD_STOP = (STOP > 0) ? STOP : 1;
  constexpr int COLS = num_img_cols;
  constexpr int COLS_W_PADDING = COLS + PAD_START + PAD_STOP;

  // Check assumptions
  static_assert(STOP > START, "pattern window must be non zero");
  static_assert(PAD_START > 0 && PAD_STOP > 0, "padding must be non negative");
  static_assert(PAD_START + START >= 0, "padding + pattern window start must be a valid index");
  static_assert(COLS + PAD_START + STOP <= COLS_W_PADDING, "padding + pattern window stop must be a valid index");

  const ap_uint<CeilLog2<COLS_W_PADDING>::value> start = col + PAD_START + START;
  const ap_uint<CeilLog2<COLS_W_PADDING>::value> stop = col + PAD_START + STOP;
  const ap_uint<COLS_W_PADDING> tmp_in = (ap_uint<PAD_STOP>(0), pooling_in_row_k, ap_uint<PAD_START>(0));  // add padding to input
  pooling_preactivation_row_k[PATT] = tmp_in.range(stop, start);
}

template <int ZONE, int ROW>
void pooling_row_op(
    const pooling_in_t& pooling_in_row_k,
    pooling_preactivation_t& pooling_preactivation_row_k,
    const int col
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

//#pragma HLS function_instantiate variable=col

//#pragma HLS INLINE region

  pooling_preactivation_row_k = 0;  // initialize

  // Loop over patterns manually
  static_assert(num_patterns == 7, "num_patterns must be 7");

  pooling_patt_op<ZONE, ROW, 0>(pooling_in_row_k, pooling_preactivation_row_k, col);
  pooling_patt_op<ZONE, ROW, 1>(pooling_in_row_k, pooling_preactivation_row_k, col);
  pooling_patt_op<ZONE, ROW, 2>(pooling_in_row_k, pooling_preactivation_row_k, col);
  pooling_patt_op<ZONE, ROW, 3>(pooling_in_row_k, pooling_preactivation_row_k, col);
  pooling_patt_op<ZONE, ROW, 4>(pooling_in_row_k, pooling_preactivation_row_k, col);
  pooling_patt_op<ZONE, ROW, 5>(pooling_in_row_k, pooling_preactivation_row_k, col);
  pooling_patt_op<ZONE, ROW, 6>(pooling_in_row_k, pooling_preactivation_row_k, col);
}

template <int ZONE>
void pooling_col_op(
    const pooling_in_t pooling_in[N_POOLING_IN],
    pooling_out_t& pooling_out_col_l,
    const int col
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

//#pragma HLS function_instantiate variable=col

//#pragma HLS INLINE region

  pooling_preactivation_t pooling_preactivation[num_img_rows];

#pragma HLS ARRAY_PARTITION variable=pooling_preactivation complete dim=0

  // Loop over rows manually
  static_assert(num_img_rows == 8, "num_img_rows must be 8");

  pooling_row_op<ZONE, 0>(pooling_in[0], pooling_preactivation[0], col);
  pooling_row_op<ZONE, 1>(pooling_in[1], pooling_preactivation[1], col);
  pooling_row_op<ZONE, 2>(pooling_in[2], pooling_preactivation[2], col);
  pooling_row_op<ZONE, 3>(pooling_in[3], pooling_preactivation[3], col);
  pooling_row_op<ZONE, 4>(pooling_in[4], pooling_preactivation[4], col);
  pooling_row_op<ZONE, 5>(pooling_in[5], pooling_preactivation[5], col);
  pooling_row_op<ZONE, 6>(pooling_in[6], pooling_preactivation[6], col);
  pooling_row_op<ZONE, 7>(pooling_in[7], pooling_preactivation[7], col);

  pooling_preactivation_trans_t pooling_preactivation_trans[num_patterns];

#pragma HLS ARRAY_PARTITION variable=pooling_preactivation_trans complete dim=0

  transpose_array(pooling_preactivation, pooling_preactivation_trans);

  pooling_activation_t pooling_activation[num_patterns];

#pragma HLS ARRAY_PARTITION variable=pooling_activation complete dim=0

  apply_activation(pooling_preactivation_trans, pooling_activation, activation_fn<ZONE>());

  // Loop over patterns manually
  static_assert(num_patterns == 7, "num_patterns must be 7");

  pooling_out_col_l = pooling_activation[0]; //FIXME - reduce max
}

// Pooling op
template <int ZONE>
void pooling_op(
    const pooling_in_t pooling_in[N_POOLING_IN],
    pooling_out_t pooling_out[N_POOLING_OUT]
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

//#pragma HLS INLINE region

  for (int col = 0; col < num_img_cols; col++) {
    pooling_col_op<ZONE>(pooling_in, pooling_out[col], col);
  }
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

  pooling_op<ZONE>(pooling_in, pooling_out);
}

}  // namespace emtf

#endif  // __EMTF_HLSLIB_POOLING_H__ not defined
