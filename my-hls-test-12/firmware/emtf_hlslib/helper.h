#ifndef __EMTF_HLSLIB_HELPER_H__
#define __EMTF_HLSLIB_HELPER_H__

#include <cassert>
#include <cstdint>
#include <cstdlib>

#ifndef __SYNTHESIS__
#define emtf_assert(expr) (assert(expr))
#else
#define emtf_assert(expr) ((void)(expr))
#endif

namespace emtf {

}  // namespace emtf

#endif  // __EMTF_HLSLIB_HELPER_H__ not defined
