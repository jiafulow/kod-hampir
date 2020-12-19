#ifndef __EMTF_HLSLIB_LAYERS_H__
#define __EMTF_HLSLIB_LAYERS_H__

// EMTF HLS
#include "common.h"
#include "traits.h"
#include "layer_constants.h"

namespace emtf {

// _____________________________________________________________________________
// Model configs

struct model_config {
  static const unsigned int n_in = num_emtf_chambers * num_emtf_segments;
  static const unsigned int n_out = num_emtf_tracks * num_emtf_features;
  static const int target_ii = 1;
};

// _____________________________________________________________________________
// Layer configs

struct zoning_config {
  static const unsigned int n_in = 0;
  static const unsigned int n_out = num_emtf_img_rows;
  static const int target_ii = 1;
};

struct pooling_config {
  static const unsigned int n_in = zoning_config::n_out;
  static const unsigned int n_out = num_emtf_img_cols;
  static const int target_ii = 1;

  // Used in the column loop
  static const int fusion_factor = 1;
};

struct suppression_config {
  static const unsigned int n_in = pooling_config::n_out;
  static const unsigned int n_out = n_in;
  static const int target_ii = 1;
};

struct zonesorting_config {
  static const unsigned int n_in = suppression_config::n_out;
  static const unsigned int n_out = num_emtf_tracks;
  static const int target_ii = 1;

  // Used in the column loop
  static const int batch_size = 8;

  // Used for sorting stages
  static const unsigned int n_skipped_stage_0 = 16;
  static const unsigned int n_stage_0 = (n_in / 2) - n_skipped_stage_0;
  static const unsigned int n_stage_1 = n_stage_0 / 2;
  static const unsigned int n_stage_2 = n_stage_1 / 2;
  static const unsigned int n_stage_3 = (n_stage_2 / 2) + n_skipped_stage_0;
  static const unsigned int n_stage_4 = n_stage_3 / 2;
  static const unsigned int n_stage_5 = n_stage_4 / 2;
  static const unsigned int n_stage_6 = n_stage_5 / 2;
};

struct zonemerging_config {
  static const unsigned int n_in = zonesorting_config::n_out;
  static const unsigned int n_out = n_in;
  static const int target_ii = 1;

