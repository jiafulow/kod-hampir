#ifndef __EMTF_HLSLIB_POOLING_H__
#define __EMTF_HLSLIB_POOLING_H__

#include <type_traits>

#include "ap_int.h"


namespace emtf {

// Definition of a pattern.
// 8 rows, 3 params per row. The params are (low, med, hi) of the pattern window.
template <int ZONE, int PATT>
struct Pattern {
  static constexpr int zone = ZONE;
  static constexpr int patt = PATT;
  static constexpr int col_offset = 55;  // offset used to encode the pattern window
  static constexpr int rows = 8;
  static constexpr int params = 3;  // per row
  static constexpr int size = rows * params;
  static const int data[size];    // need to be initialized before use
  static const int padding;       // need to be initialized before use
  static const int straightness;  // need to be initialized before use
};

// Hardcoded pattern definitions
template <>
constexpr const int Pattern<0, 0>::data[size] =  {
  21, 36, 46, 23, 35, 43, 29, 41, 49, 52, 54, 55, 54, 55, 56, 52, 57, 62,
  50, 57, 63, 46, 57, 65
};
template <>
constexpr const int Pattern<0, 1>::data[size] =  {
  35, 44, 50, 35, 44, 48, 39, 47, 51, 53, 54, 55, 54, 55, 56, 54, 56, 59,
  54, 57, 60, 53, 57, 61
};
template <>
constexpr const int Pattern<0, 2>::data[size] =  {
  43, 51, 53, 43, 51, 53, 46, 52, 54, 53, 55, 56, 54, 55, 56, 55, 56, 57,
  55, 56, 57, 55, 56, 57
};
template <>
constexpr const int Pattern<0, 3>::data[size] =  {
  51, 55, 59, 51, 55, 59, 52, 55, 58, 54, 55, 56, 54, 55, 56, 54, 55, 56,
  54, 55, 56, 54, 55, 56
};
template <>
constexpr const int Pattern<0, 4>::data[size] =  {
  57, 59, 67, 57, 59, 67, 56, 58, 64, 54, 55, 57, 54, 55, 56, 53, 54, 55,
  53, 54, 55, 53, 54, 55
};
template <>
constexpr const int Pattern<0, 5>::data[size] =  {
  60, 66, 75, 62, 66, 75, 59, 63, 71, 55, 56, 57, 54, 55, 56, 51, 54, 56,
  50, 53, 56, 49, 53, 57
};
template <>
constexpr const int Pattern<0, 6>::data[size] =  {
  64, 74, 89, 67, 75, 87, 61, 69, 81, 55, 56, 58, 54, 55, 56, 48, 53, 58,
  47, 53, 60, 45, 53, 64
};

template <>
const int Pattern<0, 0>::padding = 34;
template <>
const int Pattern<0, 1>::padding = 20;
template <>
const int Pattern<0, 2>::padding = 12;
template <>
const int Pattern<0, 3>::padding = 4;
template <>
const int Pattern<0, 4>::padding = 12;
template <>
const int Pattern<0, 5>::padding = 20;
template <>
const int Pattern<0, 6>::padding = 34;

template <>
const int Pattern<0, 0>::straightness = 1;
template <>
const int Pattern<0, 1>::straightness = 3;
template <>
const int Pattern<0, 2>::straightness = 5;
template <>
const int Pattern<0, 3>::straightness = 7;
template <>
const int Pattern<0, 4>::straightness = 5;
template <>
const int Pattern<0, 5>::straightness = 3;
template <>
const int Pattern<0, 6>::straightness = 1;

// TODO: move the pattern definitions somewhere else?


// _________________________________________________________________________________________________
// Perform ROI pooling - pool from the (low, hi)-range of each row in the input image.

template <int ROWS, int COLS, int ZONE, int PATT, int ROW>
void roi_pooling_per_row(
    const ap_uint<COLS>& input,
    ap_uint<ROWS>& output,
    const int col
) {
#pragma HLS INLINE

  typedef Pattern<ZONE, PATT> pattern_t;
  constexpr int START = pattern_t::data[ROW * 3 + 0] - pattern_t::col_offset;
  constexpr int STOP = pattern_t::data[ROW * 3 + 2] - pattern_t::col_offset;
  constexpr int PAD_START = START < 0 ? -START : 1;
  constexpr int PAD_STOP = STOP > 0 ? STOP : 1;
  constexpr int COLS_W_PADDING = COLS + PAD_START + PAD_STOP;

  // Check assumptions
  static_assert(STOP > START, "pattern window must be non zero");
  static_assert(PAD_START > 0 && PAD_STOP > 0, "padding must be non negative");

  const int start = col + PAD_START + START;
  const int stop = col + PAD_START + STOP;
  emtf_assert(start >= 0 && stop >= 0 && start < COLS_W_PADDING && stop < COLS_W_PADDING);

  ap_uint<COLS_W_PADDING> tmp_input = (ap_uint<PAD_STOP>(0), input, ap_uint<PAD_START>(0));  // add padding to input
  output[(ROWS - 1) - ROW] = tmp_input.range(stop, start);  // CUIDADO: bit order from the test bench is flipped
  return;
}

template <int ROWS, int COLS, int ZONE, int PATT>
void roi_pooling_all_rows(
    const ap_uint<COLS> buf[ROWS],
    ap_uint<ROWS>& output,
    const int col
) {
#pragma HLS INLINE

  typedef Pattern<ZONE, PATT> pattern_t;

  // Check assumptions
  static_assert(ROWS == 8, "num_rows must be 8");
  static_assert(pattern_t::rows == ROWS, "pattern data must have rows equal to num_rows");
  static_assert(pattern_t::size == ROWS * 3, "pattern data must have size equal to num_rows * 3");

  // Loop through the rows (unrolled)
  roi_pooling_per_row<ROWS, COLS, ZONE, PATT, 0>(buf[0], output, col);
  roi_pooling_per_row<ROWS, COLS, ZONE, PATT, 1>(buf[1], output, col);
  roi_pooling_per_row<ROWS, COLS, ZONE, PATT, 2>(buf[2], output, col);
  roi_pooling_per_row<ROWS, COLS, ZONE, PATT, 3>(buf[3], output, col);
  roi_pooling_per_row<ROWS, COLS, ZONE, PATT, 4>(buf[4], output, col);
  roi_pooling_per_row<ROWS, COLS, ZONE, PATT, 5>(buf[5], output, col);
  roi_pooling_per_row<ROWS, COLS, ZONE, PATT, 6>(buf[6], output, col);
  roi_pooling_per_row<ROWS, COLS, ZONE, PATT, 7>(buf[7], output, col);
  return;
}

template <int ROWS, int COLS, int PATTERNS, int ZONE>
void roi_pooling_all_patterns(
  const ap_uint<COLS> buf[ROWS],
  ap_uint<ROWS> outputs[COLS * PATTERNS],
  const int col
) {
#pragma HLS INLINE

  // Check assumptions
  static_assert(PATTERNS == 7, "num_patterns must be 7");

  // Loop through the patterns (unrolled)
  roi_pooling_all_rows<ROWS, COLS, ZONE, 0>(buf, outputs[col * PATTERNS + 0], col);
  roi_pooling_all_rows<ROWS, COLS, ZONE, 1>(buf, outputs[col * PATTERNS + 1], col);
  roi_pooling_all_rows<ROWS, COLS, ZONE, 2>(buf, outputs[col * PATTERNS + 2], col);
  roi_pooling_all_rows<ROWS, COLS, ZONE, 3>(buf, outputs[col * PATTERNS + 3], col);
  roi_pooling_all_rows<ROWS, COLS, ZONE, 4>(buf, outputs[col * PATTERNS + 4], col);
  roi_pooling_all_rows<ROWS, COLS, ZONE, 5>(buf, outputs[col * PATTERNS + 5], col);
  roi_pooling_all_rows<ROWS, COLS, ZONE, 6>(buf, outputs[col * PATTERNS + 6], col);
  return;
}

template <int ROWS, int COLS, int PATTERNS, int ZONE>
void roi_pooling(
    const ap_uint<ROWS> inputs[COLS],
    ap_uint<ROWS> outputs[COLS * PATTERNS]
) {
//#pragma HLS INLINE
#pragma HLS PIPELINE II=1

  // Create local buffer
  typedef ap_uint<COLS> buffer_t;
  buffer_t buf[ROWS];
#pragma HLS ARRAY_PARTITION variable=buf complete dim=0

  // Initialize local buffer
  pool_buf_loop : for (int row = 0; row < ROWS; row++) {
    pool_buf_loop_inner : for (int col = 0; col < COLS; col++) {
      buf[row][col] = inputs[col][(ROWS - 1) - row];  // CUIDADO: bit order from the test bench is flipped
    }
  }

  // Do pooling
  pool_loop : for (int col = 0; col < COLS; col++) {
    roi_pooling_all_patterns<ROWS, COLS, PATTERNS, ZONE>(buf, outputs, col);
  }
  return;
}

// _________________________________________________________________________________________________
// Perform non-maximum suppression - compare every pattern with its neighbors, if it has lower
// quality, kill it.

template <int ROWS, int COLS, int PATTERNS, int SCORES, int ZONE>
void nonmax_suppression(
    const ap_uint<ROWS> inputs[COLS * PATTERNS],
    ap_uint<SCORES> outputs[COLS * PATTERNS]
) {
#pragma HLS INLINE

  typedef ap_uint<SCORES> score_t;  // full score
  constexpr int COMPRESSED_SCORES = 8;
  typedef ap_uint<COMPRESSED_SCORES> zscore_t;  // compressed score
  typedef ap_uint<ROWS> rowmask_t;
  constexpr int MAX_STRAIGHTNESS = 7;
  typedef ap_uint<LOG2<MAX_STRAIGHTNESS>::cvalue> straightness_t;
  typedef ap_uint<LOG2<PATTERNS>::cvalue> pattnum_t;

  // Check assumptions
  static_assert(PATTERNS == 7, "num_patterns must be 7");
  static_assert(rowmask_t::width == 8, "rowmask must be 8-bit");
  static_assert(straightness_t::width == 3, "straightness must be 3-bit");
  static_assert(pattnum_t::width == 3, "pattern number must be 3-bit");
  static_assert(score_t::width == ROWS + pattnum_t::width, "score must be (num_rows + 3)-bit");

  // Score definitions (a.k.a. quality code)
  //
  // There are two scores. "Full" scores are sent out, while "compressed" scores are used
  // for sorting and canceling in this function.
  //
  // - Full score is simply concatenation of rowmask + pattern number. Currently, it is 11-bit,
  //   as rowmask is 8-bit and pattern number is 3-bit (for num_patterns = 7)
  //
  // - Compressed score is defined by rowmask and straightness code. Straightness code
  //   is obtained from the pattern number. Currently, compressed score is 8-bit. See below.
  //
  // zone | rowmask (r)                                     | straightness (s)
  //      | b7    b6    b5    b4    b3    b2    b1    b0    | b2    b1    b0
  // -----|-------------------------------------------------|-------------------
  // 0    | ME0   GE1/1 ME1/1 GE2/1 ME2/1 ME3/1 RE3/1 ME4/1 | straightness_3b
  // 1    | GE1/1 ME1/1 ME1/2 GE2/1 ME2/1 ME3/1 RE3/1 ME4/1 | straightness_3b
  // 2    | ME1/2 RE1/2 RE2/2 ME2/2 ME3/2 RE3/2 ME4/2 RE4/2 | straightness_3b
  //
  // zone | compressed score (z)
  //      | b7    b6    b5    b4    b3    b2    b1    b0
  // -----|-------------------------------------------------
  // 0    | ME2/1 GE2/1 ME3/1 ME4/1 ME1/1 ME0   straightness_2b
  //      |             RE3/1             GE1/1
  // 1    | ME2/1 GE2/1 ME3/1 ME4/1 ME1/2 ME1/1 straightness_2b
  //      |             RE3/1             GE1/1
  // 2    | ME2/2 RE2/2 ME3/2 ME4/2 ME1/2 RE1/2 straightness_2b
  //      |             RE3/2 RE4/2
  //
  // Mapping from r & s -> z
  //
  // zone | compressed score
  //      | b7    b6    b5    b4    b3    b2    b1    b0
  // -----|-------------------------------------------------
  // 0    | r_b3  r_b4  r_b2  r_b0  r_b5  r_b7  s_b2  s_b1
  //      |             r_b1              r_b6
  // 1    | r_b3  r_b4  r_b2  r_b0  r_b5  r_b6  s_b2  s_b1
  //      |             r_b1              r_b7
  // 2    | r_b4  r_b5  r_b3  r_b1  r_b7  r_b6  s_b2  s_b1
  //      |             r_b2  r_b0

  auto get_score = [](const rowmask_t r, const pattnum_t p) -> score_t {
    return (r, p);
  };

  auto get_zscore = [](const rowmask_t r, const straightness_t s) -> zscore_t {
#pragma HLS INLINE
    switch(ZONE) {
      case 0 : return (r[3], r[4], (r[2] | r[1]), r[0], r[5], (r[7] | r[6]), s[2], s[1]);
      case 1 : return (r[3], r[4], (r[2] | r[1]), r[0], r[5], (r[6] | r[7]), s[2], s[1]);
      case 2 : return (r[4], r[5], (r[3] | r[2]), (r[1] | r[0]), r[7], r[6], s[2], s[1]);
      default : return 0;
    }
  };

  constexpr straightness_t stght[PATTERNS] = {
    Pattern<ZONE, 0>::straightness,
    Pattern<ZONE, 1>::straightness,
    Pattern<ZONE, 2>::straightness,
    Pattern<ZONE, 3>::straightness,
    Pattern<ZONE, 4>::straightness,
    Pattern<ZONE, 5>::straightness,
    Pattern<ZONE, 6>::straightness,
  };

  max_select_loop : for (int col = 0; col < COLS; col++) {
#pragma HLS PIPELINE II=1
    zscore_t z_patt0 = get_zscore(inputs[col * PATTERNS + 0], stght[0]);
    zscore_t z_patt1 = get_zscore(inputs[col * PATTERNS + 1], stght[1]);
    zscore_t z_patt2 = get_zscore(inputs[col * PATTERNS + 2], stght[2]);
    zscore_t z_patt3 = get_zscore(inputs[col * PATTERNS + 3], stght[3]);
    zscore_t z_patt4 = get_zscore(inputs[col * PATTERNS + 4], stght[4]);
    zscore_t z_patt5 = get_zscore(inputs[col * PATTERNS + 5], stght[5]);
    zscore_t z_patt6 = get_zscore(inputs[col * PATTERNS + 6], stght[6]);

    // Max select
    // TODO: separate positive and negative patterns

    // Tree height = 0
    zscore_t comp_0_0 = (z_patt0 > z_patt1) ? z_patt0 : z_patt1;
    zscore_t comp_0_1 = (z_patt2 > z_patt3) ? z_patt2 : z_patt3;
    zscore_t comp_0_2 = (z_patt4 > z_patt5) ? z_patt4 : z_patt5;
    zscore_t comp_0_3 = (z_patt6);

    // Tree height = 1
    zscore_t comp_1_0 = (comp_0_0 > comp_0_1) ? comp_0_0 : comp_0_1;
    zscore_t comp_1_1 = (comp_0_2 > comp_0_3) ? comp_0_2 : comp_0_3;

    // Tree height = 2
    //zscore_t comp_2_0 = (comp_1_0 > comp_1_1) ? comp_1_0 : comp_1_1;

    // Tree height = 0
    pattnum_t idx_0_0 = (z_patt0 > z_patt1) ? 0 : 1;
    pattnum_t idx_0_1 = (z_patt2 > z_patt3) ? 2 : 3;
    pattnum_t idx_0_2 = (z_patt4 > z_patt5) ? 4 : 5;
    pattnum_t idx_0_3 = 6;

    // Tree height = 1
    pattnum_t idx_1_0 = (comp_0_0 > comp_0_1) ? idx_0_0 : idx_0_1;
    pattnum_t idx_1_1 = (comp_0_2 > comp_0_3) ? idx_0_2 : idx_0_3;

    // Tree height = 2
    //pattnum_t idx_2_0 = (comp_1_0 > comp_1_1) ? idx_1_0 : idx_1_1;
    pattnum_t patt = (comp_1_0 > comp_1_1) ? idx_1_0 : idx_1_1;

    outputs[col * 2 + 0] = get_score(inputs[col * PATTERNS + patt], patt);  //FIXME
    outputs[col * 2 + 1] = get_score(inputs[col * PATTERNS + patt], patt);  //FIXME
  }

  return;
}


// _________________________________________________________________________________________________
// Module

template <typename INPUT_T, typename OUTPUT_T, typename CONFIG_T>
void roi_pooling_module(
    const INPUT_T inputs[N_TOP_FN_IN],
    OUTPUT_T outputs[N_TOP_FN_OUT]
) {
#pragma HLS INLINE off

  // Make sure types are correct
  //static_assert(INPUT_T::width == OUTPUT_T::width, "inputs and outputs must have the same data width");
  static_assert(N_TOP_FN_OUT == N_TOP_FN_IN * num_patterns, "outputs array size must be inputs array size * num_patterns");

  // Deduce template arguments
  constexpr int ROWS = INPUT_T::width;
  constexpr int COLS = N_TOP_FN_IN;
  constexpr int PATTERNS = num_patterns;
  //constexpr int SCORES = ROWS + LOG2<PATTERNS>::cvalue;
  constexpr int ZONE = 0;  //FIXME

//  ap_uint<ROWS> outputs_step1[COLS * PATTERNS];
//#pragma HLS ARRAY_PARTITION variable=outputs_step1 complete dim=0

  // Do pooling
  roi_pooling<ROWS, COLS, PATTERNS, ZONE>(inputs, outputs);

  // Apply non-maximum suppression
  //nonmax_suppression<ROWS, COLS, PATTERNS, SCORES, ZONE>(outputs_step1, outputs);
}

}  // namespace emtf

#endif  // __EMTF_HLSLIB_POOLING_H__ not defined
