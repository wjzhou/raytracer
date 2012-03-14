#include <math/matrix.h>

float math::det_bm(const bits::bm44 &m)
{
	return m(0,0) * det(matrix<3>(cofactor_bm<0,0>(m)))
		- m(1,0) * det(matrix<3>(cofactor_bm<1,0>(m)))
		+ m(2,0) * det(matrix<3>(cofactor_bm<2,0>(m)))
		- m(3,0) * det(matrix<3>(cofactor_bm<3,0>(m)));
}

const math::matrix<4> math::frustum(float l, float r, float b, float t, float n, float f)
{
	float n2 = 2 * n;
	float rl = r - l;
	float tb = t - b;
	float fn = f - n;

	matrix<4> dest = zero;

	dest(0,0) = n2/rl;
	dest(0,2) = (r+l)/rl;
	dest(1,1) = n2/tb;
	dest(1,2) = (t+b)/tb;
	dest(2,2) = -(f+n)/fn;
	dest(2,3) = -2*f*n/fn;
	dest(3,2) = -1;

	return dest;
}

const math::matrix<4> math::ortho(float l, float r, float b, float t, float n, float f)
{
	float rl = r - l;
	float tb = t - b;
	float fn = f - n;

	matrix<4> dest = zero;

	dest(0,0) = 2/rl;
	dest(0,3) = (r+l)/rl;
	dest(1,1) = 2/tb;
	dest(1,3) = -(t+b)/tb;
	dest(2,2) = -2/fn;
	dest(2,3) = (f+n)/fn;
	dest(3,3) = 1;

	return dest;
}

void math::bits::generic_assign_handler::go(bm44 &dest, matrix_unop<unop_translation, bm31> m)
{
	dest(0,3) = m.a.x;
	dest(1,3) = m.a.y;
	dest(2,3) = m.a.z;
	dest(0,1) = dest(0,2) = 0;
	dest(1,0) = dest(1,2) = 0;
	dest(2,0) = dest(2,1) = 0;
	dest(3,0) = dest(3,1) = dest(3,2) = 0;
	dest(0,0) = dest(1,1) = dest(2,2) = dest(3,3) = 1;
}

void math::bits::generic_assign_handler::go(bm44 &dest, matrix_unop<unop_scaling, bm31> src)
{
	dest(0,0) = src.a.x;
	dest(1,1) = src.a.y;
	dest(2,2) = src.a.z;
	dest(3,3) = 1;
	dest(0,1) = dest(0,2) = dest(0,3) = 0;
	dest(1,0) = dest(1,2) = dest(1,3) = 0;
	dest(2,0) = dest(2,1) = dest(2,3) = 0;
	dest(3,0) = dest(3,1) = dest(3,2) = 0;
}

void math::bits::generic_assign_handler::go(bm44 &dest, matrix_unop<unop_scaling, scalar_keeper<float> > src)
{
	dest(0,0) = dest(1,1) = dest(2,2) = src.a.f;
	dest(3,3) = 1;
	dest(0,1) = dest(0,2) = dest(0,3) = 0;
	dest(1,0) = dest(1,2) = dest(1,3) = 0;
	dest(2,0) = dest(2,1) = dest(2,3) = 0;
	dest(3,0) = dest(3,1) = dest(3,2) = 0;
}

void math::bits::generic_assign_handler::go(bm44 &dest, matrix_binop<binop_rotation, bm31, scalar_keeper<float> > src)
{
	vector<3> u = norm(src.a.matrix());
	matrix<3> S;
	S <<    0.f, -u.z,  u.y,
	      u.z,    0.f, -u.x,
	     -u.y,  u.x,    0.f;

	matrix<3> uut = u*transpose(u);
	matrix<3> I = identity;
	matrix<4> & MATH2_RESTRICT R = dest.matrix();
	float a = src.b.f;

	R[r02,c02] = uut + float(cos(a))*(I - uut) + float(sin(a))*S;
	R[r3,c02] = zero;
	R[r02,c3] = zero;
	R(3,3) = 1;
}

void math::bits::generic_assign_handler::go(bm44 &dest, matrix_binop<binop_rotation, 
	x_axis_type<float>, scalar_keeper<float> > src)
{
	float c = cos(src.b.f), s = sin(src.b.f);

	dest(1,1) =  c;
	dest(2,2) =  c;
	dest(1,2) = -s;
	dest(2,1) =  s;

	dest(0,1) = dest(0,2) = 0;
	dest(1,0) = dest(2,0) = 0;
	dest(0,0) = 1;

	dest(0,3) = dest(1,3) = dest(2,3) = dest(3,0) = dest(3,1)
		= dest(3,2) = 0;
	dest(3,3) = 1;
}

