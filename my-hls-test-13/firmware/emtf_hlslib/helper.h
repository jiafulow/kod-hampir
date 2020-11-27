#ifndef __EMTF_HLSLIB_HELPER_H__
#define __EMTF_HLSLIB_HELPER_H__

#if !defined(__SYNTHESIS__) && !defined(NDEBUG)
#include <iostream>
#endif

#if !defined(__SYNTHESIS__) && !defined(NDEBUG)
#define PRINT_TOP_FN_ARRAYS_IN0 \
    std::cout << "Printing 'in0' arrays:" << std::endl; \
    for (unsigned iseg = 0; iseg < N_MODEL_IN; iseg++) { \
      if (seg_valid[iseg] == 1) { \
        std::cout << (iseg / num_emtf_segments) << " " \
                  << (iseg % num_emtf_segments) << " " \
                  << emtf_phi[iseg] << " " \
                  << emtf_bend[iseg] << " " \
                  << emtf_theta1[iseg] << " " \
                  << emtf_theta2[iseg] << " " \
                  << emtf_qual1[iseg] << " " \
                  << emtf_qual2[iseg] << " " \
                  << emtf_time[iseg] << " " \
                  << seg_zones[iseg] << " " \
                  << seg_tzones[iseg] << " " \
                  << seg_fr[iseg] << " " \
                  << seg_dl[iseg] << " " \
                  << seg_bx[iseg] << " " \
                  << seg_valid[iseg] << " " \
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
                << trk_qual[itrk] << " " \
                << trk_patt[itrk] << " " \
                << trk_col[itrk] << " " \
                << trk_zone[itrk] << " " \
                << std::endl; \
    }
#else
#define PRINT_TOP_FN_ARRAYS_IN1
#endif

#if !defined(__SYNTHESIS__) && !defined(NDEBUG)
#define PRINT_TOP_FN_ARRAYS_OTHER \
    std::cout << "Printing 'zoning_0_out' non-zero elements:" << std::endl; \
    std::cout << "row: ["; \
    for (unsigned i = 0; i < N_ZONING_OUT; i++) { \
      for (unsigned j = 0; j < zoning_out_t::width; j++) { \
        if (zoning_0_out[i].test(j)) \
          std::cout << i << ", "; \
      } \
    } \
    std::cout << "], col: ["; \
    for (unsigned i = 0; i < N_ZONING_OUT; i++) { \
      for (unsigned j = 0; j < zoning_out_t::width; j++) { \
        if (zoning_0_out[i].test(j)) \
          std::cout << j << ", "; \
      } \
    } \
    std::cout << "]" << std::endl; \
    std::cout << "Printing 'suppression_0_out' non-zero elements:" << std::endl; \
    std::cout << "col: ["; \
    for (unsigned i = 0; i < N_SUPPRESSION_OUT; i++) { \
      if (suppression_0_out[i]) \
        std::cout << i << ", "; \
    } \
    std::cout << "], value: ["; \
    for (unsigned i = 0; i < N_SUPPRESSION_OUT; i++) { \
      if (suppression_0_out[i]) \
        std::cout << suppression_0_out[i].range(pooling_activation_t::width - 1, 0) << ", "; \
    } \
    std::cout << "]" << std::endl;
#else
#define PRINT_TOP_FN_ARRAYS_OTHER
#endif

#endif  // __EMTF_HLSLIB_HELPER_H__ not defined
