#ifndef __MYPROJECT_H__
#define __MYPROJECT_H__

// Xilinx HLS
#include "ap_int.h"
//#include "ap_fixed.h"
//#include "hls_stream.h"

// EMTF HLS
#include "emtf_hlslib.h"

// Top-level function prototype
void myproject(
    const emtf::model_in_t in0[emtf::model_config::n_in],
    emtf::model_out_t out[emtf::model_config::n_out]
);

#endif  // __MYPROJECT_H__ not defined
