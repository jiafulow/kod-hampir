// Top function
#include "firmware/myproject.h"

// Test bench (C++)
#include "software/testbench.h"

void sanity_check() {
  static_assert(emtf::NUM_VARIABLES == emtf::num_variables, "Inconsistent emtf::NUM_VARIABLES");
  static_assert(emtf::model_input_t::width == 60, "Inconsistent model_input_t::width");
  static_assert(emtf::model_output_t::width == 13, "Inconsistent model_output_t::width");
  static_assert(HitsType::N == emtf::num_variables + 2, "Inconsistent HitsType::N");
  static_assert(FPGAEvent::LENGTH == N_MODEL_INPUT);
  static_assert(FPGAResult::LENGTH == N_MODEL_OUTPUT);
}

// Main driver
int main(int argc, char **argv)
{
  // Perform sanity check
  sanity_check();

#ifndef __SYNTHESIS__
  std::cout << "INFO: In standard C++ mode" << std::endl;
#else
  std::cout << "INFO: In synthesis mode" << std::endl;
#endif

  // Create Event
  Event evt;
  read_tb_event("tb_data/event_0.txt", evt);  // read from text file

  // Create FPGAEvent
  const FPGAEvent fw_evt(evt);  // get data from evt
  const FPGAResult fw_gold;  //FIXME - not yet implemented

  // Prepare input and output
  emtf::model_input_t in0[N_MODEL_INPUT];
  emtf::model_output_t out[N_MODEL_OUTPUT];
  init_array_as_zeros(in0);
  init_array_as_zeros(out);

  fw_evt.serialize_into(in0);  // get data from fw_evt

  // Call the top function !!
  myproject(in0, out);


  // Check for mismatches
  int err = 0;  // error code
  for (unsigned i = 0; i < N_MODEL_OUTPUT; i++) {
    if (out[i] != fw_gold.data[i])
      err++;
  }

  if (err) {
    // Print error info
    std::string clr_error = "\033[1;31m";  // red
    std::string clr_reset = "\033[0m";     // reset
    std::cout << clr_error << "FAILED!" << clr_reset << std::endl;
    std::cout << "Got:" << std::endl;
    print_array(out);
    std::cout << std::endl;
    std::cout << "Expected:" << std::endl;
    print_array(fw_gold.data);
    std::cout << std::endl;
  }
  return 0;  //FIXME - always success
}
