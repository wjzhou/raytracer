
namespace math {
namespace bits {

template<class A>
struct matrix_unop<unop_negate, A> {
	typedef typename A::scalar_type scalar_type;
	enum { rows = A::rows };
	enum { columns = A::columns };
	enum { is_storage = false };
	enum { is_lvalue = false };
	enum { error = A::error };
	enum { element_op = A::element_op };
	typedef matrix_unop<unop_negate, A> base_type;
	typename matrix_ref<A>::type a;
	matrix_unop(const A &a_) : a(a_) {}
	template<int R, int C> scalar_type element() const
		{ return -a.template element<R, C>(); }
};

template<class A>
struct matrix_unop<unop_reciprocal, A> {
	typedef typename A::scalar_type scalar_type;
	enum { rows = A::rows,
		columns = A::columns };
	enum { is_storage = false };
	enum { is_lvalue = false };
	enum { error = A::error };
	enum { element_op = A::element_op };
	typedef matrix_unop<unop_reciprocal, A> base_type;
	typename matrix_ref<A>::type a;
	matrix_unop(const A &a_) : a(a_) {}
	template<int R, int C> scalar_type element() const
		{ return 1 / a.template element<R, C>(); }
};

template<class A>
struct matrix_unop<unop_adjoint, A> {
	typedef typename A::scalar_type scalar_type;
	enum { rows = A::columns,
		columns = A::rows };
	enum { is_storage = false };
	enum { is_lvalue = false };
	enum { error = A::error };
	enum { element_op = false };
	typedef matrix_unop<unop_adjoint, A> base_type;
	typename matrix_ref<A>::type a;
	matrix_unop(const A &a_) : a(a_) {}
};

template<class A>
struct matrix_unop<unop_inverse, A> {
	typedef typename A::scalar_type scalar_type;
	enum { rows = A::rows,
		columns = A::columns };
	enum { is_storage = false };
	enum { is_lvalue = false };
	enum { error = A::error || rows != columns };
	enum { element_op = false };
	typedef matrix_unop<unop_inverse, A> base_type;
	typename matrix_ref<A>::type a;
	matrix_unop(const A &a_) : a(a_) {}
};

template<class A>
struct matrix_unop<unop_wdiv, A> {
	typedef typename A::scalar_type scalar_type;
	enum { rows = 3,
		columns = 1 };
	enum { is_storage = false };
	enum { is_lvalue = false };
	enum { error = A::error || A::rows != 4
		|| A::columns != 1 };
	enum { element_op = A::is_storage };
	typedef matrix_unop<unop_wdiv, A> base_type;
	typename matrix_ref<A>::type a;
	matrix_unop(const A &a_) : a(a_) {}
	template<int R, int C> scalar_type element() const
		{ return a.template element<R, 0>() / a.template element<3, 0>(); }
};

template<class A>
struct matrix_unop<unop_normalize, A> {
	typedef typename A::scalar_type scalar_type;
	enum { rows = A::rows,
		columns = 1 };
	enum { is_storage = false };
	enum { is_lvalue = false };
	enum { error = A::error || A::columns != 1 };
	enum { element_op = false };
	typedef matrix_unop<unop_normalize, A> base_type;
	typename matrix_ref<A>::type a;
	matrix_unop(const A &a_) : a(a_) {}
};

template<class A>
struct matrix_unop<unop_translation, A> {
	typedef typename A::scalar_type scalar_type;
	enum { rows = 4,
		columns = 4 };
	enum { is_storage = false };
	enum { is_lvalue = false };
	enum { error = A::error || A::rows != 3 || A::columns != 1 };
	enum { element_op = false };
	typedef matrix_unop<unop_translation, A> base_type;
	typename matrix_ref<A>::type a;
	matrix_unop(const A &a_) : a(a_) {}
};

template<class A>
struct matrix_unop<unop_scaling, A> {
	typedef typename A::scalar_type scalar_type;
	enum { rows = 4,
		columns = 4 };
	enum { is_storage = false };
	enum { is_lvalue = false };
	enum { error = A::error };
	enum { element_op = false };
	typedef matrix_unop<unop_scaling, A> base_type;
	typename matrix_ref<A>::type a;
	matrix_unop(const A &a_) : a(a_) {}
};

} // namespace bits
} // namespace math
