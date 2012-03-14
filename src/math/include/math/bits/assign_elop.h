// assignment for elementwise expressions

// type of destination. undefined at end of file
#define RTYPE Type & MATH2_RESTRICT

namespace math {
namespace bits {

// identifies an assignment operation (=, *=, +=, ...)
template<class Op, class Type> struct element_assigner;

template<class Type> struct element_assigner<unop_copy, Type> {
	static void go(Type &d, Type s) { d = s; }
};
template<class Type> struct element_assigner<binop_mul, Type> {
	static void go(Type &d, Type s) { d *= s; }
};
template<class Type> struct element_assigner<binop_div, Type> {
	static void go(Type &d, Type s) { d /= s; }
};
template<class Type> struct element_assigner<binop_add, Type> {
	static void go(Type &d, Type s) { d += s; }
};
template<class Type> struct element_assigner<binop_sub, Type> {
	static void go(Type &d, Type s) { d -= s; }
};

template<class Type, class Op, int Size> struct assign_elop_handler {};

// implemented like this instead of with a recursive template in order to
// help the optimizer and to minimize "debugging bloat"

template<class Type, class Op> struct assign_elop_handler<Type, Op, 16> {
	template<class T> static void go(RTYPE d, T a);
};

template<class Type, class Op> struct assign_elop_handler<Type, Op, 12> {
	template<class T> static void go(RTYPE d, T a);
};

template<class Type, class Op> struct assign_elop_handler<Type, Op, 9> {
	template<class T> static void go(RTYPE d, T a);
};

template<class Type, class Op>
template<class T>
void assign_elop_handler<Type, Op, 16>::go(RTYPE d, T a)
{
	typedef math::bits::element_assigner<Op, typename Type::scalar_type> op;
	op::go(d.template element<0,0>(), a.template element<0,0>());
	op::go(d.template element<1,0>(), a.template element<1,0>());
	op::go(d.template element<2,0>(), a.template element<2,0>());
	op::go(d.template element<3,0>(), a.template element<3,0>());
	op::go(d.template element<0,1>(), a.template element<0,1>());
	op::go(d.template element<1,1>(), a.template element<1,1>());
	op::go(d.template element<2,1>(), a.template element<2,1>());
	op::go(d.template element<3,1>(), a.template element<3,1>());
	op::go(d.template element<0,2>(), a.template element<0,2>());
	op::go(d.template element<1,2>(), a.template element<1,2>());
	op::go(d.template element<2,2>(), a.template element<2,2>());
	op::go(d.template element<3,2>(), a.template element<3,2>());
	op::go(d.template element<0,3>(), a.template element<0,3>());
	op::go(d.template element<1,3>(), a.template element<1,3>());
	op::go(d.template element<2,3>(), a.template element<2,3>());
	op::go(d.template element<3,3>(), a.template element<3,3>());
}

template<class Type, class Op>
template<class T>
void assign_elop_handler<Type, Op, 12>::go(RTYPE d, T a)
{
	typedef element_assigner<Op, typename Type::scalar_type> op;
	enum { r = Type::rows };
	op::go(d.template element<0%r,0/r>(), a.template element<0%r,0/r>());
	op::go(d.template element<1%r,1/r>(), a.template element<1%r,1/r>());
	op::go(d.template element<2%r,2/r>(), a.template element<2%r,2/r>());
	op::go(d.template element<3%r,3/r>(), a.template element<3%r,3/r>());
	op::go(d.template element<4%r,4/r>(), a.template element<4%r,4/r>());
	op::go(d.template element<5%r,5/r>(), a.template element<5%r,5/r>());
	op::go(d.template element<6%r,6/r>(), a.template element<6%r,6/r>());
	op::go(d.template element<7%r,7/r>(), a.template element<7%r,7/r>());
	op::go(d.template element<8%r,8/r>(), a.template element<8%r,8/r>());
	op::go(d.template element<9%r,9/r>(), a.template element<9%r,9/r>());
	op::go(d.template element<10%r,10/r>(),a.template element<10%r,10/r>());
	op::go(d.template element<11%r,11/r>(),a.template element<11%r,11/r>());
}

template<class Type, class Op>
template<class T>
void assign_elop_handler<Type, Op, 9>::go(RTYPE d, T a)
{
	typedef element_assigner<Op, typename Type::scalar_type> op;
	enum { r = Type::rows };
	op::go(d.template element<0%r,0/r>(), a.template element<0%r,0/r>());
	op::go(d.template element<1%r,1/r>(), a.template element<1%r,1/r>());
	op::go(d.template element<2%r,2/r>(), a.template element<2%r,2/r>());
	op::go(d.template element<3%r,3/r>(), a.template element<3%r,3/r>());
	op::go(d.template element<4%r,4/r>(), a.template element<4%r,4/r>());
	op::go(d.template element<5%r,5/r>(), a.template element<5%r,5/r>());
	op::go(d.template element<6%r,6/r>(), a.template element<6%r,6/r>());
	op::go(d.template element<7%r,7/r>(), a.template element<7%r,7/r>());
	op::go(d.template element<8%r,8/r>(), a.template element<8%r,8/r>());
}

template<class Type, class Op> struct assign_elop_handler<Type, Op, 8> {
	template<class T> static void go(RTYPE d, T a)
	{
		typedef element_assigner<Op, typename Type::scalar_type> op;
		enum { r = Type::rows };
		op::go(d.template element<0%r,0/r>(),
			a.template element<0%r,0/r>());
		op::go(d.template element<1%r,1/r>(), 
			a.template element<1%r,1/r>());
		op::go(d.template element<2%r,2/r>(), 
			a.template element<2%r,2/r>());
		op::go(d.template element<3%r,3/r>(), 
			a.template element<3%r,3/r>());
		op::go(d.template element<4%r,4/r>(), 
			a.template element<4%r,4/r>());
		op::go(d.template element<5%r,5/r>(), 
			a.template element<5%r,5/r>());
		op::go(d.template element<6%r,6/r>(), 
			a.template element<6%r,6/r>());
		op::go(d.template element<7%r,7/r>(), 
			a.template element<7%r,7/r>());
	}
};

template<class Type, class Op> struct assign_elop_handler<Type, Op, 6> {
	template<class T> static void go(RTYPE d, T a)
	{
		typedef element_assigner<Op, typename Type::scalar_type> op;
		enum { r = Type::rows };
		op::go(d.template element<0%r,0/r>(), 
			a.template element<0%r,0/r>());
		op::go(d.template element<1%r,1/r>(), 
			a.template element<1%r,1/r>());
		op::go(d.template element<2%r,2/r>(), 
			a.template element<2%r,2/r>());
		op::go(d.template element<3%r,3/r>(), 
			a.template element<3%r,3/r>());
		op::go(d.template element<4%r,4/r>(), 
			a.template element<4%r,4/r>());
		op::go(d.template element<5%r,5/r>(), 
			a.template element<5%r,5/r>());
	}
};

template<class Type, class Op> struct assign_elop_handler<Type, Op, 4> {
	template<class T> static void go(RTYPE d, T a)
	{
		typedef element_assigner<Op, typename Type::scalar_type> op;
		enum { r = Type::rows };
		op::go(d.template element<0%r,0/r>(), 
			a.template element<0%r,0/r>());
		op::go(d.template element<1%r,1/r>(), 
			a.template element<1%r,1/r>());
		op::go(d.template element<2%r,2/r>(), 
			a.template element<2%r,2/r>());
		op::go(d.template element<3%r,3/r>(), 
			a.template element<3%r,3/r>());
	}
};
template<class Type> struct assign_elop_handler<Type, unop_copy, 4> {
	template<class T> static void go(RTYPE d, T a)
	{
		enum { r = Type::rows };
		d.template element<0%r,0/r>() = a.template element<0%r,0/r>();
		d.template element<1%r,1/r>() = a.template element<1%r,1/r>();
		d.template element<2%r,2/r>() = a.template element<2%r,2/r>();
		d.template element<3%r,3/r>() = a.template element<3%r,3/r>();
	}
};

template<class Type, class Op> struct assign_elop_handler<Type, Op, 3> {
	template<class T> static void go(RTYPE d, T a)
	{
		typedef element_assigner<Op, typename Type::scalar_type> op;
		enum { r = Type::rows };
		op::go(d.template element<0%r,0/r>(), 
			a.template element<0%r,0/r>());
		op::go(d.template element<1%r,1/r>(), 
			a.template element<1%r,1/r>());
		op::go(d.template element<2%r,2/r>(), 
			a.template element<2%r,2/r>());
	}
};
template<class Type> struct assign_elop_handler<Type, unop_copy, 3> {
	template<class T> static void go(RTYPE d, T a)
	{
		enum { r = Type::rows };
		d.template element<0%r,0/r>() = a.template element<0%r,0/r>();
		d.template element<1%r,1/r>() = a.template element<1%r,1/r>();
		d.template element<2%r,2/r>() = a.template element<2%r,2/r>();
	}
};

template<class Type, class Op> struct assign_elop_handler<Type, Op, 2> {
	template<class T> static void go(RTYPE d, T a)
	{
		typedef element_assigner<Op, typename Type::scalar_type> op;
		enum { r = Type::rows };
		op::go(d.template element<0%r,0/r>(), 
			a.template element<0%r,0/r>());
		op::go(d.template element<1%r,1/r>(), 
			a.template element<1%r,1/r>());
	}
};
template<class Type> struct assign_elop_handler<Type, unop_copy, 2> {
	template<class T> static void go(RTYPE d, T a)
	{
		enum { r = Type::rows };
		d.template element<0%r,0/r>() = a.template element<0%r,0/r>();
		d.template element<1%r,1/r>() = a.template element<1%r,1/r>();
	}
};

template<class Type, class Op> struct assign_elop_handler<Type, Op, 1> {
	template<class T> static void go(RTYPE d, T a)
	{
		typedef element_assigner<Op, typename Type::scalar_type> op;
		op::go(d.template element<0,0>(), a.template element<0,0>());
	}
};
template<class Type> struct assign_elop_handler<Type, unop_copy, 1> {
	template<class T> static void go(RTYPE d, T a)
	{
		d.template element<0,0>() = a.template element<0,0>();
	}
};

} // namespace bits
} // namespace math

// undefine type of destination
#undef RTYPE
