#ifndef __EMTF_HLSLIB_HELPER_H__
#define __EMTF_HLSLIB_HELPER_H__

#if !defined(__SYNTHESIS__) && !defined(NDEBUG)
#include <iostream>
#endif

#if !defined(__SYNTHESIS__) && !defined(NDEBUG)
#define PRINT_TOP_FN_ARRAYS_IN0 \
    std::cout << "Printing 'in0' arrays:" << std::endl; \
    for (unsigned iseg = 0; iseg < model_config::n_in; iseg++) { \
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
    for (unsigned itrk = 0; itrk < zonemerging_config::n_out; itrk++) { \
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
    for (unsigned i = 0; i < zoning_config::n_out; i++) { \
      for (unsigned j = 0; j < zoning_out_t::width; j++) { \
        if (zoning_0_out[i].test(j)) \
          std::cout << i << ", "; \
      } \
    } \
    std::cout << "], col: ["; \
    for (unsigned i = 0; i < zoning_config::n_out; i++) { \
      for (unsigned j = 0; j < zoning_out_t::width; j++) { \
        if (zoning_0_out[i].test(j)) \
          std::cout << j << ", "; \
      } \
    } \
    std::cout << "]" << std::endl; \
    std::cout << "Printing 'pooling_0_out' non-zero elements:" << std::endl; \
    std::cout << "col: ["; \
    for (unsigned i = 0; i < pooling_config::n_out; i++) { \
      if (pooling_0_out[i]) \
        std::cout << i << ", "; \
    } \
    std::cout << "], value: ["; \
    for (unsigned i = 0; i < pooling_config::n_out; i++) { \
      if (pooling_0_out[i]) \
        std::cout << pooling_0_out[i].range(pooling_activation_t::width - 1, 0) << ", "; \
    } \
    std::cout << "]" << std::endl; \
    std::cout << "Printing 'suppression_0_out' non-zero elements:" << std::endl; \
    std::cout << "col: ["; \
    for (unsigned i = 0; i < suppression_config::n_out; i++) { \
      if (suppression_0_out[i]) \
        std::cout << i << ", "; \
    } \
    std::cout << "], value: ["; \
    for (unsigned i = 0; i < suppression_config::n_out; i++) { \
      if (suppression_0_out[i]) \
        std::cout << suppression_0_out[i].range(pooling_activation_t::width - 1, 0) << ", "; \
    } \
    std::cout << "]" << std::endl; \
    std::cout << "Printing 'zonesorting_0_out', 'zonesorting_1_out', 'zonesorting_2_out' all elements:" << std::endl; \
    std::cout << "value: ["; \
    for (unsigned i = 0; i < zonesorting_config::n_out; i++) { \
      std::cout << zonesorting_0_out[i].range(pooling_activation_t::width - 1, 0) << ", "; \
    } \
    std::cout << "], value: ["; \
    for (unsigned i = 0; i < zonesorting_config::n_out; i++) { \
      std::cout << zonesorting_1_out[i].range(pooling_activation_t::width - 1, 0) << ", "; \
    } \
    std::cout << "], value: ["; \
    for (unsigned i = 0; i < zonesorting_config::n_out; i++) { \
      std::cout << zonesorting_2_out[i].range(pooling_activation_t::width - 1, 0) << ", "; \
    } \
    std::cout << "]" << std::endl; \
    std::cout << "Printing 'zonemerging_0_out' all elements:" << std::endl; \
    std::cout << "value: ["; \
    for (unsigned i = 0; i < zonemerging_config::n_out; i++) { \
      std::cout << zonemerging_0_out[i].range(pooling_activation_t::width - 1, 0) << ", "; \
    } \
    std::cout << "]" << std::endl;
#else
#define PRINT_TOP_FN_ARRAYS_OTHER
#endif

#endif  // __EMTF_HLSLIB_HELPER_H__ not defined
