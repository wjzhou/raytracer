
namespace math {
namespace bits {

// compile-time if
template<bool Condition, class A, class B>
struct if_bool_type {
	typedef A type;
};
template<class A, class B>
struct if_bool_type<false, A, B> {
	typedef B type;
};

} // namespace bits

// should be wrapped around matrix expressions that are strictly for
// initialization to avoid having to write two constructor/assignment
// pairs per initializer
// TODO: is this used/needed?
template<class Base, class Type>
class tmatrix_ndim : public Base {
public:
	tmatrix_ndim() {}
	template<class A> explicit tmatrix_ndim(const A &a) : Base(a) {}
	template<class A, class B> tmatrix_ndim(const A &a, const B &b)
		: Base(a, b) {}
};

// wrapped around matrix expressions by tmatrix_type to make overloading based
// on size possible. the type most operators accept
template<int Rows, int Cols, class Base, class Type>
class tmatrix_dim : public Base {
	struct dummy {};
public:
	tmatrix_dim() {}
	tmatrix_dim(typename bits::if_bool_type<Rows == 1 && Cols == 1, const Type &, dummy>::type value)
		{ Base::template element<0,0>() = value; }
	template<class A> explicit tmatrix_dim(A &a) : Base(a) {}
	template<class A> explicit tmatrix_dim(const A &a) : Base(a) {}
	template<class A, class B> tmatrix_dim(const A &a, const B &b)
		: Base(a, b) {}

	tmatrix_dim &operator*=(Type);
	tmatrix_dim &operator/=(Type);

	tmatrix_dim &operator=(zero_t);
	tmatrix_dim &operator=(identity_t);

	template<class T>
	tmatrix_dim &operator=(const tmatrix_dim<Rows, Cols, T, Type> &);
	template<class T>
	tmatrix_dim &operator=(const tmatrix_ndim<T, Type> &);

	template<class A>
	tmatrix_dim &operator*=(const tmatrix_dim<Rows, 1, A, Type> &);
	template<class A>
	tmatrix_dim &operator/=(const tmatrix_dim<Rows, 1, A, Type> &);

	template<class A>
	tmatrix_dim &operator*=(const tmatrix_dim<Cols != 1 ? Cols : 100, Rows, A, Type> &);
	template<class A>
	tmatrix_dim &operator+=(const tmatrix_dim<Rows, Cols, A, Type> &);
	template<class A>
	tmatrix_dim &operator-=(const tmatrix_dim<Rows, Cols, A, Type> &);

	template<class I>
	typename bits::types<bits::matrix_unop<bits::unop_index<I>, Base> >::mutable_return_type
		operator[](indexer<I>);
	template<class I>
	typename bits::types<bits::matrix_unop<bits::unop_cindex<I>, Base> >::return_type
		operator[](indexer<I>) const;

	operator typename bits::if_bool_type<Rows == 1 && Cols == 1, Type &, dummy>::type () { return Base::template element<0,0>(); }
};

// wrapped around expressions by tmatrix. used for early detection of
// illegal operations
template<bool Error, bool Is_scalar, bool Lvalue, class Base>
struct tmatrix2_helper {
	// error - cannot be used
};
template<class Base>
struct tmatrix2_helper<false, false, true, Base> {
	// not scalar, l-value
	typedef typename Base::scalar_type scalar_type;
	typedef tmatrix_dim<Base::rows, Base::columns, Base, scalar_type> type;
};
template<class Base>
struct tmatrix2_helper<false, false, false, Base> {
	// not scalar, not l-value
	typedef typename Base::scalar_type scalar_type;
	typedef tmatrix_dim<Base::rows, Base::columns, Base, scalar_type> type;
};
template<class Base>
struct tmatrix2_helper<false, true, true, Base> {
	// scalar, l-value. disable matrix operations (elsewhere)
	typedef typename Base::scalar_type scalar_type;
	typedef tmatrix_dim<Base::rows, Base::columns, Base, scalar_type> type;
};
template<class Base>
struct tmatrix2_helper<false, true, false, Base> {
	// scalar, not l-value. disable matrix operations
	typedef typename Base::scalar_type scalar_type;

	struct type : private Base {
		template<class A> explicit type(const A &a) : Base(a) {}
		template<class A, class B> type(const A &a, const B &b) : Base(a, b) {}

		operator scalar_type() const { return Base::template element<0,0>(); }
	};
};

// selects superclasses to provide (only) the supported operations for
// expressions
template<class Base>
struct tmatrix2 {
	typedef typename tmatrix2_helper<Base::error, Base::rows == 1 && Base::columns == 1,
		Base::is_lvalue, Base>::type type;
};

} // namespace math
