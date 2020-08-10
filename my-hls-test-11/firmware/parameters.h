#ifndef __PARAMETERS_H__
#define __PARAMETERS_H__

#include "emtf_hlslib/all.h"

// Pooling configs

struct pooling_config_z0_p3 : emtf::default_pooling_config {
  static const unsigned patt_constants[patt_constants_len];
  static const unsigned zone = 0;
  static const unsigned patt = 3;
};

const unsigned pooling_config_z0_p3::patt_constants[patt_constants_len] = {
  51, 55, 59, 51, 55, 59, 52, 55, 58, 54, 55, 56, 54, 55, 56, 54, 55, 56,
  54, 55, 56, 54, 55, 56
};

#endif  // __PARAMETERS_H__ not defined
