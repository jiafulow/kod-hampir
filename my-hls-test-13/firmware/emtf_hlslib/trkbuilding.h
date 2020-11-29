#ifndef __EMTF_HLSLIB_TRKBUILDING_H__
#define __EMTF_HLSLIB_TRKBUILDING_H__

namespace emtf {

template <typename T0, typename T1, typename T_OUT>
void trkbuilding_reduce_argmin_ph_diff_op(const T0 in0[4], const T1 in1[4], T_OUT& out, bool& vld, m_20deg_chamber_tag) {
  static_assert(is_same<T0, trkbuilding_seg_t>::value, "T0 type check failed");
  static_assert(is_same<T1, trkbuilding_ph_diff_t>::value, "T1 type check failed");
  static_assert(is_same<T_OUT, T0>::value, "T_OUT type check failed");

#pragma HLS PIPELINE II=trkbuilding_config::target_ii

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE

  typedef ap_uint<2> idx_t;  // 0..3
  typedef T1 data_t;
  using pair_t = details::argsort_pair<idx_t, data_t>;

  // Stage 0: concatenate index and data
  const pair_t tmp_0_0(idx_t(0), in1[0]);
  const pair_t tmp_0_1(idx_t(1), in1[1]);
  const pair_t tmp_0_2(idx_t(2), in1[2]);
  const pair_t tmp_0_3(idx_t(3), in1[3]);

  // Stage 1
  const pair_t tmp_1_0 = (tmp_0_0 < tmp_0_1) ? tmp_0_0 : tmp_0_1;
  const pair_t tmp_1_1 = (tmp_0_2 < tmp_0_3) ? tmp_0_2 : tmp_0_3;

  // Stage 2
  const pair_t tmp_2_0 = (tmp_1_0 < tmp_1_1) ? tmp_1_0 : tmp_1_1;

  // Output
  const idx_t idx = tmp_2_0.first;
  const data_t invalid_marker = find_ap_int_max_allowed<data_t>::value;

  out = in0[idx];
  vld = (in1[idx] != invalid_marker);
}

template <typename T0, typename T1, typename T_OUT>
void trkbuilding_reduce_argmin_ph_diff_op(const T0 in0[8], const T1 in1[8], T_OUT& out, bool& vld, m_10deg_chamber_tag) {
  static_assert(is_same<T0, trkbuilding_seg_t>::value, "T0 type check failed");
  static_assert(is_same<T1, trkbuilding_ph_diff_t>::value, "T1 type check failed");
  static_assert(is_same<T_OUT, T0>::value, "T_OUT type check failed");

#pragma HLS PIPELINE II=trkbuilding_config::target_ii

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE

  typedef ap_uint<3> idx_t;  // 0..7
  typedef T1 data_t;
  using pair_t = details::argsort_pair<idx_t, data_t>;

  // Stage 0: concatenate index and data
  const pair_t tmp_0_0(idx_t(0), in1[0]);
  const pair_t tmp_0_1(idx_t(1), in1[1]);
  const pair_t tmp_0_2(idx_t(2), in1[2]);
  const pair_t tmp_0_3(idx_t(3), in1[3]);
  const pair_t tmp_0_4(idx_t(4), in1[4]);
  const pair_t tmp_0_5(idx_t(5), in1[5]);
  const pair_t tmp_0_6(idx_t(6), in1[6]);
  const pair_t tmp_0_7(idx_t(7), in1[7]);

  // Stage 1
  const pair_t tmp_1_0 = (tmp_0_0 < tmp_0_1) ? tmp_0_0 : tmp_0_1;
  const pair_t tmp_1_1 = (tmp_0_2 < tmp_0_3) ? tmp_0_2 : tmp_0_3;
  const pair_t tmp_1_2 = (tmp_0_4 < tmp_0_5) ? tmp_0_4 : tmp_0_5;
  const pair_t tmp_1_3 = (tmp_0_6 < tmp_0_7) ? tmp_0_6 : tmp_0_7;

  // Stage 2
  const pair_t tmp_2_0 = (tmp_1_0 < tmp_1_1) ? tmp_1_0 : tmp_1_1;
  const pair_t tmp_2_1 = (tmp_1_2 < tmp_1_3) ? tmp_1_2 : tmp_1_3;

  // Stage 3
  const pair_t tmp_3_0 = (tmp_2_0 < tmp_2_1) ? tmp_2_0 : tmp_2_1;

  // Output
  const idx_t idx = tmp_3_0.first;
  const data_t invalid_marker = find_ap_int_max_allowed<data_t>::value;

  out = in0[idx];
  vld = (in1[idx] != invalid_marker);
}

template <typename T0, typename T1, typename T_OUT>
void trkbuilding_reduce_argmin_ph_diff_op(const T0 in0[12], const T1 in1[12], T_OUT& out, bool& vld, m_20deg_ext_chamber_tag) {
  static_assert(is_same<T0, trkbuilding_seg_t>::value, "T0 type check failed");
  static_assert(is_same<T1, trkbuilding_ph_diff_t>::value, "T1 type check failed");
  static_assert(is_same<T_OUT, T0>::value, "T_OUT type check failed");

#pragma HLS PIPELINE II=trkbuilding_config::target_ii

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE

  typedef ap_uint<4> idx_t;  // 0..11
  typedef T1 data_t;
  using pair_t = details::argsort_pair<idx_t, data_t>;

  // Stage 0: concatenate index and data
  const pair_t tmp_0_0(idx_t(0), in1[0]);
  const pair_t tmp_0_1(idx_t(1), in1[1]);
  const pair_t tmp_0_2(idx_t(2), in1[2]);
  const pair_t tmp_0_3(idx_t(3), in1[3]);
  const pair_t tmp_0_4(idx_t(4), in1[4]);
  const pair_t tmp_0_5(idx_t(5), in1[5]);
  const pair_t tmp_0_6(idx_t(6), in1[6]);
  const pair_t tmp_0_7(idx_t(7), in1[7]);
  const pair_t tmp_0_8(idx_t(8), in1[8]);
  const pair_t tmp_0_9(idx_t(9), in1[9]);
  const pair_t tmp_0_10(idx_t(10), in1[10]);
  const pair_t tmp_0_11(idx_t(11), in1[11]);

  // Stage 1
  const pair_t tmp_1_0 = (tmp_0_0 < tmp_0_1) ? tmp_0_0 : tmp_0_1;
  const pair_t tmp_1_1 = (tmp_0_2 < tmp_0_3) ? tmp_0_2 : tmp_0_3;
  const pair_t tmp_1_2 = (tmp_0_4 < tmp_0_5) ? tmp_0_4 : tmp_0_5;
  const pair_t tmp_1_3 = (tmp_0_6 < tmp_0_7) ? tmp_0_6 : tmp_0_7;
  const pair_t tmp_1_4 = (tmp_0_8 < tmp_0_9) ? tmp_0_8 : tmp_0_9;
  const pair_t tmp_1_5 = (tmp_0_10 < tmp_0_11) ? tmp_0_10 : tmp_0_11;

  // Stage 2
  const pair_t tmp_2_0 = (tmp_1_0 < tmp_1_1) ? tmp_1_0 : tmp_1_1;
  const pair_t tmp_2_1 = (tmp_1_2 < tmp_1_3) ? tmp_1_2 : tmp_1_3;
  const pair_t tmp_2_2 = (tmp_1_4 < tmp_1_5) ? tmp_1_4 : tmp_1_5;

  // Stage 3
  const pair_t tmp_3_0 = (tmp_2_0 < tmp_2_1) ? tmp_2_0 : tmp_2_1;
  const pair_t tmp_3_1 = tmp_2_2;

  // Stage 4
  const pair_t tmp_4_0 = (tmp_3_0 < tmp_3_1) ? tmp_3_0 : tmp_3_1;

  // Output
  const idx_t idx = tmp_4_0.first;
  const data_t invalid_marker = find_ap_int_max_allowed<data_t>::value;

  out = in0[idx];
  vld = (in1[idx] != invalid_marker);
}

template <typename T_IN, typename T_OUT>
void trkbuilding_reduce_median_of_three_op(const T_IN& in0, const T_IN& in1, const T_IN& in2, T_OUT& out) {
  static_assert(is_same<T_IN, T_OUT>::value, "T_OUT type check failed");

#pragma HLS PIPELINE II=trkbuilding_config::target_ii

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE

  typedef T_IN data_t;
  const data_t invalid_marker_th = details::th_invalid;

  // See zonesorting_preprocess_eight_op() for explanations. The bubble sorting netowrk here
  // only has 3 wires (0,1,2 from top to bottom), and there are 3 stages.

  // Stage 1: compare-swap if (wire[i] < wire[j]) swap(wire[j], wire[i])
  const data_t tmp_1_0_0 = (in0 < in1) ? in1 : in0;
  const data_t tmp_1_1_0 = (in0 < in1) ? in0 : in1;
  const data_t tmp_1_0_1 = (in1 < in2) ? in2 : in1;
  const data_t tmp_1_1_1 = (in1 < in2) ? in1 : in2;
  const data_t tmp_1_0_2 = (in2 < in0) ? in0 : in2;
  const data_t tmp_1_1_2 = (in2 < in0) ? in2 : in0;

  // Stage 2
  const data_t tmp_2_1 = (tmp_1_1_0 < in2) ? in2 : tmp_1_1_0;
  const data_t tmp_2_2 = (tmp_1_1_0 < in2) ? tmp_1_1_0 : in2;  // unused

  // Stage 3
  const data_t tmp_3_0 = (tmp_1_0_0 < tmp_2_1) ? tmp_2_1 : tmp_1_0_0;  // unused
  const data_t tmp_3_1 = (tmp_1_0_0 < tmp_2_1) ? tmp_1_0_0 : tmp_2_1;

  // Output
  ap_uint<3> valid_flag = 0;
  valid_flag[0] = (in0 != invalid_marker_th);
  valid_flag[1] = (in1 != invalid_marker_th);
  valid_flag[2] = (in2 != invalid_marker_th);

  switch (valid_flag) {
    case 0: { out = invalid_marker_th; break; }
    case 1: { out = in0; break; }
    case 2: { out = in1; break; }
    case 3: { out = tmp_1_0_0; break; }
    case 4: { out = in2; break; }
    case 5: { out = tmp_1_0_2; break; }
    case 6: { out = tmp_1_0_1; break; }
    case 7: { out = tmp_3_1; break; }
    default: { out = invalid_marker_th; break; }
  }
}

template <typename T_IN, typename T_OUT>
void trkbuilding_reduce_median_theta_op(const T_IN in0[9], T_OUT& out) {
  static_assert(is_same<T_IN, T_OUT>::value, "T_OUT type check failed");

#pragma HLS PIPELINE II=trkbuilding_config::target_ii

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE

  typedef T_IN data_t;

  data_t stage_0_out[3];

#pragma HLS ARRAY_PARTITION variable=stage_0_out complete dim=0

  // Split 9 entries into 3 groups of 3, find median in each group, then find median of medians
  trkbuilding_reduce_median_of_three_op(in0[0], in0[1], in0[2], stage_0_out[0]);
  trkbuilding_reduce_median_of_three_op(in0[3], in0[4], in0[5], stage_0_out[1]);
  trkbuilding_reduce_median_of_three_op(in0[6], in0[7], in0[8], stage_0_out[2]);

  // Output
  trkbuilding_reduce_median_of_three_op(stage_0_out[0], stage_0_out[1], stage_0_out[2], out);
}

template <typename T_IN, typename T_OUT>
void trkbuilding_select_theta_op(const T_IN& in0, const T_IN& in1, const T_IN& th_median, T_OUT& out, bool& vld) {
  static_assert(is_same<T_IN, T_OUT>::value, "T_OUT type check failed");

#pragma HLS PIPELINE II=trkbuilding_config::target_ii

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE

  typedef T_IN data_t;
  const data_t invalid_marker_th = details::th_invalid;
  const data_t th_window = details::th_window;

  const data_t th_diff_tmp_0 = details::calc_abs_diff(in0, th_median);
  const data_t th_diff_tmp_1 = details::calc_abs_diff(in1, th_median);
  const bool valid_tmp_0 = (in0 != invalid_marker_th) and (th_diff_tmp_0 < th_window);
  const bool valid_tmp_1 = (in1 != invalid_marker_th) and (th_diff_tmp_1 < th_window);

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
    out = invalid_marker_th;
    vld = false;
  }
}

