/*
 * Copyright 2020 Xilinx, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "cpp_ap_fixed.h"

#define emtf_assert(expr) assert(expr)

//dout_t cpp_ap_fixed(din1_t d_in1, din2_t d_in2) {
//  static dint_t sum;
//  sum = d_in1;
//  return sum * d_in2;
//}

// Piecewise-linear tanh-like activation function
// This version is designed for ap_fixed<12,1> output
template <int W, int I, int W_OUT=12, int I_OUT=1>
ap_fixed<W_OUT,I_OUT> hard_tanh(const ap_fixed<W,I>& in0) {
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
  const ap_ufixed<W+1,I> c0 = (inabs >= b0) ? (ap_ufixed<W+1,I>(inabs - b0) >> 1) : ap_ufixed<W+1,I>(0);
  const ap_ufixed<W+2,I> c1 = (inabs >= b1) ? (ap_ufixed<W+2,I>(inabs - b1) >> 2) : ap_ufixed<W+2,I>(0);
  const ap_ufixed<W+3,I> c2 = (inabs >= b2) ? (ap_ufixed<W+3,I>(inabs - b2) >> 3) : ap_ufixed<W+3,I>(0);
  const ap_ufixed<W+4,I> c3 = (inabs >= b3) ? (ap_ufixed<W+4,I>(inabs - b3) >> 4) : ap_ufixed<W+4,I>(0);
  const ap_ufixed<W+5,I> c4 = (inabs >= b4) ? (ap_ufixed<W+5,I>(inabs - b4) >> 5) : ap_ufixed<W+5,I>(0);

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
  // 'out_tmp_1' has the desired output fraction bits (F_OUT)
  emtf_assert((W+5-I) > F_OUT);
  const ap_ufixed<1,-F_OUT> half_val = (0.5 * (1.0 / (1<<F_OUT)));  // 0.5 * LSB
  ap_fixed<I+1+F_OUT,I+1> out_tmp_1 = (out_tmp + half_val);

  // Clip
  // 'out' has the desired output integer bits (I_OUT)
  emtf_assert(I_OUT == 1);
  const ap_ufixed<W_OUT-1,I_OUT-1> limit = (1.0 - (1.0 / (1<<F_OUT)));  // 1.0 - LSB
  const ap_uint<1> larger0 = out_tmp_1.range(out_tmp_1.width - 1, out_tmp_1.width - out_tmp_1.iwidth);
  ap_fixed<W_OUT,I_OUT> out = (larger0 == 1) ? ap_fixed<W_OUT,I_OUT>(limit) : ap_fixed<W_OUT,I_OUT>(out_tmp_1);

  // Remember the sign
  out = (sign0 == 0) ? out : ap_fixed<W_OUT,I_OUT>(-out);
  emtf_assert(in0 == 0 or (in0 != 0 && out != 0));
  return out;
}

dout_t cpp_ap_fixed(din0_t in0) {

#pragma HLS PIPELINE

  return hard_tanh(in0);
}
