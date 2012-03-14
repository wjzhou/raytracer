
#include <xmmintrin.h>

// specializisations for SSE instructions using Intel intrinsics

namespace math {

// use these to overload at the correct level
typedef tmatrix_dim<4, 1, bits::basic_matrix<4, 1, float>, float> v4_dbm;
typedef tmatrix_dim<4, 4, bits::basic_matrix<4, 4, float>, float> m4_dbm;

namespace bits {
namespace simd {

// cast to __m128
inline __m128 &sse(bm41 &a)
	{ return reinterpret_cast<__m128 &>(a); }
inline __m128 sse(const bm41 &a)
	{ return reinterpret_cast<const __m128 &>(a); }

inline __m128 &sse(matrix_storage<4, 1, float, true> &a)
	{ return reinterpret_cast<__m128 &>(a); }
inline __m128 sse(const matrix_storage<4, 1, float, true> &a)
	{ return reinterpret_cast<const __m128 &>(a); }

// cast to __m128[]
inline __m128 *ssev(bm44 &a)
	{ return reinterpret_cast<__m128 *>(&a); }
inline const __m128 *ssev(const bm44 &a)
	{ return reinterpret_cast<const __m128 *>(&a); }

inline __m128 *ssev(matrix_storage<4,4,float,true> &a)
	{ return reinterpret_cast<__m128 *>(&a); }
inline const __m128 *ssev(const matrix_storage<4,4,float,true> &a)
	{ return reinterpret_cast<const __m128 *>(&a); }

// extract first value
inline float float0(__m128 t) {
	float f;
	_mm_store_ss(&f, t);
	return f;
}

// sum first 3 elements into first
inline __m128 sum3(__m128 v) {
	__m128 ty = _mm_shuffle_ps(v, v, 0x55);
	__m128 tz = _mm_movehl_ps(v, v);
	v = _mm_add_ss(v, ty);
	return _mm_add_ss(v, tz);
}
// sum all elements into first
inline __m128 sum4(__m128 v) {
	__m128 t = _mm_movehl_ps(v, v);
	v = _mm_add_ps(v, t);
	t = _mm_shuffle_ps(v, v, 0x55);
	return _mm_add_ss(v, t);
}

// cast to vector<>
inline vector<4> vec4(__m128 v)
	{ return reinterpret_cast<const vector<4> &>(v); }

} // namespace simd
} // namespace bits

inline const vector<4>
operator*(const m4_dbm &a, const v4_dbm &b) {
	using namespace bits::simd;
	__m128 v, f1, f2, f3, f4;
	v = sse(b);
	f1 = _mm_shuffle_ps(v, v, 0x00);
	f2 = _mm_shuffle_ps(v, v, 0x55);
	f3 = _mm_shuffle_ps(v, v, 0xaa);
	f4 = _mm_shuffle_ps(v, v, 0xff);
	__m128 c1, c2, c3, c4;
	c1 = _mm_mul_ps(f1, ssev(a)[0]);
	c2 = _mm_mul_ps(f2, ssev(a)[1]);
	c3 = _mm_mul_ps(f3, ssev(a)[2]);
	c4 = _mm_mul_ps(f4, ssev(a)[3]);
	__m128 s1, s2;
	s1 = _mm_add_ps(c1, c2);
	s2 = _mm_add_ps(c3, c4);
	return vec4(_mm_add_ps(s1, s2));
}

inline const vector<4>
operator+(const v4_dbm &a, const v4_dbm &b)
	{ using namespace bits::simd; return vec4(_mm_add_ps(sse(a), sse(b))); }

inline const vector<4>
operator-(const v4_dbm &a, const v4_dbm &b)
	{ using namespace bits::simd; return vec4(_mm_sub_ps(sse(a), sse(b))); }

inline const vector<4>
operator*(const v4_dbm &a, const v4_dbm &b)
	{ using namespace bits::simd; return vec4(_mm_mul_ps(sse(a), sse(b))); }

inline const vector<4>
operator*(const v4_dbm &a, float b)
	{ using namespace bits::simd; return vec4(_mm_mul_ps(sse(a), _mm_set_ps1(b))); }

inline const vector<4>
operator*(float a, const v4_dbm &b)
	{ using namespace bits::simd; return vec4(_mm_mul_ps(_mm_set_ps1(a), sse(b))); }

inline const vector<4>
operator/(const v4_dbm &a, const v4_dbm &b)
	{ using namespace bits::simd; return vec4(_mm_div_ps(sse(a), sse(b))); }

inline const vector<4>
operator/(const v4_dbm &a, float b)
	{ using namespace bits::simd; return vec4(_mm_div_ps(sse(a), _mm_set_ps1(b))); }


inline const vector<4>
reciprocal(const v4_dbm &a) {
	using namespace bits::simd;
	return vec4(_mm_rcp_ps(sse(a)));
}

inline float dot(const v4_dbm &a, const v4_dbm &b) {
	using namespace bits::simd;
	__m128 t = _mm_mul_ps(sse(a), sse(b));
	return float0(sum4(t));
}

inline vector<4> norm(const v4_dbm &a) {
	using namespace bits::simd;
	__m128 in = sse(a);
	__m128 t = _mm_mul_ps(in, in);
	t = sum4(t);
	t = _mm_sqrt_ss(t);
	t = _mm_shuffle_ps(t, t, 0x00);
	return vec4(_mm_div_ps(in, t));
}

inline float abs_squared(const v4_dbm &a) {
	using namespace bits::simd;
	__m128 t = _mm_mul_ps(sse(a), sse(a));
	return float0(sum4(t));
}

inline float sum(const v4_dbm &a) {
	using namespace bits::simd;
	return float0(sum4(sse(a)));
}

namespace bits {
namespace simd {

// copy-assign
// TODO: remove these somehow
template<>
struct simd_assign_specialized<unop_copy, bm41,	bm41>
	{ enum { value = 1 }; };
template<>
struct simd_assign_specialized<unop_copy, bm44,	bm44>
	{ enum { value = 1 }; };
template<>
struct simd_assign_specialized<unop_copy, bm44,
	matrix_binop<binop_mmul<4>, bm44, bm44> > { enum { value = 1 }; };
template<>
struct simd_assign_specialized<unop_copy, bm41,	scalar_keeper<float> >
	{ enum { value = 1 }; };
template<>
struct simd_assign_specialized<unop_copy, bm44,	zero_assigner_type<float> >
	{ enum { value = 1 }; };
template<>
struct simd_assign_specialized<unop_copy, bm41,	zero_assigner_type<float> >
	{ enum { value = 1 }; };
template<>
struct simd_assign_handler<unop_copy> {
	
