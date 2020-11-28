#ifndef __EMTF_HLSLIB_ZONING_H__
#define __EMTF_HLSLIB_ZONING_H__

namespace emtf {

// _____________________________________________________________________________
// Perform loop over chambers and all the segments in the chambers.
// Fill the chamber image for each chamber, then join all the chamber images.

template <typename Zone, typename Timezone, typename Row>
void zoning_row_op(
    const emtf_phi_t emtf_phi[model_config::n_in],
    const seg_zones_t seg_zones[model_config::n_in],
    const seg_tzones_t seg_tzones[model_config::n_in],
    const seg_valid_t seg_valid[model_config::n_in],
    zoning_out_t& zoning_out_row_i
) {

#pragma HLS PIPELINE II=zoning_config::target_ii

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE

  typedef typename details::row_chamber_category_traits<Row>::chamber_category chamber_category;
  const int N = details::num_chambers_traits<chamber_category>::value;
  const int the_zone = details::zone_traits<Zone>::value;
  const int the_tzone = details::timezone_traits<Timezone>::value;

  int chamber_id_table[N];
  details::init_table_op(chamber_id_table, details::get_chamber_id_op<Row>());

  int chamber_ph_init_table[N];
  details::init_table_op(chamber_ph_init_table, details::get_chamber_ph_init_op<chamber_category>());

  int chamber_ph_cover_table[N];
  details::init_table_op(chamber_ph_cover_table, details::get_chamber_ph_cover_op<chamber_category>());

  typedef ap_uint<details::chamber_img_bw> chamber_img_t;
  typedef ap_uint<details::chamber_img_joined_bw> chamber_img_joined_t;

  chamber_img_joined_t chamber_img_joined = 0;  // init as zero

zoning_row_op_loop:

  // Loop over chambers
  for (unsigned i = 0; i < N; i++) {

#pragma HLS UNROLL

    //std::cout << "[DEBUG] z " << ZONE << " r " << ROW << " chamber: " << chambers[i] << " ph_init: " << chamber_ph_init_table[i] << std::endl;

    chamber_img_t chamber_img = 0;  // init as zero

zoning_row_op_inner_loop:

    // Loop over segments
    for (unsigned j = 0; j < num_emtf_segments; j++) {

#pragma HLS UNROLL

      const zoning_seg_t iseg = (chamber_id_table[i] * num_emtf_segments) + j;
      assert(chamber_id_table[i] < num_emtf_chambers);
      assert(iseg < (num_emtf_chambers * num_emtf_segments));

      // Fill the chamber image. A pixel at (row, col) is set to 1 if a segment is present.
      // Use condition: (valid && is_same_zone && is_same_timezone)
      if (
          (seg_valid[iseg] == 1) and \
          (seg_zones[iseg][(num_emtf_zones - 1) - the_zone] == 1) and \
          (seg_tzones[iseg][(num_emtf_timezones - 1) - the_tzone] == 1)
      ) {
        // truncate last 4 bits (i.e. divide by 16), subtract offset
        assert((emtf_phi[iseg] >> 4) >= chamber_ph_init_table[i]);
        const zoning_col_t offset = chamber_ph_init_table[i];
        const zoning_col_t col = (emtf_phi[iseg] >> 4) - offset;

        //std::cout << "[DEBUG] chamber: " << chambers[i] << " segment: " << j << " emtf_phi: " << emtf_phi[iseg] << " col: " << col << " offset: " << offset << std::endl;

        chamber_img.set(col, 1);  // set bit to 1
      }
    }  // end loop over segments

    // Join chamber images
    const zoning_col_t col_start_rhs = 0;
    const zoning_col_t col_stop_rhs = (chamber_ph_cover_table[i] - chamber_ph_init_table[i]) - 1;
    const zoning_col_t col_start_lhs = chamber_ph_init_table[i];
    const zoning_col_t col_stop_lhs = col_start_lhs + col_stop_rhs - col_start_rhs;

    //std::cout << "[DEBUG] start_l: " << col_start_lhs << " stop_l: " << col_stop_lhs << " start_r: " << col_start_rhs << " stop_r: " << col_stop_rhs << std::endl;

    // OR combined
    assert((col_stop_lhs - col_start_lhs) == (col_stop_rhs - col_start_rhs));
    chamber_img_joined.range(col_stop_lhs, col_start_lhs) = (
        chamber_img_joined.range(col_stop_lhs, col_start_lhs) | chamber_img.range(col_stop_rhs, col_start_rhs)
    );
  }  // end loop over chambers

  zoning_out_row_i = 0;  // init as zero

  // Adjust the size of chamber_img_joined
  const zoning_col_t col_start_rhs = details::chamber_img_joined_col_start;
  const zoning_col_t col_stop_rhs = details::chamber_img_joined_col_stop;
  const zoning_col_t col_start_lhs = 0;
  const zoning_col_t col_stop_lhs = (zoning_out_t::width - 1);

  //std::cout << "[DEBUG] start_l: " << col_start_lhs << " stop_l: " << col_stop_lhs << " start_r: " << col_start_rhs << " stop_r: " << col_stop_rhs << std::endl;

  // Take selected columns of chamber_img_joined
  assert((col_stop_lhs - col_start_lhs) == (col_stop_rhs - col_start_rhs));
  zoning_out_row_i = chamber_img_joined.range(col_stop_rhs, col_start_rhs);
}

// _____________________________________________________________________________
// Zoning op

// Only enabled for Zone 0
template <typename Zone, typename Timezone, typename enable_if<is_same<Zone, m_zone_0_tag>::value, bool>::type = true>
void zoning_op(
    const emtf_phi_t emtf_phi[model_config::n_in],
    const seg_zones_t seg_zones[model_config::n_in],
    const seg_tzones_t seg_tzones[model_config::n_in],
    const seg_valid_t seg_valid[model_config::n_in],
    zoning_out_t zoning_out[zoning_config::n_out]
) {

#pragma HLS PIPELINE II=zoning_config::target_ii

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE

  zoning_out_t zoning_out_row_7_0;
  zoning_out_t zoning_out_row_7_1;

  // Loop over the rows manually
  zoning_row_op<Zone, Timezone, m_zone_0_row_0_tag>(emtf_phi, seg_zones, seg_tzones, seg_valid, zoning_out[0]);
  zoning_row_op<Zone, Timezone, m_zone_0_row_1_tag>(emtf_phi, seg_zones, seg_tzones, seg_valid, zoning_out[1]);
  zoning_row_op<Zone, Timezone, m_zone_0_row_2_tag>(emtf_phi, seg_zones, seg_tzones, seg_valid, zoning_out[2]);
  zoning_row_op<Zone, Timezone, m_zone_0_row_3_tag>(emtf_phi, seg_zones, seg_tzones, seg_valid, zoning_out[3]);
  zoning_row_op<Zone, Timezone, m_zone_0_row_4_tag>(emtf_phi, seg_zones, seg_tzones, seg_valid, zoning_out[4]);
  zoning_row_op<Zone, Timezone, m_zone_0_row_5_tag>(emtf_phi, seg_zones, seg_tzones, seg_valid, zoning_out[5]);
  zoning_row_op<Zone, Timezone, m_zone_0_row_6_tag>(emtf_phi, seg_zones, seg_tzones, seg_valid, zoning_out[6]);
  zoning_row_op<Zone, Timezone, m_zone_0_row_7_0_tag>(emtf_phi, seg_zones, seg_tzones, seg_valid, zoning_out_row_7_0);
  zoning_row_op<Zone, Timezone, m_zone_0_row_7_1_tag>(emtf_phi, seg_zones, seg_tzones, seg_valid, zoning_out_row_7_1);

  // Combine certain rows
  zoning_out[7] = (zoning_out_row_7_0 | zoning_out_row_7_1);
}

// Only enabled for Zone 1
template <typename Zone, typename Timezone, typename enable_if<is_same<Zone, m_zone_1_tag>::value, bool>::type = true>
void zoning_op(
    const emtf_phi_t emtf_phi[model_config::n_in],
    const seg_zones_t seg_zones[model_config::n_in],
    const seg_tzones_t seg_tzones[model_config::n_in],
    const seg_valid_t seg_valid[model_config::n_in],
    zoning_out_t zoning_out[zoning_config::n_out]
) {

#pragma HLS PIPELINE II=zoning_config::target_ii

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE

  zoning_out_t zoning_out_row_2_0;
  zoning_out_t zoning_out_row_2_1;
  zoning_out_t zoning_out_row_7_0;
  zoning_out_t zoning_out_row_7_1;

  // Loop over the rows manually
  zoning_row_op<Zone, Timezone, m_zone_1_row_0_tag>(emtf_phi, seg_zones, seg_tzones, seg_valid, zoning_out[0]);
  zoning_row_op<Zone, Timezone, m_zone_1_row_1_tag>(emtf_phi, seg_zones, seg_tzones, seg_valid, zoning_out[1]);
  zoning_row_op<Zone, Timezone, m_zone_1_row_2_0_tag>(emtf_phi, seg_zones, seg_tzones, seg_valid, zoning_out_row_2_0);
  zoning_row_op<Zone, Timezone, m_zone_1_row_2_1_tag>(emtf_phi, seg_zones, seg_tzones, seg_valid, zoning_out_row_2_1);
  zoning_row_op<Zone, Timezone, m_zone_1_row_3_tag>(emtf_phi, seg_zones, seg_tzones, seg_valid, zoning_out[3]);
  zoning_row_op<Zone, Timezone, m_zone_1_row_4_tag>(emtf_phi, seg_zones, seg_tzones, seg_valid, zoning_out[4]);
  zoning_row_op<Zone, Timezone, m_zone_1_row_5_tag>(emtf_phi, seg_zones, seg_tzones, seg_valid, zoning_out[5]);
  zoning_row_op<Zone, Timezone, m_zone_1_row_6_tag>(emtf_phi, seg_zones, seg_tzones, seg_valid, zoning_out[6]);
  zoning_row_op<Zone, Timezone, m_zone_1_row_7_0_tag>(emtf_phi, seg_zones, seg_tzones, seg_valid, zoning_out_row_7_0);
  zoning_row_op<Zone, Timezone, m_zone_1_row_7_1_tag>(emtf_phi, seg_zones, seg_tzones, seg_valid, zoning_out_row_7_1);

  // Combine certain rows
  zoning_out[2] = (zoning_out_row_2_0 | zoning_out_row_2_1);
  zoning_out[7] = (zoning_out_row_7_0 | zoning_out_row_7_1);
}

// Only enabled for Zone 2
template <typename Zone, typename Timezone, typename enable_if<is_same<Zone, m_zone_2_tag>::value, bool>::type = true>
void zoning_op(
    const emtf_phi_t emtf_phi[model_config::n_in],
    const seg_zones_t seg_zones[model_config::n_in],
    const seg_tzones_t seg_tzones[model_config::n_in],
    const seg_valid_t seg_valid[model_config::n_in],
    zoning_out_t zoning_out[zoning_config::n_out]
) {

#pragma HLS PIPELINE II=zoning_config::target_ii

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE

  // Loop over the rows manually
  zoning_row_op<Zone, Timezone, m_zone_2_row_0_tag>(emtf_phi, seg_zones, seg_tzones, seg_valid, zoning_out[0]);
  zoning_row_op<Zone, Timezone, m_zone_2_row_1_tag>(emtf_phi, seg_zones, seg_tzones, seg_valid, zoning_out[1]);
  zoning_row_op<Zone, Timezone, m_zone_2_row_2_tag>(emtf_phi, seg_zones, seg_tzones, seg_valid, zoning_out[2]);
  zoning_row_op<Zone, Timezone, m_zone_2_row_3_tag>(emtf_phi, seg_zones, seg_tzones, seg_valid, zoning_out[3]);
  zoning_row_op<Zone, Timezone, m_zone_2_row_4_tag>(emtf_phi, seg_zones, seg_tzones, seg_valid, zoning_out[4]);
  zoning_row_op<Zone, Timezone, m_zone_2_row_5_tag>(emtf_phi, seg_zones, seg_tzones, seg_valid, zoning_out[5]);
  zoning_row_op<Zone, Timezone, m_zone_2_row_6_tag>(emtf_phi, seg_zones, seg_tzones, seg_valid, zoning_out[6]);
  zoning_row_op<Zone, Timezone, m_zone_2_row_7_tag>(emtf_phi, seg_zones, seg_tzones, seg_valid, zoning_out[7]);
}

// _____________________________________________________________________________
// Entry point

template <typename Zone>
void zoning_layer(
    const emtf_phi_t emtf_phi[model_config::n_in],
    const seg_zones_t seg_zones[model_config::n_in],
    const seg_tzones_t seg_tzones[model_config::n_in],
    const seg_valid_t seg_valid[model_config::n_in],
    zoning_out_t zoning_out[zoning_config::n_out]
) {

#pragma HLS PIPELINE II=zoning_config::target_ii

#pragma HLS INTERFACE ap_ctrl_none port=return

  // Check assumptions
  static_assert(zoning_config::n_out == num_emtf_img_rows, "zoning_config::n_out check failed");
  static_assert(num_emtf_img_rows == 8, "num_emtf_img_rows must be 8");
  static_assert(num_emtf_img_cols == 288, "num_emtf_img_cols must be 288");

  typedef m_timezone_0_tag Timezone;  // default timezone

  zoning_op<Zone, Timezone>(emtf_phi, seg_zones, seg_tzones, seg_valid, zoning_out);
}

}  // namespace emtf

#endif  // __EMTF_HLSLIB_ZONING_H__ not defined
