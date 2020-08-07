#ifndef __MYPROJECT_H__
#define __MYPROJECT_H__

// Xilinx HLS
#include "ap_int.h"
#include "ap_fixed.h"
#include "hls_stream.h"

// Project definitions
#include "defines.h"

// Typedefs
typedef ap_uint<W_TOP_FN_IN> top_fn_in_t;
typedef ap_uint<W_TOP_FN_OUT> top_fn_out_t;
typedef ap_int<W_MODEL_DEFAULT> model_default_t;

// Top-level function prototype
void myproject(
    const top_fn_in_t inputs[N_TOP_FN_IN],
    top_fn_out_t outputs[N_TOP_FN_OUT]
);

#endif  // __MYPROJECT_H__ not defined
