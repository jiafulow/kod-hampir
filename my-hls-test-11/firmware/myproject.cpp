#include "myproject.h"
#include "parameters.h"

void myproject(
    const top_fn_in_t inputs[N_TOP_FN_IN],
    top_fn_out_t outputs[N_TOP_FN_OUT]
) {

  a_loop : for (unsigned i=0; i<N_TOP_FN_OUT; i++) {
    outputs[i] = inputs[i];
  }

}