void math::bits::generic_assign_handler::go(bm44 &dest, matrix_binop<binop_rotation, 
	y_axis_type<float>, scalar_keeper<float> > src)
{
	float c = cos(src.b.f), s = sin(src.b.f);

	dest(0,0) =  c;
	dest(2,2) =  c;
	dest(2,0) = -s;
	dest(0,2) =  s;

	dest(0,1) = dest(1,2) = 0;
	dest(1,0) = dest(2,1) = 0;
	dest(1,1) = 1;

	dest(0,3) = dest(1,3) = dest(2,3) = dest(3,0) = dest(3,1)
		= dest(3,2) = 0;
	dest(3,3) = 1;
}

void math::bits::generic_assign_handler::go(bm44 &dest, matrix_binop<binop_rotation, 
	z_axis_type<float>, scalar_keeper<float> > src)
{
	float c = cos(src.b.f), s = sin(src.b.f);

	dest(0,0) =  c;
	dest(1,1) =  c;
	dest(0,1) = -s;
	dest(1,0) =  s;

	dest(0,2) = dest(1,2) = 0;
	dest(2,0) = dest(2,1) = 0;
	dest(2,2) = 1;

	dest(0,3) = dest(1,3) = dest(2,3) = dest(3,0) = dest(3,1)
		= dest(3,2) = 0;
	dest(3,3) = 1;
}

void math::bits::generic_assign_handler::go(bm44 &dest, matrix_unop<unop_adjoint, bm44> src)
{
	matrix<4> & MATH2_RESTRICT R = dest.matrix();
	const matrix<4> & MATH2_RESTRICT S = src.a.matrix();

	R(0,0) =  det(matrix<3>(cofactor<0,0>(S)));
	R(1,0) = -det(matrix<3>(cofactor<0,1>(S)));
	R(2,0) =  det(matrix<3>(cofactor<0,2>(S)));
	R(3,0) = -det(matrix<3>(cofactor<0,3>(S)));

	R(0,1) = -det(matrix<3>(cofactor<1,0>(S)));
	R(1,1) =  det(matrix<3>(cofactor<1,1>(S)));
	R(2,1) = -det(matrix<3>(cofactor<1,2>(S)));
	R(3,1) =  det(matrix<3>(cofactor<1,3>(S)));

	R(0,2) =  det(matrix<3>(cofactor<2,0>(S)));
	R(1,2) = -det(matrix<3>(cofactor<2,1>(S)));
	R(2,2) =  det(matrix<3>(cofactor<2,2>(S)));
	R(3,2) = -det(matrix<3>(cofactor<2,3>(S)));

	R(0,3) = -det(matrix<3>(cofactor<3,0>(S)));
	R(1,3) =  det(matrix<3>(cofactor<3,1>(S)));
	R(2,3) = -det(matrix<3>(cofactor<3,2>(S)));
	R(3,3) =  det(matrix<3>(cofactor<3,3>(S)));
}

void math::bits::generic_assign_handler::go(bm44 &dest, matrix_unop<unop_inverse, bm44> src)
{
	matrix<4> & MATH2_RESTRICT R = dest.matrix();
	const matrix<4> & MATH2_RESTRICT S = src.a.matrix();

	float det_s = det(S);
	float d = 1 / det_s;

	// dest = adjoint(src.a) / det(src.a)
	R(0,0) = d *  det(matrix<3>(cofactor<0,0>(S)));
	R(1,0) = d * -det(matrix<3>(cofactor<0,1>(S)));
	R(2,0) = d *  det(matrix<3>(cofactor<0,2>(S)));
	R(3,0) = d * -det(matrix<3>(cofactor<0,3>(S)));

	R(0,1) = d * -det(matrix<3>(cofactor<1,0>(S)));
	R(1,1) = d *  det(matrix<3>(cofactor<1,1>(S)));
	R(2,1) = d * -det(matrix<3>(cofactor<1,2>(S)));
	R(3,1) = d *  det(matrix<3>(cofactor<1,3>(S)));

	R(0,2) = d *  det(matrix<3>(cofactor<2,0>(S)));
	R(1,2) = d * -det(matrix<3>(cofactor<2,1>(S)));
	R(2,2) = d *  det(matrix<3>(cofactor<2,2>(S)));
	R(3,2) = d * -det(matrix<3>(cofactor<2,3>(S)));

	R(0,3) = d * -det(matrix<3>(cofactor<3,0>(S)));
	R(1,3) = d *  det(matrix<3>(cofactor<3,1>(S)));
	R(2,3) = d * -det(matrix<3>(cofactor<3,2>(S)));
	R(3,3) = d *  det(matrix<3>(cofactor<3,3>(S)));
}
