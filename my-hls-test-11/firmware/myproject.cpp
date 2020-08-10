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

  // Pattern recognition
  emtf::pooling_module<top_fn_in_t, top_fn_out_t, pooling_config_z0_p3>(inputs, outputs);
}
