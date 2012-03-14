#include <math/matrix.h>

float math::det_bm(const bits::bm33 &m)
{
	return m(0,0) * det(matrix<2>(cofactor_bm<0,0>(m)))
		- m(1,0) * det(matrix<2>(cofactor_bm<1,0>(m)))
		+ m(2,0) * det(matrix<2>(cofactor_bm<2,0>(m)));
}

void math::bits::generic_assign_handler::go(bm33 &dest, matrix_unop<unop_adjoint, bm33> src)
{
	dest(0,0) = +det(matrix<2>(cofactor_bm<0,0>(src.a)));
	dest(1,0) = -det(matrix<2>(cofactor_bm<0,1>(src.a)));
	dest(2,0) = +det(matrix<2>(cofactor_bm<0,2>(src.a)));

	dest(0,1) = -det(matrix<2>(cofactor_bm<1,0>(src.a)));
	dest(1,1) = +det(matrix<2>(cofactor_bm<1,1>(src.a)));
	dest(2,1) = -det(matrix<2>(cofactor_bm<1,2>(src.a)));

	dest(0,2) = +det(matrix<2>(cofactor_bm<2,0>(src.a)));
	dest(1,2) = -det(matrix<2>(cofactor_bm<2,1>(src.a)));
	dest(2,2) = +det(matrix<2>(cofactor_bm<2,2>(src.a)));
}

void math::bits::generic_assign_handler::go(bm33 &dest, matrix_unop<unop_inverse, bm33> src)
{
	float det_src = det_bm(src.a);
	float d = 1.f / det_src;

	// dest = adjoint(src.a) / det(src.a)
	dest(0,0) = d * +det(matrix<2>(cofactor_bm<0,0>(src.a)));
	dest(1,0) = d * -det(matrix<2>(cofactor_bm<0,1>(src.a)));
	dest(2,0) = d * +det(matrix<2>(cofactor_bm<0,2>(src.a)));

	dest(0,1) = d * -det(matrix<2>(cofactor_bm<1,0>(src.a)));
	dest(1,1) = d * +det(matrix<2>(cofactor_bm<1,1>(src.a)));
	dest(2,1) = d * -det(matrix<2>(cofactor_bm<1,2>(src.a)));

	dest(0,2) = d * +det(matrix<2>(cofactor_bm<2,0>(src.a)));
	dest(1,2) = d * -det(matrix<2>(cofactor_bm<2,1>(src.a)));
	dest(2,2) = d * +det(matrix<2>(cofactor_bm<2,2>(src.a)));
}
