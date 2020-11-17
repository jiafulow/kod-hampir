// Top function
#include "firmware/myproject.h"

// Test bench (C++)
#include "software/testbench.h"

void sanity_check() {
  static_assert(emtf::model_in_t::width == 60, "Inconsistent model_in_t::width");
  static_assert(emtf::model_out_t::width == 13, "Inconsistent model_out_t::width");
  static_assert(HitsType::N == emtf::num_variables + 2, "Inconsistent HitsType::N");
  static_assert(TracksType::N == emtf::num_features, "Inconsistent TracksType::N");
  static_assert(FPGAEvent::LENGTH == N_MODEL_IN, "Inconsistent FPGAEvent::LENGTH");
  static_assert(FPGAResult::LENGTH == N_MODEL_OUT, "Inconsistent FPGAResult::LENGTH");
  static_assert(N_MODEL_IN < 1024, "Too large N_MODEL_IN");
  static_assert(N_MODEL_OUT < 1024, "Too large N_MODEL_OUT");
}

// Main driver
int main(int argc, char **argv)
{
  // Perform sanity check
  sanity_check();

  // Create Event & Result from 'tb_data' text files
  Event evt;
  read_tb_data<Event, EventType>("tb_data/event_0.txt", evt);
  Result res;
  read_tb_data<Result, ResultType>("tb_data/result_0.txt", res);

  // Create FPGAEvent & FPGAResult
  const FPGAEvent fw_evt(evt);
  const FPGAResult fw_res(res);

  // Prepare input and output
  emtf::model_in_t in0[N_MODEL_IN];
  emtf::model_out_t out[N_MODEL_OUT];
  init_array_as_zeros(in0);
  init_array_as_zeros(out);

  fw_evt.serialize_into(in0);  // put data from fw_evt into in0

  // Call the top function !!
  myproject(in0, out);

  // Check for mismatches
  int err = count_mismatches(std::begin(out), std::end(out), std::begin(fw_res.data));

  if (err) {
    // Print error info
    std::string clr_error = "\033[1;31m";  // red
    std::string clr_reset = "\033[0m";     // reset
    std::cout << clr_error << "FAILED!" << clr_reset << std::endl;
    std::cout << "Got:" << std::endl;
    print_array(out);
    std::cout << std::endl;
    std::cout << "Expected:" << std::endl;
    print_array(fw_res.data);
    std::cout << std::endl;
    std::cout << "Mismatches: " << err << std::endl;
  }
  return err;
}
