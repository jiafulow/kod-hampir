#ifndef __EMTF_HLSLIB_HELPER_FROM_XFOPENCV_H__
#define __EMTF_HLSLIB_HELPER_FROM_XFOPENCV_H__

// -----------------------------------------------------------------------------
// NOTE: This source code is not an identical copy of the source code from
//       Xilinx xfOpenCV Library (now Vitis Vision Library), but part of it
//       is based on the xfOpenCV or Vitis Vision Library. Therefore, the
//       Xilinx copyright notice is reproduced below. The use of xfOpenCV
//       or Vitis Vision Library source code is intended for research purposes
//       only.
//
//       xfOpenCV: https://github.com/Xilinx/xfopencv
//       Vitis Vision Library: https://github.com/Xilinx/Vitis_Libraries/tree/master/vision
//
// -----------------------------------------------------------------------------


/*
 * Copyright 2019 Xilinx, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


namespace emtf {

  // Get max for template metaprogramming
  template <int A, int B>
  struct MAX
  {
    static constexpr int value = (A > B) ? A : B;
  };

  // Get min for template metaprogramming
  template <int A, int B>
  struct MIN
  {
    static constexpr int value = (A < B) ? A : B;
  };

  // Get abs for template metaprogramming
  template <int A>
  struct ABS
  {
    static constexpr int value = (A < 0) ? -A : A;
  };

  // Template metaprogramming implementation of ceil log2 and floor log2
  template <int N>
  struct LOG2 {
    // floor value
    static constexpr int fvalue = 1 + (LOG2<N / 2>::fvalue);
    // ceiling value
    static constexpr int cvalue = (N > (1 << fvalue)) ? (fvalue + 1) : fvalue;
  };

  template <>
  struct LOG2<1> {
    static constexpr int fvalue = 0;
    static constexpr int cvalue = 1;  // set to 1, although mathematically it should be 0
  };

  template <>
  struct LOG2<0> {};

  // Template metaprogramming implementation of pow2
  template <int N>
  struct POW2 {
    static constexpr int value = 2 * (POW2<N - 1>::value);
  };

  template <>
  struct POW2<0> {
    static constexpr int value = 1;
  };

}  // namespace emtf

#endif  // __EMTF_HLSLIB_HELPER_FROM_XFOPENCV_H__ not defined
