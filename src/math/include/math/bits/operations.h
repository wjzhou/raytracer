
namespace math {

// vector product
template<class A, class B, class T> inline
const typename tmatrix2<bits::matrix_binop<bits::binop_cross, A, B> >::type
cross(const tmatrix_dim<3, 1, A, T> &a, const tmatrix_dim<3, 1, B, T> &b)
	{ return typename tmatrix2<bits::matrix_binop<bits::binop_cross, A, B> >::type(a, b); }

// scalar product
template<class A, class B, int R, class T> inline
T dot(const tmatrix_dim<R, 1, A, T> &a, const tmatrix_dim<R, 1, B, T> &b)
	{ return typename tmatrix2<bits::matrix_binop<bits::binop_dot<R>, A, B> >::type(a, b); }


// transpose
template<class A, int R, int C, class T> inline
const typename tmatrix2<bits::matrix_unop<bits::unop_cindex<bits::index_transpose>, A> >::type
transpose(const tmatrix_dim<R, C, A, T> &a)
	{ return typename tmatrix2<bits::matrix_unop<bits::unop_cindex<bits::index_transpose>, A> >::type(a); }

// inverse
template<int RC, class T> inline
const typename tmatrix2<bits::matrix_unop<bits::unop_inverse, bits::basic_matrix<RC, RC, T> > >::type
inverse(const matrix<RC, RC, T> &a)
	{ return typename tmatrix2<bits::matrix_unop<bits::unop_inverse, bits::basic_matrix<RC, RC, T> > >::type(a); }

// adjoint
template<class A, int R, int C, class T> inline
const typename tmatrix2<bits::matrix_unop<bits::unop_adjoint, A> >::type
adjoint(const tmatrix_dim<R, C, A, T> &a)
	{ return typename tmatrix2<bits::matrix_unop<bits::unop_adjoint, A> >::type(a); }


// make a translation matrix
template<class A, class T> inline
const typename tmatrix2<bits::matrix_unop<bits::unop_translation, A> >::type
translation(const tmatrix_dim<3, 1, A, T> &a)
	{ return typename tmatrix2<bits::matrix_unop<bits::unop_translation, A> >::type(a); }

// make a scaling matrix
template<class A, class T> inline
const typename tmatrix2<bits::matrix_unop<bits::unop_scaling, A> >::type
scaling(const tmatrix_dim<3, 1, A, T> &a)
	{ return typename tmatrix2<bits::matrix_unop<bits::unop_scaling, A> >::type(a); }
inline const tmatrix2<bits::matrix_unop<bits::unop_scaling, bits::scalar_keeper<float> > >::type
scaling(float a)
	{ return tmatrix2<bits::matrix_unop<bits::unop_scaling, bits::scalar_keeper<float> > >::type(a); }

// make a rotation matrix
template<class A, class T> inline
const typename tmatrix2<bits::matrix_binop<bits::binop_rotation, A, bits::scalar_keeper<T> > >::type
rotation(const tmatrix_dim<3, 1, A, T> &axis, T radians) {
	return typename tmatrix2<bits::matrix_binop<bits::binop_rotation, A, bits::scalar_keeper<T> > >::type
		(axis, radians);
}

// make a perspective projection matrix
const matrix<4> frustum(float left, float right, float bottom, float top,
	float near, float far);

// make an orthographic projection matrix
const matrix<4> ortho(float left, float right, float bottom, float top,
	float near, float far);


// perspective division
template<class A, class T> inline
const typename tmatrix2<bits::matrix_unop<bits::unop_wdiv, A> >::type
wdiv(const tmatrix_dim<4, 1, A, T> &a)
	{ return typename tmatrix2<bits::matrix_unop<bits::unop_wdiv, A> >::type(a); }

// normalize vector
template<int R, class A, class T> inline
const typename tmatrix2<bits::matrix_unop<bits::unop_normalize, A> >::type
norm(const tmatrix_dim<R, 1, A, T> &a)
	{ return typename tmatrix2<bits::matrix_unop<bits::unop_normalize, A> >::type(a); }

// reciprocal of vector
template<int R, class A, class T> inline
const typename tmatrix2<bits::matrix_unop<bits::unop_reciprocal, A> >::type
reciprocal(const tmatrix_dim<R, 1, A, T> &a)
	{ return typename tmatrix2<bits::matrix_unop<bits::unop_reciprocal, A> >::type(a); }


// expand vector
template<class A, int R, class T> inline
const typename tmatrix2<bits::matrix_binop<bits::binop_expand, A, bits::scalar_keeper<T> > >::type
expand(const tmatrix_dim<R, 1, A, T> &a, T b)
	{ return typename tmatrix2<bits::matrix_binop<bits::binop_expand, A, bits::scalar_keeper<T> > >::type(a, b); }

// remove row R and column C
template<int R, int C, class A, int D, int E, class T> inline
const typename tmatrix2<bits::matrix_unop<bits::unop_cindex<bits::index_cofactor<R, C> >, A> >::type
cofactor(const tmatrix_dim<D, E, A, T> &a) {
	return typename tmatrix2<bits::matrix_unop<bits::unop_cindex<bits::index_cofactor<R, C> >, A> >::type(a);
}

// same as above, usable from impementations of other operations
template<int R, int C, class T> inline
const typename tmatrix2<bits::matrix_unop<bits::unop_cindex<bits::index_cofactor<R, C> >, T> >::type
cofactor_bm(const T &a) {
	return typename tmatrix2<bits::matrix_unop<bits::unop_cindex<bits::index_cofactor<R, C> >, T> >::type(a);
}

// evaluate to temporary
template<int R, int C, class T, class ST> inline
const matrix<R, C> temp(const tmatrix_dim<R, C, T, ST> &a) { return a; }


// determinant
template<class T>
inline T det(T a1, T a2, T b1, T b2)
	{ return a1*b2 - a2*b1; }
template<class T, class U, class V>
inline T det(const tmatrix_dim<2, 1, U, T> &a, const tmatrix_dim<2, 1, V, T> &b) {
	vector<2, T> av = a, bv = b;
	return av.x*bv.y - av.y*bv.x;
}
template<class T>
inline T det_bm(const bits::basic_matrix<1, 1, T> &m) { return m(0,0); }
template<class T>
inline T det_bm(const bits::basic_matrix<2, 2, T> &m)
	{ return m(0,0)*m(1,1) - m(1,0)*m(0,1); }
template<class T>
inline T det(T a1, T a2, T a3, T b1, T b2, T b3, T c1, T c2, T c3)
{
	return a1*b2*c3 + a2*b3*c1 + a3*b1*c2 - a3*b2*c1 - a1*b3*c2 - a2*b1*c3;
}
template<class T>
inline T det(bits::basic_matrix<3, 1, T> a, bits::basic_matrix<3, 1, T> b, bits::basic_matrix<3, 1, T> c)
{
	return det(a.x, a.y, a.z, b.x, b.y, b.z, c.x, c.y, c.z);
}
float det_bm(const bits::bm33 &);
float det_bm(const bits::bm44 &);

template<int RC, class A, class T> inline T det(const tmatrix_dim<RC, RC, A, T> &a)
	{ return det_bm(static_cast<const bits::basic_matrix<RC, RC, T> &>(a)); }


// squared length of vector
template<class T>
inline T abs_squared_bm(const bits::basic_matrix<2, 1, T> &a)
	{ return a.x*a.x + a.y*a.y; }
template<class T>
inline T abs_squared_bm(const bits::basic_matrix<3, 1, T> &a)
	{ return a.x*a.x + a.y*a.y + a.z*a.z; }
template<class T>
inline T abs_squared_bm(const bits::basic_matrix<4, 1, T> &a)
	{ return a.x*a.x + a.y*a.y + a.z*a.z + a.w*a.w; }

template<int R, class A, class T> inline
T abs_squared(const tmatrix_dim<R, 1, A, T> &a)
	{ return abs_squared_bm(static_cast<const bits::basic_matrix<R, 1, T> &>(a)); }


// length of vector
template<int R, class A, class T> inline
T abs(const tmatrix_dim<R, 1, A, T> &a) {
	using std::sqrt;
	return sqrt(abs_squared(a));
}


// sum of elements
template<class T>
inline T sum_bm(const bits::basic_matrix<2, 1, T> &a)
	{ return a.x + a.y; }
template<class T>
inline T sum_bm(const bits::basic_matrix<3, 1, T> &a)
	{ return a.x + a.y + a.z; }
template<class T>
inline T sum_bm(const bits::basic_matrix<4, 1, T> &a)
	{ return a.x + a.y + a.z + a.w; }

template<int R, class A, class T> inline
T sum(const tmatrix_dim<R, 1, A, T> &a)
	{ return sum_bm(static_cast<const bits::basic_matrix<R, 1, T> &>(a)); }


// convert to vector
template<class T> vector<2> vector_xy(T v) { return vector<2>(float(v.x), float(v.y)); }
template<class T> vector<3> vector_xyz(const T &v)
	{ return vector<3>(v.x, v.y, v.z); }
template<class T> vector<4> vector_xyzw(const T &v)
	{ return vector<4>(v.x, v.y, v.z, v.w); }

template<class T> vector<3> vector_rgb(const T &v)
	{ return vector<3>(v.r, v.g, v.b); }
template<class T> vector<4> vector_rgba(const T &v)
	{ return vector<4>(v.r, v.g, v.b, v.a); }

template<class T> vector<2> vector_st(T v) { return vector<2>(v.s, v.t); }
template<class T> vector<3> vector_stu(const T &v)
	{ return vector<3>(v.s, v.t, v.u); }
template<class T> vector<4> vector_stuv(const T &v)
	{ return vector<4>(v.s, v.t, v.u, v.v); }

} // namespace math
