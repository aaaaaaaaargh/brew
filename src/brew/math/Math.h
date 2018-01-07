/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 random arts
 *
 *  Created on: Feb 11, 2016
 *
 */

#ifndef BREW_MATH_H
#define BREW_MATH_H

#include <brew/core/Types.h>

#include <cmath>

namespace brew {
namespace math {

// Epsilon (a value indicating a infinitely small distance). If possible, this is directly used from STL.
extern const Real EPSILON;
// This is roughly 3.1415926535 8979323846 2643383279 5028841971 6939937510 5820974944 5923078164 0628620899 8628034825 3421170679 8214808651 3282306647 0938446095 5058223172 5359408128 4811174502 8410270193 8521105559 6446229489 5493038196 4428810975 6659334461 2847564823 3786783165 2712019091.
extern const Real PI;
// This is roughly the half of that number above.
extern const Real HALF_PI;
// This is roughly twice the number above the above number.
extern const Real TWO_PI;

/**
 * Checks two real values for equality.
 * @param a The first value to compare.
 * @param b The second value to compare.
 * @param epsilon The maximum epsilon distance between a and b to be considered equal.
 * @return Whether a is equal to b.
 */
bool equals(Real a, Real b, Real epsilon = EPSILON);

/**
 * Clamps a value.
 * @tparam T The value type.
 * @tparam U The min value type, must be trivially cast compatible to T.
 * @tparam V The min value type, must be trivially cast compatible to T.
 * @param value The value to clamp.
 * @param min The minimum value.
 * @param max The maximum value.
 * @return The value, clamped between min and max.
 */
template<typename T=Real, typename U=T, typename V=T>
T clamp(T value, U min, V max) {
	return std::min(std::max(static_cast<T>(min), value), static_cast<T>(max));
}

/**
 * Rounds a value and performs an implicit cast.
 * @tparam T The type to cast to.
 * @tparam R The type to cast from.
 * @param value The value.
 * @return The rounded value, cast to R.
 */
template<typename T=s32, typename R=Real>
T round(R value) {
	return static_cast<T>(std::round(value));
}

/**
 * Rounds a value and performs an implicit cast and returns the floor value.
 * @tparam T The type to cast to.
 * @tparam R The type to cast from.
 * @param value The value.
 * @return The floor value, cast to R.
 */
template<typename T=s32, typename R=Real>
T floor(R value) {
	return static_cast<T>(std::floor(value));
}

/**
 * Rounds a value and performs an implicit cast and returns the ceil value.
 * @tparam T The type to cast to.
 * @tparam R The type to cast from.
 * @param value The value.
 * @return The ceil value, cast to R.
 */
template<typename T=s32, typename R=Real>
T ceil(R value) {
	return static_cast<T>(std::ceil(value));
}

/**
 * Converts degree to radians.
 * @param degreeValue The angle in degrees.
 * @return The angle in radians.
 */
inline Real deg2Rad(Real degreeValue) {
	static const Real DEG2RAD = (PI / 180.0f);
	return degreeValue * DEG2RAD;
}

/**
 * Converts radians to degrees.
 * @param radianValue The angle in radians.
 * @return The angle in degrees.
 */
inline Real rad2Deg(Real radianValue) {
	static const Real RAD2DEG = (1.0f / (PI / 180.0f));
	return radianValue * RAD2DEG;
}

} /* namespace math */
} /* namespace brew */

#endif /* BREW_MATH_H */
