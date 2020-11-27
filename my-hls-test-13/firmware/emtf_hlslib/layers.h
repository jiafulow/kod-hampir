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
  static const int n_in = num_emtf_chambers * num_emtf_segments;
  static const int n_out = num_emtf_tracks * num_emtf_features;
  static const int target_ii = 1;
};

// _____________________________________________________________________________
// Layer configs

struct zoning_config {
  static const int n_in = 0;
  static const int n_out = num_emtf_img_rows;
  static const int target_ii = 1;
};

struct pooling_config {
  static const int n_in = zoning_config::n_out;
  static const int n_out = num_emtf_img_cols;
  static const int target_ii = 1;
};

struct suppression_config {
  static const int n_in = pooling_config::n_out;
  static const int n_out = n_in;
  static const int target_ii = 1;
};

struct zonesorting_config {
  static const int n_in = suppression_config::n_out;
  static const int n_out = num_emtf_tracks;
  static const int target_ii = 1;
};

struct zonemerging_config {
  static const int n_in = zonesorting_config::n_out;
  static const int n_out = n_in;
  static const int target_ii = 1;
};

struct trkbuilding_config {
  static const int n_in = zonemerging_config::n_out;
  static const int n_out = n_in;
  static const int target_ii = 1;
};

struct duperemoval_config {
  static const int n_in = trkbuilding_config::n_out;
  static const int n_out = n_in;
  static const int target_ii = 1;
};

// _____________________________________________________________________________
// Utilities

// Chamber tags
struct m_10deg_chamber_tag {};
struct m_20deg_chamber_tag {};
struct m_20deg_ext_chamber_tag {};

// Zone tags
struct m_zone_0_tag {};
struct m_zone_1_tag {};
struct m_zone_2_tag {};
struct m_zone_any_tag {};

// Timezone tags
struct m_timezone_0_tag {};
struct m_timezone_1_tag {};
struct m_timezone_2_tag {};
struct m_timezone_any_tag {};

// Row tags
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
struct row_chamber_category_traits {};

