#ifndef __EMTF_HLSLIB_HELPER_FROM_OPENCV_H__
#define __EMTF_HLSLIB_HELPER_FROM_OPENCV_H__

// -----------------------------------------------------------------------------
// NOTE: This source code is not an identical copy of the OpenCV source code,
//       but part of it is based on from the OpenCV library. Therefore, the
//       OpenCV copyright notice is reproduced below. The use of OpenCV source
//       code is intended for research purposes only.
//
//       OpenCV: https://github.com/opencv/opencv
//
// -----------------------------------------------------------------------------


/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//
//                          License Agreement
//                For Open Source Computer Vision Library
//
// Copyright (C) 2000-2008, Intel Corporation, all rights reserved.
// Copyright (C) 2009, Willow Garage Inc., all rights reserved.
// Copyright (C) 2013, OpenCV Foundation, all rights reserved.
// Third party copyrights are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistribution's of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//   * Redistribution's in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//   * The name of the copyright holders may not be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
// This software is provided by the copyright holders and contributors "as is" and
// any express or implied warranties, including, but not limited to, the implied
// warranties of merchantability and fitness for a particular purpose are disclaimed.
// In no event shall the Intel Corporation or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
//
//M*/


namespace emtf {

  //
  // Small matrices and vectors with extremely basic functionality. Based on
  // OpenCV cv::Matx and cv::Vec.
  //
  // OpenCV: https://github.com/opencv/opencv/blob/master/modules/core/include/opencv2/core/matx.hpp
  //

  // Mat is used for a 2D matrix with constant data members. It is being used to pass
  // compile-time parameters.
  template <typename T, int ROWS, int COLS>
  class Mat {
  public:
    typedef T value_type;
    static constexpr int rows = ROWS;
    static constexpr int cols = COLS;
    static constexpr int size = rows * cols;
    T data[size];  // elements

    // Element access
    const T& operator ()(int row, int col) const;
    T& operator ()(int row, int col);

    // 1D element access
    const T& operator ()(int i) const;
    T& operator ()(int i);

    // Unsafe 1D element access
    const T& operator [](int i) const;
    T& operator [](int i);
  };

  // Vec is Mat reduced to 1D-vector, such as a row or a column of a 2D matrix.
  template <typename T, int N>
  class Vec {
  public:
    typedef T value_type;
    static constexpr int size = N;
    T data[size];  // elements

    // Element access
    const T& operator ()(int i) const;
    T& operator ()(int i);

    // Unsafe element access
    const T& operator [](int i) const;
    T& operator [](int i);
  };

  // Til is Mat promoted to 3D-tensor, such as tiles (or submatrices) of a 2D matrix.
  template <typename T, int TILES, int ROWS, int COLS>
  class Til {
  public:
    typedef T value_type;
    static constexpr int tiles = TILES;
    static constexpr int rows = ROWS;
    static constexpr int cols = COLS;
    static constexpr int size = tiles * rows * cols;
    T data[size];  // need to be initialized before use

    // Element access
    const T& operator ()(int tile, int row, int col) const;
    T& operator ()(int tile, int row, int col);

    // 1D element access
    const T& operator ()(int i) const;
    T& operator ()(int i);

    // Unsafe 1D element access
    const T& operator [](int i) const;
    T& operator [](int i);
  };

  // ___________________________________________________________________________
  // Implementation

  template <typename T, int ROWS, int COLS>
  inline const T& Mat<T, ROWS, COLS>::operator ()(int row, int col) const {
    emtf_assert(static_cast<size_t>(row) < static_cast<size_t>(rows));
    emtf_assert(static_cast<size_t>(col) < static_cast<size_t>(cols));
    return data[(row * cols) + col];
  }

  template <typename T, int ROWS, int COLS>
  inline T& Mat<T, ROWS, COLS>::operator ()(int row, int col) {
    emtf_assert(static_cast<size_t>(row) < static_cast<size_t>(rows));
    emtf_assert(static_cast<size_t>(col) < static_cast<size_t>(cols));
    return data[(row * cols) + col];
  }

