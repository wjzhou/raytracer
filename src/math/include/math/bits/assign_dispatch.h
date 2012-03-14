
namespace math {
namespace bits {

// expression dispatch

struct erroneous_expression_handler;

template<class Op, class D, class S, int R, int C, bool Simd>
struct assign_dispatch_elop_2 {
	// normal elop
	typedef assign_elop_handler<D, Op, R*C> 
		handler;
};
template<class Op, class D, class S, int R, int C>
struct assign_dispatch_elop_2<Op, D, S, R, C, true> {
	// simd elop
	typedef simd::simd_assign_handler<Op> handler;
};

template<class Op, class D, class S, int DR, int DC, int SR, int SC>
struct assign_dispatch_elop {
	// size mismatch
	typedef erroneous_expression_handler handler;
};
template<class Op, class D, class S, int R, int C>
struct assign_dispatch_elop<Op, D, S, R, C, R, C> {
	// correct size
	typedef typename D::base_type DB;
	typedef typename S::base_type SB;
	typedef typename assign_dispatch_elop_2<Op, DB, SB, R, C, 
		simd::simd_assign_specialized<Op, DB, SB>::value>::handler 
		handler;
};

template<class Op, class D, class S>
struct assign_op {
	typedef typename assign_dispatch_elop<Op, D, S, D::rows, D::columns,
		S::rows, S::columns>::handler handler;
};

template<class D, class S, bool ElOp, bool Simd>
struct assign_dispatch_2 {
	// generic
	typedef generic_assign_handler handler;
};
template<class D, class S, bool ElOp>
struct assign_dispatch_2<D, S, ElOp, true> {
	// simd specialized
	typedef simd::simd_assign_handler<unop_copy> handler;
};
template<class D, class S>
struct assign_dispatch_2<D, S, true, false> {
	// element_op
	typedef typename assign_dispatch_elop<unop_copy, D, S, D::rows,
		D::columns, S::rows, S::columns>::handler handler;
};

template<class D, class S, bool Error>
struct assign_dispatch_1 { // detect errors
	typedef erroneous_expression_handler handler;
};
template<class D, class S>
struct assign_dispatch_1<D, S, false> { // matrix result
	typedef typename assign_dispatch_2<D, S, S::element_op, 
		simd::simd_assign_specialized<unop_copy, D, S>::value>::handler 
		handler;
};

template<class D, class S> struct assign_dispatch {
	typedef typename D::base_type DB;
	typedef typename S::base_type SB;
	enum { error = S::error || D::error || !D::is_lvalue };
	typedef typename assign_dispatch_1<DB, SB, error>::handler handler;
};


// more convenient than assign_dispatch, but potentially less efficient
template<class D, class S> inline
void assign_matrix(D &dest, const S &src) {
	typedef typename assign_dispatch<D, S>::handler handler;
	handler::go(dest, src);
}

} // namespace bits
} // namespace math
