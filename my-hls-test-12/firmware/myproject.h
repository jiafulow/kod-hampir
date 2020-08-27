#ifndef __MYPROJECT_H__
#define __MYPROJECT_H__

// Xilinx HLS
#include "ap_int.h"
#include "ap_fixed.h"
//#include "hls_stream.h"

// EMTF HLS
#include "emtf_hlslib/all.h"

using emtf::N_MODEL_INPUT;
using emtf::N_MODEL_OUTPUT;

// Top-level function prototype
void myproject(
    const emtf::model_input_t in0[N_MODEL_INPUT],
    emtf::model_output_t out[N_MODEL_OUTPUT]
);

#endif  // __MYPROJECT_H__ not defined
