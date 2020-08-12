#include "myproject.h"
#include "parameters.h"


// Forward declaration
template <int I>
void run_sector_processor(
    const top_fn_in_t inputs[N_TOP_FN_IN],
    top_fn_out_t outputs[N_TOP_FN_OUT]
);

// Top-level function implementation
void myproject(
    const top_fn_in_t inputs[N_TOP_FN_IN],
    top_fn_out_t outputs[N_TOP_FN_OUT]
) {
  // Run sector processors
  run_sector_processor<0>(inputs, outputs);
}

// _________________________________________________________________________________________________
template <int I>
void run_sector_processor(
    const top_fn_in_t inputs[N_TOP_FN_IN],
    top_fn_out_t outputs[N_TOP_FN_OUT]
) {
  constexpr int sector = I;
  static_assert((0 <= sector && sector < emtf::num_sectors), "sector must be an integer [0-11]");


#pragma HLS ARRAY_RESHAPE variable=inputs complete dim=0
#pragma HLS ARRAY_RESHAPE variable=outputs complete dim=0
#pragma HLS INTERFACE ap_vld port=inputs,outputs
#pragma HLS PIPELINE II=1

  // Pattern recognition (via ROI pooling)
  emtf::roi_pooling_module<top_fn_in_t, top_fn_out_t, default_pooling_config>(inputs, outputs);

}
