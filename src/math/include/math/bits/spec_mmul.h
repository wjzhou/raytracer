
namespace math {
namespace bits {

// matrix multiplication for x1*1y, x2*2y, x3*3y, x4*4y
// implemented like this to avoid the (admittedly small) overhead suffered by
// introducing a helper class (important operation)
template<class A, class B>
struct matrix_binop<binop_mmul<1>, A, B> {
	typedef typename A::scalar_type scalar_type;
	enum { rows = A::rows,
		columns = B::columns };
	enum { is_storage = false };
	enum { is_lvalue = false };
	enum { error = A::error || B::error || int(A::columns) != B::rows };
	enum { element_op = A::element_op && B::element_op };
	typedef matrix_binop<binop_mmul<1>, A, B> base_type;
	typename matrix_ref<A>::type a;
	typename matrix_ref<B>::type b;
	matrix_binop(const A &a_, const B &b_) : a(a_), b(b_) {}
	template<int R, int C> float element() const {
		return a.template element<R, 0>() * b.template element<0, C>();
	}
};
template<class A, class B>
struct matrix_binop<binop_mmul<2>, A, B> {
	typedef typename A::scalar_type scalar_type;
	enum { rows = A::rows,
		columns = B::columns };
	enum { is_storage = false };
	enum { is_lvalue = false };
	enum { error = A::error || B::error || int(A::columns) != B::rows };
	enum { a_eo = A::is_storage || A::element_op && B::columns == 1 };
	enum { b_eo = B::is_storage || B::element_op && A::rows == 1 };
	enum { element_op = a_eo && b_eo };
	typedef matrix_binop<binop_mmul<2>, A, B> base_type;
	typename matrix_ref<A>::type a;
	typename matrix_ref<B>::type b;
	matrix_binop(const A &a_, const B &b_) : a(a_), b(b_) {}
	template<int R, int C> float element() const {
		return a.template element<R, 0>() * b.template element<0, C>()
			+ a.template element<R, 1>() * b.template element<1, C>();
	}
};
template<class A, class B>
struct matrix_binop<binop_mmul<3>, A, B> {
	typedef typename A::scalar_type scalar_type;
	enum { rows = A::rows,
		columns = B::columns };
	enum { is_storage = false };
	enum { is_lvalue = false };
	enum { error = A::error || B::error || int(A::columns) != B::rows };
	enum { a_eo = A::is_storage || A::element_op && B::columns == 1 };
	enum { b_eo = B::is_storage || B::element_op && A::rows == 1 };
	enum { element_op = a_eo && b_eo };
	typedef matrix_binop<binop_mmul<3>, A, B> base_type;
	typename matrix_ref<A>::type a;
	typename matrix_ref<B>::type b;
	matrix_binop(const A &a_, const B &b_) : a(a_), b(b_) {}
	template<int R, int C> float element() const {
		return a.template element<R, 0>() * b.template element<0, C>()
			+ a.template element<R, 1>() * b.template element<1, C>()
			+ a.template element<R, 2>() * b.template element<2, C>();
	}
};
template<class A, class B>
struct matrix_binop<binop_mmul<4>, A, B> {
	typedef typename A::scalar_type scalar_type;
	enum { rows = A::rows,
		columns = B::columns };
	enum { is_storage = false };
	enum { is_lvalue = false };
	enum { error = A::error || B::error || int(A::columns) != B::rows };
	enum { a_eo = A::is_storage || A::element_op && B::columns == 1 };
	enum { b_eo = B::is_storage || B::element_op && A::rows == 1 };
	enum { element_op = a_eo && b_eo };
	typedef matrix_binop<binop_mmul<4>, A, B> base_type;
	typename matrix_ref<A>::type a;
	typename matrix_ref<B>::type b;
	matrix_binop(const A &a_, const B &b_) : a(a_), b(b_) {}
	template<int R, int C> float element() const {
		return a.template element<R, 0>() * b.template element<0, C>()
			+ a.template element<R, 1>() * b.template element<1, C>()
			+ a.template element<R, 2>() * b.template element<2, C>()
			+ a.template element<R, 3>() * b.template element<3, C>();
	}
};

} // namespace bits
} // namespace math