  // Used for sorting stages
  static const unsigned int n_stage_0 = n_in * num_emtf_zones;
};

struct trkbuilding_config {
  static const unsigned int n_in = zonemerging_config::n_out;
  static const unsigned int n_out = n_in;
  static const int target_ii = 1;
};

struct duperemoval_config {
  static const unsigned int n_in = trkbuilding_config::n_out;
  static const unsigned int n_out = n_in;
  static const int target_ii = 1;
};

// _____________________________________________________________________________
// Various tags

// Subsystem
struct m_dt_subsystem_tag {};
struct m_csc_subsystem_tag {};
struct m_rpc_subsystem_tag {};
struct m_gem_subsystem_tag {};
struct m_me0_subsystem_tag {};

// Chamber
struct m_10deg_chamber_tag {};
struct m_20deg_chamber_tag {};
struct m_20deg_ext_chamber_tag {};

// Zone
struct m_zone_0_tag {};
struct m_zone_1_tag {};
struct m_zone_2_tag {};
struct m_zone_any_tag {};

// Timezone
struct m_timezone_0_tag {};
struct m_timezone_1_tag {};
struct m_timezone_2_tag {};
struct m_timezone_any_tag {};

// Row
struct m_zone_0_row_0_tag : m_zone_0_tag {};
struct m_zone_0_row_1_tag : m_zone_0_tag {};
struct m_zone_0_row_2_tag : m_zone_0_tag {};
struct m_zone_0_row_3_tag : m_zone_0_tag {};
struct m_zone_0_row_4_tag : m_zone_0_tag {};
struct m_zone_0_row_5_tag : m_zone_0_tag {};
struct m_zone_0_row_6_tag : m_zone_0_tag {};
struct m_zone_0_row_7_0_tag : m_zone_0_tag {};
struct m_zone_0_row_7_1_tag : m_zone_0_tag {};
//
struct m_zone_1_row_0_tag : m_zone_1_tag {};
struct m_zone_1_row_1_tag : m_zone_1_tag {};
struct m_zone_1_row_2_0_tag : m_zone_1_tag {};
struct m_zone_1_row_2_1_tag : m_zone_1_tag {};
struct m_zone_1_row_3_tag : m_zone_1_tag {};
struct m_zone_1_row_4_tag : m_zone_1_tag {};
struct m_zone_1_row_5_tag : m_zone_1_tag {};
struct m_zone_1_row_6_tag : m_zone_1_tag {};
struct m_zone_1_row_7_0_tag : m_zone_1_tag {};
struct m_zone_1_row_7_1_tag : m_zone_1_tag {};
//
struct m_zone_2_row_0_tag : m_zone_2_tag {};
struct m_zone_2_row_1_tag : m_zone_2_tag {};
struct m_zone_2_row_2_tag : m_zone_2_tag {};
struct m_zone_2_row_3_tag : m_zone_2_tag {};
struct m_zone_2_row_4_tag : m_zone_2_tag {};
struct m_zone_2_row_5_tag : m_zone_2_tag {};
struct m_zone_2_row_6_tag : m_zone_2_tag {};
struct m_zone_2_row_7_tag : m_zone_2_tag {};

// Site
struct m_site_0_tag : m_zone_any_tag {};
struct m_site_1_tag : m_zone_any_tag {};
struct m_site_2_tag : m_zone_any_tag {};
struct m_site_3_tag : m_zone_any_tag {};
struct m_site_4_tag : m_zone_any_tag {};
struct m_site_5_tag : m_zone_any_tag {};
struct m_site_6_tag : m_zone_any_tag {};
struct m_site_7_tag : m_zone_any_tag {};
struct m_site_8_tag : m_zone_any_tag {};
struct m_site_9_tag : m_zone_any_tag {};
struct m_site_10_tag : m_zone_any_tag {};
struct m_site_11_tag : m_zone_any_tag {};

// HLS directives
struct m_inline_directive {};

// _____________________________________________________________________________
// Utilities

namespace details {

// Traits
template <typename Category>
struct num_chambers_traits {};

template <> struct num_chambers_traits<m_10deg_chamber_tag> { static const int value = num_chambers_10deg; };
template <> struct num_chambers_traits<m_20deg_chamber_tag> { static const int value = num_chambers_20deg; };
template <> struct num_chambers_traits<m_20deg_ext_chamber_tag> { static const int value = num_chambers_20deg_ext; };

template <typename Category>
struct zone_traits {};

template <> struct zone_traits<m_zone_0_tag> { static const int value = 0; };
template <> struct zone_traits<m_zone_1_tag> { static const int value = 1; };
template <> struct zone_traits<m_zone_2_tag> { static const int value = 2; };

template <typename Category>
struct zone_num_rows_traits {};

template <> struct zone_num_rows_traits<m_zone_0_tag> { static const int value = 1 + 1 + 1 + 1 + 1 + 1 + 1 + 2; };
template <> struct zone_num_rows_traits<m_zone_1_tag> { static const int value = 1 + 1 + 2 + 1 + 1 + 1 + 1 + 2; };
template <> struct zone_num_rows_traits<m_zone_2_tag> { static const int value = 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1; };

template <typename Category>
struct timezone_traits {};

template <> struct timezone_traits<m_timezone_0_tag> { static const int value = 0; };
template <> struct timezone_traits<m_timezone_1_tag> { static const int value = 1; };
template <> struct timezone_traits<m_timezone_2_tag> { static const int value = 2; };

template <typename Category>
struct site_traits {};

template <> struct site_traits<m_site_0_tag> { static const int value = 0; };
template <> struct site_traits<m_site_1_tag> { static const int value = 1; };
template <> struct site_traits<m_site_2_tag> { static const int value = 2; };
template <> struct site_traits<m_site_3_tag> { static const int value = 3; };
template <> struct site_traits<m_site_4_tag> { static const int value = 4; };
template <> struct site_traits<m_site_5_tag> { static const int value = 5; };
template <> struct site_traits<m_site_6_tag> { static const int value = 6; };
template <> struct site_traits<m_site_7_tag> { static const int value = 7; };
template <> struct site_traits<m_site_8_tag> { static const int value = 8; };
template <> struct site_traits<m_site_9_tag> { static const int value = 9; };
template <> struct site_traits<m_site_10_tag> { static const int value = 10; };
template <> struct site_traits<m_site_11_tag> { static const int value = 11; };

template <typename Category>
struct chamber_category_traits {};

template <> struct chamber_category_traits<m_zone_0_row_0_tag> { typedef m_10deg_chamber_tag chamber_category; };
template <> struct chamber_category_traits<m_zone_0_row_1_tag> { typedef m_10deg_chamber_tag chamber_category; };
template <> struct chamber_category_traits<m_zone_0_row_2_tag> { typedef m_10deg_chamber_tag chamber_category; };
template <> struct chamber_category_traits<m_zone_0_row_3_tag> { typedef m_20deg_chamber_tag chamber_category; };
template <> struct chamber_category_traits<m_zone_0_row_4_tag> { typedef m_20deg_chamber_tag chamber_category; };
template <> struct chamber_category_traits<m_zone_0_row_5_tag> { typedef m_20deg_chamber_tag chamber_category; };
template <> struct chamber_category_traits<m_zone_0_row_6_tag> { typedef m_20deg_chamber_tag chamber_category; };
template <> struct chamber_category_traits<m_zone_0_row_7_0_tag> { typedef m_20deg_chamber_tag chamber_category; };
template <> struct chamber_category_traits<m_zone_0_row_7_1_tag> { typedef m_20deg_chamber_tag chamber_category; };
//
template <> struct chamber_category_traits<m_zone_1_row_0_tag> { typedef m_10deg_chamber_tag chamber_category; };
template <> struct chamber_category_traits<m_zone_1_row_1_tag> { typedef m_10deg_chamber_tag chamber_category; };
template <> struct chamber_category_traits<m_zone_1_row_2_0_tag> { typedef m_10deg_chamber_tag chamber_category; };
template <> struct chamber_category_traits<m_zone_1_row_2_1_tag> { typedef m_10deg_chamber_tag chamber_category; };
template <> struct chamber_category_traits<m_zone_1_row_3_tag> { typedef m_20deg_chamber_tag chamber_category; };
template <> struct chamber_category_traits<m_zone_1_row_4_tag> { typedef m_20deg_chamber_tag chamber_category; };
template <> struct chamber_category_traits<m_zone_1_row_5_tag> { typedef m_20deg_ext_chamber_tag chamber_category; };
template <> struct chamber_category_traits<m_zone_1_row_6_tag> { typedef m_20deg_ext_chamber_tag chamber_category; };
template <> struct chamber_category_traits<m_zone_1_row_7_0_tag> { typedef m_20deg_ext_chamber_tag chamber_category; };
template <> struct chamber_category_traits<m_zone_1_row_7_1_tag> { typedef m_20deg_ext_chamber_tag chamber_category; };
//
template <> struct chamber_category_traits<m_zone_2_row_0_tag> { typedef m_10deg_chamber_tag chamber_category; };
template <> struct chamber_category_traits<m_zone_2_row_1_tag> { typedef m_10deg_chamber_tag chamber_category; };
template <> struct chamber_category_traits<m_zone_2_row_2_tag> { typedef m_10deg_chamber_tag chamber_category; };
template <> struct chamber_category_traits<m_zone_2_row_3_tag> { typedef m_10deg_chamber_tag chamber_category; };
template <> struct chamber_category_traits<m_zone_2_row_4_tag> { typedef m_10deg_chamber_tag chamber_category; };
template <> struct chamber_category_traits<m_zone_2_row_5_tag> { typedef m_10deg_chamber_tag chamber_category; };
template <> struct chamber_category_traits<m_zone_2_row_6_tag> { typedef m_10deg_chamber_tag chamber_category; };
template <> struct chamber_category_traits<m_zone_2_row_7_tag> { typedef m_10deg_chamber_tag chamber_category; };
//
template <> struct chamber_category_traits<m_site_0_tag> { typedef m_10deg_chamber_tag chamber_category; };
template <> struct chamber_category_traits<m_site_1_tag> { typedef m_10deg_chamber_tag chamber_category; };
template <> struct chamber_category_traits<m_site_2_tag> { typedef m_20deg_ext_chamber_tag chamber_category; };
template <> struct chamber_category_traits<m_site_3_tag> { typedef m_20deg_ext_chamber_tag chamber_category; };
template <> struct chamber_category_traits<m_site_4_tag> { typedef m_20deg_ext_chamber_tag chamber_category; };
template <> struct chamber_category_traits<m_site_5_tag> { typedef m_10deg_chamber_tag chamber_category; };
template <> struct chamber_category_traits<m_site_6_tag> { typedef m_10deg_chamber_tag chamber_category; };
template <> struct chamber_category_traits<m_site_7_tag> { typedef m_20deg_ext_chamber_tag chamber_category; };
template <> struct chamber_category_traits<m_site_8_tag> { typedef m_20deg_ext_chamber_tag chamber_category; };
template <> struct chamber_category_traits<m_site_9_tag> { typedef m_10deg_chamber_tag chamber_category; };
template <> struct chamber_category_traits<m_site_10_tag> { typedef m_20deg_chamber_tag chamber_category; };
template <> struct chamber_category_traits<m_site_11_tag> { typedef m_10deg_chamber_tag chamber_category; };

template <typename Category, int I>
struct pattern_col_pad_traits {};

template <int I> struct pattern_col_pad_traits<m_zone_0_tag, I> { static const int value = pattern_col_pad_zone_0[I]; };
template <int I> struct pattern_col_pad_traits<m_zone_1_tag, I> { static const int value = pattern_col_pad_zone_1[I]; };
template <int I> struct pattern_col_pad_traits<m_zone_2_tag, I> { static const int value = pattern_col_pad_zone_2[I]; };

// Helper class to round up to the nearest multiple of 4
template <unsigned int N>
struct ceil_mul4 {
  static const unsigned int value = ((N + 4 - 1) / 4) * 4;
};

template <typename Category>
struct site_num_segments_traits {
  static const int num_chambers = num_chambers_traits<Category>::value;
  static const int num_chambers_round = ceil_mul4<num_chambers>::value;
  static const int value = num_chambers_round * num_emtf_segments;
};

template <typename Category>
struct area_num_segments_traits {
  static const int site_num_segments = site_num_segments_traits<Category>::value;
  static const int value = site_num_segments / ((num_emtf_img_areas + 1) / 2);
};

template <typename Category, int I>
struct select_pattern_col_padding_type {
  static const int pad = pattern_col_pad_traits<Category, I>::value;
  typedef ap_uint<pad> type;
};

template <typename Category, int I>
struct select_pattern_col_padded_type {
  static const int pad = pattern_col_pad_traits<Category, I>::value;
  typedef ap_uint<num_emtf_img_cols + (pad * 2)> type;
};

template <typename Category, int I>
struct select_pattern_col_patch_type {
  static const int pad = pattern_col_pad_traits<Category, I>::value;
  typedef ap_uint<1 + (pad * 2)> type;
};

template <typename Category, int I>
struct select_pattern_col_fused_patch_type {
  static const int pad = pattern_col_pad_traits<Category, I>::value;
  typedef ap_uint<pooling_config::fusion_factor + (pad * 2)> type;
};

// Getter ops
template <typename Category>
struct get_chamber_id_op {};

template <> struct get_chamber_id_op<m_zone_0_row_0_tag> { inline int operator ()(int i) const { return chamber_id_zone_0_row_0[i]; } };
template <> struct get_chamber_id_op<m_zone_0_row_1_tag> { inline int operator ()(int i) const { return chamber_id_zone_0_row_1[i]; } };
template <> struct get_chamber_id_op<m_zone_0_row_2_tag> { inline int operator ()(int i) const { return chamber_id_zone_0_row_2[i]; } };
template <> struct get_chamber_id_op<m_zone_0_row_3_tag> { inline int operator ()(int i) const { return chamber_id_zone_0_row_3[i]; } };
template <> struct get_chamber_id_op<m_zone_0_row_4_tag> { inline int operator ()(int i) const { return chamber_id_zone_0_row_4[i]; } };
template <> struct get_chamber_id_op<m_zone_0_row_5_tag> { inline int operator ()(int i) const { return chamber_id_zone_0_row_5[i]; } };
template <> struct get_chamber_id_op<m_zone_0_row_6_tag> { inline int operator ()(int i) const { return chamber_id_zone_0_row_6[i]; } };
template <> struct get_chamber_id_op<m_zone_0_row_7_0_tag> { inline int operator ()(int i) const { return chamber_id_zone_0_row_7_0[i]; } };
template <> struct get_chamber_id_op<m_zone_0_row_7_1_tag> { inline int operator ()(int i) const { return chamber_id_zone_0_row_7_1[i]; } };
//
template <> struct get_chamber_id_op<m_zone_1_row_0_tag> { inline int operator ()(int i) const { return chamber_id_zone_1_row_0[i]; } };
template <> struct get_chamber_id_op<m_zone_1_row_1_tag> { inline int operator ()(int i) const { return chamber_id_zone_1_row_1[i]; } };
template <> struct get_chamber_id_op<m_zone_1_row_2_0_tag> { inline int operator ()(int i) const { return chamber_id_zone_1_row_2_0[i]; } };
template <> struct get_chamber_id_op<m_zone_1_row_2_1_tag> { inline int operator ()(int i) const { return chamber_id_zone_1_row_2_1[i]; } };
template <> struct get_chamber_id_op<m_zone_1_row_3_tag> { inline int operator ()(int i) const { return chamber_id_zone_1_row_3[i]; } };
template <> struct get_chamber_id_op<m_zone_1_row_4_tag> { inline int operator ()(int i) const { return chamber_id_zone_1_row_4[i]; } };
template <> struct get_chamber_id_op<m_zone_1_row_5_tag> { inline int operator ()(int i) const { return chamber_id_zone_1_row_5[i]; } };
template <> struct get_chamber_id_op<m_zone_1_row_6_tag> { inline int operator ()(int i) const { return chamber_id_zone_1_row_6[i]; } };
template <> struct get_chamber_id_op<m_zone_1_row_7_0_tag> { inline int operator ()(int i) const { return chamber_id_zone_1_row_7_0[i]; } };
template <> struct get_chamber_id_op<m_zone_1_row_7_1_tag> { inline int operator ()(int i) const { return chamber_id_zone_1_row_7_1[i]; } };
//
template <> struct get_chamber_id_op<m_zone_2_row_0_tag> { inline int operator ()(int i) const { return chamber_id_zone_2_row_0[i]; } };
template <> struct get_chamber_id_op<m_zone_2_row_1_tag> { inline int operator ()(int i) const { return chamber_id_zone_2_row_1[i]; } };
template <> struct get_chamber_id_op<m_zone_2_row_2_tag> { inline int operator ()(int i) const { return chamber_id_zone_2_row_2[i]; } };
template <> struct get_chamber_id_op<m_zone_2_row_3_tag> { inline int operator ()(int i) const { return chamber_id_zone_2_row_3[i]; } };
template <> struct get_chamber_id_op<m_zone_2_row_4_tag> { inline int operator ()(int i) const { return chamber_id_zone_2_row_4[i]; } };
template <> struct get_chamber_id_op<m_zone_2_row_5_tag> { inline int operator ()(int i) const { return chamber_id_zone_2_row_5[i]; } };
template <> struct get_chamber_id_op<m_zone_2_row_6_tag> { inline int operator ()(int i) const { return chamber_id_zone_2_row_6[i]; } };
template <> struct get_chamber_id_op<m_zone_2_row_7_tag> { inline int operator ()(int i) const { return chamber_id_zone_2_row_7[i]; } };
//
template <> struct get_chamber_id_op<m_site_0_tag> { inline int operator ()(int i) const { return chamber_id_zone_any_site_0[i]; } };
template <> struct get_chamber_id_op<m_site_1_tag> { inline int operator ()(int i) const { return chamber_id_zone_any_site_1[i]; } };
template <> struct get_chamber_id_op<m_site_2_tag> { inline int operator ()(int i) const { return chamber_id_zone_any_site_2[i]; } };
template <> struct get_chamber_id_op<m_site_3_tag> { inline int operator ()(int i) const { return chamber_id_zone_any_site_3[i]; } };
template <> struct get_chamber_id_op<m_site_4_tag> { inline int operator ()(int i) const { return chamber_id_zone_any_site_4[i]; } };
template <> struct get_chamber_id_op<m_site_5_tag> { inline int operator ()(int i) const { return chamber_id_zone_any_site_5[i]; } };
template <> struct get_chamber_id_op<m_site_6_tag> { inline int operator ()(int i) const { return chamber_id_zone_any_site_6[i]; } };
template <> struct get_chamber_id_op<m_site_7_tag> { inline int operator ()(int i) const { return chamber_id_zone_any_site_7[i]; } };
template <> struct get_chamber_id_op<m_site_8_tag> { inline int operator ()(int i) const { return chamber_id_zone_any_site_8[i]; } };
template <> struct get_chamber_id_op<m_site_9_tag> { inline int operator ()(int i) const { return chamber_id_zone_any_site_9[i]; } };
template <> struct get_chamber_id_op<m_site_10_tag> { inline int operator ()(int i) const { return chamber_id_zone_any_site_10[i]; } };
template <> struct get_chamber_id_op<m_site_11_tag> { inline int operator ()(int i) const { return chamber_id_zone_any_site_11[i]; } };

template <typename Category>
struct get_chamber_ph_init_op {};

template <> struct get_chamber_ph_init_op<m_10deg_chamber_tag> { inline int operator ()(int i) const { return chamber_ph_init_10deg[i]; } };
template <> struct get_chamber_ph_init_op<m_20deg_chamber_tag> { inline int operator ()(int i) const { return chamber_ph_init_20deg[i]; } };
template <> struct get_chamber_ph_init_op<m_20deg_ext_chamber_tag> { inline int operator ()(int i) const { return chamber_ph_init_20deg_ext[i]; } };

template <typename Category>
struct get_chamber_ph_cover_op {};

template <> struct get_chamber_ph_cover_op<m_10deg_chamber_tag> { inline int operator ()(int i) const { return chamber_ph_cover_10deg[i]; } };
template <> struct get_chamber_ph_cover_op<m_20deg_chamber_tag> { inline int operator ()(int i) const { return chamber_ph_cover_20deg[i]; } };
template <> struct get_chamber_ph_cover_op<m_20deg_ext_chamber_tag> { inline int operator ()(int i) const { return chamber_ph_cover_20deg_ext[i]; } };

// Text replacement macro ("token pasting") used to define the getters for col_start, col_mid, col_stop.
// The template parameter takes zone. The operator () takes patt i row j. Note that padding is added.
#define DEFINE_PATTERN_GETTER_OP(NAME) \
    template <typename Zone, typename Enable = void> \
    struct get_pattern_##NAME##_op {}; \
    \
    template <typename Zone> struct get_pattern_##NAME##_op<Zone, typename enable_if<is_same<Zone, m_zone_0_tag>::value>::type> { \
      inline int operator ()(int i, int j) const { \
        const int ref = pattern_col_reference; \
        switch (i) { \
          case 0: return pattern_##NAME##_zone_0_patt_0[j] + pattern_col_pad_zone_0[j] - ref; \
          case 1: return pattern_##NAME##_zone_0_patt_1[j] + pattern_col_pad_zone_0[j] - ref; \
          case 2: return pattern_##NAME##_zone_0_patt_2[j] + pattern_col_pad_zone_0[j] - ref; \
          case 3: return pattern_##NAME##_zone_0_patt_3[j] + pattern_col_pad_zone_0[j] - ref; \
          case 4: return pattern_##NAME##_zone_0_patt_4[j] + pattern_col_pad_zone_0[j] - ref; \
          case 5: return pattern_##NAME##_zone_0_patt_5[j] + pattern_col_pad_zone_0[j] - ref; \
          case 6: return pattern_##NAME##_zone_0_patt_6[j] + pattern_col_pad_zone_0[j] - ref; \
          default: return 0; \
        } \
      } \
    }; \
    template <typename Zone> struct get_pattern_##NAME##_op<Zone, typename enable_if<is_same<Zone, m_zone_1_tag>::value>::type> { \
      inline int operator ()(int i, int j) const { \
        const int ref = pattern_col_reference; \
        switch (i) { \
          case 0: return pattern_##NAME##_zone_1_patt_0[j] + pattern_col_pad_zone_1[j] - ref; \
          case 1: return pattern_##NAME##_zone_1_patt_1[j] + pattern_col_pad_zone_1[j] - ref; \
          case 2: return pattern_##NAME##_zone_1_patt_2[j] + pattern_col_pad_zone_1[j] - ref; \
          case 3: return pattern_##NAME##_zone_1_patt_3[j] + pattern_col_pad_zone_1[j] - ref; \
          case 4: return pattern_##NAME##_zone_1_patt_4[j] + pattern_col_pad_zone_1[j] - ref; \
          case 5: return pattern_##NAME##_zone_1_patt_5[j] + pattern_col_pad_zone_1[j] - ref; \
          case 6: return pattern_##NAME##_zone_1_patt_6[j] + pattern_col_pad_zone_1[j] - ref; \
          default: return 0; \
        } \
      } \
    }; \
    template <typename Zone> struct get_pattern_##NAME##_op<Zone, typename enable_if<is_same<Zone, m_zone_2_tag>::value>::type> { \
      inline int operator ()(int i, int j) const { \
        const int ref = pattern_col_reference; \
        switch (i) { \
          case 0: return pattern_##NAME##_zone_2_patt_0[j] + pattern_col_pad_zone_2[j] - ref; \
          case 1: return pattern_##NAME##_zone_2_patt_1[j] + pattern_col_pad_zone_2[j] - ref; \
          case 2: return pattern_##NAME##_zone_2_patt_2[j] + pattern_col_pad_zone_2[j] - ref; \
          case 3: return pattern_##NAME##_zone_2_patt_3[j] + pattern_col_pad_zone_2[j] - ref; \
          case 4: return pattern_##NAME##_zone_2_patt_4[j] + pattern_col_pad_zone_2[j] - ref; \
          case 5: return pattern_##NAME##_zone_2_patt_5[j] + pattern_col_pad_zone_2[j] - ref; \
          case 6: return pattern_##NAME##_zone_2_patt_6[j] + pattern_col_pad_zone_2[j] - ref; \
          default: return 0; \
        } \
      } \
    };

