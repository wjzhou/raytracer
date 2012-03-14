#include <math/bits/simd/config.h>

#if MATH2_INTEL_SSE

#include <math/matrix.tpp>

void math::bits::simd::simd_assign_handler<math::bits::unop_copy>::go(bm44 &dest,
	matrix_binop<binop_mmul<4>, bm44, bm44> src) {

	__m128 v, f1, f2, f3, f4;
	__m128 c1, c2, c3, c4;
	__m128 ac1, ac2, ac3, ac4;
	__m128 s1, s2;

	ac1 = ssev(src.a)[0];
	ac2 = ssev(src.a)[1];
	ac3 = ssev(src.a)[2];
	ac4 = ssev(src.a)[3];

	v = ssev(src.b)[0];
	f1 = _mm_shuffle_ps(v, v, 0x00);
	f2 = _mm_shuffle_ps(v, v, 0x55);
	f3 = _mm_shuffle_ps(v, v, 0xaa);
	f4 = _mm_shuffle_ps(v, v, 0xff);
	c1 = _mm_mul_ps(f1, ac1);
	c2 = _mm_mul_ps(f2, ac2);
	c3 = _mm_mul_ps(f3, ac3);
	c4 = _mm_mul_ps(f4, ac4);
	s1 = _mm_add_ps(c1, c2);
	s2 = _mm_add_ps(c3, c4);
	ssev(dest)[0] = _mm_add_ps(s1, s2);

	v = ssev(src.b)[1];
	f1 = _mm_shuffle_ps(v, v, 0x00);
	f2 = _mm_shuffle_ps(v, v, 0x55);
	f3 = _mm_shuffle_ps(v, v, 0xaa);
	f4 = _mm_shuffle_ps(v, v, 0xff);
	c1 = _mm_mul_ps(f1, ac1);
	c2 = _mm_mul_ps(f2, ac2);
	c3 = _mm_mul_ps(f3, ac3);
	c4 = _mm_mul_ps(f4, ac4);
	s1 = _mm_add_ps(c1, c2);
	s2 = _mm_add_ps(c3, c4);
	ssev(dest)[1] = _mm_add_ps(s1, s2);

	v = ssev(src.b)[2];
	f1 = _mm_shuffle_ps(v, v, 0x00);
	f2 = _mm_shuffle_ps(v, v, 0x55);
	f3 = _mm_shuffle_ps(v, v, 0xaa);
	f4 = _mm_shuffle_ps(v, v, 0xff);
	c1 = _mm_mul_ps(f1, ac1);
	c2 = _mm_mul_ps(f2, ac2);
	c3 = _mm_mul_ps(f3, ac3);
	c4 = _mm_mul_ps(f4, ac4);
	s1 = _mm_add_ps(c1, c2);
	s2 = _mm_add_ps(c3, c4);
	ssev(dest)[2] = _mm_add_ps(s1, s2);

	v = ssev(src.b)[3];
	f1 = _mm_shuffle_ps(v, v, 0x00);
	f2 = _mm_shuffle_ps(v, v, 0x55);
	f3 = _mm_shuffle_ps(v, v, 0xaa);
	f4 = _mm_shuffle_ps(v, v, 0xff);
	c1 = _mm_mul_ps(f1, ac1);
	c2 = _mm_mul_ps(f2, ac2);
	c3 = _mm_mul_ps(f3, ac3);
	c4 = _mm_mul_ps(f4, ac4);
	s1 = _mm_add_ps(c1, c2);
	s2 = _mm_add_ps(c3, c4);
	ssev(dest)[3] = _mm_add_ps(s1, s2);
}

#endif // MATH2_INTEL_SSE
