
namespace math {

// element selection
const indexer<bits::index_element<0,0> > x;
const indexer<bits::index_element<1,0> > y;
const indexer<bits::index_element<2,0> > z;
const indexer<bits::index_element<3,0> > w;
const indexer<bits::index_element<0,0> > s;
const indexer<bits::index_element<1,0> > t;
const indexer<bits::index_element<2,0> > u;
const indexer<bits::index_element<3,0> > v;
const indexer<bits::index_element<0,0> > r;
const indexer<bits::index_element<1,0> > g;
const indexer<bits::index_element<2,0> > b;
const indexer<bits::index_element<3,0> > a;

// transpose
const indexer<bits::index_transpose> tr;

// cartesian coordinate swizzling
const indexer<bits::index_swizzle<0,1> > xy;
const indexer<bits::index_swizzle<0,2> > xz;
const indexer<bits::index_swizzle<0,3> > xw;
const indexer<bits::index_swizzle<1,2> > yz;
const indexer<bits::index_swizzle<1,3> > yw;
const indexer<bits::index_swizzle<2,3> > zw;
const indexer<bits::index_swizzle<0,1,2> > xyz;
const indexer<bits::index_swizzle<0,1,3> > xyw;
const indexer<bits::index_swizzle<0,2,3> > xzw;
const indexer<bits::index_swizzle<1,2,3> > yzw;

// color swizzling
const indexer<bits::index_swizzle<0,1> > ra;
const indexer<bits::index_swizzle<0,1,2> > rgb;
const indexer<bits::index_swizzle<2,1,0> > bgr;
const indexer<bits::index_swizzle<2,1,0,3> > bgra;
const indexer<bits::index_swizzle<3,0,1,2> > argb;
const indexer<bits::index_swizzle<0,2,1,0> > abgr;

// texture coordinate swizzling
const indexer<bits::index_swizzle<0,1> > st;
const indexer<bits::index_swizzle<0,2> > sz;
const indexer<bits::index_swizzle<0,3> > sw;
const indexer<bits::index_swizzle<1,2> > tu;
const indexer<bits::index_swizzle<1,3> > tv;
const indexer<bits::index_swizzle<2,3> > uv;
const indexer<bits::index_swizzle<0,1,2> > stu;
const indexer<bits::index_swizzle<0,1,3> > stv;
const indexer<bits::index_swizzle<0,2,3> > suv;
const indexer<bits::index_swizzle<1,2,3> > tuv;

// submatrix selection
const indexer<bits::index_submatrix<0,0,1,1> > m22;
const indexer<bits::index_submatrix<0,0,1,2> > m23;
const indexer<bits::index_submatrix<0,0,1,3> > m24;
const indexer<bits::index_submatrix<0,0,2,1> > m32;
const indexer<bits::index_submatrix<0,0,2,2> > m33;
const indexer<bits::index_submatrix<0,0,2,3> > m34;
const indexer<bits::index_submatrix<0,0,3,1> > m42;
const indexer<bits::index_submatrix<0,0,3,2> > m43;

// row selection
const indexer<bits::index_submatrix<0,0,0,3,true,false> > r0;
const indexer<bits::index_submatrix<1,0,1,3,true,false> > r1;
const indexer<bits::index_submatrix<2,0,2,3,true,false> > r2;
const indexer<bits::index_submatrix<3,0,3,3,true,false> > r3;
const indexer<bits::index_submatrix<0,0,1,3,true,false> > r01;
const indexer<bits::index_submatrix<0,0,2,3,true,false> > r02;
const indexer<bits::index_submatrix<1,0,2,3,true,false> > r12;
const indexer<bits::index_submatrix<1,0,3,3,true,false> > r13;
const indexer<bits::index_submatrix<2,0,3,3,true,false> > r23;

// column selection
const indexer<bits::index_submatrix<0,0,3,0,false,true> > c0;
const indexer<bits::index_submatrix<0,1,3,1,false,true> > c1;
const indexer<bits::index_submatrix<0,2,3,2,false,true> > c2;
const indexer<bits::index_submatrix<0,3,3,3,false,true> > c3;
const indexer<bits::index_submatrix<0,0,3,1,false,true> > c01;
const indexer<bits::index_submatrix<0,0,3,2,false,true> > c02;
const indexer<bits::index_submatrix<0,1,3,2,false,true> > c12;
const indexer<bits::index_submatrix<0,1,3,3,false,true> > c13;
const indexer<bits::index_submatrix<0,2,3,3,false,true> > c23;

} // namespace math