template <> struct row_chamber_category_traits<m_zone_0_row_0_tag> { typedef m_10deg_chamber_tag chamber_category; };
template <> struct row_chamber_category_traits<m_zone_0_row_1_tag> { typedef m_10deg_chamber_tag chamber_category; };
template <> struct row_chamber_category_traits<m_zone_0_row_2_tag> { typedef m_10deg_chamber_tag chamber_category; };
template <> struct row_chamber_category_traits<m_zone_0_row_3_tag> { typedef m_20deg_chamber_tag chamber_category; };
template <> struct row_chamber_category_traits<m_zone_0_row_4_tag> { typedef m_20deg_chamber_tag chamber_category; };
template <> struct row_chamber_category_traits<m_zone_0_row_5_tag> { typedef m_20deg_chamber_tag chamber_category; };
template <> struct row_chamber_category_traits<m_zone_0_row_6_tag> { typedef m_20deg_chamber_tag chamber_category; };
template <> struct row_chamber_category_traits<m_zone_0_row_7_0_tag> { typedef m_20deg_chamber_tag chamber_category; };
template <> struct row_chamber_category_traits<m_zone_0_row_7_1_tag> { typedef m_20deg_chamber_tag chamber_category; };
//
template <> struct row_chamber_category_traits<m_zone_1_row_0_tag> { typedef m_10deg_chamber_tag chamber_category; };
template <> struct row_chamber_category_traits<m_zone_1_row_1_tag> { typedef m_10deg_chamber_tag chamber_category; };
template <> struct row_chamber_category_traits<m_zone_1_row_2_0_tag> { typedef m_10deg_chamber_tag chamber_category; };
template <> struct row_chamber_category_traits<m_zone_1_row_2_1_tag> { typedef m_10deg_chamber_tag chamber_category; };
template <> struct row_chamber_category_traits<m_zone_1_row_3_tag> { typedef m_20deg_chamber_tag chamber_category; };
template <> struct row_chamber_category_traits<m_zone_1_row_4_tag> { typedef m_20deg_chamber_tag chamber_category; };
template <> struct row_chamber_category_traits<m_zone_1_row_5_tag> { typedef m_20deg_ext_chamber_tag chamber_category; };
template <> struct row_chamber_category_traits<m_zone_1_row_6_tag> { typedef m_20deg_ext_chamber_tag chamber_category; };
template <> struct row_chamber_category_traits<m_zone_1_row_7_0_tag> { typedef m_20deg_ext_chamber_tag chamber_category; };
template <> struct row_chamber_category_traits<m_zone_1_row_7_1_tag> { typedef m_20deg_ext_chamber_tag chamber_category; };
//
template <> struct row_chamber_category_traits<m_zone_2_row_0_tag> { typedef m_10deg_chamber_tag chamber_category; };
template <> struct row_chamber_category_traits<m_zone_2_row_1_tag> { typedef m_10deg_chamber_tag chamber_category; };
template <> struct row_chamber_category_traits<m_zone_2_row_2_tag> { typedef m_10deg_chamber_tag chamber_category; };
template <> struct row_chamber_category_traits<m_zone_2_row_3_tag> { typedef m_10deg_chamber_tag chamber_category; };
template <> struct row_chamber_category_traits<m_zone_2_row_4_tag> { typedef m_10deg_chamber_tag chamber_category; };
template <> struct row_chamber_category_traits<m_zone_2_row_5_tag> { typedef m_10deg_chamber_tag chamber_category; };
template <> struct row_chamber_category_traits<m_zone_2_row_6_tag> { typedef m_10deg_chamber_tag chamber_category; };
template <> struct row_chamber_category_traits<m_zone_2_row_7_tag> { typedef m_10deg_chamber_tag chamber_category; };

// Getters
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

template <> struct get_chamber_id_op<m_zone_2_row_0_tag> { inline int operator ()(int i) const { return chamber_id_zone_2_row_0[i]; } };
template <> struct get_chamber_id_op<m_zone_2_row_1_tag> { inline int operator ()(int i) const { return chamber_id_zone_2_row_1[i]; } };
template <> struct get_chamber_id_op<m_zone_2_row_2_tag> { inline int operator ()(int i) const { return chamber_id_zone_2_row_2[i]; } };
template <> struct get_chamber_id_op<m_zone_2_row_3_tag> { inline int operator ()(int i) const { return chamber_id_zone_2_row_3[i]; } };
template <> struct get_chamber_id_op<m_zone_2_row_4_tag> { inline int operator ()(int i) const { return chamber_id_zone_2_row_4[i]; } };
template <> struct get_chamber_id_op<m_zone_2_row_5_tag> { inline int operator ()(int i) const { return chamber_id_zone_2_row_5[i]; } };
template <> struct get_chamber_id_op<m_zone_2_row_6_tag> { inline int operator ()(int i) const { return chamber_id_zone_2_row_6[i]; } };
template <> struct get_chamber_id_op<m_zone_2_row_7_tag> { inline int operator ()(int i) const { return chamber_id_zone_2_row_7[i]; } };

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

// Function to init table
struct init_table_op {
  template <typename T, int N, class U>
  inline void operator()(T (&arr)[N], U op) const {
    for (int i = 0; i < N; i++) {
      arr[i] = op(i);
    }
  }
};

// Function to init 2D table
struct init_2d_table_op {
  template <typename T, int M, int N, class U>
  inline void operator()(T (&arr)[M][N], U op) const {
    for (int i = 0; i < M; i++) {
      for (int j = 0; j < N; j++) {
        arr[i][j] = op(i, j);
      }
    }
  }
};

}  // namespace details

}  // namespace emtf

#endif  // __EMTF_HLSLIB_LAYERS_H__ not defined
