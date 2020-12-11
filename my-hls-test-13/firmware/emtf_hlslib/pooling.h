#ifndef __EMTF_HLSLIB_POOLING_H__
#define __EMTF_HLSLIB_POOLING_H__

namespace emtf {

// Function to set accumulator value
template <typename T0, typename T1, typename T2, typename T3,
          typename T4, typename T5, typename T6, typename T7,
          typename T_OUT>
void pooling_accumulate_op(
    const T0& in0, const T1& in1, const T2& in2, const T3& in3,
    const T4& in4, const T5& in5, const T6& in6, const T7& in7,
    T_OUT& out
) {
  static_assert(T_OUT::width == 8, "T_OUT type check failed");

#pragma HLS PIPELINE II=pooling_config::target_ii

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE

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
template <typename Zone, typename T_IN, typename T_OUT>
void pooling_activate_op(const T_IN& in0, T_OUT& out) {
  static_assert(is_same<T_IN, pooling_accumulation_t>::value, "T_IN type check failed");
  static_assert(is_same<T_OUT, pooling_activation_t>::value, "T_OUT type check failed");

#pragma HLS PIPELINE II=pooling_config::target_ii

#pragma HLS INTERFACE ap_ctrl_none port=return

//#pragma HLS INLINE

  const unsigned int N = (1u << num_emtf_img_rows);

#if !defined(__SYNTHESIS__)
  static bool initialized = false;
  static int lookup_table[N];
#else
  bool initialized = false;
  int lookup_table[N];
#endif

  if (!initialized) {
    details::init_table_op<N>(lookup_table, details::get_pattern_activation_op<Zone>());
    initialized = true;
  }

  // Lookup
  out = (T_OUT) lookup_table[in0];
}

// Function to find max activation, keeping pattern number
template <typename T_IN, typename T_OUT>
void pooling_reduce_argmax_op(const T_IN in0[num_emtf_patterns], T_OUT& out) {
  static_assert(is_same<T_IN, pooling_activation_t>::value, "T_IN type check failed");
  static_assert(is_same<T_OUT, pooling_out_t>::value, "T_OUT type check failed");

#pragma HLS PIPELINE II=pooling_config::target_ii

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE

  typedef pooling_patt_t idx_t;
  typedef pooling_activation_t data_t;
  using pair_t = details::argsort_pair<idx_t, data_t>;

  // Stage 0: concatenate index and data.
  const pair_t tmp_0_0(idx_t(0), in0[0]);
  const pair_t tmp_0_1(idx_t(1), in0[1]);
  const pair_t tmp_0_2(idx_t(2), in0[2]);
  const pair_t tmp_0_3(idx_t(3), in0[3]);
  const pair_t tmp_0_4(idx_t(4), in0[4]);
  const pair_t tmp_0_5(idx_t(5), in0[5]);
  const pair_t tmp_0_6(idx_t(6), in0[6]);

  // Stage 1
  const pair_t tmp_1_0 = tmp_0_0;
  const pair_t tmp_1_1 = (tmp_0_1 >= tmp_0_2) ? tmp_0_1 : tmp_0_2;
  const pair_t tmp_1_2 = (tmp_0_3 >= tmp_0_4) ? tmp_0_3 : tmp_0_4;
  const pair_t tmp_1_3 = (tmp_0_5 >= tmp_0_6) ? tmp_0_5 : tmp_0_6;

  // Stage 2
  const pair_t tmp_2_0 = (tmp_1_0 >= tmp_1_1) ? tmp_1_0 : tmp_1_1;
  const pair_t tmp_2_1 = (tmp_1_2 >= tmp_1_3) ? tmp_1_2 : tmp_1_3;

  // Stage 3
  const pair_t tmp_3_0 = (tmp_2_0 >= tmp_2_1) ? tmp_2_0 : tmp_2_1;

  // Output (incl pattern number)
  out = (tmp_3_0.first, tmp_3_0.second);
}

// _____________________________________________________________________________
// Apply the patterns at a particular column

template <typename Zone>
void pooling_col_op(
    const typename details::select_pattern_col_patch_type<Zone, 0>::type patch_row_0,
    const typename details::select_pattern_col_patch_type<Zone, 1>::type patch_row_1,
    const typename details::select_pattern_col_patch_type<Zone, 2>::type patch_row_2,
    const typename details::select_pattern_col_patch_type<Zone, 3>::type patch_row_3,
    const typename details::select_pattern_col_patch_type<Zone, 4>::type patch_row_4,
    const typename details::select_pattern_col_patch_type<Zone, 5>::type patch_row_5,
    const typename details::select_pattern_col_patch_type<Zone, 6>::type patch_row_6,
    const typename details::select_pattern_col_patch_type<Zone, 7>::type patch_row_7,
    pooling_out_t& pooling_out_col_j
) {

#pragma HLS PIPELINE II=pooling_config::target_ii

#pragma HLS INTERFACE ap_ctrl_none port=return

//#pragma HLS INLINE

  int pattern_col_start_table[num_emtf_patterns * num_emtf_img_rows];
  details::init_2d_table_op<num_emtf_patterns, num_emtf_img_rows>(pattern_col_start_table, details::get_pattern_col_start_op<Zone>());

  int pattern_col_stop_table[num_emtf_patterns * num_emtf_img_rows];
  details::init_2d_table_op<num_emtf_patterns, num_emtf_img_rows>(pattern_col_stop_table, details::get_pattern_col_stop_op<Zone>());

  pooling_accumulation_t pooling_accumulations[num_emtf_patterns];
  pooling_activation_t pooling_activations[num_emtf_patterns];

#pragma HLS ARRAY_PARTITION variable=pooling_accumulations complete dim=0
#pragma HLS ARRAY_PARTITION variable=pooling_activations complete dim=0

  // Loop over patterns
  LOOP_PATT: for (unsigned patt = 0; patt < num_emtf_patterns; patt++) {

#pragma HLS UNROLL

    // Check pattern windows in each row
    pooling_accumulate_op(
        patch_row_0.range(pattern_col_stop_table[(patt * num_emtf_img_rows) + 0], pattern_col_start_table[(patt * num_emtf_img_rows) + 0]),
        patch_row_1.range(pattern_col_stop_table[(patt * num_emtf_img_rows) + 1], pattern_col_start_table[(patt * num_emtf_img_rows) + 1]),
        patch_row_2.range(pattern_col_stop_table[(patt * num_emtf_img_rows) + 2], pattern_col_start_table[(patt * num_emtf_img_rows) + 2]),
        patch_row_3.range(pattern_col_stop_table[(patt * num_emtf_img_rows) + 3], pattern_col_start_table[(patt * num_emtf_img_rows) + 3]),
        patch_row_4.range(pattern_col_stop_table[(patt * num_emtf_img_rows) + 4], pattern_col_start_table[(patt * num_emtf_img_rows) + 4]),
        patch_row_5.range(pattern_col_stop_table[(patt * num_emtf_img_rows) + 5], pattern_col_start_table[(patt * num_emtf_img_rows) + 5]),
        patch_row_6.range(pattern_col_stop_table[(patt * num_emtf_img_rows) + 6], pattern_col_start_table[(patt * num_emtf_img_rows) + 6]),
        patch_row_7.range(pattern_col_stop_table[(patt * num_emtf_img_rows) + 7], pattern_col_start_table[(patt * num_emtf_img_rows) + 7]),
        pooling_accumulations[patt]
    );

    // Activation
    pooling_activate_op<Zone>(pooling_accumulations[patt], pooling_activations[patt]);
  }  // end loop over patterns

  // Find max activation
  pooling_reduce_argmax_op(pooling_activations, pooling_out_col_j);
}

// _____________________________________________________________________________
// Pooling op

template <typename Zone>
void pooling_op(
    const pooling_in_t pooling_in[pooling_config::n_in],
    pooling_out_t pooling_out[pooling_config::n_out]
) {

#pragma HLS PIPELINE II=pooling_config::target_ii

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE

  typedef typename details::select_pattern_col_padding_type<Zone, 0>::type padding_row_0_t;
  typedef typename details::select_pattern_col_padding_type<Zone, 1>::type padding_row_1_t;
  typedef typename details::select_pattern_col_padding_type<Zone, 2>::type padding_row_2_t;
  typedef typename details::select_pattern_col_padding_type<Zone, 3>::type padding_row_3_t;
  typedef typename details::select_pattern_col_padding_type<Zone, 4>::type padding_row_4_t;
  typedef typename details::select_pattern_col_padding_type<Zone, 5>::type padding_row_5_t;
  typedef typename details::select_pattern_col_padding_type<Zone, 6>::type padding_row_6_t;
  typedef typename details::select_pattern_col_padding_type<Zone, 7>::type padding_row_7_t;

  typedef typename details::select_pattern_col_padded_type<Zone, 0>::type padded_row_0_t;
  typedef typename details::select_pattern_col_padded_type<Zone, 1>::type padded_row_1_t;
  typedef typename details::select_pattern_col_padded_type<Zone, 2>::type padded_row_2_t;
  typedef typename details::select_pattern_col_padded_type<Zone, 3>::type padded_row_3_t;
  typedef typename details::select_pattern_col_padded_type<Zone, 4>::type padded_row_4_t;
  typedef typename details::select_pattern_col_padded_type<Zone, 5>::type padded_row_5_t;
  typedef typename details::select_pattern_col_padded_type<Zone, 6>::type padded_row_6_t;
  typedef typename details::select_pattern_col_padded_type<Zone, 7>::type padded_row_7_t;

  const padded_row_0_t padded_row_0 = (padding_row_0_t(0), pooling_in[0], padding_row_0_t(0));
  const padded_row_1_t padded_row_1 = (padding_row_1_t(0), pooling_in[1], padding_row_1_t(0));
  const padded_row_2_t padded_row_2 = (padding_row_2_t(0), pooling_in[2], padding_row_2_t(0));
  const padded_row_3_t padded_row_3 = (padding_row_3_t(0), pooling_in[3], padding_row_3_t(0));
  const padded_row_4_t padded_row_4 = (padding_row_4_t(0), pooling_in[4], padding_row_4_t(0));
  const padded_row_5_t padded_row_5 = (padding_row_5_t(0), pooling_in[5], padding_row_5_t(0));
  const padded_row_6_t padded_row_6 = (padding_row_6_t(0), pooling_in[6], padding_row_6_t(0));
  const padded_row_7_t padded_row_7 = (padding_row_7_t(0), pooling_in[7], padding_row_7_t(0));

  // Loop over columns
  LOOP_COL: for (unsigned col = 0; col < num_emtf_img_cols; col++) {

#pragma HLS UNROLL

    pooling_col_op<Zone>(
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

template <typename Zone>
void pooling_layer(
    const pooling_in_t pooling_in[pooling_config::n_in],
    pooling_out_t pooling_out[pooling_config::n_out]
) {

#pragma HLS PIPELINE II=pooling_config::target_ii

#pragma HLS INTERFACE ap_ctrl_none port=return

  // Check assumptions
  static_assert(pooling_config::n_in == num_emtf_img_rows, "pooling_config::n_in check failed");
  static_assert(pooling_config::n_out == num_emtf_img_cols, "pooling_config::n_out check failed");
  static_assert(num_emtf_img_rows == 8, "num_emtf_img_rows must be 8");
  static_assert(num_emtf_img_cols == 288, "num_emtf_img_cols must be 288");
  static_assert(num_emtf_patterns == 7, "num_emtf_patterns must be 7");

  pooling_op<Zone>(pooling_in, pooling_out);
}

}  // namespace emtf

#endif  // __EMTF_HLSLIB_POOLING_H__ not defined
