
namespace math {

template<int R, int C, int I, class T>
struct matrix_assigner {
	T &dest;
	matrix_assigner(T &d) : dest(d) {}
	matrix_assigner<R, C, I+1, T> operator,(typename T::scalar_type f)
		{ dest.template element<I/C, I%C>() = f; return dest; }
};

// matrix - scalar
template<class A, int R, int C, class T> inline
const typename tmatrix2<bits::matrix_binop<bits::binop_mul, bits::scalar_keeper<T>, A> >::type
operator*(T a, const tmatrix_dim<R, C, A, T> &b)
	{ return typename tmatrix2<bits::matrix_binop<bits::binop_mul, bits::scalar_keeper<T>, A> >::type(a, b); }

template<class A, int R, int C, class T> inline
const typename tmatrix2<bits::matrix_binop<bits::binop_mul, A, bits::scalar_keeper<T> > >::type
operator*(const tmatrix_dim<R, C, A, T> &a, T b)
	{ return typename tmatrix2<bits::matrix_binop<bits::binop_mul, A, bits::scalar_keeper<T> > >::type(a, b); }

template<class A, int R, int C, class T> inline
const typename tmatrix2<bits::matrix_binop<bits::binop_div, A, bits::scalar_keeper<T> > >::type
operator/(const tmatrix_dim<R, C, A, T> &a, T b)
	{ return typename tmatrix2<bits::matrix_binop<bits::binop_div, A, bits::scalar_keeper<T> > >::type(a, b); }

// matrix - matrix
template<class A, class B, int R, int C, class T> inline
const typename tmatrix2<bits::matrix_binop<bits::binop_add, A, B> >::type
operator+(const tmatrix_dim<R, C, A, T> &a, const tmatrix_dim<R, C, B, T> &b)
	{ return typename tmatrix2<bits::matrix_binop<bits::binop_add, A, B> >::type(a, b); }

template<class A, class B, int R, int C, class T> inline
const typename tmatrix2<bits::matrix_binop<bits::binop_sub, A, B> >::type
operator-(const tmatrix_dim<R, C, A, T> &a, const tmatrix_dim<R, C, B, T> &b)
	{ return typename tmatrix2<bits::matrix_binop<bits::binop_sub, A, B> >::type(a, b); }

template<class A, class B, int C, int D, int E, class T> inline
const typename tmatrix2<bits::matrix_binop<bits::binop_mmul<D>, A, B> >::type
operator*(const tmatrix_dim<C, D, A, T> &a, const tmatrix_dim<D, E, B, T> &b)
	{ return typename tmatrix2<bits::matrix_binop<bits::binop_mmul<D>, A, B> >::type(a, b); }

// unary matrix
template<class A, int R, int C, class T> inline
const typename tmatrix2<bits::matrix_unop<bits::unop_negate, A> >::type
operator-(const tmatrix_dim<R, C, A, T> &a)
	{ return typename tmatrix2<bits::matrix_unop<bits::unop_negate, A> >::type(a); }

// vector - vector
template<class A, class B, int R, class T> inline
const typename tmatrix2<bits::matrix_binop<bits::binop_mul, A, B> >::type
operator*(const tmatrix_dim<R, 1, A, T> &a, const tmatrix_dim<R, 1, B, T> &b)
	{ return typename tmatrix2<bits::matrix_binop<bits::binop_mul, A, B> >::type(a, b); }

template<class A, class B, int R, class T> inline
const typename tmatrix2<bits::matrix_binop<bits::binop_div, A, B> >::type
operator/(const tmatrix_dim<R, 1, A, T> &a, const tmatrix_dim<R, 1, B, T> &b)
	{ return typename tmatrix2<bits::matrix_binop<bits::binop_div, A, B> >::type(a, b); }


#pragma warning(push)
#pragma warning(disable: 4244)

// assign to matrix
template<int R, int C, class T, class ST, class ST2> inline
matrix_assigner<R, C, 1, T> operator<<(tmatrix_dim<R, C, T, ST> &dest, ST2 f)
	{ dest.template element<0,0>() = f; return dest; }

// assign to matrix
// TODO: what is this for?
template<int R, int C, class T, class ST, class ST2> inline
matrix_assigner<R, C, 1, T> operator<<(const tmatrix_dim<R, C, T, ST> &d, ST2 f) {
	T &dest = const_cast<T &>(static_cast<const T &>(d));
	dest.template element<0,0>() = f; return dest;
}

#pragma warning(pop)


// compare matrices
template<int A, int B, class T>
bool operator==(const matrix<A, B, T> &a, const matrix<A, B, T> &b)
{
	for (int i=0; i!=A*B; ++i)
		if (a.data()[i] != b.data()[i])
			return false;
	return true;
}
template<int A, int B, class T> inline
bool operator!=(const matrix<A, B, T> &a, const matrix<A, B, T> &b)
	{ return !(a == b); }

// compare vectors
template<int A, class T>
bool operator==(const vector<A, T> &a, const vector<A, T> &b)
{
	for (int i=0; i!=A; ++i)
		if (a.data()[i] != b.data()[i])
			return false;
	return true;
}
template<int A, class T> inline
bool operator!=(const vector<A, T> &a, const vector<A, T> &b)
	{ return !(a == b); }



// print matrix
template<class Ch, class Tr, int A, int B, class T>
std::ostream &operator<<(std::basic_ostream<Ch, Tr> &s, const matrix<A, B, T> &m)
{
	for (int r=0; r<A-1; ++r) {
		s << '(';
		for (int c=0; c<B-1; ++c)
			s << m(r,c) << ' ';
		s << m(r,B-1) << "),\n ";
	}
	s << '(';
	for (int c=0; c<B-1; ++c)
		s << m(A-1,c) << ' ';
	return s << m(A-1,B-1) << ")";
}

// print vector
template<class Ch, class Tr, int A, class T>
std::ostream &operator<<(std::basic_ostream<Ch, Tr> &s, const vector<A, T> &m)
{
	for (int i=0; i<A-1; ++i)
		s << m(i) << ' ';
	return s << m(A-1);
}

// read vector
template<class Ch, class Tr, int A, class T>
std::istream &operator>>(std::basic_istream<Ch, Tr> &s, vector<A, T> &m)
{
	vector<A, T> t;
	for (int i=0; i!=A; ++i)
		s >> t(i);
	if (s)
		m = t;
	return s;
}

} // namespace math
