#ifndef __EMTF_HLSLIB_HELPER_H__
#define __EMTF_HLSLIB_HELPER_H__

#include <cassert>
#include <cstdint>
#include <cstdlib>

#ifndef __SYNTHESIS__
#define emtf_assert(expr) (assert(expr))
#else
#define emtf_assert(expr) ((void)(expr))
#endif

#if !defined(__SYNTHESIS__) && !defined(NDEBUG)
#define PRINT_TOP_FN_ARRAYS \
  for (unsigned iseg = 0; iseg < N_MODEL_INPUT; iseg++) { \
    if (valid[iseg] == 1) { \
      std::cout << (iseg / emtf::num_segments) << " " \
                << (iseg % emtf::num_segments) << " " \
                << emtf_phi[iseg] << " " \
                << emtf_bend[iseg] << " " \
                << emtf_theta1[iseg] << " " \
                << emtf_theta2[iseg] << " " \
                << emtf_qual[iseg] << " " \
                << emtf_time[iseg] << " " \
                << zones[iseg] << " " \
                << timezones[iseg] << " " \
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