template <typename T_IN, typename T_OUT>
void trkbuilding_select_theta_op(const T_IN& in0, const T_IN& th_median, T_OUT& out, bool& vld) {
  static_assert(is_same<T_IN, T_OUT>::value, "T_OUT type check failed");

#pragma HLS PIPELINE II=trkbuilding_config::target_ii

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE

  typedef T_IN data_t;
  const data_t invalid_marker_th = details::th_invalid;
  const data_t th_window = details::th_window;

  const data_t th_diff_tmp_0 = details::calc_abs_diff(in0, th_median);
  const bool valid_tmp_0 = (in0 != invalid_marker_th) and (th_diff_tmp_0 < th_window);

  // Output
  if (valid_tmp_0) {
    out = in0;
    vld = true;
  } else {
    out = invalid_marker_th;
    vld = false;
  }
}

template <int N>
void trkbuilding_pack_booleans_op(const bool in0[N], ap_uint<N>& out) {

#pragma HLS PIPELINE II=trkbuilding_config::target_ii

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE

  // Pack bits into word
  for (unsigned i = 0; i < N; i++) {

#pragma HLS UNROLL

    out[i] = in0[i];
  }
}

// _____________________________________________________________________________
// Perform loop over chambers and all the segments in the chambers.
// Find the best matches in phi.

