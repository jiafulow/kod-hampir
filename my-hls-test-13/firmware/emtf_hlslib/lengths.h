#ifndef __EMTF_HLSLIB_LENGTHS_H__
#define __EMTF_HLSLIB_LENGTHS_H__

// EMTF HLS
#include "common.h"

namespace emtf {

// _____________________________________________________________________________
// Model lengths

constexpr int N_MODEL_IN = num_emtf_chambers * num_emtf_segments;
constexpr int N_MODEL_OUT = num_emtf_tracks * num_emtf_features;

// _____________________________________________________________________________
// Layer lengths

constexpr int N_ZONING_OUT = num_emtf_img_rows;
constexpr int N_POOLING_IN = N_ZONING_OUT;
constexpr int N_POOLING_OUT = num_emtf_img_cols;
constexpr int N_SUPPRESSION_IN = N_POOLING_OUT;
constexpr int N_SUPPRESSION_OUT = N_SUPPRESSION_IN;
constexpr int N_ZONESORTING_IN = N_SUPPRESSION_OUT;
constexpr int N_ZONESORTING_OUT = num_emtf_tracks;
constexpr int N_ZONEMERGING_IN = N_ZONESORTING_OUT;
constexpr int N_ZONEMERGING_OUT = N_ZONEMERGING_IN;
constexpr int N_TRKBUILDING_IN = N_ZONEMERGING_OUT;
constexpr int N_TRKBUILDING_OUT = N_TRKBUILDING_IN;
constexpr int N_DUPEREMOVAL_IN = N_TRKBUILDING_OUT;
constexpr int N_DUPEREMOVAL_OUT = N_DUPEREMOVAL_IN;

}  // namespace emtf

#endif  // __EMTF_HLSLIB_LENGTHS_H__ not defined
