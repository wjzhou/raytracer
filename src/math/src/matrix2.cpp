#include <math/matrix.h>

void math::bits::generic_assign_handler::go(bm22 &dest, matrix_unop<unop_inverse, bm22> src)
{
	float det_src = det_bm(src.a);
	float d = 1.f / det_src;

	// dest = adjoint(src.a) / det(src.a)
	dest(0,0) = d * +src.a(1,1);
	dest(1,0) = d * -src.a(1,0);

	dest(0,1) = d * -src.a(0,1);
	dest(1,1) = d * +src.a(0,0);
}