template <typename Site>
void trkbuilding_match_ph_op(
    const emtf_phi_t emtf_phi[model_config::n_in],
    const seg_zones_t seg_zones[model_config::n_in],
    const seg_valid_t seg_valid[model_config::n_in],
    const trk_qual_t& curr_trk_qual,
    const trk_patt_t& curr_trk_patt,
    const trk_col_t& curr_trk_col,
    const trk_zone_t& curr_trk_zone,
    trk_seg_t& curr_trk_seg_site_i,
    bool& curr_trk_seg_v_site_i
) {

#pragma HLS PIPELINE II=trkbuilding_config::target_ii

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE

  typedef typename details::chamber_category_traits<Site>::chamber_category chamber_category;
  const int num_chambers = details::num_chambers_traits<chamber_category>::value;
  const int num_chambers_round = details::ceil_mul4<num_chambers>::value;
  const int num_segments_round = num_chambers_round * num_emtf_segments;
  const int N = num_segments_round;

  int segment_id_table[N];
  details::init_table_op(segment_id_table, details::get_site_segment_id_op<Site>());

  int pattern_col_start_table[num_emtf_zones][num_emtf_patterns];
  details::init_2d_table_op(pattern_col_start_table, details::get_site_pattern_col_start_op<Site>());

  int pattern_col_mid_table[num_emtf_zones][num_emtf_patterns];
  details::init_2d_table_op(pattern_col_mid_table, details::get_site_pattern_col_mid_op<Site>());

  int pattern_col_stop_table[num_emtf_zones][num_emtf_patterns];
  details::init_2d_table_op(pattern_col_stop_table, details::get_site_pattern_col_stop_op<Site>());

  int pattern_col_pad_table[num_emtf_zones];
  details::init_table_op(pattern_col_pad_table, details::get_site_pattern_col_pad_op<Site>());

  // Find segments matched to the pattern
  trkbuilding_seg_t trkbuilding_ph_seg[N];
  trkbuilding_ph_diff_t trkbuilding_ph_diff[N];

#pragma HLS ARRAY_PARTITION variable=trkbuilding_ph_seg complete dim=0
#pragma HLS ARRAY_PARTITION variable=trkbuilding_ph_diff complete dim=0

  const trkbuilding_seg_t invalid_marker_ph_seg = model_config::n_in;
  const trkbuilding_ph_diff_t invalid_marker_ph_diff = find_ap_int_max_allowed<trkbuilding_ph_diff_t>::value;

  const trkbuilding_col_t col_patt = curr_trk_col + static_cast<trkbuilding_col_t>(details::chamber_img_joined_col_start);
  const trkbuilding_col_t col_start = col_patt + pattern_col_start_table[curr_trk_zone][curr_trk_patt];
  const trkbuilding_col_t col_mid = col_patt + pattern_col_mid_table[curr_trk_zone][curr_trk_patt];
  const trkbuilding_col_t col_stop = col_patt + pattern_col_stop_table[curr_trk_zone][curr_trk_patt];
  const trkbuilding_col_t col_pad = pattern_col_pad_table[curr_trk_zone];

trkbuilding_match_ph_op_loop:

  // Loop over segments (incl those in fake chambers)
  for (unsigned i = 0; i < N; i++) {

#pragma HLS UNROLL

    const trkbuilding_seg_t iseg = segment_id_table[i];
    const bool is_valid_seg = (iseg != invalid_marker_ph_seg);

    // Keep track of segment id
    trkbuilding_ph_seg[i] = iseg;

    if (is_valid_seg) {
      const trkbuilding_col_t col = (emtf_phi[iseg] >> 4);
      const trkbuilding_col_t padded_col = col + col_pad;
      const bool is_valid_col = (
          (seg_valid[iseg] == 1) and \
          (seg_zones[iseg][(num_emtf_zones - 1) - curr_trk_zone] == 1) and \
          (col_start <= padded_col) and (padded_col <= col_stop)
      );

      if (is_valid_col) {
        // Calculate abs difference
        const emtf_phi_t ph_seg = emtf_phi[iseg];
        const emtf_phi_t ph_patt_tmp = details::calc_rectified_diff(col_mid, col_pad);
        const emtf_phi_t ph_patt = (ph_patt_tmp << 4) + (1 << 3);
        const emtf_phi_t ph_diff = details::calc_abs_diff(ph_seg, ph_patt);
        assert(((ph_patt >> 4) + col_pad) == col_mid);
        const bool is_valid_ph_diff = (ph_diff < invalid_marker_ph_diff);
        trkbuilding_ph_diff[i] = is_valid_ph_diff ? static_cast<trkbuilding_ph_diff_t>(ph_diff) : invalid_marker_ph_diff;
      } else {
        // Invalid segment
        trkbuilding_ph_diff[i] = invalid_marker_ph_diff;
      }
    } else {
      // Invalid segment id
      trkbuilding_ph_diff[i] = invalid_marker_ph_diff;
    }
  }  // end loop over segments

  // Select an area (40 deg = 2x 20 deg chambers, 4x 10 deg chambers, or 6x 20 deg ext chambers)
  const bool vld_area_0 = (col_patt < static_cast<trkbuilding_col_t>(details::chamber_ph_cover_20deg[0]));
  const bool vld_area_1 = (col_patt < static_cast<trkbuilding_col_t>(details::chamber_ph_cover_20deg[1]));
  const bool vld_area_2 = (col_patt < static_cast<trkbuilding_col_t>(details::chamber_ph_cover_20deg[2]));

  const trkbuilding_area_t area = vld_area_0 ? 0 : (vld_area_1 ? 1 : (vld_area_2 ? 2 : num_emtf_img_areas));
  assert(area != num_emtf_img_areas);

  // Select min activation
  const int area_start = area * (N / (num_emtf_img_areas + 1));
  trkbuilding_reduce_argmin_ph_diff_op(
      stl_next(trkbuilding_ph_seg, area_start),
      stl_next(trkbuilding_ph_diff, area_start),
      curr_trk_seg_site_i,
      curr_trk_seg_v_site_i,
      chamber_category()
  );
}

