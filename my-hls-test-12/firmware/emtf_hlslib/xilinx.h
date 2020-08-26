#ifndef __EMTF_HLSLIB_XILINX_H__
#define __EMTF_HLSLIB_XILINX_H__

// -----------------------------------------------------------------------------
// This file contains source code that is copyrighted by Xilinx.
// The Xilinx source code is used here for research purposes only.
//
// The following functions come from:
// - Power           : $XILINX_VIVADO/include/utils/x_hls_utils.h
// - BitWidth        : $XILINX_VIVADO/include/utils/x_hls_utils.h
// - UnsignedBitWidth: $XILINX_VIVADO/include/utils/x_hls_utils.h
//
// This file also includes other functions that are derived based on them.
//
// -----------------------------------------------------------------------------


/*****************************************************************************
 *
 *     Author: Xilinx, Inc.
 *
 *     This text contains proprietary, confidential information of
 *     Xilinx, Inc. , is distributed by under license from Xilinx,
 *     Inc., and may be used, copied and/or disclosed only pursuant to
 *     the terms of a valid license agreement with Xilinx, Inc.
 *
 *     XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS"
 *     AS A COURTESY TO YOU, SOLELY FOR USE IN DEVELOPING PROGRAMS AND
 *     SOLUTIONS FOR XILINX DEVICES.  BY PROVIDING THIS DESIGN, CODE,
 *     OR INFORMATION AS ONE POSSIBLE IMPLEMENTATION OF THIS FEATURE,
 *     APPLICATION OR STANDARD, XILINX IS MAKING NO REPRESENTATION
 *     THAT THIS IMPLEMENTATION IS FREE FROM ANY CLAIMS OF INFRINGEMENT,
 *     AND YOU ARE RESPONSIBLE FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE
 *     FOR YOUR IMPLEMENTATION.  XILINX EXPRESSLY DISCLAIMS ANY
 *     WARRANTY WHATSOEVER WITH RESPECT TO THE ADEQUACY OF THE
 *     IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO ANY WARRANTIES OR
 *     REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE FROM CLAIMS OF
 *     INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *     FOR A PARTICULAR PURPOSE.
 *
 *     Xilinx products are not intended for use in life support appliances,
 *     devices, or systems. Use in such applications is expressly prohibited.
 *
 *     (c) Copyright 2012 Xilinx Inc.
 *     All rights reserved.
 *
 *****************************************************************************/


/*
*------------------------------------------------------------------------------
* Raise a value to a certain power (B^N).
*
* This class is necessary in template arguments due to its static const nature
* and the fact that it performs the power operation as part of the recursive
* class declaration. A standard recursive power function would not return
* a static const value.
*
*------------------------------------------------------------------------------
*/
template <unsigned int _Base, unsigned int _Num>
struct Power
{
  static const unsigned int value = _Base * Power<_Base, _Num - 1>::value;
};

template <unsigned int _Base>
struct Power<_Base, 0>
{
  static const unsigned int value = 1;
};

/*
*------------------------------------------------------------------------------
* Raise a value to power of 2 (2^N).
*------------------------------------------------------------------------------
*/
template <unsigned int _Num>
struct Pow2 : public Power<2, _Num> {};

/*
*------------------------------------------------------------------------------
* Calculate the minimum # of bits to store the given signed integer value.
*
* BitWidth<0>::value == 1
* BitWidth<1>::value == 2
* BitWidth<2>::value == 3
* BitWidth<3>::value == 3
* BitWidth<4>::value == 4
* BitWidth<5>::value == 4
*------------------------------------------------------------------------------
*/
template <unsigned int _Num>
struct BitWidth
{
  static const unsigned int value = 1 + BitWidth<_Num / 2>::value;
};

template <>
struct BitWidth<0>
{
  static const unsigned int value = 1;
};

/*
*------------------------------------------------------------------------------
* Calculate the minimum # of bits to store the given unsigned integer value.
*
* UnsignedBitWidth<0>::value == 0
* UnsignedBitWidth<1>::value == 1
* UnsignedBitWidth<2>::value == 2
* UnsignedBitWidth<3>::value == 2
* UnsignedBitWidth<4>::value == 3
* UnsignedBitWidth<5>::value == 3
*------------------------------------------------------------------------------
*/
template <unsigned int _Num>
struct UnsignedBitWidth
{
  static const unsigned int value = 1 + UnsignedBitWidth<_Num / 2>::value;
};

template <>
struct UnsignedBitWidth<0>
{
  static const unsigned int value = 0;
};

/*
*------------------------------------------------------------------------------
* Calculate floor(log2(N)) - in the context of FPGA, it is equal to
* UnsignedBitWidth(N) - 1.
*
* FloorLog2<0>::value == 0
* FloorLog2<1>::value == 0
* FloorLog2<2>::value == 1
* FloorLog2<3>::value == 1
* FloorLog2<4>::value == 2
* FloorLog2<5>::value == 2
*------------------------------------------------------------------------------
*/
template <unsigned int _Num>
struct FloorLog2
{
  static const unsigned int value = (_Num > 1) ? (1 + FloorLog2<_Num / 2>::value) : 0;
};

template <>
struct FloorLog2<0>
{
  static const unsigned int value = 0;
};

/*
*------------------------------------------------------------------------------
* Calculate ceil(log2(N)) - in the context of FPGA, it is equal to the
* minimum # of bits needed to store N numbers.
*
* CeilLog2<0>::value == 0
* CeilLog2<1>::value == 1  // mathematically it should be 0
* CeilLog2<2>::value == 1
* CeilLog2<3>::value == 2
* CeilLog2<4>::value == 2
* CeilLog2<5>::value == 3
*------------------------------------------------------------------------------
*/
template <unsigned int _Num>
struct CeilLog2
{
  static const unsigned int value = (_Num > 0) ? (1 + FloorLog2<_Num - 1>::value) : 0;
};

#endif  // __EMTF_HLSLIB_XILINX_H__ not defined