  template <typename T, int ROWS, int COLS>
  inline const T& Mat<T, ROWS, COLS>::operator ()(int i) const {
    emtf_assert(static_cast<size_t>(i) < static_cast<size_t>(size));
    return data[i];
  }

  template <typename T, int ROWS, int COLS>
  inline T& Mat<T, ROWS, COLS>::operator ()(int i) {
    emtf_assert(static_cast<size_t>(i) < static_cast<size_t>(size));
    return data[i];
  }

  template <typename T, int ROWS, int COLS>
  inline const T& Mat<T, ROWS, COLS>::operator [](int i) const {
    //emtf_assert(static_cast<size_t>(i) < static_cast<size_t>(size));
    return data[i];
  }

  template <typename T, int ROWS, int COLS>
  inline T& Mat<T, ROWS, COLS>::operator [](int i) {
    //emtf_assert(static_cast<size_t>(i) < static_cast<size_t>(size));
    return data[i];
  }

  template <typename T, int N>
  inline const T& Vec<T, N>::operator ()(int i) const {
    emtf_assert(static_cast<size_t>(i) < static_cast<size_t>(size));
    return data[i];
  }

  template <typename T, int N>
  inline T& Vec<T, N>::operator ()(int i) {
    emtf_assert(static_cast<size_t>(i) < static_cast<size_t>(size));
    return data[i];
  }

  template <typename T, int N>
  inline const T& Vec<T, N>::operator [](int i) const {
    //emtf_assert(static_cast<size_t>(i) < static_cast<size_t>(size));
    return data[i];
  }

  template <typename T, int N>
  inline T& Vec<T, N>::operator [](int i) {
    //emtf_assert(static_cast<size_t>(i) < static_cast<size_t>(size));
    return data[i];
  }

  template <typename T, int TILES, int ROWS, int COLS>
  inline const T& Til<T, TILES, ROWS, COLS>::operator ()(int tile, int row, int col) const {
    emtf_assert(static_cast<size_t>(tile) < static_cast<size_t>(tiles));
    emtf_assert(static_cast<size_t>(row) < static_cast<size_t>(rows));
    emtf_assert(static_cast<size_t>(col) < static_cast<size_t>(cols));
    return data[(tile * rows * cols) + (row * cols) + col];
  }

  template <typename T, int TILES, int ROWS, int COLS>
  inline T& Til<T, TILES, ROWS, COLS>::operator ()(int tile, int row, int col) {
    emtf_assert(static_cast<size_t>(tile) < static_cast<size_t>(tiles));
    emtf_assert(static_cast<size_t>(row) < static_cast<size_t>(rows));
    emtf_assert(static_cast<size_t>(col) < static_cast<size_t>(cols));
    return data[(tile * rows * cols) + (row * cols) + col];
  }

  template <typename T, int TILES, int ROWS, int COLS>
  inline const T& Til<T, TILES, ROWS, COLS>::operator ()(int i) const {
    emtf_assert(static_cast<size_t>(i) < static_cast<size_t>(size));
    return data[i];
  }

  template <typename T, int TILES, int ROWS, int COLS>
  inline T& Til<T, TILES, ROWS, COLS>::operator ()(int i) {
    emtf_assert(static_cast<size_t>(i) < static_cast<size_t>(size));
    return data[i];
  }

  template <typename T, int TILES, int ROWS, int COLS>
  inline const T& Til<T, TILES, ROWS, COLS>::operator [](int i) const {
    //emtf_assert(static_cast<size_t>(i) < static_cast<size_t>(size));
    return data[i];
  }

  template <typename T, int TILES, int ROWS, int COLS>
  inline T& Til<T, TILES, ROWS, COLS>::operator [](int i) {
    //emtf_assert(static_cast<size_t>(i) < static_cast<size_t>(size));
    return data[i];
  }

}  // namespace emtf

#endif  // __EMTF_HLSLIB_HELPER_FROM_OPENCV_H__ not defined
