#ifndef __EMTF_HLSLIB_SUPPRESSION_H__
#define __EMTF_HLSLIB_SUPPRESSION_H__

namespace emtf {

// _____________________________________________________________________________
// Non-max suppression op

template <typename Zone>
void suppression_op(
    const suppression_in_t suppression_in[suppression_config::n_in],
    suppression_out_t suppression_out[suppression_config::n_out]
) {

#pragma HLS PIPELINE II=suppression_config::target_ii

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE

  typedef pooling_activation_t data_t;

  constexpr unsigned int bits_lo = 0;
  constexpr unsigned int bits_hi = (data_t::width - 1);

  // Loop over columns
  LOOP_COL: for (unsigned col = 0; col < num_emtf_img_cols; col++) {

#pragma HLS UNROLL

    const bool leftmost = (col == 0);
    const bool rightmost = (col == num_emtf_img_cols - 1);

    // Take the activation value
    const data_t ql = leftmost ? data_t(0) : suppression_in[col - 1].range(bits_hi, bits_lo);
    const data_t qc = suppression_in[col].range(bits_hi, bits_lo);
    const data_t qr = rightmost ? data_t(0) : suppression_in[col + 1].range(bits_hi, bits_lo);

    // Suppress if not local maximum
    const bool suppress = (qc <= ql || qc < qr);

    // Output
    suppression_out[col] = suppress ? suppression_out_t(0) : suppression_in[col];
  }  // end loop over columns
}

// _____________________________________________________________________________
// Entry point

template <typename Zone>
void suppression_layer(
    const suppression_in_t suppression_in[suppression_config::n_in],
    suppression_out_t suppression_out[suppression_config::n_out]
) {

#pragma HLS PIPELINE II=suppression_config::target_ii

#pragma HLS INTERFACE ap_ctrl_none port=return

  // Check assumptions
  static_assert(suppression_config::n_in == num_emtf_img_cols, "suppression_config::n_in check failed");
  static_assert(suppression_config::n_out == num_emtf_img_cols, "suppression_config::n_out check failed");

  suppression_op<Zone>(suppression_in, suppression_out);
}

}  // namespace emtf

#endif  // __EMTF_HLSLIB_SUPPRESSION_H__ not defined