DEFINE_PATTERN_GETTER_OP(col_start)
DEFINE_PATTERN_GETTER_OP(col_mid)
DEFINE_PATTERN_GETTER_OP(col_stop)
#undef DEFINE_PATTERN_GETTER_OP

template <typename Category>
struct get_pattern_activation_op {};

template <> struct get_pattern_activation_op<m_zone_0_tag> { inline int operator ()(int i) const { return pattern_activation_zone_0[i]; } };
template <> struct get_pattern_activation_op<m_zone_1_tag> { inline int operator ()(int i) const { return pattern_activation_zone_1[i]; } };
template <> struct get_pattern_activation_op<m_zone_2_tag> { inline int operator ()(int i) const { return pattern_activation_zone_2[i]; } };

template <typename Category>
struct get_site_chamber_order_op {};

template <> struct get_site_chamber_order_op<m_10deg_chamber_tag> { inline int operator ()(int i) const { return site_chamber_order_10deg[i]; } };
template <> struct get_site_chamber_order_op<m_20deg_chamber_tag> { inline int operator ()(int i) const { return site_chamber_order_20deg[i]; } };
template <> struct get_site_chamber_order_op<m_20deg_ext_chamber_tag> { inline int operator ()(int i) const { return site_chamber_order_20deg_ext[i]; } };

