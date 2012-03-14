
namespace math {
namespace bits {

// 4x4 float matrix
template<>
class MATH2_SIMD4_ALIGN_PRE matrix_storage<4, 4, float, true> {
	float m_data[4][4];
public:
	float &operator()(int r, int c) { return m_data[c][r]; }
	float operator()(int r, int c) const { return m_data[c][r]; }
	float *data() { return &m_data[0][0]; }
	const float *data() const { return &m_data[0][0]; }

	matrix_storage() {}
	matrix_storage(const matrix_storage &);
	matrix_storage &operator=(const matrix_storage &);
} MATH2_SIMD4_ALIGN_POST;

// 4x1 float vector
template<>
class MATH2_SIMD4_ALIGN_PRE matrix_storage<4, 1, float, true> {
public:
 	union { float x; float s; float r; };
 	union { float y; float t; float g; };
 	union { float z; float u; float b; };
	union { float w; float v; float a; };

	float &operator()(int r, int) { return (&x)[r]; }
	float operator()(int r, int) const { return (&x)[r]; }
	float &operator()(int r) { return (&x)[r]; }
	float operator()(int r) const { return (&x)[r]; }
	float *data() { return &x; }
	const float *data() const { return &x; }

	void assign(float a, float b, float c, float d)
		{ x = a; y = b; z = c; w = d; }

	matrix_storage() {}
	matrix_storage(const matrix_storage &);
	matrix_storage &operator=(const matrix_storage &);
} MATH2_SIMD4_ALIGN_POST;

} // namespace bits
} // namespace math
