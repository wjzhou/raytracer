
namespace math {

template<int R, int C, class T> template<class U> inline
bits::basic_matrix<R, C, T>::basic_matrix(const U &m) {
	typedef typename bits::assign_dispatch<math::matrix<R, C, T>, U>::handler handler;
	handler::go(*this, m);
}

template<int R, int C, class B, class T> template<class U> inline
tmatrix_dim<R, C, B, T> &
tmatrix_dim<R, C, B, T>::operator=(const tmatrix_dim<R, C, U, T> &m)
{
	typedef typename bits::assign_dispatch<B, U>::handler handler;
	handler::go(*this, m);
	return *this;
}

template<int R, int C, class B, class T> template<class U> inline
tmatrix_dim<R, C, B, T> &tmatrix_dim<R, C, B, T>::operator=(const tmatrix_ndim<U, T> &m)
{
	typedef typename bits::assign_dispatch<B, U>::handler handler;
	handler::go(*this, m);
	return *this;
}

template<int R, int C, class B, class T> inline
tmatrix_dim<R, C, B, T> &tmatrix_dim<R, C, B, T>::operator=(const zero_t)
{
	typedef typename bits::assign_dispatch_elop<bits::unop_copy, B, 
		bits::zero_assigner_type<T>, R, C, R, C>::handler handler;
	handler::go(*this, bits::zero_assigner_type<T>());
	return *this;
}

template<int R, int C, class B, class T> inline
tmatrix_dim<R, C, B, T> &tmatrix_dim<R, C, B, T>::operator=(const identity_t)
{
	typedef typename bits::assign_dispatch_elop<bits::unop_copy, B, 
		bits::identity_assigner_type<T>, R, C, R, R>::handler handler;
	handler::go(*this, bits::identity_assigner_type<T>());
	return *this;
}

template<int R, int C, class A, class T>
template<class I> inline
typename bits::types<bits::matrix_unop<bits::unop_index<I>, A> >::mutable_return_type
tmatrix_dim<R, C, A, T>::operator[](const indexer<I>)
	{ return typename tmatrix2<bits::matrix_unop<bits::unop_index<I>, A> >::type(*this); }

template<int R, int C, class A, class T>
template<class I> inline
typename bits::types<bits::matrix_unop<bits::unop_cindex<I>, A> >::return_type
tmatrix_dim<R, C, A, T>::operator[](const indexer<I>) const
	{ return typename tmatrix2<bits::matrix_unop<bits::unop_cindex<I>, A> >::type(*this); }

template<int R, int C, class B, class T>
template<class A> inline
tmatrix_dim<R, C, B, T> &
tmatrix_dim<R, C, B, T>::operator*=(const tmatrix_dim<C != 1 ? C : 100, R, A, T> &a) {
	matrix<R, C, T> t = *this * a;
	*this = t;
	return *this;
}

template<int R, int C, class B, class T>
template<class A> inline
tmatrix_dim<R, C, B, T> &
tmatrix_dim<R, C, B, T>::operator*=(const tmatrix_dim<R, 1, A, T> &a) {
	typedef typename bits::assign_op<bits::binop_mul, B, A>::handler handler;
	handler::go(*this, a);
	return *this;
}

template<int R, int C, class B, class T>
template<class A> inline
tmatrix_dim<R, C, B, T> &
tmatrix_dim<R, C, B, T>::operator/=(const tmatrix_dim<R, 1, A, T> &a) {
	typedef typename bits::assign_op<bits::binop_div, B, A>::handler handler;
	handler::go(*this, a);
	return *this;
}

template<int R, int C, class B, class T> inline
tmatrix_dim<R, C, B, T> &
tmatrix_dim<R, C, B, T>::operator*=(T a) {
	typedef typename bits::assign_dispatch_elop<bits::binop_mul, B, bits::scalar_keeper<T>,
		R, C, R, C>::handler handler;
	bits::scalar_keeper<T> f = a;
	handler::go(*this, f);
	return *this;
}

template<int R, int C, class B, class T> inline
tmatrix_dim<R, C, B, T> &
tmatrix_dim<R, C, B, T>::operator/=(T a) {
	typedef typename bits::assign_dispatch_elop<bits::binop_div, B, bits::scalar_keeper<T>,
		R, C, R, C>::handler handler;
	bits::scalar_keeper<T> f = a;
	handler::go(*this, f);
	return *this;
}

template<int R, int C, class B, class T>
template<class A> inline
tmatrix_dim<R, C, B, T> &
tmatrix_dim<R, C, B, T>::operator+=(const tmatrix_dim<R, C, A, T> &a) {
	typedef typename bits::assign_op<bits::binop_add, B, A>::handler handler;
	handler::go(*this, a);
	return *this;
}

template<int R, int C, class B, class T>
template<class A> inline
tmatrix_dim<R, C, B, T> &
tmatrix_dim<R, C, B, T>::operator-=(const tmatrix_dim<R, C, A, T> &a) {
	typedef typename bits::assign_op<bits::binop_sub, B, A>::handler handler;
	handler::go(*this, a);
	return *this;
}

} // namespace math
