#ifndef __EMTF_HLSLIB_POOLING_H__
#define __EMTF_HLSLIB_POOLING_H__

namespace emtf {

// Function to apply activation
template <typename Zone, typename T_IN, typename T_OUT>
void pooling_activate_op(const T_IN& in0, T_OUT& out) {
  static_assert(is_same<T_IN, dio_row_accum_t>::value, "T_IN type check failed");
  static_assert(is_same<T_OUT, trk_qual_t>::value, "T_OUT type check failed");

#pragma HLS PIPELINE II=pooling_config::target_ii

#pragma HLS INTERFACE ap_ctrl_none port=return

//#pragma HLS INLINE

  const unsigned int N = (1u << T_IN::width);

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
  emtf_assert(in0 < N);
  out = static_cast<T_OUT>(lookup_table[in0]);
}

// Function to find max activation, keeping pattern number
template <typename T_IN, typename T_OUT>
void pooling_reduce_argmax_op(const T_IN in0[num_emtf_patterns], T_OUT& out) {
  static_assert(is_same<T_IN, trk_qual_t>::value, "T_IN type check failed");
  static_assert(is_same<T_OUT, pooling_out_t>::value, "T_OUT type check failed");

#pragma HLS PIPELINE II=pooling_config::target_ii

#pragma HLS INTERFACE ap_ctrl_none port=return

//#pragma HLS INLINE

  typedef trk_patt_t idx_t;  // encodes 0..6
  typedef trk_qual_t data_t;
  typedef details::argsort_pair<idx_t, data_t> pair_t;

  // Binary tree structure
  const unsigned int N = details::ceil_mul4<num_emtf_patterns>::value;  // round up to 8
  const unsigned int num_nodes = (2 * N) - 1;  // only works if N is multiple of 2
  const unsigned int num_nodes_last = N;  // last level
  const unsigned int num_nodes_above_last = N - 1;

  pair_t nodes[num_nodes];

#pragma HLS DATA_PACK variable=nodes

#pragma HLS ARRAY_PARTITION variable=nodes complete dim=0

  // Fetch input
  // Note that in0[0] is inserted twice to round up to 8
  nodes[(num_nodes - 1) - 0] = pair_t(idx_t(6), in0[6]);
  nodes[(num_nodes - 1) - 1] = pair_t(idx_t(5), in0[5]);
  nodes[(num_nodes - 1) - 2] = pair_t(idx_t(4), in0[4]);
  nodes[(num_nodes - 1) - 3] = pair_t(idx_t(3), in0[3]);
  nodes[(num_nodes - 1) - 4] = pair_t(idx_t(2), in0[2]);
  nodes[(num_nodes - 1) - 5] = pair_t(idx_t(1), in0[1]);
  nodes[(num_nodes - 1) - 6] = pair_t(idx_t(0), in0[0]);
  nodes[(num_nodes - 1) - 7] = pair_t(idx_t(0), in0[0]);

  // Binary-tree reduce
  LOOP_NOD: for (unsigned i = 0; i < num_nodes_above_last; i++) {

#pragma HLS UNROLL

    const unsigned int node_index = (num_nodes_above_last - 1) - i;
    const unsigned int child_l_index = (2 * node_index) + 1;
    const unsigned int child_r_index = (2 * node_index) + 2;
    nodes[node_index] = (nodes[child_l_index] >= nodes[child_r_index]) ? nodes[child_l_index] : nodes[child_r_index];
  }

  // Output
  out = (nodes[0].first, nodes[0].second);
}

// _____________________________________________________________________________
// Apply the patterns at a particular column

template <typename Zone>
void pooling_col_op(
    const dio_row_accum_t preactivations_col_j[num_emtf_patterns],
    pooling_out_t& pooling_out_col_j
) {

#pragma HLS PIPELINE II=pooling_config::target_ii

#pragma HLS INTERFACE ap_ctrl_none port=return

//#pragma HLS INLINE

  trk_qual_t activations_col_j[num_emtf_patterns];

#pragma HLS ARRAY_PARTITION variable=activations_col_j complete dim=0

  // Loop over patterns
  LOOP_PATT_2: for (unsigned patt = 0; patt < num_emtf_patterns; patt++) {

#pragma HLS UNROLL

    // Activation at (col, patt)
    pooling_activate_op<Zone>(preactivations_col_j[patt], activations_col_j[patt]);
  }  // end loop over patterns

  // Find max activation
  pooling_reduce_argmax_op(activations_col_j, pooling_out_col_j);
}

template <typename Zone>
void pooling_col_fused_op(
    const typename details::select_pattern_col_fused_patch_type<Zone, 0>::type& patch_row_0,
    const typename details::select_pattern_col_fused_patch_type<Zone, 1>::type& patch_row_1,
    const typename details::select_pattern_col_fused_patch_type<Zone, 2>::type& patch_row_2,
    const typename details::select_pattern_col_fused_patch_type<Zone, 3>::type& patch_row_3,
    const typename details::select_pattern_col_fused_patch_type<Zone, 4>::type& patch_row_4,
    const typename details::select_pattern_col_fused_patch_type<Zone, 5>::type& patch_row_5,
    const typename details::select_pattern_col_fused_patch_type<Zone, 6>::type& patch_row_6,
    const typename details::select_pattern_col_fused_patch_type<Zone, 7>::type& patch_row_7,
    pooling_out_t pooling_out_col_fused_j[pooling_config::fusion_factor]
) {

#pragma HLS PIPELINE II=pooling_config::target_ii

#pragma HLS INTERFACE ap_ctrl_none port=return

//#pragma HLS INLINE

  int pattern_col_start_table[num_emtf_patterns * num_emtf_img_rows];
  details::init_2d_table_op<num_emtf_patterns, num_emtf_img_rows>(pattern_col_start_table, details::get_pattern_col_start_op<Zone>());

  int pattern_col_stop_table[num_emtf_patterns * num_emtf_img_rows];
  details::init_2d_table_op<num_emtf_patterns, num_emtf_img_rows>(pattern_col_stop_table, details::get_pattern_col_stop_op<Zone>());

  const int fusion_factor = pooling_config::fusion_factor;

  dio_row_accum_t preactivations[fusion_factor * num_emtf_patterns];

#pragma HLS ARRAY_PARTITION variable=preactivations complete dim=0

  // Loop over patterns
  LOOP_PATT_1: for (unsigned patt = 0; patt < num_emtf_patterns; patt++) {

#pragma HLS UNROLL

    // Loop over columns
    LOOP_COL_1: for (unsigned col = 0; col < fusion_factor; col++) {

#pragma HLS UNROLL

      // Preactivation at (col, patt)
      const unsigned int table_index = (patt * num_emtf_img_rows);
      auto& preactivation = preactivations[(col * num_emtf_patterns) + patt];
      preactivation[0] = (bool) patch_row_0.range(col + pattern_col_stop_table[table_index + 0], col + pattern_col_start_table[table_index + 0]);
      preactivation[1] = (bool) patch_row_1.range(col + pattern_col_stop_table[table_index + 1], col + pattern_col_start_table[table_index + 1]);
      preactivation[2] = (bool) patch_row_2.range(col + pattern_col_stop_table[table_index + 2], col + pattern_col_start_table[table_index + 2]);
      preactivation[3] = (bool) patch_row_3.range(col + pattern_col_stop_table[table_index + 3], col + pattern_col_start_table[table_index + 3]);
      preactivation[4] = (bool) patch_row_4.range(col + pattern_col_stop_table[table_index + 4], col + pattern_col_start_table[table_index + 4]);
      preactivation[5] = (bool) patch_row_5.range(col + pattern_col_stop_table[table_index + 5], col + pattern_col_start_table[table_index + 5]);
      preactivation[6] = (bool) patch_row_6.range(col + pattern_col_stop_table[table_index + 6], col + pattern_col_start_table[table_index + 6]);
      preactivation[7] = (bool) patch_row_7.range(col + pattern_col_stop_table[table_index + 7], col + pattern_col_start_table[table_index + 7]);
    }  // end loop over columns
  }  // end loop over patterns

  // Loop over columns
  LOOP_COL_2: for (unsigned col = 0; col < fusion_factor; col++) {

#pragma HLS UNROLL

    pooling_col_op<Zone>(
        stl_next(preactivations, col * num_emtf_patterns),
        pooling_out_col_fused_j[col]
    );
  }  // end loop over columns
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

  const int fusion_factor = pooling_config::fusion_factor;

  // Loop over columns with certain step size
  LOOP_COL_FUSED: for (unsigned col = 0; col < num_emtf_img_cols; col += fusion_factor) {

#pragma HLS UNROLL

    pooling_col_fused_op<Zone>(
        padded_row_0.range(col + (fusion_factor - 1) + (padding_row_0_t::width * 2), col),
        padded_row_1.range(col + (fusion_factor - 1) + (padding_row_1_t::width * 2), col),
        padded_row_2.range(col + (fusion_factor - 1) + (padding_row_2_t::width * 2), col),
        padded_row_3.range(col + (fusion_factor - 1) + (padding_row_3_t::width * 2), col),
        padded_row_4.range(col + (fusion_factor - 1) + (padding_row_4_t::width * 2), col),
        padded_row_5.range(col + (fusion_factor - 1) + (padding_row_5_t::width * 2), col),
        padded_row_6.range(col + (fusion_factor - 1) + (padding_row_6_t::width * 2), col),
        padded_row_7.range(col + (fusion_factor - 1) + (padding_row_7_t::width * 2), col),
        stl_next(pooling_out, col)
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