	static void go(bm44 &, matrix_binop<binop_mmul<4>, bm44, bm44>);

	static void go(bm41 &d, const bm41 &s) { sse(d) = sse(s); }
	static void go(bm44 &d, const bm44 &s) {
		ssev(d)[0] = ssev(s)[0];
		ssev(d)[1] = ssev(s)[1];
		ssev(d)[2] = ssev(s)[2];
		ssev(d)[3] = ssev(s)[3];
	}


	static void go(bm41 &d, scalar_keeper<float> s) { sse(d) = _mm_set_ps1(s.f); }
	static void go(bm41 &d, zero_assigner_type<float>)
		{ sse(d) = _mm_setzero_ps(); }
	static void go(bm44 &d, zero_assigner_type<float>) {
		__m128 t = _mm_setzero_ps();
		ssev(d)[0] = t;
		ssev(d)[1] = t;
		ssev(d)[2] = t;
		ssev(d)[3] = t;
	}
};

// add-assign
template<> struct simd_assign_specialized<binop_add, bm44, bm44>
	{ enum { value = 1 }; };
template<> struct simd_assign_specialized<binop_add, bm41, bm41>
	{ enum { value = 1 }; };
template<>
struct simd_assign_handler<binop_add> {

	static void go(bm41 &d, const bm41 & MATH2_RESTRICT s)
		{ sse(d) = _mm_add_ps(sse(s), sse(d)); }
	static void go(bm44 &d, const bm44 & MATH2_RESTRICT s) {
		ssev(d)[0] = _mm_add_ps(ssev(s)[0], ssev(d)[0]);
		ssev(d)[1] = _mm_add_ps(ssev(s)[1], ssev(d)[1]);
		ssev(d)[2] = _mm_add_ps(ssev(s)[2], ssev(d)[2]);
		ssev(d)[3] = _mm_add_ps(ssev(s)[3], ssev(d)[3]);
	}
};

// sub-assign
template<> struct simd_assign_specialized<binop_sub, bm44, bm44>
	{ enum { value = 1 }; };
template<> struct simd_assign_specialized<binop_sub, bm41, bm41>
	{ enum { value = 1 }; };
template<>
struct simd_assign_handler<binop_sub> {