template <typename T=void>
void trkbuilding_match_th_op(
    const emtf_theta1_t emtf_theta1[model_config::n_in],
    const emtf_theta2_t emtf_theta2[model_config::n_in],
    const trk_seg_t curr_trk_seg[num_emtf_sites],
    const bool curr_trk_seg_v_from_ph[num_emtf_sites],
    emtf_theta1_t& theta_median,
    emtf_theta1_t emtf_theta_best[num_emtf_sites],
    bool curr_trk_seg_v_from_th[num_emtf_sites]
) {

#pragma HLS PIPELINE II=trkbuilding_config::target_ii

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE

  typedef emtf_theta1_t emtf_theta_t;

  emtf_theta_t theta_values[9];
  emtf_theta_t theta_values_s1[9];  // special case for ME0/ME1-only tracks

#pragma HLS ARRAY_PARTITION variable=theta_values complete dim=0
#pragma HLS ARRAY_PARTITION variable=theta_values_s1 complete dim=0

  const emtf_theta_t invalid_marker_th = details::th_invalid;

  // Loop over the theta values manually
  const emtf_theta_t theta_value_0_0 = curr_trk_seg_v_from_ph[0] ? emtf_theta1[curr_trk_seg[0]] : invalid_marker_th;
  const emtf_theta_t theta_value_0_1 = curr_trk_seg_v_from_ph[0] ? emtf_theta2[curr_trk_seg[0]] : invalid_marker_th;
  const emtf_theta_t theta_value_1_0 = curr_trk_seg_v_from_ph[1] ? emtf_theta1[curr_trk_seg[1]] : invalid_marker_th;
  const emtf_theta_t theta_value_1_1 = curr_trk_seg_v_from_ph[1] ? emtf_theta2[curr_trk_seg[1]] : invalid_marker_th;
  const emtf_theta_t theta_value_2_0 = curr_trk_seg_v_from_ph[2] ? emtf_theta1[curr_trk_seg[2]] : invalid_marker_th;
  const emtf_theta_t theta_value_2_1 = curr_trk_seg_v_from_ph[2] ? emtf_theta2[curr_trk_seg[2]] : invalid_marker_th;
  const emtf_theta_t theta_value_3_0 = curr_trk_seg_v_from_ph[3] ? emtf_theta1[curr_trk_seg[3]] : invalid_marker_th;
  const emtf_theta_t theta_value_3_1 = curr_trk_seg_v_from_ph[3] ? emtf_theta2[curr_trk_seg[3]] : invalid_marker_th;
  const emtf_theta_t theta_value_4_0 = curr_trk_seg_v_from_ph[4] ? emtf_theta1[curr_trk_seg[4]] : invalid_marker_th;
  const emtf_theta_t theta_value_4_1 = curr_trk_seg_v_from_ph[4] ? emtf_theta2[curr_trk_seg[4]] : invalid_marker_th;
  const emtf_theta_t theta_value_5_0 = curr_trk_seg_v_from_ph[5] ? emtf_theta1[curr_trk_seg[5]] : invalid_marker_th;
  const emtf_theta_t theta_value_6_0 = curr_trk_seg_v_from_ph[6] ? emtf_theta1[curr_trk_seg[6]] : invalid_marker_th;
  const emtf_theta_t theta_value_7_0 = curr_trk_seg_v_from_ph[7] ? emtf_theta1[curr_trk_seg[7]] : invalid_marker_th;
  const emtf_theta_t theta_value_8_0 = curr_trk_seg_v_from_ph[8] ? emtf_theta1[curr_trk_seg[8]] : invalid_marker_th;
  const emtf_theta_t theta_value_9_0 = curr_trk_seg_v_from_ph[9] ? emtf_theta1[curr_trk_seg[9]] : invalid_marker_th;
  const emtf_theta_t theta_value_10_0 = curr_trk_seg_v_from_ph[10] ? emtf_theta1[curr_trk_seg[10]] : invalid_marker_th;
  const emtf_theta_t theta_value_11_0 = curr_trk_seg_v_from_ph[11] ? emtf_theta1[curr_trk_seg[11]] : invalid_marker_th;

  theta_values[0] = theta_value_2_0;  // ME2 theta 1
  theta_values[1] = theta_value_3_0;  // ME3 theta 1
  theta_values[2] = theta_value_4_0;  // ME4 theta 1
  theta_values[3] = theta_value_2_1;  // ME2 theta 2
  theta_values[4] = theta_value_3_1;  // ME3 theta 2
  theta_values[5] = theta_value_4_1;  // ME4 theta 2
  theta_values[6] = (theta_value_6_0 != invalid_marker_th) ? theta_value_6_0 : theta_value_10_0;  // RE2 or GE2/1 theta
  theta_values[7] = theta_value_7_0;  // RE3 theta
  theta_values[8] = theta_value_8_0;  // RE4 theta

  theta_values_s1[0] = theta_value_0_0;  // ME1/1 theta 1
  theta_values_s1[1] = theta_value_1_0;  // ME1/2 theta 1
  theta_values_s1[2] = invalid_marker_th;
  theta_values_s1[3] = theta_value_0_1;  // ME1/1 theta 2
  theta_values_s1[4] = theta_value_1_1;  // ME1/2 theta 2
  theta_values_s1[5] = invalid_marker_th;
  theta_values_s1[6] = theta_value_9_0;  // GE1/1 theta
  theta_values_s1[7] = theta_value_5_0;  // RE1/2 theta
  theta_values_s1[8] = theta_value_11_0; // ME0 theta

  // Find theta_median
  emtf_theta_t theta_median_tmp_0 = invalid_marker_th;
  emtf_theta_t theta_median_tmp_1 = invalid_marker_th;
  trkbuilding_reduce_median_theta_op(theta_values, theta_median_tmp_0);
  trkbuilding_reduce_median_theta_op(theta_values_s1, theta_median_tmp_1);

  theta_median = (theta_median_tmp_0 != invalid_marker_th) ? theta_median_tmp_0 : theta_median_tmp_1;
  assert(theta_median != invalid_marker_th);

  // Find the most compatible theta values, also apply theta window cut
  trkbuilding_select_theta_op(theta_value_0_0, theta_value_0_1, theta_median, emtf_theta_best[0], curr_trk_seg_v_from_th[0]);
  trkbuilding_select_theta_op(theta_value_1_0, theta_value_1_1, theta_median, emtf_theta_best[1], curr_trk_seg_v_from_th[1]);
  trkbuilding_select_theta_op(theta_value_2_0, theta_value_2_1, theta_median, emtf_theta_best[2], curr_trk_seg_v_from_th[2]);
  trkbuilding_select_theta_op(theta_value_3_0, theta_value_3_1, theta_median, emtf_theta_best[3], curr_trk_seg_v_from_th[3]);
  trkbuilding_select_theta_op(theta_value_4_0, theta_value_4_1, theta_median, emtf_theta_best[4], curr_trk_seg_v_from_th[4]);
  trkbuilding_select_theta_op(theta_value_5_0, theta_median, emtf_theta_best[5], curr_trk_seg_v_from_th[5]);
  trkbuilding_select_theta_op(theta_value_6_0, theta_median, emtf_theta_best[6], curr_trk_seg_v_from_th[6]);
  trkbuilding_select_theta_op(theta_value_7_0, theta_median, emtf_theta_best[7], curr_trk_seg_v_from_th[7]);
  trkbuilding_select_theta_op(theta_value_8_0, theta_median, emtf_theta_best[8], curr_trk_seg_v_from_th[8]);
  trkbuilding_select_theta_op(theta_value_9_0, theta_median, emtf_theta_best[9], curr_trk_seg_v_from_th[9]);
  trkbuilding_select_theta_op(theta_value_10_0, theta_median, emtf_theta_best[10], curr_trk_seg_v_from_th[10]);
  trkbuilding_select_theta_op(theta_value_11_0, theta_median, emtf_theta_best[11], curr_trk_seg_v_from_th[11]);
}

