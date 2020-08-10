#ifndef __EMTF_HLSLIB_HELPERS_H__
#define __EMTF_HLSLIB_HELPERS_H__

#include <cassert>
#include <cstdint>
#include <cstdlib>

#ifndef __SYNTHESIS__
#define emtf_assert(expr) (assert(expr))
#else
#define emtf_assert(expr) ((void)(expr))
#endif

namespace emtf {

// Get max (for template programming)
template <int A, int B>
struct MAX
{
  static const int value = (A > B) ? A : B;
};

// Get min (for template programming)
template <int A, int B>
struct MIN
{
  static const int value = (A < B) ? A : B;
};

// Get abs (for template programming)
template <int A>
struct ABS
{
  static const int value = (A < 0) ? -A : A;
};

// Get array length
template <typename T, size_t N>
constexpr size_t get_array_length(T const (&arr)[N]) { return N; }

// From: hls-fpga-machine-learning/hls4ml - hls4ml/templates/vivado/nnet_utils/nnet_helpers.h
constexpr int ceillog2(int x) {
  return (x <= 2) ? 1 : 1 + ceillog2((x+1) / 2);
}

constexpr int floorlog2(int x) {
  return (x < 2) ? 0 : 1 + floorlog2(x / 2);
}

constexpr int pow2(int x) {
  return x == 0 ? 1 : 2 * pow2(x - 1);
}

// Dumb int tuples (pair, triple, quadruple)

struct int_pair {
  const int first;
  const int second;

  int_pair() : first(), second() {}
  int_pair(int a, int b) : first(a), second(b) {}
  inline int operator[](int index) const {
    switch (index) {
      case 0: return first;
      case 1: return second;
    }
    return 0;
  }
};

struct int_triple {
  const int first;
  const int second;
  const int third;

  int_triple() : first(), second(), third() {}
  int_triple(int a, int b, int c) : first(a), second(b), third(c) {}
  inline int operator[](int index) const {
    switch (index) {
      case 0: return first;
      case 1: return second;
      case 2: return third;
    }
    return 0;
  }
};

struct int_quadruple {
  const int first;
  const int second;
  const int third;
  const int fourth;

  int_quadruple() : first(), second(), third(), fourth() {}
  int_quadruple(int a, int b, int c, int d) : first(a), second(b), third(c), fourth(d) {}
  inline int operator[](int index) const {
    switch (index) {
      case 0: return first;
      case 1: return second;
      case 2: return third;
      case 3: return fourth;
    }
    return 0;
  }
};

}  // namespace emtf

#endif  // __EMTF_HLSLIB_HELPERS_H__ not defined
