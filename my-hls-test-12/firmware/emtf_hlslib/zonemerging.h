#ifndef __EMTF_HLSLIB_ZONEMERGING_H__
#define __EMTF_HLSLIB_ZONEMERGING_H__

namespace emtf {

template <typename T_IN, typename T_OUT>
void zonemerging_preprocess_twelve(const T_IN in0[4], const T_IN in1[4], const T_IN in2[4], T_OUT out[12]) {
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

  typedef ap_uint<4> idx_t;
  typedef pooling_activation_t value_t;
  typedef ap_uint<idx_t::width + value_t::width> T;

  constexpr unsigned int bits_lo = 0;
  constexpr unsigned int bits_hi = (value_t::width - 1);
  constexpr unsigned int index_bits_lo = value_t::width;
  constexpr unsigned int index_bits_hi = (idx_t::width + value_t::width - 1);

  // Concatenate index and value
  const T x0 = (idx_t(0), in0[0].range(bits_hi, bits_lo));
  const T x1 = (idx_t(1), in0[1].range(bits_hi, bits_lo));
  const T x2 = (idx_t(2), in0[2].range(bits_hi, bits_lo));
  const T x3 = (idx_t(3), in0[3].range(bits_hi, bits_lo));
  const T x4 = (idx_t(4), in0[4].range(bits_hi, bits_lo));
  const T x5 = (idx_t(5), in0[5].range(bits_hi, bits_lo));
  const T x6 = (idx_t(6), in0[6].range(bits_hi, bits_lo));
  const T x7 = (idx_t(7), in0[7].range(bits_hi, bits_lo));
  const T x8 = (idx_t(8), in0[8].range(bits_hi, bits_lo));
  const T x9 = (idx_t(9), in0[9].range(bits_hi, bits_lo));
  const T x10 = (idx_t(10), in0[10].range(bits_hi, bits_lo));
  const T x11 = (idx_t(11), in0[11].range(bits_hi, bits_lo));

  // Stage 0
  const T tmp_0_0 = (x0.range(bits_hi, bits_lo) >= x4.range(bits_hi, bits_lo)) ? x0 : x4;
  const T tmp_0_1 = (x0.range(bits_hi, bits_lo) >= x4.range(bits_hi, bits_lo)) ? x4 : x0;
  const T tmp_0_2 = (x1.range(bits_hi, bits_lo) >= x5.range(bits_hi, bits_lo)) ? x1 : x5;
  const T tmp_0_3 = (x1.range(bits_hi, bits_lo) >= x5.range(bits_hi, bits_lo)) ? x5 : x1;
  const T tmp_0_4 = (x2.range(bits_hi, bits_lo) >= x6.range(bits_hi, bits_lo)) ? x2 : x6;
  const T tmp_0_5 = (x2.range(bits_hi, bits_lo) >= x6.range(bits_hi, bits_lo)) ? x6 : x2;
  const T tmp_0_6 = (x3.range(bits_hi, bits_lo) >= x7.range(bits_hi, bits_lo)) ? x3 : x7;
  //const T tmp_0_7 = (x3.range(bits_hi, bits_lo) >= x7.range(bits_hi, bits_lo)) ? x7 : x3;  // unused

  // Stage 1
  const T tmp_1_0 = (tmp_0_1.range(bits_hi, bits_lo) >= tmp_0_2.range(bits_hi, bits_lo)) ? tmp_0_1 : tmp_0_2;
  const T tmp_1_1 = (tmp_0_1.range(bits_hi, bits_lo) >= tmp_0_2.range(bits_hi, bits_lo)) ? tmp_0_2 : tmp_0_1;
  const T tmp_1_2 = (tmp_0_3.range(bits_hi, bits_lo) >= tmp_0_4.range(bits_hi, bits_lo)) ? tmp_0_3 : tmp_0_4;
  const T tmp_1_3 = (tmp_0_3.range(bits_hi, bits_lo) >= tmp_0_4.range(bits_hi, bits_lo)) ? tmp_0_4 : tmp_0_3;
  const T tmp_1_4 = (tmp_0_5.range(bits_hi, bits_lo) >= tmp_0_6.range(bits_hi, bits_lo)) ? tmp_0_5 : tmp_0_6;
  //const T tmp_1_5 = (tmp_0_5.range(bits_hi, bits_lo) >= tmp_0_6.range(bits_hi, bits_lo)) ? tmp_0_6 : tmp_0_5;  // unused

  // Stage 2
  const T tmp_2_0 = (tmp_1_1.range(bits_hi, bits_lo) >= tmp_1_2.range(bits_hi, bits_lo)) ? tmp_1_1 : tmp_1_2;
  const T tmp_2_1 = (tmp_1_1.range(bits_hi, bits_lo) >= tmp_1_2.range(bits_hi, bits_lo)) ? tmp_1_2 : tmp_1_1;
  const T tmp_2_2 = (tmp_1_3.range(bits_hi, bits_lo) >= tmp_1_4.range(bits_hi, bits_lo)) ? tmp_1_3 : tmp_1_4;
  //const T tmp_2_3 = (tmp_1_3.range(bits_hi, bits_lo) >= tmp_1_4.range(bits_hi, bits_lo)) ? tmp_1_4 : tmp_1_3;  // unused

  // Stage 3
  const T tmp_3_0 = (tmp_2_1.range(bits_hi, bits_lo) >= tmp_2_2.range(bits_hi, bits_lo)) ? tmp_2_1 : tmp_2_2;
  //const T tmp_3_1 = (tmp_2_1.range(bits_hi, bits_lo) >= tmp_2_2.range(bits_hi, bits_lo)) ? tmp_2_2 : tmp_2_1;  // unused

  // Stage 4
  const T tmp_4_0 = (tmp_0_0.range(bits_hi, bits_lo) >= x8.range(bits_hi, bits_lo)) ? tmp_0_0 : x8;
  const T tmp_4_1 = (tmp_0_0.range(bits_hi, bits_lo) >= x8.range(bits_hi, bits_lo)) ? x8 : tmp_0_0;
  const T tmp_4_2 = (tmp_1_0.range(bits_hi, bits_lo) >= x9.range(bits_hi, bits_lo)) ? tmp_1_0 : x9;
  const T tmp_4_3 = (tmp_1_0.range(bits_hi, bits_lo) >= x9.range(bits_hi, bits_lo)) ? x9 : tmp_1_0;
  const T tmp_4_4 = (tmp_2_0.range(bits_hi, bits_lo) >= x10.range(bits_hi, bits_lo)) ? tmp_2_0 : x10;
  const T tmp_4_5 = (tmp_2_0.range(bits_hi, bits_lo) >= x10.range(bits_hi, bits_lo)) ? x10 : tmp_2_0;
  const T tmp_4_6 = (tmp_3_0.range(bits_hi, bits_lo) >= x11.range(bits_hi, bits_lo)) ? tmp_3_0 : x11;
  //const T tmp_4_7 = (tmp_3_0.range(bits_hi, bits_lo) >= x11.range(bits_hi, bits_lo)) ? x11 : tmp_3_0;  // unused

  // Stage 5
  const T tmp_5_0 = (tmp_4_1.range(bits_hi, bits_lo) >= tmp_4_2.range(bits_hi, bits_lo)) ? tmp_4_1 : tmp_4_2;
  const T tmp_5_1 = (tmp_4_1.range(bits_hi, bits_lo) >= tmp_4_2.range(bits_hi, bits_lo)) ? tmp_4_2 : tmp_4_1;
  const T tmp_5_2 = (tmp_4_3.range(bits_hi, bits_lo) >= tmp_4_4.range(bits_hi, bits_lo)) ? tmp_4_3 : tmp_4_4;
  const T tmp_5_3 = (tmp_4_3.range(bits_hi, bits_lo) >= tmp_4_4.range(bits_hi, bits_lo)) ? tmp_4_4 : tmp_4_3;
  const T tmp_5_4 = (tmp_4_5.range(bits_hi, bits_lo) >= tmp_4_6.range(bits_hi, bits_lo)) ? tmp_4_5 : tmp_4_6;
  //const T tmp_5_5 = (tmp_4_5.range(bits_hi, bits_lo) >= tmp_4_6.range(bits_hi, bits_lo)) ? tmp_4_6 : tmp_4_5;  // unused

  // Stage 6
  const T tmp_6_0 = (tmp_5_1.range(bits_hi, bits_lo) >= tmp_5_2.range(bits_hi, bits_lo)) ? tmp_5_1 : tmp_5_2;
  const T tmp_6_1 = (tmp_5_1.range(bits_hi, bits_lo) >= tmp_5_2.range(bits_hi, bits_lo)) ? tmp_5_2 : tmp_5_1;
  const T tmp_6_2 = (tmp_5_3.range(bits_hi, bits_lo) >= tmp_5_4.range(bits_hi, bits_lo)) ? tmp_5_3 : tmp_5_4;
  //const T tmp_6_3 = (tmp_5_3.range(bits_hi, bits_lo) >= tmp_5_4.range(bits_hi, bits_lo)) ? tmp_5_4 : tmp_5_3;  // unused

  // Stage 7
  const T tmp_7_0 = (tmp_6_1.range(bits_hi, bits_lo) >= tmp_6_2.range(bits_hi, bits_lo)) ? tmp_6_1 : tmp_6_2;
  //const T tmp_7_1 = (tmp_6_1.range(bits_hi, bits_lo) >= tmp_6_2.range(bits_hi, bits_lo)) ? tmp_6_2 : tmp_6_1;  // unused

  // Output
  const idx_t idx0 = tmp_4_0.range(index_bits_hi, index_bits_lo);
  const idx_t idx1 = tmp_5_0.range(index_bits_hi, index_bits_lo);
  const idx_t idx2 = tmp_6_0.range(index_bits_hi, index_bits_lo);
  const idx_t idx3 = tmp_7_0.range(index_bits_hi, index_bits_lo);

  out[0] = in0[idx0];
  out[1] = in0[idx1];
  out[2] = in0[idx2];
  out[3] = in0[idx3];
}


// _____________________________________________________________________________
// Zone merging op

template <int ZONE>
void zonemerging_op(
    const zonemerging_in_t zonemerging_0_in[N_ZONEMERGING_IN],
    const zonemerging_in_t zonemerging_1_in[N_ZONEMERGING_IN],
    const zonemerging_in_t zonemerging_2_in[N_ZONEMERGING_IN],
    zonemerging_out_t zonemerging_out[N_ZONEMERGING_OUT]
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE region

//#pragma HLS DATAFLOW

  zonemerging_out_t zonemerging_out_tmp[N_ZONEMERGING_IN * 3];

#pragma HLS ARRAY_PARTITION variable=zonemerging_out_tmp complete dim=0

  // Preprocessing the inputs and concatenate them
  zonemerging_preprocess_twelve(zonemerging_0_in, zonemerging_1_in, zonemerging_2_in, zonemerging_out_tmp);

  // Merge 'em
  zonemerging_merge_twelve(zonemerging_out_tmp, zonemerging_out);
}


// _____________________________________________________________________________
// Entry point

template <int ZONE>
void zonemerging_layer(
    const zonemerging_in_t zonemerging_0_in[N_ZONEMERGING_IN],
    const zonemerging_in_t zonemerging_1_in[N_ZONEMERGING_IN],
    const zonemerging_in_t zonemerging_2_in[N_ZONEMERGING_IN],
    zonemerging_out_t zonemerging_out[N_ZONEMERGING_OUT]
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE region

  // Check assumptions
  static_assert(N_ZONEMERGING_IN == num_tracks, "N_ZONEMERGING_IN check failed");
  static_assert(N_ZONEMERGING_OUT == num_tracks, "N_ZONEMERGING_OUT check failed");

  zonemerging_op<ZONE>(zonemerging_0_in, zonemerging_1_in, zonemerging_2_in, zonemerging_out);
}

}  // namespace emtf

#endif  // __EMTF_HLSLIB_ZONEMERGING_H__ not defined
