#ifndef __EMTF_HLSLIB_LAYER_CONSTANTS_H__
#define __EMTF_HLSLIB_LAYER_CONSTANTS_H__

namespace emtf {

namespace details {

// Num of chambers in a row
// 10 deg: 6 native + 1 neighbor
// 20 deg: 3 native + 1 neighbor
// 20 deg ext: 3 native (20 deg) + 1 neighbor (20 deg) + 6 native (10 deg) + 1 neighbor (10 deg)
constexpr static const int num_chambers_10deg = 7;
constexpr static const int num_chambers_20deg = 4;
constexpr static const int num_chambers_20deg_ext = 11;

// Zone 0: 9 rows, 45 chambers
constexpr static const int chamber_id_zone_0_row_0[7]     = {108, 109, 110, 111, 112, 113, 114};  // ME0
constexpr static const int chamber_id_zone_0_row_1[7]     = { 54,  55,  56,  63,  64,  65,  99};  // GE1/1
constexpr static const int chamber_id_zone_0_row_2[7]     = {  0,   1,   2,   9,  10,  11,  45};  // ME1/1
constexpr static const int chamber_id_zone_0_row_3[4]     = { 72,  73,  74, 102};                 // GE2/1
constexpr static const int chamber_id_zone_0_row_4[4]     = { 18,  19,  20,  48};                 // ME2/1
constexpr static const int chamber_id_zone_0_row_5[4]     = { 27,  28,  29,  50};                 // ME3/1
constexpr static const int chamber_id_zone_0_row_6[4]     = { 81,  82,  83, 104};                 // RE3/1
constexpr static const int chamber_id_zone_0_row_7_0[4]   = { 36,  37,  38,  52};                 // ME4/1
constexpr static const int chamber_id_zone_0_row_7_1[4]   = { 90,  91,  92, 106};                 // RE4/1

// Zone 1: 14 rows, 80 chambers
constexpr static const int chamber_id_zone_1_row_0[7]     = { 54,  55,  56,  63,  64,  65,  99};  // GE1/1
constexpr static const int chamber_id_zone_1_row_1[7]     = {  0,   1,   2,   9,  10,  11,  45};  // ME1/1
constexpr static const int chamber_id_zone_1_row_2_0[7]   = {  3,   4,   5,  12,  13,  14,  46};  // ME1/2
constexpr static const int chamber_id_zone_1_row_2_1[7]   = { 57,  58,  59,  66,  67,  68, 100};  // RE1/2
constexpr static const int chamber_id_zone_1_row_3[4]     = { 72,  73,  74, 102};                 // GE2/1
constexpr static const int chamber_id_zone_1_row_4[4]     = { 18,  19,  20,  48};                 // ME2/1
constexpr static const int chamber_id_zone_1_row_5[11]    = { 27,  28,  29,  50,  30,  31,  32,  33,  34,  35,  51};  // ME3/1 + ME3/2
constexpr static const int chamber_id_zone_1_row_6[11]    = { 81,  82,  83, 104,  84,  85,  86,  87,  88,  89, 105};  // RE3/1 + RE3/2
constexpr static const int chamber_id_zone_1_row_7_0[11]  = { 36,  37,  38,  52,  39,  40,  41,  42,  43,  44,  53};  // ME4/1 + ME4/2
constexpr static const int chamber_id_zone_1_row_7_1[11]  = { 90,  91,  92, 106,  93,  94,  95,  96,  97,  98, 107};  // RE4/1 + RE4/2

// Zone 2: 8 rows, 56 chambers
constexpr static const int chamber_id_zone_2_row_0[7]     = {  3,   4,   5,  12,  13,  14,  46};  // ME1/2
constexpr static const int chamber_id_zone_2_row_1[7]     = { 57,  58,  59,  66,  67,  68, 100};  // RE1/2
constexpr static const int chamber_id_zone_2_row_2[7]     = { 75,  76,  77,  78,  79,  80, 103};  // RE2/2
constexpr static const int chamber_id_zone_2_row_3[7]     = { 21,  22,  23,  24,  25,  26,  49};  // ME2/2
constexpr static const int chamber_id_zone_2_row_4[7]     = { 30,  31,  32,  33,  34,  35,  51};  // ME3/2
constexpr static const int chamber_id_zone_2_row_5[7]     = { 84,  85,  86,  87,  88,  89, 105};  // RE3/2
constexpr static const int chamber_id_zone_2_row_6[7]     = { 39,  40,  41,  42,  43,  44,  53};  // ME4/2
constexpr static const int chamber_id_zone_2_row_7[7]     = { 93,  94,  95,  96,  97,  98, 107};  // RE4/2

// ph_init reference values
// [0, 38, 75, 113, 150, 188, 225, 263] -> [0.0, 10.1333, 20.0, 30.1333, 40.0, 50.1333, 60.0, 70.1333] deg
constexpr static const int chamber_ph_init_10deg[7]       = { 75, 113, 150, 188, 225, 263,  38};
constexpr static const int chamber_ph_init_20deg[4]       = { 75, 150, 225,   0};
constexpr static const int chamber_ph_init_20deg_ext[11]  = { 75, 150, 225,   0,  75, 113, 150, 188, 225, 263,  38};

// ph_cover reference values
// [52, 90, 127, 165, 202, 240, 277, 315] -> [13.8667, 24.0, 33.8667, 44.0, 53.8667, 64.0, 73.8667, 84.0] deg
constexpr static const int chamber_ph_cover_10deg[7]      = {127, 165, 202, 240, 277, 315,  90};
constexpr static const int chamber_ph_cover_20deg[4]      = {165, 240, 315,  90};
constexpr static const int chamber_ph_cover_20deg_ext[11] = {165, 240, 315,  90, 127, 165, 202, 240, 277, 315,  90};

// Chamber img width
// They must be compatible with num_emtf_img_cols
constexpr static const int chamber_img_bw = 90;          // 24 deg
constexpr static const int chamber_img_joined_bw = 315;  // 84 deg
constexpr static const int chamber_img_joined_col_start = chamber_img_joined_bw - 288;
constexpr static const int chamber_img_joined_col_stop = chamber_img_joined_bw - 1;

}  // namespace details

}  // namespace emtf

#endif  // __EMTF_HLSLIB_LAYER_CONSTANTS_H__ not defined
