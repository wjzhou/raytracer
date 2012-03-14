#ifndef MATH2_BITS_MATRIX_H
#define MATH2_BITS_MATRIX_H

// class definitions for matrix and vector

#include <math/fwd.h>

#include <math/bits/config.h>
#include <math/bits/simd/config.h>

#include <math/bits/scalar_traits.h>
#include <math/bits/opcodes.h>

#include <math/bits/matrix_storage.h>
#include <math/bits/basic_matrix.h>

#include <math/bits/tmatrix_types.h>
#include <math/bits/tmatrix.h>

namespace math {

// friendly matrix
template<int Rows, int Cols = Rows, class Type = float>
class matrix : public tmatrix2<bits::basic_matrix<Rows, Cols, Type> >::type {
	typedef typename tmatrix2<bits::basic_matrix<Rows, Cols, Type> >::type m_base;
public:
	matrix() {}
	matrix(const zero_t);
	matrix(const identity_t);
	template<class T> matrix(const tmatrix_dim<Rows, Cols, T, Type> &);
	template<class T> matrix(const tmatrix_ndim<T, Type> &);

	using m_base::operator=;
};

// friendly column matrix
template<int Rows, class Type = float>
class vector : public tmatrix2<bits::basic_matrix<Rows, 1, Type> >::type {
	typedef typename tmatrix2<bits::basic_matrix<Rows, 1, Type> >::type m_base;
public:
	vector() {}
	explicit vector(Type filler);
	vector(Type x, Type y) { assign(x, y); }
	vector(Type x, Type y, Type z) { assign(x, y, z); }
	vector(Type x, Type y, Type z, Type w) { assign(x, y, z, w); }
	vector(const zero_t);
	template<class T> vector(const tmatrix_dim<Rows, 1, T, Type> &);
	template<class T> vector(const tmatrix_dim<Rows-1, 1, T, Type> &, Type);
	template<class T> vector(const tmatrix_ndim<T, Type> &);
	template<class T> explicit vector(const math::vector<Rows, T> &);

	using m_base::operator=;
};

} // namespace math

#endif