template <typename Category>
struct get_site_chamber_valid_op {
  inline bool operator ()(int i) const { return (i < (num_chambers_traits<Category>::value)); }
};

template <typename Category>
struct get_site_segment_id_op {
  typedef typename chamber_category_traits<Category>::chamber_category chamber_category;

  inline int operator ()(int i) const {
    auto get_chamber_id = get_chamber_id_op<Category>();
    auto get_site_chamber_order = get_site_chamber_order_op<chamber_category>();
    auto get_site_chamber_valid = get_site_chamber_valid_op<chamber_category>();

    const int tmp_chm_0 = (i / num_emtf_segments);
    const int tmp_chm_1 = get_site_chamber_order(tmp_chm_0);
    const bool is_valid_chm = get_site_chamber_valid(tmp_chm_1);

    const int invalid_marker = model_config::n_in;
    int iseg = invalid_marker;  // default to 'invalid'
    if (is_valid_chm) {
      const int tmp_chm = get_chamber_id(tmp_chm_1);
      const int tmp_seg = (i % num_emtf_segments);
      iseg = ((tmp_chm * num_emtf_segments) + tmp_seg);
    }
    return iseg;
  }
};

// Text replacement macro ("token pasting") used to define the getters for col_start, col_mid, col_stop.
// The template parameter takes site. The operator () takes zone i patt j. Note that padding is added.
#define DEFINE_SITE_PATTERN_GETTER_OP(NAME) \
    template <typename Site> \
    struct get_site_pattern_##NAME##_op { \
      inline int operator ()(int i, int j) const { \
        const int site = site_traits<Site>::value; \
        const int ref = pattern_col_reference; \
        switch (i) { \
          case 0: \
            switch (j) { \
              case 0: return pattern_##NAME##_zone_0_patt_0[site_to_row_zone_0[site]] + pattern_col_pad_zone_0[site_to_row_zone_0[site]] - ref; \
              case 1: return pattern_##NAME##_zone_0_patt_1[site_to_row_zone_0[site]] + pattern_col_pad_zone_0[site_to_row_zone_0[site]] - ref; \
              case 2: return pattern_##NAME##_zone_0_patt_2[site_to_row_zone_0[site]] + pattern_col_pad_zone_0[site_to_row_zone_0[site]] - ref; \
              case 3: return pattern_##NAME##_zone_0_patt_3[site_to_row_zone_0[site]] + pattern_col_pad_zone_0[site_to_row_zone_0[site]] - ref; \
              case 4: return pattern_##NAME##_zone_0_patt_4[site_to_row_zone_0[site]] + pattern_col_pad_zone_0[site_to_row_zone_0[site]] - ref; \
              case 5: return pattern_##NAME##_zone_0_patt_5[site_to_row_zone_0[site]] + pattern_col_pad_zone_0[site_to_row_zone_0[site]] - ref; \
              case 6: return pattern_##NAME##_zone_0_patt_6[site_to_row_zone_0[site]] + pattern_col_pad_zone_0[site_to_row_zone_0[site]] - ref; \
              default: return 0; \
            } \
          case 1: \
            switch (j) { \
              case 0: return pattern_##NAME##_zone_1_patt_0[site_to_row_zone_1[site]] + pattern_col_pad_zone_1[site_to_row_zone_1[site]] - ref; \
              case 1: return pattern_##NAME##_zone_1_patt_1[site_to_row_zone_1[site]] + pattern_col_pad_zone_1[site_to_row_zone_1[site]] - ref; \
              case 2: return pattern_##NAME##_zone_1_patt_2[site_to_row_zone_1[site]] + pattern_col_pad_zone_1[site_to_row_zone_1[site]] - ref; \
              case 3: return pattern_##NAME##_zone_1_patt_3[site_to_row_zone_1[site]] + pattern_col_pad_zone_1[site_to_row_zone_1[site]] - ref; \
              case 4: return pattern_##NAME##_zone_1_patt_4[site_to_row_zone_1[site]] + pattern_col_pad_zone_1[site_to_row_zone_1[site]] - ref; \
              case 5: return pattern_##NAME##_zone_1_patt_5[site_to_row_zone_1[site]] + pattern_col_pad_zone_1[site_to_row_zone_1[site]] - ref; \
              case 6: return pattern_##NAME##_zone_1_patt_6[site_to_row_zone_1[site]] + pattern_col_pad_zone_1[site_to_row_zone_1[site]] - ref; \
              default: return 0; \
            } \
          case 2: \
            switch (j) { \
              case 0: return pattern_##NAME##_zone_2_patt_0[site_to_row_zone_2[site]] + pattern_col_pad_zone_2[site_to_row_zone_2[site]] - ref; \
              case 1: return pattern_##NAME##_zone_2_patt_1[site_to_row_zone_2[site]] + pattern_col_pad_zone_2[site_to_row_zone_2[site]] - ref; \
              case 2: return pattern_##NAME##_zone_2_patt_2[site_to_row_zone_2[site]] + pattern_col_pad_zone_2[site_to_row_zone_2[site]] - ref; \
              case 3: return pattern_##NAME##_zone_2_patt_3[site_to_row_zone_2[site]] + pattern_col_pad_zone_2[site_to_row_zone_2[site]] - ref; \
              case 4: return pattern_##NAME##_zone_2_patt_4[site_to_row_zone_2[site]] + pattern_col_pad_zone_2[site_to_row_zone_2[site]] - ref; \
              case 5: return pattern_##NAME##_zone_2_patt_5[site_to_row_zone_2[site]] + pattern_col_pad_zone_2[site_to_row_zone_2[site]] - ref; \
              case 6: return pattern_##NAME##_zone_2_patt_6[site_to_row_zone_2[site]] + pattern_col_pad_zone_2[site_to_row_zone_2[site]] - ref; \
              default: return 0; \
            } \
          default: return 0; \
        } \
      } \
    };

