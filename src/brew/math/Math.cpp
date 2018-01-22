/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: Feb 11, 2016
 *
 */

#include <brew/math/Math.h>

namespace brew {
namespace math {

const Real EPSILON = std::numeric_limits<Real>::epsilon();
const Real PI = 3.1415926535897932f;
const Real HALF_PI = PI * 0.5f;
const Real TWO_PI = PI * 2;

bool equals(Real a, Real b, Real epsilon) {
    return std::fabs(a-b) < epsilon;
}

} /* namespace math */
} /* namespace brew */