template <typename T=void>
void trkbuilding_extract_features_op(
    const emtf_phi_t emtf_phi[model_config::n_in],
    const emtf_bend_t emtf_bend[model_config::n_in],
    const emtf_qual1_t emtf_qual1[model_config::n_in],
    const emtf_qual2_t emtf_qual2[model_config::n_in],
    const emtf_time_t emtf_time[model_config::n_in],
    const emtf_phi_t& phi_median,
    const emtf_theta1_t& theta_median,
    const emtf_theta1_t emtf_theta_best[num_emtf_sites],
    const trk_seg_t curr_trk_seg[num_emtf_sites],
    const trk_seg_v_t& curr_trk_seg_v,
    trk_feat_t curr_trk_feat[num_emtf_features]
) {

#pragma HLS PIPELINE II=trkbuilding_config::target_ii

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE

  // Table showing the 36 features sent to NN
  //
  // feat       | ME1/1 | ME1/2 |  ME2  |  ME3  |  ME4  |  RE1  |  RE2  |  RE3  |  RE4  | GE1/1 | GE2/1 |  ME0
  // -----------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------
  // emtf_phi   |   *   |   *   |   *   |   *   |   *   |   *   |   *   |   *   |   *   |   *   |   *   |   *
  // emtf_theta |   *   |   *   |   *   |   *   |   *   |   *   |   *   |   *   |   *   |   *   |   *   |   *
  // emtf_bend  |   *   |   *   |   *   |   *   |   *   |       |       |       |       |       |       |   *
  // emtf_qual  |   *   |   *   |   *   |   *   |   *   |       |       |       |       |       |       |   *
  // emtf_time  |       |       |       |       |       |       |       |       |       |       |       |

  int k = 0;

  // emtf_phi
  curr_trk_feat[k++] = details::take_value_if(curr_trk_seg_v[0], details::calc_signed_diff(emtf_phi[curr_trk_seg[0]], phi_median));
  curr_trk_feat[k++] = details::take_value_if(curr_trk_seg_v[1], details::calc_signed_diff(emtf_phi[curr_trk_seg[1]], phi_median));
  curr_trk_feat[k++] = details::take_value_if(curr_trk_seg_v[2], details::calc_signed_diff(emtf_phi[curr_trk_seg[2]], phi_median));
  curr_trk_feat[k++] = details::take_value_if(curr_trk_seg_v[3], details::calc_signed_diff(emtf_phi[curr_trk_seg[3]], phi_median));
  curr_trk_feat[k++] = details::take_value_if(curr_trk_seg_v[4], details::calc_signed_diff(emtf_phi[curr_trk_seg[4]], phi_median));
  curr_trk_feat[k++] = details::take_value_if(curr_trk_seg_v[5], details::calc_signed_diff(emtf_phi[curr_trk_seg[5]], phi_median));
  curr_trk_feat[k++] = details::take_value_if(curr_trk_seg_v[6], details::calc_signed_diff(emtf_phi[curr_trk_seg[6]], phi_median));
  curr_trk_feat[k++] = details::take_value_if(curr_trk_seg_v[7], details::calc_signed_diff(emtf_phi[curr_trk_seg[7]], phi_median));
  curr_trk_feat[k++] = details::take_value_if(curr_trk_seg_v[8], details::calc_signed_diff(emtf_phi[curr_trk_seg[8]], phi_median));
  curr_trk_feat[k++] = details::take_value_if(curr_trk_seg_v[9], details::calc_signed_diff(emtf_phi[curr_trk_seg[9]], phi_median));
  curr_trk_feat[k++] = details::take_value_if(curr_trk_seg_v[10], details::calc_signed_diff(emtf_phi[curr_trk_seg[10]], phi_median));
  curr_trk_feat[k++] = details::take_value_if(curr_trk_seg_v[11], details::calc_signed_diff(emtf_phi[curr_trk_seg[11]], phi_median));

  // emtf_theta
  curr_trk_feat[k++] = details::take_value_if(curr_trk_seg_v[0], details::calc_signed_diff(emtf_theta_best[0], theta_median));
  curr_trk_feat[k++] = details::take_value_if(curr_trk_seg_v[1], details::calc_signed_diff(emtf_theta_best[1], theta_median));
  curr_trk_feat[k++] = details::take_value_if(curr_trk_seg_v[2], details::calc_signed_diff(emtf_theta_best[2], theta_median));
  curr_trk_feat[k++] = details::take_value_if(curr_trk_seg_v[3], details::calc_signed_diff(emtf_theta_best[3], theta_median));
  curr_trk_feat[k++] = details::take_value_if(curr_trk_seg_v[4], details::calc_signed_diff(emtf_theta_best[4], theta_median));
  curr_trk_feat[k++] = details::take_value_if(curr_trk_seg_v[5], details::calc_signed_diff(emtf_theta_best[5], theta_median));
  curr_trk_feat[k++] = details::take_value_if(curr_trk_seg_v[6], details::calc_signed_diff(emtf_theta_best[6], theta_median));
  curr_trk_feat[k++] = details::take_value_if(curr_trk_seg_v[7], details::calc_signed_diff(emtf_theta_best[7], theta_median));
  curr_trk_feat[k++] = details::take_value_if(curr_trk_seg_v[8], details::calc_signed_diff(emtf_theta_best[8], theta_median));
  curr_trk_feat[k++] = details::take_value_if(curr_trk_seg_v[9], details::calc_signed_diff(emtf_theta_best[9], theta_median));
  curr_trk_feat[k++] = details::take_value_if(curr_trk_seg_v[10], details::calc_signed_diff(emtf_theta_best[10], theta_median));
  curr_trk_feat[k++] = details::take_value_if(curr_trk_seg_v[11], details::calc_signed_diff(emtf_theta_best[11], theta_median));

  // emtf_bend
  curr_trk_feat[k++] = details::take_value_if(curr_trk_seg_v[0], emtf_bend[curr_trk_seg[0]]);
  curr_trk_feat[k++] = details::take_value_if(curr_trk_seg_v[1], emtf_bend[curr_trk_seg[1]]);
  curr_trk_feat[k++] = details::take_value_if(curr_trk_seg_v[2], emtf_bend[curr_trk_seg[2]]);
  curr_trk_feat[k++] = details::take_value_if(curr_trk_seg_v[3], emtf_bend[curr_trk_seg[3]]);
  curr_trk_feat[k++] = details::take_value_if(curr_trk_seg_v[4], emtf_bend[curr_trk_seg[4]]);
  curr_trk_feat[k++] = details::take_value_if(curr_trk_seg_v[11], emtf_bend[curr_trk_seg[11]]);

  // emtf_qual
  curr_trk_feat[k++] = details::take_value_if(curr_trk_seg_v[0], emtf_qual1[curr_trk_seg[0]]);
  curr_trk_feat[k++] = details::take_value_if(curr_trk_seg_v[1], emtf_qual1[curr_trk_seg[1]]);
  curr_trk_feat[k++] = details::take_value_if(curr_trk_seg_v[2], emtf_qual1[curr_trk_seg[2]]);
  curr_trk_feat[k++] = details::take_value_if(curr_trk_seg_v[3], emtf_qual1[curr_trk_seg[3]]);
  curr_trk_feat[k++] = details::take_value_if(curr_trk_seg_v[4], emtf_qual1[curr_trk_seg[4]]);
  curr_trk_feat[k++] = details::take_value_if(curr_trk_seg_v[11], emtf_qual1[curr_trk_seg[11]]);
  assert(k == num_emtf_features);
}

