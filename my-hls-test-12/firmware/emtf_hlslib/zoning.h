#ifndef __EMTF_HLSLIB_ZONING_H__
#define __EMTF_HLSLIB_ZONING_H__

namespace emtf {

// _____________________________________________________________________________
// Entry point

template <int ZONE>
void zoning_layer(
    const emtf::emtf_phi_t emtf_phi[N_MODEL_IN],
    const emtf::zones_t zones[N_MODEL_IN],
    const emtf::timezones_t timezones[N_MODEL_IN],
    const emtf::valid_t valid[N_MODEL_IN],
    emtf::zoning_out_t zoning_out[N_ZONING_OUT]
) {

#pragma HLS PIPELINE II=1

}


}  // namespace emtf

#endif  // __EMTF_HLSLIB_ZONING_H__ not defined
