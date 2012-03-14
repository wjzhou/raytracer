
namespace math {
namespace bits {

// generic matrix
template<int Rows, int Cols, class Type, bool POD>
class matrix_storage {
	Type m_data[Cols][Rows];
public:
	Type &operator()(int r, int c) { return m_data[c][r]; }
	Type operator()(int r, int c) const { return m_data[c][r]; }
	Type *data() { return &m_data[0][0]; }
	const Type *data() const { return &m_data[0][0]; }
};

// generic vector
template<int Rows, class Type, bool POD>
class matrix_storage<Rows, 1, Type, POD> {
	Type m_data[Rows];
public:
	Type &operator()(int r, int) { return m_data[r]; }
	Type operator()(int r, int) const { return m_data[r]; }
	Type &operator()(int r) { return m_data[r]; }
	Type operator()(int r) const { return m_data[r]; }
	Type *data() { return m_data; }
	const Type *data() const { return m_data; }
};

// 2x1 vector for POD types
template<class Type>
class matrix_storage<2, 1, Type, true> {
public:
	union { Type x; Type s; };
	union { Type y; Type t; };

	Type &operator()(int r, int) { return (&x)[r]; }
	Type operator()(int r, int) const { return (&x)[r]; }
	Type &operator()(int r) { return (&x)[r]; }
	Type operator()(int r) const { return (&x)[r]; }
	Type *data() { return &x; }
	const Type *data() const { return &x; }

	void assign(Type a, Type b) { x = a; y = b; }
};

// 2x1 vector for non-POD types
template<class Type>
class matrix_storage<2, 1, Type, false> {
public:
	Type x, y;

	Type &operator()(int r, int) { return (&x)[r]; }
	const Type &operator()(int r, int) const { return (&x)[r]; }
	Type &operator()(int r) { return (&x)[r]; }
	const Type &operator()(int r) const { return (&x)[r]; }
	Type *data() { return &x; }
	const Type *data() const { return &x; }

	void assign(const Type &a, const Type &b)
		{ x = a; y = b; }
};

// 3x1 vector for POD types
template<class Type>
class matrix_storage<3, 1, Type, true> {
public:
 	union { Type x; Type s; Type r; };
 	union { Type y; Type t; Type g; };
 	union { Type z; Type u; Type b; };

	Type &operator()(int r, int) { return (&x)[r]; }
	Type operator()(int r, int) const { return (&x)[r]; }
	Type &operator()(int r) { return (&x)[r]; }
	Type operator()(int r) const { return (&x)[r]; }
	Type *data() { return &x; }
	const Type *data() const { return &x; }

	void assign(Type a, Type b, Type c) { x = a; y = b; z = c; }
};

// 3x1 vector for non-POD types
template<class Type>
class matrix_storage<3, 1, Type, false> {
public:
 	Type x, y, z;

	Type &operator()(int r, int) { return (&x)[r]; }
	const Type &operator()(int r, int) const { return (&x)[r]; }
	Type &operator()(int r) { return (&x)[r]; }
	const Type &operator()(int r) const { return (&x)[r]; }
	Type *data() { return &x; }
	const Type *data() const { return &x; }

	void assign(const Type &a, const Type &b, const Type &c)
		{ x = a; y = b; z = c; }
};

// 4x1 vector for POD types
template<class Type>
class matrix_storage<4, 1, Type, true> {
public:
 	union { Type x; Type s; Type r; };
 	union { Type y; Type t; Type g; };
 	union { Type z; Type u; Type b; };
	union { Type w; Type v; Type a; };

	Type &operator()(int r, int) { return (&x)[r]; }
	Type operator()(int r, int) const { return (&x)[r]; }
	Type &operator()(int r) { return (&x)[r]; }
	Type operator()(int r) const { return (&x)[r]; }
	Type *data() { return &x; }
	const Type *data() const { return &x; }

	void assign(Type a, Type b, Type c, Type d)
		{ x = a; y = b; z = c; w = d; }
};

// 4x1 vector for non-POD types
template<class Type>
class matrix_storage<4, 1, Type, false> {
public:
 	Type x, y, z, w;

	Type &operator()(int r, int) { return (&x)[r]; }
	const Type &operator()(int r, int) const { return (&x)[r]; }
	Type &operator()(int r) { return (&x)[r]; }
	const Type &operator()(int r) const { return (&x)[r]; }
	Type *data() { return &x; }
	const Type *data() const { return &x; }

	void assign(const Type &a, const Type &b, const Type &c, const Type &d)
		{ x = a; y = b; z = c; w = d; }
};

} // namespace bits
} // namespace math