DEFINE_SITE_PATTERN_GETTER_OP(col_start)
DEFINE_SITE_PATTERN_GETTER_OP(col_mid)
DEFINE_SITE_PATTERN_GETTER_OP(col_stop)
#undef DEFINE_SITE_PATTERN_GETTER_OP

template <typename Site>
struct get_site_pattern_col_pad_op {
  inline int operator ()(int i) const {
    const int site = site_traits<Site>::value;
    switch (i) {
      case 0: return pattern_col_pad_zone_0[site_to_row_zone_0[site]];
      case 1: return pattern_col_pad_zone_1[site_to_row_zone_1[site]];
      case 2: return pattern_col_pad_zone_2[site_to_row_zone_2[site]];
      default: return 0;
    }
  }
};

// Helper classes to calculate floor(log2(N)) and ceil(log2(N))
// floor_log2<0>::value == 0; ceil_log2<0> == 0;
// floor_log2<1>::value == 0; ceil_log2<1> == 1;
// floor_log2<2>::value == 1; ceil_log2<2> == 1;
// floor_log2<3>::value == 1; ceil_log2<3> == 2;
// floor_log2<4>::value == 2; ceil_log2<4> == 2;
// floor_log2<5>::value == 2; ceil_log2<5> == 3;
// floor_log2<6>::value == 2; ceil_log2<6> == 3;
// floor_log2<7>::value == 2; ceil_log2<7> == 3;
template <unsigned int N>
struct floor_log2 {
  static const unsigned int value = (N > 1) ? (1 + floor_log2<N / 2>::value) : 0;
};