	static void go(bm41 &d, const bm41 & MATH2_RESTRICT s)
		{ sse(d) = _mm_sub_ps(sse(s), sse(d)); }
	static void go(bm44 &d, const bm44 & MATH2_RESTRICT s) {
		ssev(d)[0] = _mm_sub_ps(ssev(s)[0], ssev(d)[0]);
		ssev(d)[1] = _mm_sub_ps(ssev(s)[1], ssev(d)[1]);
		ssev(d)[2] = _mm_sub_ps(ssev(s)[2], ssev(d)[2]);
		ssev(d)[3] = _mm_sub_ps(ssev(s)[3], ssev(d)[3]);
	}
};

// mul-assign
template<> struct simd_assign_specialized<binop_mul, bm41, bm41>
	{ enum { value = 1 }; };
template<> struct simd_assign_specialized<binop_mul, bm41, scalar_keeper<float> >
	{ enum { value = 1 }; };
template<>
struct simd_assign_handler<binop_mul> {

	static void go(bm41 &d, const bm41 & MATH2_RESTRICT s)
		{ sse(d) = _mm_mul_ps(sse(s), sse(d)); }
	static void go(bm41 &d, scalar_keeper<float> s)
		{ sse(d) = _mm_mul_ps(_mm_set_ps1(s.f), sse(d)); }
};

// div-assign
template<> struct simd_assign_specialized<binop_div, bm41, bm41>
	{ enum { value = 1 }; };
template<> struct simd_assign_specialized<binop_div, bm41, scalar_keeper<float> >
	{ enum { value = 1 }; };
template<>
struct simd_assign_handler<binop_div> {

	static void go(bm41 &d, const bm41 & MATH2_RESTRICT s)
		{ sse(d) = _mm_div_ps(sse(s), sse(d)); }
	static void go(bm41 &d, scalar_keeper<float> s)
		{ sse(d) = _mm_div_ps(_mm_set_ps1(s.f), sse(d)); }
};

} // namespace simd

inline matrix_storage<4, 1, float, true>::matrix_storage(const matrix_storage &a) {
	using namespace simd;
	sse(*this) = sse(a);
}
inline matrix_storage<4, 1, float, true> &
matrix_storage<4, 1, float, true>::operator=(const matrix_storage &a) { 
	using namespace simd;
	sse(*this) = sse(a);
	return *this;
}

inline matrix_storage<4, 4, float, true>::matrix_storage(const matrix_storage &a) {
	using namespace simd;
	ssev(*this)[0] = ssev(a)[0];
	ssev(*this)[1] = ssev(a)[1];
	ssev(*this)[2] = ssev(a)[2];
	ssev(*this)[3] = ssev(a)[3];
}
inline matrix_storage<4, 4, float, true> &
matrix_storage<4, 4, float, true>::operator=(const matrix_storage &a) { 
	using namespace simd;
	ssev(*this)[0] = ssev(a)[0];
	ssev(*this)[1] = ssev(a)[1];
	ssev(*this)[2] = ssev(a)[2];
	ssev(*this)[3] = ssev(a)[3];
	return *this;
}

} // namespace bits
} // namespace math
