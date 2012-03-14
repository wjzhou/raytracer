
namespace math {
namespace bits {

// the type most matrix operations work with. subclass tmatrix<basic_matrix>
// to make your own matrix type. do not use basic_matrix directly
template<int Rows, int Cols, class Type>
class basic_matrix : public matrix_storage<Rows, Cols, Type, scalar_traits<Type>::is_pod> {
public:
	typedef Type scalar_type;

	enum { rows = Rows };
	enum { columns = Cols };
	enum { is_storage = true };
	enum { is_lvalue = true };
	enum { error = false };
	enum { element_op = true };
	typedef basic_matrix<Rows, Cols, Type> base_type;

	basic_matrix() {}
	// used for implicit evaluation by the select_* templates in
	// matrix_operators.tpp
	template<class T> basic_matrix(const T &m);

	template<int R, int C> Type element() const {
		enum { i = R+C*Rows };
		return basic_matrix::data()[i];
	}
	template<int R, int C> Type &element() {
		enum { i = R+C*Rows };
		return basic_matrix::data()[i];
	}

	math::matrix<Rows, Cols, Type> &matrix() {
		return *static_cast<math::matrix<Rows, Cols, Type> *>(this);
	}
	const math::matrix<Rows, Cols, Type> &matrix() const {
		return *static_cast<const math::matrix<Rows, Cols, Type> *>(this);
	}

	math::vector<Rows, Type> &vector() {
	
		typedef typename static_assert<Cols == 1>::test test;
		return *static_cast<math::vector<Rows, Type> *>(this);
	}
	const math::vector<Rows, Type> &vector() const {
		typedef typename static_assert<Cols == 1>::test test;
		return *static_cast<const math::vector<Rows, Type> *>(this);
	}
};

} // namespace bits
} // namespace math
