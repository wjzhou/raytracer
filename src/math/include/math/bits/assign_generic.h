
namespace math {
namespace bits {

struct generic_assign_handler {

	// decompose, evaluate, recombine, retry
	template<int R, int C, class Op, class T, class ST>
	static void go(basic_matrix<R, C, ST> &d, matrix_unop<Op, T> s) {
		typedef matrix_unop<Op, typename result_type<typename 
			T::base_type>::type> combined;
		typedef typename assign_dispatch<basic_matrix<R, C, ST>, 
			combined>::handler handler;
		handler::go(d, combined(s.a));
	}

	// decompose, evaluate, recombine, retry (non-const indexed)
	template<int R, int C, class I, class T, class ST>
	static void go(basic_matrix<R, C, ST> &d, matrix_unop<unop_index<I>, T> s) {
		// recombine to const
		typedef matrix_unop<unop_cindex<I>, typename 
			result_type<typename T::base_type>::type> combined;
		typedef typename assign_dispatch<basic_matrix<R, C, ST>, 
			combined>::handler handler;
		handler::go(d, combined(s.a));
	}

	// decompose, evaluate, recombine, retry
	template<int R, int C, class Op, class T, class U, class ST>
	static void go(basic_matrix<R, C, ST> &d, matrix_binop<Op, T, U> s) {
		typedef typename result_type<typename T::base_type>::type TA;
		typedef typename result_type<typename U::base_type>::type UA;
		typedef matrix_binop<Op, TA, UA> combined;
		typedef typename assign_dispatch<basic_matrix<R, C, ST>, 
			combined>::handler handler;
		handler::go(d, combined(s.a, s.b));
	}

	// decompose, evaluate, recombine, retry (indexed)
	template<class I, class A, class Op, class T>
	static void go(matrix_unop<unop_index<I>, A> &d,
		matrix_unop<Op, T> s) {

		typedef matrix_unop<Op, typename result_type<typename 
			T::base_type>::type> combined;
		typedef typename assign_dispatch<matrix_unop<unop_index<I>, A>, 
			combined>::handler handler;
		handler::go(d, combined(s.a));
	}

	// decompose, evaluate, recombine, retry (indexed) (non-const indexed)
	template<class I, class A, class J, class T>
	static void go(matrix_unop<unop_index<I>, A> &d, 
		matrix_unop<unop_index<J>, T> s) {

		// recombine to const
		typedef matrix_unop<unop_cindex<J>, typename 
			result_type<typename T::base_type>::type> combined;
		typedef typename assign_dispatch<matrix_unop<
			unop_index<I>, A>, combined>::handler handler;
		handler::go(d, combined(s.a));
	}

	// decompose, evaluate, recombine, retry (indexed)
	template<class I, class A, class Op, class T, class U>
	static void go(matrix_unop<unop_index<I>, A> &d,
		matrix_binop<Op, T, U> s) {

		typedef typename result_type<typename T::base_type>::type TA;
		typedef typename result_type<typename U::base_type>::type UA;
		typedef matrix_binop<Op, TA, UA> combined;
		typedef typename assign_dispatch<matrix_unop<
			unop_index<I>, A>, combined>::handler handler;
		handler::go(d, combined(s.a, s.b));
	}

	// normalize vector
	static void go(bm21 &dest, matrix_unop<unop_normalize, bm21> src) {
		float l = sqrt(abs_squared_bm(src.a));
		dest.x = src.a.x / l;
		dest.y = src.a.y / l;
	}
	static void go(bm31 &dest, matrix_unop<unop_normalize, bm31> src) {
		float l = sqrt(abs_squared_bm(src.a));
		dest.x = src.a.x / l;
		dest.y = src.a.y / l;
		dest.z = src.a.z / l;
	}
	static void go(bm41 &dest, matrix_unop<unop_normalize, bm41> src) {
		float l = sqrt(abs_squared_bm(src.a));
		dest.x = src.a.x / l;
		dest.y = src.a.y / l;
		dest.z = src.a.z / l;
		dest.w = src.a.w / l;
	}

	// inverse
	static void go(bm22 &, matrix_unop<unop_inverse, bm22>);
	static void go(bm33 &, matrix_unop<unop_inverse, bm33>);
	static void go(bm44 &, matrix_unop<unop_inverse, bm44>);

	// adjoint
	static void go(bm33 &, matrix_unop<unop_adjoint, bm33>);
	static void go(bm44 &, matrix_unop<unop_adjoint, bm44>);
	static void go(bm22 &dest, matrix_unop<unop_adjoint, bm22> src)
	{
		dest(0,0) = +src.a(1,1);
		dest(1,0) = -src.a(1,0);
		dest(0,1) = -src.a(0,1);
		dest(1,1) = +src.a(0,0);
	}

	// make translation matrix
	static void go(bm44 &, matrix_unop<unop_translation, bm31>);

	// make scaling matrix
	static void go(bm44 &, matrix_unop<unop_scaling, bm31>);
	static void go(bm44 &, matrix_unop<unop_scaling, scalar_keeper<float> >);

	// make rotation matrix
	static void go(bm44 &, matrix_binop<binop_rotation, bm31, scalar_keeper<float> >);
	static void go(bm44 &, matrix_binop<binop_rotation, x_axis_type<float>, scalar_keeper<float> >);
	static void go(bm44 &, matrix_binop<binop_rotation, y_axis_type<float>, scalar_keeper<float> >);
	static void go(bm44 &, matrix_binop<binop_rotation, z_axis_type<float>, scalar_keeper<float> >);

	// expand vector
	static void go(bm31 &dest, matrix_binop<binop_expand, bm21, scalar_keeper<float> > src)
	{
		dest.x = src.a.x;
		dest.y = src.a.y;
		dest.z = src.b.f;
	}
	static void go(bm41 &dest, matrix_binop<binop_expand, bm31, scalar_keeper<float> > src)
	{
		dest.x = src.a.x;
		dest.y = src.a.y;
		dest.z = src.a.z;
		dest.w = src.b.f;
	}
	static void go(bm41 &dest, matrix_binop<binop_expand, bm21, bm21> src)
	{
		dest.x = src.a.x;
		dest.y = src.a.y;
		dest.z = src.b.x;
		dest.w = src.b.y;
	}
};

} // namespace bits
} // namespace math
