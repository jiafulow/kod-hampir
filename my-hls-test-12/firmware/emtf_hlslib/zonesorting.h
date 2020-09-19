#ifndef __EMTF_HLSLIB_ZONESORTING_H__
#define __EMTF_HLSLIB_ZONESORTING_H__

namespace emtf {

template <typename T>
void sort_four(
    const T in0, const T in1, const T in2, const T in3,
    T& out0, T& out1, T& out2, T& out3
) {
  T tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;

  // To completely sort 4 values, compare each value against the other 3.
  // Stage 0
  tmp0 = (in0 >= in1) ? in0 : in1;
  tmp1 = (in0 >= in1) ? in1 : in0;
  tmp2 = (in2 >= in3) ? in2 : in3;
  tmp3 = (in2 >= in3) ? in3 : in2;

  // Stage 1
  tmp4 = (tmp0 >= tmp2) ? tmp0 : tmp2;
  tmp5 = (tmp0 >= tmp2) ? tmp2 : tmp0;
  tmp6 = (tmp1 >= tmp3) ? tmp1 : tmp3;
  tmp7 = (tmp1 >= tmp3) ? tmp3 : tmp1;

  // Stage 2
  out0 = tmp4;
  out1 = (tmp5 >= tmp6) ? tmp5 : tmp6;
  out2 = (tmp5 >= tmp6) ? tmp6 : tmp5;
  out3 = tmp7;
}

template <typename T>
void merge_eight(
    const T in0, const T in1, const T in2, const T in3,
    const T in4, const T in5, const T in6, const T in7,
    T& out0, T& out1, T& out2, T& out3
) {
  T tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
  T tmp8, tmp9, tmp10, tmp11, tmp12, tmp13, tmp14, tmp15;

  // Merge a pair of sorted tuples
  // Stage 0
  tmp0 = (in0 >= in4) ? in0 : in4;
  tmp1 = (in0 >= in4) ? in4 : in0;
  tmp2 = (in1 >= in5) ? in1 : in5;
  tmp3 = (in1 >= in5) ? in5 : in1;
  tmp4 = (in2 >= in6) ? in2 : in6;
  tmp5 = (in2 >= in6) ? in6 : in2;
  tmp6 = (in3 >= in7) ? in3 : in7;

  // Stage 2
  tmp7 = (tmp1 >= tmp2) ? tmp1 : tmp2;
  tmp8 = (tmp1 >= tmp2) ? tmp2 : tmp1;
  tmp9 = (tmp3 >= tmp4) ? tmp3 : tmp4;
  tmp10 = (tmp3 >= tmp4) ? tmp4 : tmp3;
  tmp11 = (tmp5 >= tmp6) ? tmp5 : tmp6;

  // Stage 3
  tmp12 = (tmp8 >= tmp9) ? tmp8 : tmp9;
  tmp13 = (tmp8 >= tmp9) ? tmp9 : tmp8;
  tmp14 = (tmp10 >= tmp11) ? tmp10 : tmp11;

  // Stage 4
  tmp15 = (tmp13 >= tmp14) ? tmp13 : tmp14;

  out0 = tmp0;
  out1 = tmp7;
  out2 = tmp12;
  out3 = tmp15;
}

// Zone sorting op
template <int ZONE>
void zonesorting_op(
    const zonesorting_in_t zonesorting_in[N_ZONESORTING_IN],
    zonesorting_out_t zonesorting_out[N_ZONESORTING_OUT]
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

  // Check assumptions
  static_assert(N_ZONESORTING_IN == num_img_cols, "N_ZONESORTING_IN check failed");
  static_assert(N_ZONESORTING_OUT == num_out_tracks, "N_ZONESORTING_OUT check failed");

  constexpr int n_zonesorting_out_tmp0 = num_img_cols/2;
  zonesorting_out_t zonesorting_out_tmp0[n_zonesorting_out_tmp0];

#pragma HLS ARRAY_PARTITION variable=zonesorting_out_tmp0 complete dim=0

  constexpr int n_zonesorting_out_tmp1 = 64;
  zonesorting_out_t zonesorting_out_tmp1[n_zonesorting_out_tmp1];

#pragma HLS ARRAY_PARTITION variable=zonesorting_out_tmp1 complete dim=0

  constexpr int n_zonesorting_out_tmp2 = 32;
  zonesorting_out_t zonesorting_out_tmp2[n_zonesorting_out_tmp2];

#pragma HLS ARRAY_PARTITION variable=zonesorting_out_tmp2 complete dim=0

  constexpr int n_zonesorting_out_tmp3 = 32;
  zonesorting_out_t zonesorting_out_tmp3[n_zonesorting_out_tmp3];

#pragma HLS ARRAY_PARTITION variable=zonesorting_out_tmp3 complete dim=0

  constexpr int n_zonesorting_out_tmp4 = 16;
  zonesorting_out_t zonesorting_out_tmp4[n_zonesorting_out_tmp4];

#pragma HLS ARRAY_PARTITION variable=zonesorting_out_tmp4 complete dim=0

  constexpr int n_zonesorting_out_tmp5 = 8;
  zonesorting_out_t zonesorting_out_tmp5[n_zonesorting_out_tmp5];

#pragma HLS ARRAY_PARTITION variable=zonesorting_out_tmp5 complete dim=0


  // Implement mux for each pair of cols
  // After non-max suppression, the adjacent col next to the local-max col is always zero
  // Sort each block of 4
  // Num of cols: 288 -> 144

  static_assert((num_img_cols % 8) == 0, "num_img_cols must be divisible by 8");
  static_assert((n_zonesorting_out_tmp0 % 8) == 0, "n_zonesorting_out_tmp0 must be divisible by 8");
  static_assert((n_zonesorting_out_tmp1 % 8) == 0, "n_zonesorting_out_tmp1 must be divisible by 8");
  static_assert((n_zonesorting_out_tmp2 % 8) == 0, "n_zonesorting_out_tmp2 must be divisible by 8");
  static_assert((n_zonesorting_out_tmp3 % 8) == 0, "n_zonesorting_out_tmp3 must be divisible by 8");
  static_assert((n_zonesorting_out_tmp4 % 8) == 0, "n_zonesorting_out_tmp4 must be divisible by 8");
  static_assert((n_zonesorting_out_tmp5 % 8) == 0, "n_zonesorting_out_tmp5 must be divisible by 8");

  //FIXME: ignore the pattnum
  //FIXME: keep the column index
  //FIXME: put each stage into a function

  for (int i = 0; i < num_img_cols; i += 8) {

#pragma HLS UNROLL

    zonesorting_out_t in0 = (zonesorting_in[i+0] | zonesorting_in[i+1]);
    zonesorting_out_t in1 = (zonesorting_in[i+2] | zonesorting_in[i+3]);
    zonesorting_out_t in2 = (zonesorting_in[i+4] | zonesorting_in[i+5]);
    zonesorting_out_t in3 = (zonesorting_in[i+6] | zonesorting_in[i+7]);

    sort_four(
        in0,
        in1,
        in2,
        in3,
        zonesorting_out_tmp0[(i/2)+0],
        zonesorting_out_tmp0[(i/2)+1],
        zonesorting_out_tmp0[(i/2)+2],
        zonesorting_out_tmp0[(i/2)+3]
    );
  }

  // Merge each pair of blocks
  // Start with the first 128 cols, leaving out the last 16 cols
  // Stage 0  : 128 -> 64
  // Stage 1  : 64 -> 32
  // Stage 2  : 32 -> 16
  // Stage 2.5: 16 -> 32 (put back the 16 cols that were left out)
  // Stage 3  : 32 -> 16
  // Stage 4  : 16 -> 8
  // Stage 5  : 8 -> 4

  for (int i = 0; i < (n_zonesorting_out_tmp0 - 16); i += 8) {  // merge stage 0

#pragma HLS UNROLL

    merge_eight(
        zonesorting_out_tmp0[i+0],
        zonesorting_out_tmp0[i+1],
        zonesorting_out_tmp0[i+2],
        zonesorting_out_tmp0[i+3],
        zonesorting_out_tmp0[i+4],
        zonesorting_out_tmp0[i+5],
        zonesorting_out_tmp0[i+6],
        zonesorting_out_tmp0[i+7],
        zonesorting_out_tmp1[(i/2)+0],
        zonesorting_out_tmp1[(i/2)+1],
        zonesorting_out_tmp1[(i/2)+2],
        zonesorting_out_tmp1[(i/2)+3]
    );
  }

  for (int i = 0; i < n_zonesorting_out_tmp1; i += 8) {  // merge stage 1

#pragma HLS UNROLL

    merge_eight(
        zonesorting_out_tmp1[i+0],
        zonesorting_out_tmp1[i+1],
        zonesorting_out_tmp1[i+2],
        zonesorting_out_tmp1[i+3],
        zonesorting_out_tmp1[i+4],
        zonesorting_out_tmp1[i+5],
        zonesorting_out_tmp1[i+6],
        zonesorting_out_tmp1[i+7],
        zonesorting_out_tmp2[(i/2)+0],
        zonesorting_out_tmp2[(i/2)+1],
        zonesorting_out_tmp2[(i/2)+2],
        zonesorting_out_tmp2[(i/2)+3]
    );
  }

  for (int i = 0; i < n_zonesorting_out_tmp2; i += 8) {  // merge stage 2

#pragma HLS UNROLL

    merge_eight(
        zonesorting_out_tmp2[i+0],
        zonesorting_out_tmp2[i+1],
        zonesorting_out_tmp2[i+2],
        zonesorting_out_tmp2[i+3],
        zonesorting_out_tmp2[i+4],
        zonesorting_out_tmp2[i+5],
        zonesorting_out_tmp2[i+6],
        zonesorting_out_tmp2[i+7],
        zonesorting_out_tmp3[(i/2)+0],
        zonesorting_out_tmp3[(i/2)+1],
        zonesorting_out_tmp3[(i/2)+2],
        zonesorting_out_tmp3[(i/2)+3]
    );
  }

  for (int i = (n_zonesorting_out_tmp0 - 16); i < n_zonesorting_out_tmp0; i++) {  // merge stage 2.5

#pragma HLS UNROLL

    int j = i - (n_zonesorting_out_tmp0 - 16) + 16;
    zonesorting_out_tmp3[j] = zonesorting_out_tmp0[i];
  }

  for (int i = 0; i < n_zonesorting_out_tmp3; i += 8) {  // merge stage 3

#pragma HLS UNROLL

    merge_eight(
        zonesorting_out_tmp3[i+0],
        zonesorting_out_tmp3[i+1],
        zonesorting_out_tmp3[i+2],
        zonesorting_out_tmp3[i+3],
        zonesorting_out_tmp3[i+4],
        zonesorting_out_tmp3[i+5],
        zonesorting_out_tmp3[i+6],
        zonesorting_out_tmp3[i+7],
        zonesorting_out_tmp4[(i/2)+0],
        zonesorting_out_tmp4[(i/2)+1],
        zonesorting_out_tmp4[(i/2)+2],
        zonesorting_out_tmp4[(i/2)+3]
    );
  }

  for (int i = 0; i < n_zonesorting_out_tmp4; i += 8) {  // merge stage 4

#pragma HLS UNROLL

    merge_eight(
        zonesorting_out_tmp4[i+0],
        zonesorting_out_tmp4[i+1],
        zonesorting_out_tmp4[i+2],
        zonesorting_out_tmp4[i+3],
        zonesorting_out_tmp4[i+4],
        zonesorting_out_tmp4[i+5],
        zonesorting_out_tmp4[i+6],
        zonesorting_out_tmp4[i+7],
        zonesorting_out_tmp5[(i/2)+0],
        zonesorting_out_tmp5[(i/2)+1],
        zonesorting_out_tmp5[(i/2)+2],
        zonesorting_out_tmp5[(i/2)+3]
    );
  }

  for (int i = 0; i < n_zonesorting_out_tmp5; i += 8) {  // merge stage 5

#pragma HLS UNROLL

    merge_eight(
        zonesorting_out_tmp5[i+0],
        zonesorting_out_tmp5[i+1],
        zonesorting_out_tmp5[i+2],
        zonesorting_out_tmp5[i+3],
        zonesorting_out_tmp5[i+4],
        zonesorting_out_tmp5[i+5],
        zonesorting_out_tmp5[i+6],
        zonesorting_out_tmp5[i+7],
        zonesorting_out[(i/2)+0],
        zonesorting_out[(i/2)+1],
        zonesorting_out[(i/2)+2],
        zonesorting_out[(i/2)+3]
    );
  }

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

  zonesorting_op<ZONE>(zonesorting_in, zonesorting_out);
}

}  // namespace emtf

#endif  // __EMTF_HLSLIB_ZONESORTING_H__ not defined