// _____________________________________________________________________________
// Track building op

template <typename Zone, typename Timezone>
void trkbuilding_op(
    const emtf_phi_t    emtf_phi       [model_config::n_in],
    const emtf_bend_t   emtf_bend      [model_config::n_in],
    const emtf_theta1_t emtf_theta1    [model_config::n_in],
    const emtf_theta2_t emtf_theta2    [model_config::n_in],
    const emtf_qual1_t  emtf_qual1     [model_config::n_in],
    const emtf_qual2_t  emtf_qual2     [model_config::n_in],
    const emtf_time_t   emtf_time      [model_config::n_in],
    const seg_zones_t   seg_zones      [model_config::n_in],
    const seg_tzones_t  seg_tzones     [model_config::n_in],
    const seg_fr_t      seg_fr         [model_config::n_in],
    const seg_dl_t      seg_dl         [model_config::n_in],
    const seg_bx_t      seg_bx         [model_config::n_in],
    const seg_valid_t   seg_valid      [model_config::n_in],
    const trk_qual_t&   curr_trk_qual  ,
    const trk_patt_t&   curr_trk_patt  ,
    const trk_col_t&    curr_trk_col   ,
    const trk_zone_t&   curr_trk_zone  ,
    trk_seg_t           curr_trk_seg   [num_emtf_sites],
    trk_seg_v_t&        curr_trk_seg_v ,
    trk_feat_t          curr_trk_feat  [num_emtf_features],
    trk_valid_t&        curr_trk_valid
) {

#pragma HLS PIPELINE II=trkbuilding_config::target_ii

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE

  typedef emtf_theta1_t emtf_theta_t;

  bool curr_trk_seg_v_from_ph[num_emtf_sites];
  bool curr_trk_seg_v_from_th[num_emtf_sites];
  emtf_theta_t emtf_theta_best[num_emtf_sites];

#pragma HLS ARRAY_PARTITION variable=curr_trk_seg_v_from_ph complete dim=0
#pragma HLS ARRAY_PARTITION variable=curr_trk_seg_v_from_th complete dim=0
#pragma HLS ARRAY_PARTITION variable=emtf_theta_best complete dim=0

  emtf_phi_t phi_median = 0;
  emtf_theta_t theta_median = 0;

  // Find phi_median, select best segment indices (closest to phi_median)

  // Loop over sites manually
  {
    trkbuilding_match_ph_op<m_zone_any_site_0_tag>(emtf_phi, seg_zones, seg_valid, curr_trk_qual, curr_trk_patt, curr_trk_col, curr_trk_zone, curr_trk_seg[0], curr_trk_seg_v_from_ph[0]);
    trkbuilding_match_ph_op<m_zone_any_site_1_tag>(emtf_phi, seg_zones, seg_valid, curr_trk_qual, curr_trk_patt, curr_trk_col, curr_trk_zone, curr_trk_seg[1], curr_trk_seg_v_from_ph[1]);
    trkbuilding_match_ph_op<m_zone_any_site_2_tag>(emtf_phi, seg_zones, seg_valid, curr_trk_qual, curr_trk_patt, curr_trk_col, curr_trk_zone, curr_trk_seg[2], curr_trk_seg_v_from_ph[2]);
    trkbuilding_match_ph_op<m_zone_any_site_3_tag>(emtf_phi, seg_zones, seg_valid, curr_trk_qual, curr_trk_patt, curr_trk_col, curr_trk_zone, curr_trk_seg[3], curr_trk_seg_v_from_ph[3]);
    trkbuilding_match_ph_op<m_zone_any_site_4_tag>(emtf_phi, seg_zones, seg_valid, curr_trk_qual, curr_trk_patt, curr_trk_col, curr_trk_zone, curr_trk_seg[4], curr_trk_seg_v_from_ph[4]);
    trkbuilding_match_ph_op<m_zone_any_site_5_tag>(emtf_phi, seg_zones, seg_valid, curr_trk_qual, curr_trk_patt, curr_trk_col, curr_trk_zone, curr_trk_seg[5], curr_trk_seg_v_from_ph[5]);
    trkbuilding_match_ph_op<m_zone_any_site_6_tag>(emtf_phi, seg_zones, seg_valid, curr_trk_qual, curr_trk_patt, curr_trk_col, curr_trk_zone, curr_trk_seg[6], curr_trk_seg_v_from_ph[6]);
    trkbuilding_match_ph_op<m_zone_any_site_7_tag>(emtf_phi, seg_zones, seg_valid, curr_trk_qual, curr_trk_patt, curr_trk_col, curr_trk_zone, curr_trk_seg[7], curr_trk_seg_v_from_ph[7]);
    trkbuilding_match_ph_op<m_zone_any_site_8_tag>(emtf_phi, seg_zones, seg_valid, curr_trk_qual, curr_trk_patt, curr_trk_col, curr_trk_zone, curr_trk_seg[8], curr_trk_seg_v_from_ph[8]);
    trkbuilding_match_ph_op<m_zone_any_site_9_tag>(emtf_phi, seg_zones, seg_valid, curr_trk_qual, curr_trk_patt, curr_trk_col, curr_trk_zone, curr_trk_seg[9], curr_trk_seg_v_from_ph[9]);
    trkbuilding_match_ph_op<m_zone_any_site_10_tag>(emtf_phi, seg_zones, seg_valid, curr_trk_qual, curr_trk_patt, curr_trk_col, curr_trk_zone, curr_trk_seg[10], curr_trk_seg_v_from_ph[10]);
    trkbuilding_match_ph_op<m_zone_any_site_11_tag>(emtf_phi, seg_zones, seg_valid, curr_trk_qual, curr_trk_patt, curr_trk_col, curr_trk_zone, curr_trk_seg[11], curr_trk_seg_v_from_ph[11]);
  }

  // Set phi_median
  const emtf_phi_t col_patt = curr_trk_col + static_cast<trkbuilding_col_t>(details::chamber_img_joined_col_start);
  phi_median = (col_patt << 4) + (1 << 3);

  // Find theta_median, select best theta values (closest to theta_median)
  trkbuilding_match_th_op(emtf_theta1, emtf_theta2, curr_trk_seg, curr_trk_seg_v_from_ph, theta_median, emtf_theta_best, curr_trk_seg_v_from_th);

  // Set segment valid flag and track valid flag
  trkbuilding_pack_booleans_op(curr_trk_seg_v_from_th, curr_trk_seg_v);
  curr_trk_valid = (bool) curr_trk_seg_v;

  // Extract features
  trkbuilding_extract_features_op(emtf_phi, emtf_bend, emtf_qual1, emtf_qual2, emtf_time, phi_median, theta_median, emtf_theta_best, curr_trk_seg, curr_trk_seg_v, curr_trk_feat);
}

