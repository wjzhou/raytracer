
namespace math {
namespace bits {

// unary operations

struct unop_copy {};
struct unop_negate {};
struct unop_inverse {};
struct unop_adjoint {};
struct unop_reciprocal {};
struct unop_wdiv {}; // perspective division 4x1 -> 3x1
struct unop_normalize {}; // normalize vector
struct unop_translation {}; // make a translation matrix
struct unop_scaling {}; // make a scaling matrix
template<class I> struct unop_index {}; // apply fancy indexing
template<class I> struct unop_cindex {}; // apply fancy indexing (const)


// binary operations

struct binop_mul {};
template<int Common> struct binop_mmul {}; // matrix multiplication
template<int R> struct binop_dot {}; // scalar product
struct binop_div {};
struct binop_add {};
struct binop_sub {};
struct binop_cross {}; // vector product
struct binop_expand {}; // add element(s) to vector
struct binop_rotation {}; // make a rotation matrix


// index modes

struct index_transpose {};
template<int R, int C> struct index_cofactor {}; // remove row R and column C
template<int R1, int C1, int R2, int C2, bool RestrictR = true,
	bool RestrictC = RestrictR> struct index_submatrix {};
	// select a submatrix where R1 <= R <= R2, C1 <= C <= C2
template<int X, int Y, int Z = -98, int W = -99> struct index_swizzle {};
	// swizzle vector elements
template<int R, int C> struct index_element {}; // select a matrix element
template<class I, class J> struct index_sequence {};
	// concatenate indexing transformations
template<class I, class J> struct index_stack {};
	// stack submatrices

} // namespace bits
} // namespace math
