#ifndef __EMTF_HLSLIB_HELPER_H__
#define __EMTF_HLSLIB_HELPER_H__

#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <iostream>

#if !defined(__SYNTHESIS__) && !defined(NDEBUG)
#define PRINT_TOP_FN_ARRAYS \
    for (unsigned iseg = 0; iseg < N_MODEL_IN; iseg++) { \
      if (valid[iseg] == 1) { \
        std::cout << (iseg / emtf::num_segments) << " " \
                  << (iseg % emtf::num_segments) << " " \
                  << emtf_phi[iseg] << " " \
                  << emtf_bend[iseg] << " " \
                  << emtf_theta1[iseg] << " " \
                  << emtf_theta2[iseg] << " " \
                  << emtf_qual[iseg] << " " \
                  << emtf_time[iseg] << " " \
                  << flags_zone[iseg] << " " \
                  << flags_tzone[iseg] << " " \
                  << bx[iseg] << " " \
                  << valid[iseg] << " " \
                  << std::endl; \
      } \
    }
#else
#define PRINT_TOP_FN_ARRAYS
#endif


namespace emtf {

}  // namespace emtf

#endif  // __EMTF_HLSLIB_HELPER_H__ not defined
