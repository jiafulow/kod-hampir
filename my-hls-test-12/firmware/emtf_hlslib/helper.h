#ifndef __EMTF_HLSLIB_HELPER_H__
#define __EMTF_HLSLIB_HELPER_H__

#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <iostream>

#if !defined(__SYNTHESIS__) && !defined(NDEBUG)
#define PRINT_TOP_FN_ARRAYS_IN0 \
    std::cout << "Printing 'in0' arrays:" << std::endl; \
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
#define PRINT_TOP_FN_ARRAYS_IN0
#endif

#if !defined(__SYNTHESIS__) && !defined(NDEBUG)
#define PRINT_TOP_FN_ARRAYS_IN1 \
    std::cout << "Printing 'in1' arrays:" << std::endl; \
    for (unsigned itrk = 0; itrk < N_ZONEMERGING_OUT; itrk++) { \
      std::cout << itrk << " " \
                << track_qual[itrk] << " " \
                << track_patt[itrk] << " " \
                << track_col[itrk] << " " \
                << track_zone[itrk] << " " \
                << std::endl; \
    }
#else
#define PRINT_TOP_FN_ARRAYS_IN1
#endif


namespace emtf {

}  // namespace emtf

#endif  // __EMTF_HLSLIB_HELPER_H__ not defined
