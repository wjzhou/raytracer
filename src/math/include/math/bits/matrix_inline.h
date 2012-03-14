
namespace math {

template<int R, int C, class T> template<class U> inline
matrix<R, C, T>::matrix(const tmatrix_dim<R, C, U, T> &m) {
	typedef typename bits::assign_dispatch<math::matrix<R, C, T>, U>::handler handler;
	handler::go(*this, m);
}

template<int R, int C, class T> template<class U> inline
matrix<R, C, T>::matrix(const tmatrix_ndim<U, T> &m) {
	typedef typename bits::assign_dispatch<math::matrix<R, C, T>, U>::handler handler;
	handler::go(*this, m);
}

template<int R, int C, class T> inline
matrix<R, C, T>::matrix(const zero_t)
{
	using namespace bits;
	typedef typename assign_dispatch_elop<unop_copy, basic_matrix<R, C, T>, 
		zero_assigner_type<T>, R, C, R, C>::handler handler;
	handler::go(*this, zero_assigner_type<T>());
}

template<int R, int C, class T> inline
matrix<R, C, T>::matrix(const identity_t)
{
	using namespace bits;
	typedef typename assign_dispatch_elop<unop_copy, math::matrix<R, C, T>, 
		identity_assigner_type<T>, R, C, R, R>::handler handler;
	handler::go(*this, identity_assigner_type<T>());
}

} // namespace math
