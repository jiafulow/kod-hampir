#ifndef __EMTF_HLSLIB_ZONESORTING_H__
#define __EMTF_HLSLIB_ZONESORTING_H__

namespace emtf {

struct zonesorting_stage_traits {
  // Stage 0: perform mux for each pair of 2, and sort each block of 4. N: 288 -> 144
  // Stage 1: merge each pair of blocks, exclude the last 16 cols. N: 144 -> 64
  // Stage 2: merge each pair of blocks. N: 64 -> 32
  // Stage 3: merge each pair of blocks, include the 16 cols that were excluded. N: 32 -> 32
  // Stage 4: merge each pair of blocks. N: 32 -> 16
  // Stage 5: merge each pair of blocks. N: 16 -> 8
  // Stage 6: merge each pair of blocks, write to output. 8 -> 4
  static const unsigned int n_stage_0 = num_img_cols / 2;
  static const unsigned int n_stage_1 = (n_stage_0 - 16) / 2;
  static const unsigned int n_stage_2 = n_stage_1 / 2;
  static const unsigned int n_stage_3 = (n_stage_2 / 2) + 16;
  static const unsigned int n_stage_4 = n_stage_3 / 2;
  static const unsigned int n_stage_5 = n_stage_4 / 2;
  static const unsigned int n_stage_6 = n_stage_5 / 2;
};

template <typename T_IN, typename T_OUT>
void zonesorting_preprocess_eight(const pooling_col_t col, const T_IN in0[8], T_OUT out[4]) {
  static_assert(is_same<T_IN, zonesorting_in_t>::value, "T_IN type check failed");
  static_assert(is_same<T_OUT, zonesorting_out_t>::value, "T_OUT type check failed");

  typedef pooling_activation_t value_t;
  constexpr unsigned int bits_lo = 0;
  constexpr unsigned int bits_hi = (value_t::width - 1);

  // Implement mux for each pair of cols
  // Prepend col number to the input value
  out[0] = (in0[1].range(bits_hi, bits_lo) == 0) ? (pooling_col_t(col + 0), in0[0]) : (pooling_col_t(col + 1), in0[1]);
  out[1] = (in0[3].range(bits_hi, bits_lo) == 0) ? (pooling_col_t(col + 2), in0[2]) : (pooling_col_t(col + 3), in0[3]);
  out[2] = (in0[5].range(bits_hi, bits_lo) == 0) ? (pooling_col_t(col + 4), in0[4]) : (pooling_col_t(col + 5), in0[5]);
  out[3] = (in0[7].range(bits_hi, bits_lo) == 0) ? (pooling_col_t(col + 6), in0[6]) : (pooling_col_t(col + 7), in0[7]);
}

template <typename T_IN, typename T_OUT>
void zonesorting_sort_four(const T_IN in0[4], T_OUT out[4]) {
  static_assert(is_same<T_IN, T_OUT>::value, "T_OUT type check failed");

  typedef pooling_activation_t value_t;
  constexpr unsigned int bits_lo = 0;
  constexpr unsigned int bits_hi = (value_t::width - 1);

  typedef ap_uint<2> idx_t;  // 0..3
  constexpr unsigned int index_bits_lo = value_t::width;
  constexpr unsigned int index_bits_hi = (idx_t::width + value_t::width - 1);

  typedef ap_uint<idx_t::width + value_t::width> T;

  // The following implements the bubble sorting network, which is a stable sort algo.
  // There are 4 wires (0,1,2,3 from top to bottom), and there are 5 stages (not counting
  // Stage 0 which is used as input).
  // In each stage, compare a pair of wires (connected by a vertical line in the diagram).
  // If the value of the top wire is less than that of the bottom wire, swap the wires.
  // Thus, the smallest value moves to the bottom. At the end, all the values are sorted
  // (descending from top to bottom).
  //
  // 0   1   2   3   4   5
  // ----o-------o-------o----
  //     |       |       |
  // ----o---o---o---o---o----
  //         |       |
  // --------o---o---o--------
  //             |
  // ------------o------------

  // Stage 0: concatenate index and value
  const T tmp_0_0 = (idx_t(0), in0[0].range(bits_hi, bits_lo));
  const T tmp_0_1 = (idx_t(1), in0[1].range(bits_hi, bits_lo));
  const T tmp_0_2 = (idx_t(2), in0[2].range(bits_hi, bits_lo));
  const T tmp_0_3 = (idx_t(3), in0[3].range(bits_hi, bits_lo));

  // Stage 1: compare-swap if (wire[i] < wire[j]) swap(wire[j], wire[i])
  const T tmp_1_0 = (tmp_0_0.range(bits_hi, bits_lo) < tmp_0_1.range(bits_hi, bits_lo)) ? tmp_0_1 : tmp_0_0;
  const T tmp_1_1 = (tmp_0_0.range(bits_hi, bits_lo) < tmp_0_1.range(bits_hi, bits_lo)) ? tmp_0_0 : tmp_0_1;

  // Stage 2
  const T tmp_2_1 = (tmp_1_1.range(bits_hi, bits_lo) < tmp_0_2.range(bits_hi, bits_lo)) ? tmp_0_2 : tmp_1_1;
  const T tmp_2_2 = (tmp_1_1.range(bits_hi, bits_lo) < tmp_0_2.range(bits_hi, bits_lo)) ? tmp_1_1 : tmp_0_2;

  // Stage 3
  const T tmp_3_0 = (tmp_1_0.range(bits_hi, bits_lo) < tmp_2_1.range(bits_hi, bits_lo)) ? tmp_2_1 : tmp_1_0;
  const T tmp_3_1 = (tmp_1_0.range(bits_hi, bits_lo) < tmp_2_1.range(bits_hi, bits_lo)) ? tmp_1_0 : tmp_2_1;
  const T tmp_3_2 = (tmp_2_2.range(bits_hi, bits_lo) < tmp_0_3.range(bits_hi, bits_lo)) ? tmp_0_3 : tmp_2_2;
  const T tmp_3_3 = (tmp_2_2.range(bits_hi, bits_lo) < tmp_0_3.range(bits_hi, bits_lo)) ? tmp_2_2 : tmp_0_3;

  // Stage 4
  const T tmp_4_1 = (tmp_3_1.range(bits_hi, bits_lo) < tmp_3_2.range(bits_hi, bits_lo)) ? tmp_3_2 : tmp_3_1;
  const T tmp_4_2 = (tmp_3_1.range(bits_hi, bits_lo) < tmp_3_2.range(bits_hi, bits_lo)) ? tmp_3_1 : tmp_3_2;

  // Stage 5
  const T tmp_5_0 = (tmp_3_0.range(bits_hi, bits_lo) < tmp_4_1.range(bits_hi, bits_lo)) ? tmp_4_1 : tmp_3_0;
  const T tmp_5_1 = (tmp_3_0.range(bits_hi, bits_lo) < tmp_4_1.range(bits_hi, bits_lo)) ? tmp_3_0 : tmp_4_1;

  // Output
  const idx_t idx0 = tmp_5_0.range(index_bits_hi, index_bits_lo);
  const idx_t idx1 = tmp_5_1.range(index_bits_hi, index_bits_lo);
  const idx_t idx2 = tmp_4_2.range(index_bits_hi, index_bits_lo);
  const idx_t idx3 = tmp_3_3.range(index_bits_hi, index_bits_lo);

  out[0] = in0[idx0];
  out[1] = in0[idx1];
  out[2] = in0[idx2];
  out[3] = in0[idx3];
}

template <typename T_IN, typename T_OUT>
void zonesorting_merge_eight(const T_IN in0[8], T_OUT out[4]) {
  static_assert(is_same<T_IN, T_OUT>::value, "T_OUT type check failed");

  typedef pooling_activation_t value_t;
  constexpr unsigned int bits_lo = 0;
  constexpr unsigned int bits_hi = (value_t::width - 1);

  typedef ap_uint<3> idx_t;  // 0..7
  constexpr unsigned int index_bits_lo = value_t::width;
  constexpr unsigned int index_bits_hi = (idx_t::width + value_t::width - 1);

  typedef ap_uint<idx_t::width + value_t::width> T;

  // The following implements the odd-even merge sorting network, which is *not* a stable sort algo.
  // There are 8 wires (0..7 from top to bottom), and there are 3 stages (not counting
  // Stage 0 which is used as input). Each set of top 4 and bottom 4 wires is assumed to
  // be sorted.
  // In each stage, compare a pair of wires (connected by a vertical line in the diagram).
  // If the value of the top wire is less than that of the bottom wire, swap the wires.
  //
  // 0     1         2       3
  // ----o-------------------------
  //     |
  // ----|-o-----------------o-----
  //     | |                 |
  // ----|-|-o-------o-------o-----
  //     | | |       |
  // ----|-|-|-o-----|-o-----o-----
  //     | | | |     | |     |
  // ----o-|-|-|-----o-|-----o-----
  //       | | |       |
  // ------o-|-|-------o-----o-----
  //         | |             |
  // --------o-|-------------o-----
  //           |
  // ----------o-------------------

  // Stage 0: concatenate index and value
  const T tmp_0_0 = (idx_t(0), in0[0].range(bits_hi, bits_lo));
  const T tmp_0_1 = (idx_t(1), in0[1].range(bits_hi, bits_lo));
  const T tmp_0_2 = (idx_t(2), in0[2].range(bits_hi, bits_lo));
  const T tmp_0_3 = (idx_t(3), in0[3].range(bits_hi, bits_lo));
  const T tmp_0_4 = (idx_t(4), in0[4].range(bits_hi, bits_lo));
  const T tmp_0_5 = (idx_t(5), in0[5].range(bits_hi, bits_lo));
  const T tmp_0_6 = (idx_t(6), in0[6].range(bits_hi, bits_lo));
  const T tmp_0_7 = (idx_t(7), in0[7].range(bits_hi, bits_lo));

  // Stage 1: compare-swap if (wire[i] < wire[j]) swap(wire[j], wire[i])
  const T tmp_1_0 = (tmp_0_0.range(bits_hi, bits_lo) < tmp_0_4.range(bits_hi, bits_lo)) ? tmp_0_4 : tmp_0_0;
  const T tmp_1_1 = (tmp_0_1.range(bits_hi, bits_lo) < tmp_0_5.range(bits_hi, bits_lo)) ? tmp_0_5 : tmp_0_1;
  const T tmp_1_2 = (tmp_0_2.range(bits_hi, bits_lo) < tmp_0_6.range(bits_hi, bits_lo)) ? tmp_0_6 : tmp_0_2;
  const T tmp_1_3 = (tmp_0_3.range(bits_hi, bits_lo) < tmp_0_7.range(bits_hi, bits_lo)) ? tmp_0_7 : tmp_0_3;
  const T tmp_1_4 = (tmp_0_0.range(bits_hi, bits_lo) < tmp_0_4.range(bits_hi, bits_lo)) ? tmp_0_0 : tmp_0_4;
  const T tmp_1_5 = (tmp_0_1.range(bits_hi, bits_lo) < tmp_0_5.range(bits_hi, bits_lo)) ? tmp_0_1 : tmp_0_5;
  //const T tmp_1_6 = (tmp_0_2.range(bits_hi, bits_lo) < tmp_0_6.range(bits_hi, bits_lo)) ? tmp_0_2 : tmp_0_6;  // unused
  //const T tmp_1_7 = (tmp_0_3.range(bits_hi, bits_lo) < tmp_0_7.range(bits_hi, bits_lo)) ? tmp_0_3 : tmp_0_7;  // unused

  // Stage 2
  const T tmp_2_2 = (tmp_1_2.range(bits_hi, bits_lo) < tmp_1_4.range(bits_hi, bits_lo)) ? tmp_1_4 : tmp_1_2;
  const T tmp_2_3 = (tmp_1_3.range(bits_hi, bits_lo) < tmp_1_5.range(bits_hi, bits_lo)) ? tmp_1_5 : tmp_1_3;
  const T tmp_2_4 = (tmp_1_2.range(bits_hi, bits_lo) < tmp_1_4.range(bits_hi, bits_lo)) ? tmp_1_2 : tmp_1_4;
  //const T tmp_2_5 = (tmp_1_3.range(bits_hi, bits_lo) < tmp_1_5.range(bits_hi, bits_lo)) ? tmp_1_3 : tmp_1_5;  // unused

  // Stage 3
  const T tmp_3_1 = (tmp_1_1.range(bits_hi, bits_lo) < tmp_2_2.range(bits_hi, bits_lo)) ? tmp_2_2 : tmp_1_1;
  const T tmp_3_2 = (tmp_1_1.range(bits_hi, bits_lo) < tmp_2_2.range(bits_hi, bits_lo)) ? tmp_1_1 : tmp_2_2;
  const T tmp_3_3 = (tmp_2_3.range(bits_hi, bits_lo) < tmp_2_4.range(bits_hi, bits_lo)) ? tmp_2_4 : tmp_2_3;
  //const T tmp_3_4 = (tmp_2_3.range(bits_hi, bits_lo) < tmp_2_4.range(bits_hi, bits_lo)) ? tmp_2_3 : tmp_2_4;  // unused
  //const T tmp_3_5 = (tmp_2_5.range(bits_hi, bits_lo) < tmp_1_6.range(bits_hi, bits_lo)) ? tmp_1_6 : tmp_2_5;  // unused
  //const T tmp_3_6 = (tmp_2_5.range(bits_hi, bits_lo) < tmp_1_6.range(bits_hi, bits_lo)) ? tmp_2_5 : tmp_1_6;  // unused

  // Output
  const idx_t idx0 = tmp_1_0.range(index_bits_hi, index_bits_lo);
  const idx_t idx1 = tmp_3_1.range(index_bits_hi, index_bits_lo);
  const idx_t idx2 = tmp_3_2.range(index_bits_hi, index_bits_lo);
  const idx_t idx3 = tmp_3_3.range(index_bits_hi, index_bits_lo);

  out[0] = in0[idx0];
  out[1] = in0[idx1];
  out[2] = in0[idx2];
  out[3] = in0[idx3];
}


// _____________________________________________________________________________
// A wrapper for sorting
template <typename T_IN, typename T_OUT>
void zonesorting_preprocess_eight_and_sort(const pooling_col_t col, const T_IN in0[8], T_OUT out[4]) {
  static_assert(is_same<T_IN, zonesorting_in_t>::value, "T_IN type check failed");
  static_assert(is_same<T_OUT, zonesorting_out_t>::value, "T_OUT type check failed");

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE region

  zonesorting_out_t out_tmp[4];

#pragma HLS ARRAY_PARTITION variable=out_tmp complete dim=0

  zonesorting_preprocess_eight(col, in0, out_tmp);
  zonesorting_sort_four(out_tmp, out);
}

// A wrapper for sorting
template <int N_IN, int N_OUT>
void zonesorting_sort_stage(
    const zonesorting_in_t in0[N_IN],
    zonesorting_out_t out[N_OUT]
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE region

  // Loop with step size 8
  for (unsigned i = 0; i < N_IN; i += 8) {

#pragma HLS UNROLL

    zonesorting_preprocess_eight_and_sort(i, in0 + i, out + (i/2));
  }
}

// A wrapper for merging
template <int N_IN, int N_OUT>
void zonesorting_merge_stage(
    const zonesorting_out_t in0[N_IN],
    zonesorting_out_t out[N_OUT]
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE region

  // Loop with step size 8
  for (unsigned i = 0; i < N_IN; i += 8) {

#pragma HLS UNROLL

    zonesorting_merge_eight(in0 + i, out + (i/2));
  }
}

// A wrapper for merging (stage 1 is a special case)
template <int N_IN, int N_OUT_0, int N_OUT_1>
void zonesorting_merge_stage_s1(
    const zonesorting_out_t in0[N_IN],
    zonesorting_out_t out0[N_OUT_0],
    zonesorting_out_t out1[N_OUT_1]
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE region

  // Loop with step size 8, exclude last 16 elements
  for (unsigned i = 0; i < (N_IN - 16); i += 8) {

#pragma HLS UNROLL

    zonesorting_merge_eight(in0 + i, out0 + (i/2));
  }

  // Copy the remaining 16 elements
  for (unsigned i = (N_IN - 16), j = 16; i < N_IN; i++, j++) {

#pragma HLS UNROLL

    out1[j] = in0[i];
  }
}


// _____________________________________________________________________________
// Zone sorting op

template <int ZONE>
void zonesorting_op(
    const zonesorting_in_t zonesorting_in[N_ZONESORTING_IN],
    zonesorting_out_t zonesorting_out[N_ZONESORTING_OUT]
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE region

//#pragma HLS DATAFLOW

  constexpr unsigned int n_stage_0 = zonesorting_stage_traits::n_stage_0;
  constexpr unsigned int n_stage_1 = zonesorting_stage_traits::n_stage_1;
  constexpr unsigned int n_stage_2 = zonesorting_stage_traits::n_stage_2;
  constexpr unsigned int n_stage_3 = zonesorting_stage_traits::n_stage_3;
  constexpr unsigned int n_stage_4 = zonesorting_stage_traits::n_stage_4;
  constexpr unsigned int n_stage_5 = zonesorting_stage_traits::n_stage_5;
  constexpr unsigned int n_stage_6 = zonesorting_stage_traits::n_stage_6;

  zonesorting_out_t stage_0_out[n_stage_0];
  zonesorting_out_t stage_1_out[n_stage_1];
  zonesorting_out_t stage_2_out[n_stage_2];
  zonesorting_out_t stage_3_out[n_stage_3];
  zonesorting_out_t stage_4_out[n_stage_4];
  zonesorting_out_t stage_5_out[n_stage_5];

#pragma HLS ARRAY_PARTITION variable=stage_0_out complete dim=0
#pragma HLS ARRAY_PARTITION variable=stage_1_out complete dim=0
#pragma HLS ARRAY_PARTITION variable=stage_2_out complete dim=0
#pragma HLS ARRAY_PARTITION variable=stage_3_out complete dim=0
#pragma HLS ARRAY_PARTITION variable=stage_4_out complete dim=0
#pragma HLS ARRAY_PARTITION variable=stage_5_out complete dim=0

  // Implement mux for each pair of cols.
  // After non-max suppression, the adjacent col next to the local-max col is always zero.
  // Then, sort each block of 4.
  // Stage 0 : 288 -> 144
  zonesorting_sort_stage<num_img_cols, n_stage_0>(zonesorting_in, stage_0_out);

  // Merge each pair of blocks.
  // Stage 1 : 128 -> 64 (start with the first 128 cols, excluding the last 16 cols)
  // Stage 2 : 64 -> 32
  // Stage 3 : 32 -> 32 (include the 16 cols that were excluded)
  // Stage 4 : 32 -> 16
  // Stage 5 : 16 -> 8
  // Stage 6 : 8 -> 4
  zonesorting_merge_stage_s1<n_stage_0, n_stage_1, n_stage_3>(stage_0_out, stage_1_out, stage_3_out);  // stage 1 is a special case
  zonesorting_merge_stage<n_stage_1, n_stage_2>(stage_1_out, stage_2_out);
  zonesorting_merge_stage<n_stage_2, n_stage_3>(stage_2_out, stage_3_out);
  zonesorting_merge_stage<n_stage_3, n_stage_4>(stage_3_out, stage_4_out);
  zonesorting_merge_stage<n_stage_4, n_stage_5>(stage_4_out, stage_5_out);
  zonesorting_merge_stage<n_stage_5, n_stage_6>(stage_5_out, zonesorting_out);
}


// _____________________________________________________________________________
// Entry point

template <int ZONE>
void zonesorting_layer(
    const zonesorting_in_t zonesorting_in[N_ZONESORTING_IN],
    zonesorting_out_t zonesorting_out[N_ZONESORTING_OUT]
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE region

  // Check assumptions
  static_assert(N_ZONESORTING_IN == num_img_cols, "N_ZONESORTING_IN check failed");
  static_assert(N_ZONESORTING_OUT == num_tracks, "N_ZONESORTING_OUT check failed");
  static_assert((zonesorting_stage_traits::n_stage_0 % 8) == 0, "n_stage_0 must be divisible by 8");
  static_assert((zonesorting_stage_traits::n_stage_1 % 8) == 0, "n_stage_1 must be divisible by 8");
  static_assert((zonesorting_stage_traits::n_stage_2 % 8) == 0, "n_stage_2 must be divisible by 8");
  static_assert((zonesorting_stage_traits::n_stage_3 % 8) == 0, "n_stage_3 must be divisible by 8");
  static_assert((zonesorting_stage_traits::n_stage_4 % 8) == 0, "n_stage_4 must be divisible by 8");
  static_assert((zonesorting_stage_traits::n_stage_5 % 8) == 0, "n_stage_5 must be divisible by 8");
  static_assert(zonesorting_stage_traits::n_stage_6 == num_tracks, "n_stage_6 must be equal to num_tracks");

  zonesorting_op<ZONE>(zonesorting_in, zonesorting_out);
}

}  // namespace emtf

#endif  // __EMTF_HLSLIB_ZONESORTING_H__ not defined
