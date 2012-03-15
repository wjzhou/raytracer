#ifndef MATHLIB_SIMD_CONFIG_H
#define MATHLIB_SIMD_CONFIG_H

// type definitions and defines for simd instructions

namespace math {

#define MATH2_NO_SIMD

#if defined MATH2_NO_SIMD
	// simd support manually disabled
#elif defined __GNUG__ && defined __SSE__
	// g++ with sse instructions enabled
#	define MATH2_SIMD 1
#	define MATH2_SIMD4 1
#	define MATH2_INTEL_SSE 1

#	define MATH2_SIMD4_ALIGN_POST __attribute__((aligned(16)))

#elif defined _MSC_VER && _M_IX86 >= 700
	// Visual C++ optimizing for Pentium 4 or better
#	define MATH2_SIMD 1
#	define MATH2_SIMD4 1
#	define MATH2_INTEL_SSE 1

#	define MATH2_SIMD4_ALIGN_PRE __declspec(align(16))

#endif

#ifndef MATH2_SIMD4_ALIGN_PRE
#	define MATH2_SIMD4_ALIGN_PRE
#endif
#ifndef MATH2_SIMD4_ALIGN_POST
#	define MATH2_SIMD4_ALIGN_POST
#endif

} // namespace math

#endif
