
namespace math {

template<int R, class T> inline
vector<R, T>::vector(const zero_t)
{
	using namespace bits;
	typedef typename assign_dispatch_elop<unop_copy, basic_matrix<R, 1, T>, 
		zero_assigner_type<T>, R, 1, R, 1>::handler handler;
	handler::go(*this, zero_assigner_type<T>());
}

template<int R, class T> inline
vector<R, T>::vector(T filler)
{
	using namespace bits;
	typedef typename assign_dispatch_elop<unop_copy, basic_matrix<R, 1, T>, 
		scalar_keeper<T>, R, 1, R, 1>::handler handler;
	handler::go(*this, scalar_keeper<T>(filler));
}

template<int R, class T> template<class U> inline
vector<R, T>::vector(const tmatrix_dim<R, 1, U, T> &v) {
	typedef typename bits::assign_dispatch<math::vector<R, T>, U>::handler handler;
	handler::go(*this, v);
}

template<int R, class T> template<class U> inline
vector<R, T>::vector(const tmatrix_dim<R-1, 1, U, T> &v, T pad) {
	const indexer<bits::index_submatrix<0,0,R-2,0> > top;
	(*this)[top] = v;
	(*this)(R-1) = pad;
}

template<int R, class T> template<class U> inline
vector<R, T>::vector(const tmatrix_ndim<U, T> &v) {
	typedef typename bits::assign_dispatch<math::vector<R, T>, U>::handler handler;
	handler::go(*this, v);
}

template<int R, class T> template<class U> inline
vector<R, T>::vector(const math::vector<R, U> &v) {
	for (int i=0; i!=R; ++i)
		(*this)(i) = T(v(i));
}

} // namespace math
