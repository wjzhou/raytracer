#ifndef MATH2_CONSTANTS_H
#define MATH2_CONSTANTS_H

#include <limits>

namespace math {

const float pi = 3.1415926535897932384626433832795;
const float ln_2 = 0.693147180559945309417;
const float epsilon = std::numeric_limits<float>::epsilon();

// typeless multiplicative identity
const identity_t identity = identity_t();

// typeless zero
const zero_t zero = zero_t();

// fake axis vector constants
const tmatrix2<bits::x_axis_type<float> >::type x_axis;
const tmatrix2<bits::y_axis_type<float> >::type y_axis;
const tmatrix2<bits::z_axis_type<float> >::type z_axis;

} // namespace math

#endif
