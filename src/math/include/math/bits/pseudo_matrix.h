
namespace math {

struct identity_t {};
struct zero_t {
	// TODO: should be defined by scalar_traits
	operator float() const { return 0.0f; }
	operator double() const { return 0.0; }
	operator long double() const { return 0.0L; }
};

namespace bits {

// scalar constant expression
template<class Type>
struct scalar_keeper {
	typedef Type scalar_type;
	enum { rows = 1 };
	enum { columns = 1 };
	enum { is_storage = true };
	enum { is_lvalue = false };
	enum { error = false };
	enum { element_op = true };
	typedef scalar_keeper<Type> base_type;
	Type f;
	scalar_keeper() {}
	scalar_keeper(Type v) : f(v) {}
	template<int R, int C> Type element() const { return f; }
};

// base class for axis constant types
template<class Type>
struct axis_type {
	typedef Type scalar_type;
	enum { rows = 3 };
	enum { columns = 1 };
	enum { is_storage = true };
	enum { is_lvalue = false };
	enum { error = false };
	enum { element_op = true };
};

// axis constant types
template<class Type>
struct x_axis_type : axis_type<Type> {
	typedef x_axis_type base_type;
	template<int R, int C> static Type element() { return Type(R == 0); }
};
template<class Type>
struct y_axis_type : axis_type<Type> {
	typedef y_axis_type base_type;
	template<int R, int C> static Type element() { return Type(R == 1); }
};
template<class Type>
struct z_axis_type : axis_type<Type> {
	typedef z_axis_type base_type;
	template<int R, int C> static Type element() { return Type(R == 2); }
};

} // namespace bits
} // namespace math
