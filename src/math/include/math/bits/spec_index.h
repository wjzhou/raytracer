
namespace math {
namespace bits {

template<class I, class A>
struct matrix_unop<unop_index<I>, A> {
	typedef typename A::scalar_type scalar_type;
	typedef index_info<I, A> info;
	enum { rows = info::rows,
		columns = info::columns };
	enum { is_storage = A::is_storage };
	enum { is_lvalue = is_storage && !info::aliasing };
	enum { error = A::error || info::error };
	enum { element_op = (A::element_op && !info::aliasing)
		|| is_storage };

	typedef matrix_unop<unop_index<I>, A> base_type;

	typename matrix_ref<A>::noconst_type a;
	matrix_unop(A &a_) : a(a_) {}

	matrix_unop &operator=(const matrix_unop &m) {
		typedef typename assign_dispatch<matrix_unop, 
			matrix_unop>::handler handler;
		handler::go(*this, m);
		return *this;
	}

	template<int R, int C> scalar_type element() const {
		typedef typename info::template index<R, C> i;
		return a.template element<i::r, i::c>();
	}
	template<int R, int C> scalar_type &element() {
		typedef typename info::template index<R, C> i;
		return a.template element<i::r, i::c>();
	}
};

template<class I, class A>
struct matrix_unop<unop_cindex<I>, A> {
	typedef typename A::scalar_type scalar_type;
	typedef index_info<I, A> info;
	enum { rows = info::rows,
		columns = info::columns };
	enum { is_storage = A::is_storage };
	enum { is_lvalue = false };
	enum { error = A::error || info::error };
	enum { element_op = (A::element_op && !info::aliasing)
		|| is_storage };

	typedef matrix_unop<unop_cindex<I>, A> base_type;

	typename matrix_ref<A>::type a;
	matrix_unop(const A &a_) : a(a_) {}

	template<int R, int C> scalar_type element() const {
		typedef typename info::template index<R, C> i;
		return a.template element<i::r, i::c>();
	}
};

} // namespace bits
} // namespace math