template <> struct floor_log2<0> {
  static const unsigned int value = 0;
};

template <unsigned int N>
struct ceil_log2 {
  static const unsigned int value = (N > 0) ? (1 + floor_log2<N - 1>::value) : 0;
};

// Helper class for argsort
template <typename T, typename U>
struct argsort_pair {
  typedef T first_type;
  typedef U second_type;
  T first;
  U second;
  argsort_pair() : first(), second() {}
  argsort_pair(const T& a, const U& b) : first(a), second(b) {}
  argsort_pair(const argsort_pair<T, U>& p) : first(p.first), second(p.second) {}

  inline bool operator <(const argsort_pair& o) const {

#pragma HLS INLINE

    return second < o.second;
  }

  inline bool operator <=(const argsort_pair& o) const {

#pragma HLS INLINE

    return second <= o.second;
  }

  inline bool operator >(const argsort_pair& o) const {

#pragma HLS INLINE

    return second > o.second;
  }

  inline bool operator >=(const argsort_pair& o) const {

#pragma HLS INLINE

    return second >= o.second;
  }
};

// Helper function to calculate abs difference
template <typename T>
T calc_abs_diff(const T& lhs, const T& rhs) {

#pragma HLS INLINE

  return (lhs >= rhs) ? static_cast<T>(lhs - rhs) : static_cast<T>(rhs - lhs);
}

