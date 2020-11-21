#ifndef __MYPROJECT_H__
#define __MYPROJECT_H__

// Xilinx HLS
#include "ap_int.h"
//#include "ap_fixed.h"
//#include "hls_stream.h"

// EMTF HLS
#include "emtf_hlslib/types.h"

// Top-level function prototype
void myproject(
    const emtf::model_in_t in0[N_MODEL_IN],
    emtf::model_out_t out[N_MODEL_OUT]
);

#endif  // __MYPROJECT_H__ not defined
