// Top function
#include "firmware/myproject.h"

// Test bench
#include "software/testbench.h"

using namespace testbench;

void sanity_check() {
  static_assert(HitsType::len == emtf::num_emtf_variables + 2, "Inconsistent HitsType::len");
  static_assert(TracksType::len == emtf::num_emtf_features, "Inconsistent TracksType::len");
  static_assert(FPGAEvent::len == emtf::model_config::n_in, "Inconsistent FPGAEvent::len");
  static_assert(FPGAResult::len == emtf::model_config::n_out, "Inconsistent FPGAResult::len");
}

// Main driver
int main(int argc, char **argv) {
  // Perform sanity check
  sanity_check();

  // Create Event & Result from 'tb_data' text files
  Event evt;
  read_tb_data("tb_data/event_0.txt", evt);
  Result res;
  read_tb_data("tb_data/result_0.txt", res);

  // Create FPGAEvent & FPGAResult
  const FPGAEvent fw_evt(evt);
  const FPGAResult fw_res(res);

  // Prepare input and output
  emtf::model_in_t in0[emtf::model_config::n_in];
  emtf::model_out_t out[emtf::model_config::n_out];
  copy_array(fw_evt.data, in0);
  init_array_as_zeros(out);

  // Call the top function !!
  myproject(in0, out);

  // Compare with the expectation
  int err = count_mismatches(std::begin(out), std::end(out), std::begin(fw_res.data));

  // Print error info
  if (err) {
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

  // Return 0 only if the results are correct
  return err;
}