// Helper function to calculate rectified difference i.e. max(0, x)
template <typename T>
T calc_rectified_diff(const T& lhs, const T& rhs) {

#pragma HLS INLINE

  return (lhs >= rhs) ? static_cast<T>(lhs - rhs) : static_cast<T>(0);
}

// Helper function to calculate signed difference
template <typename T, typename U=typename make_signed<typename make_wider<T>::type>::type>
U calc_signed_diff(const T& lhs, const T& rhs) {

#pragma HLS INLINE

  return (static_cast<U>(lhs) - static_cast<U>(rhs));
}

// Helper function to suppress value if condition is false
template <typename T>
T take_value_if(bool cond, const T& x) {

#pragma HLS INLINE

  return cond ? x : static_cast<T>(0);
}

// Helper function to copy multiple values
template <unsigned int N, typename T>
void copy_n_values(const T in0[N], T out[N]) {

#pragma HLS INLINE

  for (unsigned i = 0; i < N; i++) {

#pragma HLS UNROLL

    out[i] = in0[i];
  }
}

// Helper function to fill multiple values
template <unsigned int N, typename T>
void fill_n_values(T out[N], const T& value) {

#pragma HLS INLINE

  for (unsigned i = 0; i < N; i++) {

#pragma HLS UNROLL

    out[i] = value;
  }
}

