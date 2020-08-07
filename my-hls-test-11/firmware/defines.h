#ifndef __DEFINES_H__
#define __DEFINES_H__

#include "ap_int.h"
#include "ap_fixed.h"

// Define data lengths
#define N_TOP_FN_IN 288
#define N_TOP_FN_OUT 288

// Define data widths
#define W_TOP_FN_IN 8
#define W_TOP_FN_OUT 8

// Define data types
typedef ap_uint<W_TOP_FN_IN> top_fn_in_t;
typedef ap_uint<W_TOP_FN_OUT> top_fn_out_t;

#endif  // __DEFINES_H__ not defined
