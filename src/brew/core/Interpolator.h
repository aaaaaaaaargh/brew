/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 Marcus v. Keil
 *
 *  Created on: 3 Jun 2015
 *
 */

#ifndef BREW_INTERPOLATOR_H
#define BREW_INTERPOLATOR_H

#include <brew/math/Math.h>

namespace brew
{

/**
 * The base interpolator. These classes can be used to interpolate a value with a given function.
 * @tparam T The value type to interpolate.
 */
template<typename T = Real>
class Interpolator
{
public:
	/**
	 * Interpolates a value.
	 * @param min The minumum value.
	 * @param max The maximum value.
	 * @param amount The amount, will be clamped to a value between [0...1].
	 * @return The interpolated value.
	 */
    inline T interpolate(T min, T max, Real amount) {
        return onApply(min, max, math::clamp<Real>(amount, 0, 1));
    }

protected:
    /**
     * The interpolation function.
	 * @param min The minumum value.
	 * @param max The maximum value.
	 * @param amount The amount, will be clamped to a value between [0...1].
     * @return The interpolated value.
     */
    virtual T onApply(T min, T max, Real amount) const = 0;

};

namespace interpolate {
/**
 * Interpolates a value using a custom interpolator.
 * @tparam InterpolatorT The interpolator type.
 * @tparam T The value type to interpolate.
 * @return The interpolated value.
 */
template<typename InterpolatorT, typename T = Real>
inline static T apply(T min, T max, Real amount) {
    static InterpolatorT interpolator;
    return interpolator.interpolate(min, max, amount);
}

} /* namespace interpolate */

/**
 * An interpolator using a linear function.
 * @tparam T The value type to interpolate.
 */
template<typename T = Real>
class LinearInterpolator : public Interpolator<T>
{
protected:
    /**
     * The interpolation function.
	 * @param min The minumum value.
	 * @param max The maximum value.
	 * @param amount The amount, will be clamped to a value between [0...1].
     * @return The interpolated value.
     */
    inline T onApply(T min, T max, Real amount) const
    {
        return min + static_cast<T>(amount * (max - min));
    }
};

namespace interpolate {
/**
 * Interpolates a value using a linear interpolator.
 * @tparam T The value type to interpolate.
 * @return The interpolated value.
 */
template<typename T = Real> const auto& linear = apply<LinearInterpolator<T>, T>;

} /* namespace interpolate */

/**
 * An interpolator using a sine function.
 * @tparam T The value type to interpolate.
 */
template<typename T = Real>
class SineInterpolator : public Interpolator<T>
{
protected:
    /**
     * The interpolation function.
	 * @param min The minumum value.
	 * @param max The maximum value.
	 * @param amount The amount, will be clamped to a value between [0...1].
     * @return The interpolated value.
     */
    inline T onApply(T min, T max, Real amount) const
	{
		return min + ((1.0 - std::cos(amount * math::PI)) * 0.5) * (max - min);
	}
};

namespace interpolate {
/**
 * Interpolates a value using a sine interpolator.
 * @tparam T The value type to interpolate.
 * @return The interpolated value.
 */
template<typename T = Real> const auto& sine = apply<SineInterpolator<T>, T>;
} /* namespace interpolate */

} /* namespace brew */

#endif /* BREW_INTERPOLATOR_H */
