#ifndef MATH2_FWD_H
#define MATH2_FWD_H

namespace math {

template<int R, int C, class Scalar> class matrix;
template<int R, class Scalar> class vector;
template<class I> struct indexer;

template<class Base> struct tmatrix2;

namespace bits {

template<bool> struct static_assert;

template<>
struct static_assert<true> {
	typedef void test;
};

} // namespace bits

struct zero_t;
struct identity_t;

namespace bits {

template<class S> struct scalar_keeper;
template<class D, class S> struct assign_dispatch;
template<class Op, class A> struct matrix_unop;
template<class Op, class A, class B> struct matrix_binop;

} // namespace bits
} // namespace math

#endif
