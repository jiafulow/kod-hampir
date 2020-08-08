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

  //FIXME
  a_loop : for (unsigned i = 0; i < N_TOP_FN_OUT; i++) {
    outputs[i] = inputs[i];
  }

  // Run sector processors
  run_sector_processor<0>(inputs, outputs);
}

// _________________________________________________________________________________________________
template <int I>
void run_sector_processor(
    const top_fn_in_t inputs[N_TOP_FN_IN],
    top_fn_out_t outputs[N_TOP_FN_OUT]
) {
  static const int sector = I;
  static_assert(sector < emtf::num_sectors);

  //FIXME
  emtf::pooling_module<top_fn_in_t, top_fn_out_t, pooling_config_z0_p3>(inputs, outputs);
}
