#ifndef __EMTF_HLSLIB_SUPPRESSION_H__
#define __EMTF_HLSLIB_SUPPRESSION_H__

namespace emtf {

// Non-max suppression op
template <int ZONE>
void suppression_op(
    const suppression_in_t suppression_in[N_SUPPRESSION_IN],
    suppression_out_t suppression_out[N_SUPPRESSION_OUT]
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

  // Check assumptions
  static_assert(N_SUPPRESSION_IN == num_img_cols, "N_SUPPRESSION_IN check failed");
  static_assert(N_SUPPRESSION_OUT == num_img_cols, "N_SUPPRESSION_OUT check failed");

  // Loop over columns
  for (pooling_col_t col = 0; col < num_img_cols; col++) {
    const bool leftmost = (col == 0);
    const bool rightmost = (col == num_img_cols - 1);
    const suppression_in_t zero_val = 0;

    suppression_in_t ql = leftmost ? zero_val : suppression_in[col - 1];
    suppression_in_t qc = suppression_in[col];
    suppression_in_t qr = rightmost ? zero_val : suppression_in[col + 1];

    ql >>= pooling_pattnum_t::width;
    qc >>= pooling_pattnum_t::width;
    qr >>= pooling_pattnum_t::width;

    bool suppress = (qc <= ql || qc < qr);

    suppression_out[col] = suppress ? zero_val : suppression_in[col];
  }
}


// _____________________________________________________________________________
// Entry point

template <int ZONE>
void suppression_layer(
    const suppression_in_t suppression_in[N_SUPPRESSION_IN],
    suppression_out_t suppression_out[N_SUPPRESSION_OUT]
) {

#pragma HLS PIPELINE II=1

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INLINE region

  suppression_op<ZONE>(suppression_in, suppression_out);
}

}  // namespace emtf

#endif  // __EMTF_HLSLIB_SUPPRESSION_H__ not defined
