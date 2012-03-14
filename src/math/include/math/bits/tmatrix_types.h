
namespace math {
namespace bits {

// the type of temporary storage required.
template<class T, bool Is_scalar>
struct tmatrix_type_helper {
	typedef const typename tmatrix2<T>::type return_type;
	typedef typename tmatrix2<T>::type mutable_return_type;
};
template<class T> struct tmatrix_type_helper<T, true> {
	typedef const typename T::scalar_type return_type;
	typedef typename T::scalar_type &mutable_return_type;
};

template<class T>
struct types : tmatrix_type_helper<T, (T::rows == 1 && T::columns == 1)> {};

} // namespace bits
} // namespace math
