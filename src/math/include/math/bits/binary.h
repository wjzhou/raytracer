
namespace math {
namespace bits {

template<class A, class B>
struct matrix_binop<binop_mul, A, B> {
	typedef typename A::scalar_type scalar_type;
	typedef typename select_matrix<A, B>::type possibly_A;
	enum { rows = possibly_A::rows,
		columns = possibly_A::columns };
	enum { is_storage = false };
	enum { is_lvalue = false };
	enum { error = A::error || B::error };
	enum { element_op = A::element_op && B::element_op };
	typedef matrix_binop<binop_mul, A, B> base_type;
	typename matrix_ref<A>::type a;
	typename matrix_ref<B>::type b;
	matrix_binop(const A &a_, const B &b_) : a(a_), b(b_) {}
	template<int R, int C> scalar_type element() const
		{ return a.template element<R, C>() * b.template element<R, C>(); }
};

template<class A, class B>
struct matrix_binop<binop_cross, A, B> {
	typedef typename A::scalar_type scalar_type;
	enum { rows = 3,
		columns = 1 };
	enum { is_storage = false };
	enum { is_lvalue = false };
	enum { error = A::error || B::error
		|| !is_vector_3<A>::value || !is_vector_3<B>::value };
	enum { element_op = A::is_storage && B::is_storage };
	typedef matrix_binop<binop_cross, A, B> base_type;
	typename matrix_ref<A>::type a;
	typename matrix_ref<B>::type b;
	matrix_binop(const A &a_, const B &b_) : a(a_), b(b_) {}
	template<int R, int C> scalar_type element() const {
		enum { e1 = (R+1) % 3 };
		enum { e2 = (R+2) % 3 };
		return a.template element<e1, 0>() * b.template element<e2, 0>()
			- a.template element<e2, 0>() * b.template element<e1, 0>();
	}
};

template<class A, class B>
struct matrix_binop<binop_div, A, B> {
	typedef typename A::scalar_type scalar_type;
	typedef typename select_matrix<A, B>::type possibly_A;
	enum { rows = possibly_A::rows,
		columns = possibly_A::columns };
	enum { is_storage = false };
	enum { is_lvalue = false };
	enum { error = A::error || B::error };
	enum { element_op = A::element_op && B::element_op };
	typedef matrix_binop<binop_div, A, B> base_type;
	typename matrix_ref<A>::type a;
	typename matrix_ref<B>::type b;
	matrix_binop(const A &a_, const B &b_) : a(a_), b(b_) {}
	template<int R, int C> scalar_type element() const
		{ return a.template element<R, C>() / b.template element<R, C>(); }
};

template<class A, class B>
struct matrix_binop<binop_add, A, B> {
	typedef typename A::scalar_type scalar_type;
	enum { rows = A::rows,
		columns = A::columns };
	enum { is_storage = false };
	enum { is_lvalue = false };
	enum { error = A::error || B::error || int(A::rows) != B::rows
		|| int(A::columns) != B::columns };
	enum { element_op = A::element_op && B::element_op };
	typedef matrix_binop<binop_add, A, B> base_type;
	typename matrix_ref<A>::type a;
	typename matrix_ref<B>::type b;
	matrix_binop(const A &a_, const B &b_) : a(a_), b(b_) {}
	template<int R, int C> scalar_type element() const
		{ return a.template element<R, C>() + b.template element<R, C>(); }
};

template<class A, class B>
struct matrix_binop<binop_sub, A, B> {
	typedef typename A::scalar_type scalar_type;
	enum { rows = A::rows,
		columns = B::columns };
	enum { is_storage = false };
	enum { is_lvalue = false };
	enum { error = A::error || B::error || A::rows != B::rows
		|| int(A::columns) != B::columns };
	enum { element_op = A::element_op && B::element_op };
	typedef matrix_binop<binop_sub, A, B> base_type;
	typename matrix_ref<A>::type a;
	typename matrix_ref<B>::type b;
	matrix_binop(const A &a_, const B &b_) : a(a_), b(b_) {}
	template<int R, int C> scalar_type element() const
		{ return a.template element<R, C>() - b.template element<R, C>(); }
};

template<class A, class B>
struct matrix_binop<binop_expand, A, B> {
	typedef typename A::scalar_type scalar_type;
	enum { rows = A::rows + B::rows,
		columns = 1 };
	enum { is_storage = false };
	enum { is_lvalue = false };
	enum { error = A::error || B::error };
	enum { element_op = false };
	typedef matrix_binop<binop_expand, A, B> base_type;
	typename matrix_ref<A>::type a;
	typename matrix_ref<B>::type b;
	matrix_binop(const A &a_, const B &b_) : a(a_), b(b_) {}
};

template<class A, class B>
struct matrix_binop<binop_rotation, A, B> {
	typedef typename A::scalar_type scalar_type;
	enum { rows = 4,
		columns = 4 };
	enum { is_storage = false };
	enum { is_lvalue = false };
	enum { error = A::error || B::error };
	enum { element_op = false };
	typedef matrix_binop<binop_rotation, A, B> base_type;
	typename matrix_ref<A>::type a;
	typename matrix_ref<B>::type b;
	matrix_binop(const A &a_, const B &b_) : a(a_), b(b_) {}
};

} // namespace bits
} // namespace math
