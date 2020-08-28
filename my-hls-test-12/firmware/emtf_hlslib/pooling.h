#ifndef __EMTF_HLSLIB_POOLING_H__
#define __EMTF_HLSLIB_POOLING_H__

namespace emtf {

// _____________________________________________________________________________
// Entry point

template <int ZONE>
void pooling_layer(
    const emtf::zoning_out_t zoning_out[N_ZONING_OUT],
    emtf::pooling_out_t pooling_out[N_POOLING_OUT]
) {

#pragma HLS PIPELINE II=1

}


}  // namespace emtf

#endif  // __EMTF_HLSLIB_POOLING_H__ not defined