// _____________________________________________________________________________
// Entry point

template <typename Zone>
void trkbuilding_layer(
    const emtf_phi_t    emtf_phi       [model_config::n_in],
    const emtf_bend_t   emtf_bend      [model_config::n_in],
    const emtf_theta1_t emtf_theta1    [model_config::n_in],
    const emtf_theta2_t emtf_theta2    [model_config::n_in],
    const emtf_qual1_t  emtf_qual1     [model_config::n_in],
    const emtf_qual2_t  emtf_qual2     [model_config::n_in],
    const emtf_time_t   emtf_time      [model_config::n_in],
    const seg_zones_t   seg_zones      [model_config::n_in],
    const seg_tzones_t  seg_tzones     [model_config::n_in],
    const seg_fr_t      seg_fr         [model_config::n_in],
    const seg_dl_t      seg_dl         [model_config::n_in],
    const seg_bx_t      seg_bx         [model_config::n_in],
    const seg_valid_t   seg_valid      [model_config::n_in],
    const trk_qual_t    trk_qual       [trkbuilding_config::n_in],
    const trk_patt_t    trk_patt       [trkbuilding_config::n_in],
    const trk_col_t     trk_col        [trkbuilding_config::n_in],
    const trk_zone_t    trk_zone       [trkbuilding_config::n_in],
    trk_seg_t           trk_seg        [trkbuilding_config::n_out * num_emtf_sites],
    trk_seg_v_t         trk_seg_v      [trkbuilding_config::n_out],
    trk_feat_t          trk_feat       [trkbuilding_config::n_out * num_emtf_features],
    trk_valid_t         trk_valid      [trkbuilding_config::n_out]
) {

#pragma HLS PIPELINE II=trkbuilding_config::target_ii

#pragma HLS INTERFACE ap_ctrl_none port=return

  // Check assumptions
  static_assert(trkbuilding_config::n_in == num_emtf_tracks, "trkbuilding_config::n_in check failed");
  static_assert(trkbuilding_config::n_out == num_emtf_tracks, "trkbuilding_config::n_out check failed");
  static_assert(num_emtf_sites == 12, "num_emtf_sites must be 12");
  static_assert(num_emtf_features == 36, "num_emtf_features must be 36");

  typedef m_timezone_0_tag Timezone;  // default timezone

trkbuilding_layer_loop:

  // Loop over tracks
  for (unsigned itrk = 0; itrk < trkbuilding_config::n_in; itrk++) {

#pragma HLS UNROLL

    auto curr_trk_seg = stl_next(trk_seg, itrk * num_emtf_sites);
    auto curr_trk_feat = stl_next(trk_feat, itrk * num_emtf_features);

    trkbuilding_op<Zone, Timezone>(
        emtf_phi, emtf_bend, emtf_theta1, emtf_theta2, emtf_qual1, emtf_qual2,
        emtf_time, seg_zones, seg_tzones, seg_fr, seg_dl, seg_bx,
        seg_valid, trk_qual[itrk], trk_patt[itrk], trk_col[itrk], trk_zone[itrk], curr_trk_seg,
        trk_seg_v[itrk], curr_trk_feat, trk_valid[itrk]
    );
  }  // end loop over tracks
}

}  // namespace emtf

#endif  // __EMTF_HLSLIB_TRKBUILDING_H__ not defined
