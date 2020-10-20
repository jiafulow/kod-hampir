#ifndef __EMTF_HLSLIB_ZONEMERGING_H__
#define __EMTF_HLSLIB_ZONEMERGING_H__

namespace emtf {

template <typename T_IN, typename T_OUT>
void zonemerging_preprocess_twelve(const T_IN in0[4], const T_IN in1[4], const T_IN in2[4], T_OUT out[12]) {
  static_assert(is_same<T_IN, zonemerging_in_t>::value, "T_IN type check failed");
  static_assert(is_same<T_OUT, zonemerging_out_t>::value, "T_OUT type check failed");

  // Prepend zone number to the input value
  out[0] = (pooling_zone_t(0), in0[0]);
  out[1] = (pooling_zone_t(0), in0[1]);
  out[2] = (pooling_zone_t(0), in0[2]);
  out[3] = (pooling_zone_t(0), in0[3]);
  out[4] = (pooling_zone_t(1), in1[0]);
  out[5] = (pooling_zone_t(1), in1[1]);
  out[6] = (pooling_zone_t(1), in1[2]);
  out[7] = (pooling_zone_t(1), in1[3]);
  out[8] = (pooling_zone_t(2), in2[0]);
  out[9] = (pooling_zone_t(2), in2[1]);
  out[10] = (pooling_zone_t(2), in2[2]);
  out[11] = (pooling_zone_t(2), in2[3]);
}

template <typename T_IN, typename T_OUT>
void zonemerging_merge_twelve(const T_IN in0[12], T_OUT out[4]) {
  static_assert(is_same<T_IN, T_OUT>::value, "T_OUT type check failed");

  typedef pooling_activation_t value_t;
  constexpr unsigned int bits_lo = 0;
  constexpr unsigned int bits_hi = (value_t::width - 1);

  typedef ap_uint<4> idx_t;  // 0..11
  constexpr unsigned int index_bits_lo = value_t::width;
  constexpr unsigned int index_bits_hi = (idx_t::width + value_t::width - 1);

  typedef ap_uint<idx_t::width + value_t::width> T;

  // This is based on zonesorting_merge_eight(). See comments in emtf_hlslib/zonesorting.h
  // for explanations.

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

  // Stage 4
  const T tmp_4_0 = (tmp_1_0.range(bits_hi, bits_lo) < tmp_0_8.range(bits_hi, bits_lo)) ? tmp_0_8 : tmp_1_0;
  const T tmp_4_1 = (tmp_3_1.range(bits_hi, bits_lo) < tmp_0_9.range(bits_hi, bits_lo)) ? tmp_0_9 : tmp_3_1;
  const T tmp_4_2 = (tmp_3_2.range(bits_hi, bits_lo) < tmp_0_10.range(bits_hi, bits_lo)) ? tmp_0_10 : tmp_3_2;
  const T tmp_4_3 = (tmp_3_3.range(bits_hi, bits_lo) < tmp_0_11.range(bits_hi, bits_lo)) ? tmp_0_11 : tmp_3_3;
  const T tmp_4_4 = (tmp_1_0.range(bits_hi, bits_lo) < tmp_0_8.range(bits_hi, bits_lo)) ? tmp_1_0 : tmp_0_8;
  const T tmp_4_5 = (tmp_3_1.range(bits_hi, bits_lo) < tmp_0_9.range(bits_hi, bits_lo)) ? tmp_3_1 : tmp_0_9;
  //const T tmp_4_6 = (tmp_3_2.range(bits_hi, bits_lo) < tmp_0_10.range(bits_hi, bits_lo)) ? tmp_3_2 : tmp_0_10;  // unused
  //const T tmp_4_7 = (tmp_3_3.range(bits_hi, bits_lo) < tmp_0_11.range(bits_hi, bits_lo)) ? tmp_3_3 : tmp_0_11;  // unused

  // Stage 5
  const T tmp_5_2 = (tmp_4_2.range(bits_hi, bits_lo) < tmp_4_4.range(bits_hi, bits_lo)) ? tmp_4_4 : tmp_4_2;
  const T tmp_5_3 = (tmp_4_3.range(bits_hi, bits_lo) < tmp_4_5.range(bits_hi, bits_lo)) ? tmp_4_5 : tmp_4_3;
  const T tmp_5_4 = (tmp_4_2.range(bits_hi, bits_lo) < tmp_4_4.range(bits_hi, bits_lo)) ? tmp_4_2 : tmp_4_4;
  //const T tmp_5_5 = (tmp_4_3.range(bits_hi, bits_lo) < tmp_4_5.range(bits_hi, bits_lo)) ? tmp_4_3 : tmp_4_5;  // unused

  // Stage 6
  const T tmp_6_1 = (tmp_4_1.range(bits_hi, bits_lo) < tmp_5_2.range(bits_hi, bits_lo)) ? tmp_5_2 : tmp_4_1;
  const T tmp_6_2 = (tmp_4_1.range(bits_hi, bits_lo) < tmp_5_2.range(bits_hi, bits_lo)) ? tmp_4_1 : tmp_5_2;
  const T tmp_6_3 = (tmp_5_3.range(bits_hi, bits_lo) < tmp_5_4.range(bits_hi, bits_lo)) ? tmp_5_4 : tmp_5_3;
  //const T tmp_6_4 = (tmp_5_3.range(bits_hi, bits_lo) < tmp_5_4.range(bits_hi, bits_lo)) ? tmp_5_3 : tmp_5_4;  // unused
  //const T tmp_6_5 = (tmp_5_5.range(bits_hi, bits_lo) < tmp_4_6.range(bits_hi, bits_lo)) ? tmp_4_6 : tmp_5_5;  // unused
  //const T tmp_6_6 = (tmp_5_5.range(bits_hi, bits_lo) < tmp_4_6.range(bits_hi, bits_lo)) ? tmp_5_5 : tmp_4_6;  // unused

  // Output
  const idx_t idx0 = tmp_4_0.range(index_bits_hi, index_bits_lo);
  const idx_t idx1 = tmp_6_1.range(index_bits_hi, index_bits_lo);
  const idx_t idx2 = tmp_6_2.range(index_bits_hi, index_bits_lo);
  const idx_t idx3 = tmp_6_3.range(index_bits_hi, index_bits_lo);

  out[0] = in0[idx0];
  out[1] = in0[idx1];
  out[2] = in0[idx2];
  out[3] = in0[idx3];
}


// _____________________________________________________________________________
// Zone merging op

template <int ZONE>
void zonemerging_op(
    const zonemerging_in_t zonemerging_in_0[N_ZONEMERGING_IN],
    const zonemerging_in_t zonemerging_in_1[N_ZONEMERGING_IN],
    const zonemerging_in_t zonemerging_in_2[N_ZONEMERGING_IN],
    zonemerging_out_t zonemerging_out[N_ZONEMERGING_OUT]
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE region

//#pragma HLS DATAFLOW

  zonemerging_out_t zonemerging_out_tmp[N_ZONEMERGING_IN * 3];

#pragma HLS ARRAY_PARTITION variable=zonemerging_out_tmp complete dim=0

  // Preprocessing and concatenate them.
  zonemerging_preprocess_twelve(zonemerging_in_0, zonemerging_in_1, zonemerging_in_2, zonemerging_out_tmp);

  // Merge 3 blocks of 4.
  zonemerging_merge_twelve(zonemerging_out_tmp, zonemerging_out);
}


// _____________________________________________________________________________
// Entry point

template <int ZONE>
void zonemerging_layer(
    const zonemerging_in_t zonemerging_in_0[N_ZONEMERGING_IN],
    const zonemerging_in_t zonemerging_in_1[N_ZONEMERGING_IN],
    const zonemerging_in_t zonemerging_in_2[N_ZONEMERGING_IN],
    zonemerging_out_t zonemerging_out[N_ZONEMERGING_OUT]
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE region

  // Check assumptions
  static_assert(N_ZONEMERGING_IN == num_tracks, "N_ZONEMERGING_IN check failed");
  static_assert(N_ZONEMERGING_OUT == num_tracks, "N_ZONEMERGING_OUT check failed");

  zonemerging_op<ZONE>(zonemerging_in_0, zonemerging_in_1, zonemerging_in_2, zonemerging_out);
}

}  // namespace emtf

#endif  // __EMTF_HLSLIB_ZONEMERGING_H__ not defined
