
namespace math {
namespace bits {

// scalar product
// same rationale as for mmul
template<class A, class B>
struct matrix_binop<binop_dot<1>, A, B> {
	typedef typename A::scalar_type scalar_type;
	enum { rows = 1,
		columns = 1 };
	enum { is_storage = false };
	enum { is_lvalue = false };
	enum { error = A::error || B::error || A::rows != 1
		|| B::rows != 1 || A::columns != 1 || B::columns != 1 };
	enum { element_op = A::element_op && B::element_op };
	typedef matrix_binop<binop_dot<1>, A, B> base_type;
	typename matrix_ref<A>::type a;
	typename matrix_ref<B>::type b;
	matrix_binop(const A &a_, const B &b_) : a(a_), b(b_) {}
	template<int R, int C> float element() const {
		return a.template element<0, 0>() * b.template element<0, 0>();
	}
};
template<class A, class B>
struct matrix_binop<binop_dot<2>, A, B> {
	typedef typename A::scalar_type scalar_type;
	enum { rows = 1,
		columns = 1 };
	enum { is_storage = false };
	enum { is_lvalue = false };
	enum { error = A::error || B::error || A::rows != 2
		|| B::rows != 2 || A::columns != 1 || B::columns != 1 };
	enum { element_op = A::element_op && B::element_op };
	typedef matrix_binop<binop_dot<1>, A, B> base_type;
	typename matrix_ref<A>::type a;
	typename matrix_ref<B>::type b;
	matrix_binop(const A &a_, const B &b_) : a(a_), b(b_) {}
	template<int R, int C> float element() const {
		return a.template element<0, 0>() * b.template element<0, 0>()
			+ a.template element<1, 0>() * b.template element<1, 0>();
	}
};
template<class A, class B>
struct matrix_binop<binop_dot<3>, A, B> {
	typedef typename A::scalar_type scalar_type;
	enum { rows = 1,
		columns = 1 };
	enum { is_storage = false };
	enum { is_lvalue = false };
	enum { error = A::error || B::error || A::rows != 3
		|| B::rows != 3 || A::columns != 1 || B::columns != 1 };
	enum { element_op = A::element_op && B::element_op };
	typedef matrix_binop<binop_dot<1>, A, B> base_type;
	typename matrix_ref<A>::type a;
	typename matrix_ref<B>::type b;
	matrix_binop(const A &a_, const B &b_) : a(a_), b(b_) {}
	template<int R, int C> float element() const {
		return a.template element<0, 0>() * b.template element<0, 0>()
			+ a.template element<1, 0>() * b.template element<1, 0>()
			+ a.template element<2, 0>() * b.template element<2, 0>();
	}
};
template<class A, class B>
struct matrix_binop<binop_dot<4>, A, B> {
	typedef typename A::scalar_type scalar_type;
	enum { rows = 1,
		columns = 1 };
	enum { is_storage = false };
	enum { is_lvalue = false };
	enum { error = A::error || B::error || A::rows != 4
		|| B::rows != 4 || A::columns != 1 || B::columns != 1 };
	enum { element_op = A::element_op && B::element_op };
	typedef matrix_binop<binop_dot<1>, A, B> base_type;
	typename matrix_ref<A>::type a;
	typename matrix_ref<B>::type b;
	matrix_binop(const A &a_, const B &b_) : a(a_), b(b_) {}
	template<int R, int C> float element() const {
		return a.template element<0, 0>() * b.template element<0, 0>()
			+ a.template element<1, 0>() * b.template element<1, 0>()
			+ a.template element<2, 0>() * b.template element<2, 0>()
			+ a.template element<3, 0>() * b.template element<3, 0>();
	}
};

} // namespace bits
} // namespace math
