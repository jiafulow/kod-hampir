#ifndef __EMTF_HLSLIB_COMMON_H__
#define __EMTF_HLSLIB_COMMON_H__

namespace emtf {

  // from official-cmssw: DataFormats/MuonDetId/interface/CSCDetId.h
  constexpr int min_endcap = 1;
  constexpr int max_endcap = 2;
  constexpr int min_station = 1;
  constexpr int max_station = 4;
  constexpr int min_ring = 1;
  constexpr int max_ring = 4;
  constexpr int min_chamber = 1;
  constexpr int max_chamber = 36;
  constexpr int min_layer = 1;
  constexpr int max_layer = 6;

  // from official-cmssw: DataFormats/MuonDetId/interface/CSCTriggerNumbering.h
  constexpr int min_cscid = 1;
  constexpr int max_cscid = 9;
  constexpr int min_trigsector = 1;
  constexpr int max_trigsector = 6;
  constexpr int min_trigsubsector = 0;
  constexpr int max_trigsubsector = 2;

  // EMTF
  constexpr int num_sectors = 12;  // 2 endcaps, 6 sectors per endcap
  constexpr int num_zones = 3;     // per sector
  constexpr int num_timezones = 1; //FIXME - need to include more than one BX

  constexpr int num_chambers = 115;
  constexpr int num_segments = 2;  //FIXME - need to accommodate GEM and ME0
  constexpr int num_variables = 10;

  constexpr int num_tracks = 4;    // per sector
  constexpr int num_patterns = 7;  // per zone
  constexpr int num_features = 36; // per track
  constexpr int num_sites = 12;
  constexpr int num_sites_rm = 5;

  constexpr int num_img_rows = 8;
  constexpr int num_img_cols = 288;
  constexpr int num_img_areas = 3;

}  // namespace emtf

#endif  // __EMTF_HLSLIB_COMMON_H__ not defined
