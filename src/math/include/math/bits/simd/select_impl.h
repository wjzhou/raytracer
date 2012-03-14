// includes machine specific simd implementations

namespace math {
namespace bits {
namespace simd {

template<class Op> struct simd_assign_handler;

// default specialization indicator
// TODO: remove somehow
template<class Op, class D, class S>
struct simd_assign_specialized {
	enum { value = 0 };
};

} // namespace simd
} // namespace bits
} // namespace math

#if MATH2_INTEL_SSE
#	include <math/bits/simd/simd4_types.h>
#	include <math/bits/simd/intel_sse.h>
#endif