template <unsigned int N, typename T_IN, typename T_OUT>
void pack_boolean_values(const T_IN (&in0)[N], T_OUT& out) {
  static_assert(is_same<T_IN, ap_uint<1> >::value, "T_IN type check failed");
  static_assert(is_same<T_OUT, ap_uint<N> >::value, "T_OUT type check failed");

#pragma HLS INLINE

  for (unsigned i = 0; i < N; i++) {

#pragma HLS UNROLL

    out[i] = in0[i];
  }
}

// Helper function to init a lookup table
// Note: If complex assignments are used to initialize a ROM, placing the array initialization
// into a separate function allows a ROM to be inferred.
template <unsigned int N, typename T, typename U>
void init_table_op(T* arr, U op) {
  for (unsigned i = 0; i < N; i++) {
    arr[i] = op(i);
  }
}

// Helper function to init a 2D lookup table
// Note: If complex assignments are used to initialize a ROM, placing the array initialization
// into a separate function allows a ROM to be inferred.
template <unsigned int M, unsigned int N, typename T, typename U>
void init_2d_table_op(T* arr, U op) {
  for (unsigned i = 0; i < M; i++) {
    for (unsigned j = 0; j < N; j++) {
      arr[(i * N) + j] = op(i, j);
    }
  }
}

}  // namespace details

}  // namespace emtf

#endif  // __EMTF_HLSLIB_LAYERS_H__ not defined
