#ifndef __EMTF_HLSLIB_TYPES_H__
#define __EMTF_HLSLIB_TYPES_H__

// Xilinx HLS
#include "ap_int.h"

// EMTF HLS
#include "traits.h"

namespace emtf {

// Scoped enums
enum struct SegmentDataType {
  emtf_phi = 0,
  emtf_bend = 1,
  emtf_theta1 = 2,
  emtf_theta2 = 3,
  emtf_qual1 = 4,
  emtf_qual2 = 5,
  emtf_time = 6,
  seg_zones = 7,
  seg_tzones = 8,
  seg_fr = 9,
  seg_dl = 10,
  seg_bx = 11,
  seg_valid = 12
};

enum struct TrackDataType {
  trk_qual = 0,
  trk_patt = 1,
  trk_col = 2,
  trk_zone = 3,
  trk_tzone = 4,
  trk_seg = 5,
  trk_feat = 6,
  trk_valid = 7
};

// Bit width
template <SegmentDataType T> struct segment_data_bw_traits {};
template <> struct segment_data_bw_traits<SegmentDataType::emtf_phi>    { static const int value = 13; };
template <> struct segment_data_bw_traits<SegmentDataType::emtf_bend>   { static const int value = 10; };
template <> struct segment_data_bw_traits<SegmentDataType::emtf_theta1> { static const int value = 8; };
template <> struct segment_data_bw_traits<SegmentDataType::emtf_theta2> { static const int value = 8; };
template <> struct segment_data_bw_traits<SegmentDataType::emtf_qual1>  { static const int value = 6; };
template <> struct segment_data_bw_traits<SegmentDataType::emtf_qual2>  { static const int value = 6; };
template <> struct segment_data_bw_traits<SegmentDataType::emtf_time>   { static const int value = 6; };
template <> struct segment_data_bw_traits<SegmentDataType::seg_zones>   { static const int value = 3; };
template <> struct segment_data_bw_traits<SegmentDataType::seg_tzones>  { static const int value = 3; };
template <> struct segment_data_bw_traits<SegmentDataType::seg_fr>      { static const int value = 1; };
template <> struct segment_data_bw_traits<SegmentDataType::seg_dl>      { static const int value = 1; };
template <> struct segment_data_bw_traits<SegmentDataType::seg_bx>      { static const int value = 2; };
template <> struct segment_data_bw_traits<SegmentDataType::seg_valid>   { static const int value = 1; };

template <TrackDataType T> struct track_data_bw_traits {};
template <> struct track_data_bw_traits<TrackDataType::trk_qual>  { static const int value = 6; };
template <> struct track_data_bw_traits<TrackDataType::trk_patt>  { static const int value = 3; };
template <> struct track_data_bw_traits<TrackDataType::trk_col>   { static const int value = 9; };
template <> struct track_data_bw_traits<TrackDataType::trk_zone>  { static const int value = 2; };
template <> struct track_data_bw_traits<TrackDataType::trk_tzone> { static const int value = 2; };
template <> struct track_data_bw_traits<TrackDataType::trk_seg>   { static const int value = 8; };
template <> struct track_data_bw_traits<TrackDataType::trk_feat>  { static const int value = 13; };
template <> struct track_data_bw_traits<TrackDataType::trk_valid> { static const int value = 1; };

// Is signed
template <SegmentDataType T> struct segment_data_sign_traits {};
template <> struct segment_data_sign_traits<SegmentDataType::emtf_phi>    { static const bool value = 0; };
template <> struct segment_data_sign_traits<SegmentDataType::emtf_bend>   { static const bool value = 1; };
template <> struct segment_data_sign_traits<SegmentDataType::emtf_theta1> { static const bool value = 0; };
template <> struct segment_data_sign_traits<SegmentDataType::emtf_theta2> { static const bool value = 0; };
template <> struct segment_data_sign_traits<SegmentDataType::emtf_qual1>  { static const bool value = 1; };
template <> struct segment_data_sign_traits<SegmentDataType::emtf_qual2>  { static const bool value = 1; };
template <> struct segment_data_sign_traits<SegmentDataType::emtf_time>   { static const bool value = 1; };
template <> struct segment_data_sign_traits<SegmentDataType::seg_zones>   { static const bool value = 0; };
template <> struct segment_data_sign_traits<SegmentDataType::seg_tzones>  { static const bool value = 0; };
template <> struct segment_data_sign_traits<SegmentDataType::seg_fr>      { static const bool value = 0; };
template <> struct segment_data_sign_traits<SegmentDataType::seg_dl>      { static const bool value = 0; };
template <> struct segment_data_sign_traits<SegmentDataType::seg_bx>      { static const bool value = 1; };
template <> struct segment_data_sign_traits<SegmentDataType::seg_valid>   { static const bool value = 0; };

template <TrackDataType T> struct track_data_sign_traits {};
template <> struct track_data_sign_traits<TrackDataType::trk_qual>  { static const bool value = 0; };
template <> struct track_data_sign_traits<TrackDataType::trk_patt>  { static const bool value = 0; };
template <> struct track_data_sign_traits<TrackDataType::trk_col>   { static const bool value = 0; };
template <> struct track_data_sign_traits<TrackDataType::trk_zone>  { static const bool value = 0; };
template <> struct track_data_sign_traits<TrackDataType::trk_tzone> { static const bool value = 0; };
template <> struct track_data_sign_traits<TrackDataType::trk_seg>   { static const bool value = 0; };
template <> struct track_data_sign_traits<TrackDataType::trk_feat>  { static const bool value = 1; };
template <> struct track_data_sign_traits<TrackDataType::trk_valid> { static const bool value = 0; };

// Use bw and sign traits to select the ap datatype
template <SegmentDataType T> struct select_segment_datatype {
  typedef typename make_ap_int_type<
      segment_data_bw_traits<T>::value, segment_data_sign_traits<T>::value>::type type;
};

template <TrackDataType T> struct select_track_datatype {
  typedef typename make_ap_int_type<
      track_data_bw_traits<T>::value, track_data_sign_traits<T>::value>::type type;
};

// Text replacement macro ("token pasting") used to define the ap datatype
#define DEFINE_SEGMENT_DATATYPE(NAME) \
    typedef select_segment_datatype<SegmentDataType::NAME>::type NAME##_t;

DEFINE_SEGMENT_DATATYPE(emtf_phi)
DEFINE_SEGMENT_DATATYPE(emtf_bend)
DEFINE_SEGMENT_DATATYPE(emtf_theta1)
DEFINE_SEGMENT_DATATYPE(emtf_theta2)
DEFINE_SEGMENT_DATATYPE(emtf_qual1)
DEFINE_SEGMENT_DATATYPE(emtf_qual2)
DEFINE_SEGMENT_DATATYPE(emtf_time)
DEFINE_SEGMENT_DATATYPE(seg_zones)
DEFINE_SEGMENT_DATATYPE(seg_tzones)
DEFINE_SEGMENT_DATATYPE(seg_fr)
DEFINE_SEGMENT_DATATYPE(seg_dl)
DEFINE_SEGMENT_DATATYPE(seg_bx)
DEFINE_SEGMENT_DATATYPE(seg_valid)
#undef DEFINE_SEGMENT_DATATYPE

#define DEFINE_TRACK_DATATYPE(NAME) \
    typedef select_track_datatype<TrackDataType::NAME>::type NAME##_t;

DEFINE_TRACK_DATATYPE(trk_qual)
DEFINE_TRACK_DATATYPE(trk_patt)
DEFINE_TRACK_DATATYPE(trk_col)
DEFINE_TRACK_DATATYPE(trk_zone)
DEFINE_TRACK_DATATYPE(trk_tzone)
DEFINE_TRACK_DATATYPE(trk_seg)
DEFINE_TRACK_DATATYPE(trk_feat)
DEFINE_TRACK_DATATYPE(trk_valid)
#undef DEFINE_TRACK_DATATYPE

// _____________________________________________________________________________
// Model typedefs

typedef struct {
  emtf_phi_t emtf_phi;
  emtf_bend_t emtf_bend;
  emtf_theta1_t emtf_theta1;
  emtf_theta2_t emtf_theta2;
  emtf_qual1_t emtf_qual1;
  emtf_qual2_t emtf_qual2;
  emtf_time_t emtf_time;
  seg_zones_t seg_zones;
  seg_tzones_t seg_tzones;
  seg_fr_t seg_fr;
  seg_dl_t seg_dl;
  seg_bx_t seg_bx;
  seg_valid_t seg_valid;
} model_in_t;

typedef trk_feat_t model_out_t;

// _____________________________________________________________________________
// Layer typedefs

typedef ap_uint<8>                 zoning_seg_t;            // bw: ceil(log2(num_emtf_chambers * num_emtf_segments))
typedef ap_uint<9>                 zoning_col_t;            // bw: ceil(log2(80 / coarse_emtf_strip))
typedef ap_uint<num_emtf_img_cols> zoning_out_t;            // bw: num_emtf_img_cols
typedef ap_uint<num_emtf_img_rows> pooling_accumulation_t;  // bw: num_emtf_img_rows
typedef ap_uint<6>                 pooling_activation_t;    // bw: accumulation bw - 2
typedef ap_uint<3>                 pooling_patt_t;          // bw: ceil(log2(num_emtf_patterns))
typedef ap_uint<9>                 pooling_col_t;           // bw: ceil(log2(num_emtf_img_cols))
typedef ap_uint<2>                 pooling_zone_t;          // bw: ceil(log2(num_emtf_zones))
typedef ap_uint<6+3>               pooling_out_t;           // bw: activation bw + patt bw
typedef ap_uint<6+3+9>             zonesorting_out_t;       // bw: activation bw + patt bw + col bw
typedef ap_uint<6+3+9+2>           zonemerging_out_t;       // bw: activation bw + patt bw + col bw + zone bw
typedef ap_uint<2>                 trkbuilding_area_t;      // bw: ceil(log2(num_emtf_img_areas))
typedef ap_uint<10>                trkbuilding_ph_diff_t;   // bw: ceil(log2(10 / emtf_phi_scale))
typedef ap_uint<6>                 trkbuilding_th_diff_t;   // bw: ceil(log2(14 / emtf_theta_scale))
typedef ap_uint<num_emtf_tracks>   duperemoval_survivor_t;  // bw: num_emtf_tracks

// Synonyms
typedef zoning_out_t               pooling_in_t;
typedef pooling_out_t              suppression_in_t;
typedef suppression_in_t           suppression_out_t;
typedef suppression_out_t          zonesorting_in_t;
typedef zonesorting_out_t          zonemerging_in_t;

}  // namespace emtf

#endif  // __EMTF_HLSLIB_TYPES_H__ not defined
