// Top function
#include "firmware/myproject.h"

// Main driver
int main(int argc, char **argv)
{
  emtf::model_in_t in0[N_MODEL_IN];
  emtf::model_out_t out[N_MODEL_OUT];
  myproject(in0, out);
  return 0;
}
