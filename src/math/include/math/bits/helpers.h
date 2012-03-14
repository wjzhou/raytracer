
namespace math {
namespace bits {

typedef basic_matrix<2, 1, float> bm21;
typedef basic_matrix<3, 1, float> bm31;
typedef basic_matrix<4, 1, float> bm41;
typedef basic_matrix<1, 2, float> bm12;
typedef basic_matrix<2, 2, float> bm22;
typedef basic_matrix<3, 2, float> bm32;
typedef basic_matrix<4, 2, float> bm42;
typedef basic_matrix<1, 3, float> bm13;
typedef basic_matrix<2, 3, float> bm23;
typedef basic_matrix<3, 3, float> bm33;
typedef basic_matrix<4, 3, float> bm43;
typedef basic_matrix<1, 4, float> bm14;
typedef basic_matrix<2, 4, float> bm24;
typedef basic_matrix<3, 4, float> bm34;
typedef basic_matrix<4, 4, float> bm44;

// used for assignment
template<class Type>
struct zero_assigner_type {
	typedef zero_assigner_type base_type;
	template<int R, int C> static Type element() { return Type(0); }
};
template<class Type>
struct identity_assigner_type {
	typedef identity_assigner_type base_type;
	template<int R, int C> static Type element() { return Type(R == C); }
};

// find out which type should be used to hold references to expressions
// (const basic_matrix &, all others as themselves)
template<class T>
struct matrix_ref {
	typedef const T type;
	typedef T noconst_type;
};
template<int A, int B, class Type>
struct matrix_ref<basic_matrix<A, B, Type> > {
	typedef const basic_matrix<A, B, Type> & MATH2_RESTRICT type;
	typedef basic_matrix<A, B, Type> & MATH2_RESTRICT noconst_type;
};

template<class T, class U, bool Is_scalar>
struct select_matrix_helper { typedef T type; };
template<class T, class U>
struct select_matrix_helper<T, U, true> { typedef U type; };

// select the leftmost argument that is a matrix
template<class T, class U>
struct select_matrix {
	enum { ok = T::rows == 1 && T::columns == 1 };
	typedef typename select_matrix_helper<T, U, ok>::type type;
};

// for convenience. check if argument is a 3x1 matrix
template<class T> struct is_vector_3
	{ enum { value = T::rows == 3 && T::columns == 1 }; };

// the type of temporary storage required.
template<class T, bool Is_scalar>
struct result_type_helper {
	typedef basic_matrix<T::rows, T::columns, typename T::scalar_type> type;
};
template<class T> struct result_type_helper<T, true> {
	typedef scalar_keeper<typename T::scalar_type> type;
};

template<class T> struct result_type
	: result_type_helper<T, (T::rows == 1 && T::columns == 1)> {};

// check size equality
template<int R1, int C1, int R2, int C2> struct assert_size {};
template<int R, int C> struct assert_size<R, C, R, C> { enum { ok = 1 }; };

} // namespace bits
} // namespace math
