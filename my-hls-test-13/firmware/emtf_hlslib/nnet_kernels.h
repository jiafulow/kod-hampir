#ifndef __EMTF_HLSLIB_NNET_KERNELS_H__
#define __EMTF_HLSLIB_NNET_KERNELS_H__

namespace emtf {

namespace details {

// Piecewise-linear tanh-like activation function
// This version is designed for ap_fixed<12,1> output
template <int W, int I, int W_OUT=12, int I_OUT=1>
ap_fixed<W_OUT,I_OUT> hard_tanh(const ap_fixed<W,I>& in0) {

#pragma HLS PIPELINE II=nnet_config::target_ii

//#pragma HLS INTERFACE ap_ctrl_none port=return

//#pragma HLS INLINE

  constexpr int F = W - I;
  constexpr int F_OUT = W_OUT - I_OUT;

  // Use unsigned value
  const ap_uint<1> sign0 = in0[W-1];
  const ap_ufixed<W,I> inabs = (sign0 == 0) ? ap_ufixed<W,I>(in0) : ap_ufixed<W,I>(-in0);

  // Threshold terms
  const ap_ufixed<1,0> b0 = 0.5;
  const ap_ufixed<1,1> b1 = 1.0;
  const ap_ufixed<2,1> b2 = 1.5;
  const ap_ufixed<2,2> b3 = 2.0;
  const ap_ufixed<3,2> b4 = 2.5;

  // Subtract-and-divide terms
  // The number of bits needs to be extended before right shift
  const ap_ufixed<W,I-1> c0 = (inabs >= b0) ? ap_ufixed<W,I-1>(ap_ufixed<W+1,I>(inabs - b0) >> 1) : ap_ufixed<W,I-1>(0);
  const ap_ufixed<W,I-2> c1 = (inabs >= b1) ? ap_ufixed<W,I-2>(ap_ufixed<W+2,I>(inabs - b1) >> 2) : ap_ufixed<W,I-2>(0);
  const ap_ufixed<W,I-3> c2 = (inabs >= b2) ? ap_ufixed<W,I-3>(ap_ufixed<W+3,I>(inabs - b2) >> 3) : ap_ufixed<W,I-3>(0);
  const ap_ufixed<W,I-4> c3 = (inabs >= b3) ? ap_ufixed<W,I-4>(ap_ufixed<W+4,I>(inabs - b3) >> 4) : ap_ufixed<W,I-4>(0);
  const ap_ufixed<W,I-5> c4 = (inabs >= b4) ? ap_ufixed<W,I-5>(ap_ufixed<W+5,I>(inabs - b4) >> 5) : ap_ufixed<W,I-5>(0);

  // Compute
  ap_fixed<W+6,I+1> out_tmp = inabs;  // signed
  out_tmp -= c0;
  out_tmp -= c1;
  out_tmp -= c2;
  out_tmp -= c3;
  out_tmp -= c4;
  emtf_assert(out_tmp >= 0);
  emtf_assert(out_tmp < (1<<(I-1)));

  // Round
  emtf_assert((F+5) >= (F_OUT+1));
  ap_ufixed<1,-F_OUT> half_val = 0;
  half_val[0] = 1;  // 0.5 * LSB
  out_tmp += half_val;

  // Saturate
  ap_fixed<W_OUT,I_OUT,AP_TRN,AP_SAT> out_tmp_sat = out_tmp;

  // Remember the sign
  ap_fixed<W_OUT,I_OUT> out = (sign0 == 0) ? ap_fixed<W_OUT,I_OUT>(out_tmp_sat) : ap_fixed<W_OUT,I_OUT>(-out_tmp_sat);
  emtf_assert(in0 == 0 or (in0 != 0 && out != 0));
  return out;
}

// Returns activation(X)
template <unsigned int N, typename T_IN, typename T_OUT>
void vector_activate(const T_IN x[N], T_OUT out[N]) {

#pragma HLS PIPELINE II=nnet_config::target_ii

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE

  emtf_assert((is_same<T_OUT, ap_fixed<12,1> >::value));  // must match hard_tanh W_OUT, I_OUT

  for (unsigned i = 0; i < N; i++) {

#pragma HLS UNROLL

    const T_IN x_i = x[i];
    out[i] = hard_tanh(x_i);
  }
}

// Returns normalization(X), which is the same as doing X * Y
template <unsigned int N, typename T_IN0, typename T_IN1, typename T_OUT>
void vector_normalize(const T_IN0 x[N], const T_IN1 y[N], T_OUT out[N]) {

#pragma HLS PIPELINE II=nnet_config::target_ii

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE

  for (unsigned i = 0; i < N; i++) {

#pragma HLS UNROLL

    const T_IN0 x_i = x[i];
    const T_IN1 y_i = y[i];
    out[i] = x_i * y_i;
  }
}

// Returns dot(X, Y) + Z
// X has rows = N, Y has rows = N, Z is a scalar
// It follows the convention as used in a NN, not the convention in basic linear algebra.
template <unsigned int N, typename T_IN0, typename T_IN1, typename T_IN2, typename T_OUT>
void vector_vector_mult_biasadd(const T_IN0 x[N], const T_IN1 y[N], const T_IN2& z, T_OUT& out) {

#pragma HLS PIPELINE II=nnet_config::target_ii

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE

  constexpr int W_MACC = 18;  //FIXME
  constexpr int I_MACC = 8;
  typedef ap_fixed<W_MACC, I_MACC> macc_t;

  macc_t accum = z;

  for (unsigned i = 0; i < N; i++) {

#pragma HLS UNROLL

    const T_IN0 x_i = x[i];
    const T_IN1 y_i = y[i];
    accum += x_i * y_i;
  }

  out = accum;
}

// Returns matmul(X, Y) + Z
// X has dim (rows, cols) = (M, N), Y has rows = M, Z has cols = N
// It follows the convention as used in a NN, not the convention in basic linear algebra.
template <unsigned int M, unsigned int N, typename T_IN0, typename T_IN1, typename T_IN2, typename T_OUT>
void matrix_vector_mult_biasadd(const T_IN0 x[M * N], const T_IN1 y[M], const T_IN2 z[N], T_OUT out[N]) {

#pragma HLS PIPELINE II=nnet_config::target_ii

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE

  constexpr int W_MACC = 18;  //FIXME
  constexpr int I_MACC = 8;
  typedef ap_fixed<W_MACC, I_MACC> macc_t;

  macc_t mult[M * N];

#pragma HLS ARRAY_PARTITION variable=mult complete

  for (unsigned i = 0; i < M; i++) {

#pragma HLS UNROLL

    const T_IN1 y_i = y[i];

    for (unsigned j = 0; j < N; j++) {

#pragma HLS UNROLL

      const T_IN0 x_ij = x[(i * N) + j];
      mult[(i * N) + j] = x_ij * y_i;  // pretend y_ij = y_i for all j
    }
  }

  for (unsigned j = 0; j < N; j++) {

#pragma HLS UNROLL

    macc_t accum = z[j];

    for (unsigned i = 0; i < M; i++) {

#pragma HLS UNROLL

      accum += mult[(i * N) + j];
    }

    out[j] = accum;
  }
}

}  // namespace details

}  // namespace emtf

#endif  // __EMTF_HLSLIB_NNET_KERNELS_H__ not defined
