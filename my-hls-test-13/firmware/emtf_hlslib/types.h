#ifndef __EMTF_HLSLIB_TYPES_H__
#define __EMTF_HLSLIB_TYPES_H__

// Xilinx HLS
#include "ap_int.h"

// EMTF HLS
#include "traits.h"

namespace emtf {

// Scoped enums
enum struct SegmentDataType {
  emtf_phi    = 0,
  emtf_bend   = 1,
  emtf_theta1 = 2,
  emtf_theta2 = 3,
  emtf_qual1  = 4,
  emtf_qual2  = 5,
  emtf_time   = 6,
  seg_zones   = 7,
  seg_tzones  = 8,
  seg_fr      = 9,
  seg_dl      = 10,
  seg_bx      = 11,
  seg_valid   = 12
};

enum struct TrackDataType {
  trk_qual  = 0,
  trk_patt  = 1,
  trk_col   = 2,
  trk_zone  = 3,
  trk_tzone = 4,
  trk_seg   = 5,
  trk_seg_v = 6,
  trk_feat  = 7,
  trk_invpt = 8,
  trk_phi   = 9,
  trk_eta   = 10,
  trk_d0    = 11,
  trk_z0    = 12,
  trk_beta  = 13
};

// Bit width
template <SegmentDataType T> struct segment_data_bw_traits {};
template <> struct segment_data_bw_traits<SegmentDataType::emtf_phi>    { static const int value = 13; };
template <> struct segment_data_bw_traits<SegmentDataType::emtf_bend>   { static const int value = 10; };
template <> struct segment_data_bw_traits<SegmentDataType::emtf_theta1> { static const int value = 8; };
template <> struct segment_data_bw_traits<SegmentDataType::emtf_theta2> { static const int value = 8; };
template <> struct segment_data_bw_traits<SegmentDataType::emtf_qual1>  { static const int value = 4; };
template <> struct segment_data_bw_traits<SegmentDataType::emtf_qual2>  { static const int value = 4; };
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
template <> struct track_data_bw_traits<TrackDataType::trk_seg_v> { static const int value = 12; };
template <> struct track_data_bw_traits<TrackDataType::trk_feat>  { static const int value = 13; };
template <> struct track_data_bw_traits<TrackDataType::trk_invpt> { static const int value = 14; };
template <> struct track_data_bw_traits<TrackDataType::trk_phi>   { static const int value = 14; };
template <> struct track_data_bw_traits<TrackDataType::trk_eta>   { static const int value = 14; };
template <> struct track_data_bw_traits<TrackDataType::trk_d0>    { static const int value = 14; };
template <> struct track_data_bw_traits<TrackDataType::trk_z0>    { static const int value = 14; };
template <> struct track_data_bw_traits<TrackDataType::trk_beta>  { static const int value = 14; };

// Is signed
template <SegmentDataType T> struct segment_data_sg_traits {};
template <> struct segment_data_sg_traits<SegmentDataType::emtf_phi>    { static const bool value = 0; };
template <> struct segment_data_sg_traits<SegmentDataType::emtf_bend>   { static const bool value = 1; };
template <> struct segment_data_sg_traits<SegmentDataType::emtf_theta1> { static const bool value = 0; };
template <> struct segment_data_sg_traits<SegmentDataType::emtf_theta2> { static const bool value = 0; };
template <> struct segment_data_sg_traits<SegmentDataType::emtf_qual1>  { static const bool value = 0; };
template <> struct segment_data_sg_traits<SegmentDataType::emtf_qual2>  { static const bool value = 0; };
template <> struct segment_data_sg_traits<SegmentDataType::emtf_time>   { static const bool value = 1; };
template <> struct segment_data_sg_traits<SegmentDataType::seg_zones>   { static const bool value = 0; };
template <> struct segment_data_sg_traits<SegmentDataType::seg_tzones>  { static const bool value = 0; };
template <> struct segment_data_sg_traits<SegmentDataType::seg_fr>      { static const bool value = 0; };
template <> struct segment_data_sg_traits<SegmentDataType::seg_dl>      { static const bool value = 0; };
template <> struct segment_data_sg_traits<SegmentDataType::seg_bx>      { static const bool value = 1; };
template <> struct segment_data_sg_traits<SegmentDataType::seg_valid>   { static const bool value = 0; };

template <TrackDataType T> struct track_data_sg_traits {};
template <> struct track_data_sg_traits<TrackDataType::trk_qual>  { static const bool value = 0; };
template <> struct track_data_sg_traits<TrackDataType::trk_patt>  { static const bool value = 0; };
template <> struct track_data_sg_traits<TrackDataType::trk_col>   { static const bool value = 0; };
template <> struct track_data_sg_traits<TrackDataType::trk_zone>  { static const bool value = 0; };
template <> struct track_data_sg_traits<TrackDataType::trk_tzone> { static const bool value = 0; };
template <> struct track_data_sg_traits<TrackDataType::trk_seg>   { static const bool value = 0; };
template <> struct track_data_sg_traits<TrackDataType::trk_seg_v> { static const bool value = 0; };
template <> struct track_data_sg_traits<TrackDataType::trk_feat>  { static const bool value = 1; };
template <> struct track_data_sg_traits<TrackDataType::trk_invpt> { static const bool value = 1; };
template <> struct track_data_sg_traits<TrackDataType::trk_phi>   { static const bool value = 1; };
template <> struct track_data_sg_traits<TrackDataType::trk_eta>   { static const bool value = 1; };
template <> struct track_data_sg_traits<TrackDataType::trk_d0>    { static const bool value = 1; };
template <> struct track_data_sg_traits<TrackDataType::trk_z0>    { static const bool value = 1; };
template <> struct track_data_sg_traits<TrackDataType::trk_beta>  { static const bool value = 1; };

// Use bw and sign traits to select the ap datatype
template <SegmentDataType T> struct select_segment_datatype {
  typedef typename make_ap_int_type<
      segment_data_bw_traits<T>::value, segment_data_sg_traits<T>::value>::type type;
};

template <TrackDataType T> struct select_track_datatype {
  typedef typename make_ap_int_type<
      track_data_bw_traits<T>::value, track_data_sg_traits<T>::value>::type type;
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
DEFINE_TRACK_DATATYPE(trk_seg_v)
DEFINE_TRACK_DATATYPE(trk_feat)
DEFINE_TRACK_DATATYPE(trk_invpt)
DEFINE_TRACK_DATATYPE(trk_phi)
DEFINE_TRACK_DATATYPE(trk_eta)
DEFINE_TRACK_DATATYPE(trk_d0)
DEFINE_TRACK_DATATYPE(trk_z0)
DEFINE_TRACK_DATATYPE(trk_beta)
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

// These do not appear in the layer interfaces
typedef ap_uint<1>                 bool_t;
typedef ap_uint<num_emtf_img_cols> dio_col_accum_t;
typedef ap_uint<num_emtf_img_rows> dio_row_accum_t;
typedef ap_uint<num_emtf_tracks>   dio_trk_accum_t;
typedef ap_uint<11>                dio_ph_diff_t;  // bw: ceil(log2(20 / 0.01667))
typedef ap_uint<6>                 dio_th_diff_t;  // bw: ceil(log2(14 / 0.28515625))
typedef ap_uint<5>                 dio_ph_idx_t;   // bw: ceil(log2(site_num_segments)) = ceil(log2(24))
typedef ap_uint<2>                 dio_ph_area_t;  // bw: ceil(log2(num_emtf_areas)) = ceil(log2(3))
typedef dio_trk_accum_t            dio_survivor_t;
typedef ap_fixed<14,1>             dio_hard_tanh_t;  // fixed-point output of hard_tanh()

// These appear in the layer interfaces
typedef dio_col_accum_t                                 zoning_out_t;
typedef zoning_out_t                                    pooling_in_t;
typedef make_concat<trk_patt_t, trk_qual_t>::type       pooling_out_t;
typedef pooling_out_t                                   suppression_in_t;
typedef suppression_in_t                                suppression_out_t;
typedef suppression_out_t                               zonesorting_in_t;
typedef make_concat<trk_col_t, zonesorting_in_t>::type  zonesorting_out_t;
typedef zonesorting_out_t                               zonemerging_in_t;
typedef make_concat<trk_zone_t, zonemerging_in_t>::type zonemerging_out_t;
typedef zonemerging_out_t                               trkbuilding_in_t;

// Misc
typedef bool_t trk_valid_t;

}  // namespace emtf

#endif  // __EMTF_HLSLIB_TYPES_H__ not defined
