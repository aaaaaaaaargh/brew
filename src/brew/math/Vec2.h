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

#ifndef BREW_VEC2_H
#define BREW_VEC2_H

#include <brew/core/Types.h>

namespace brew {

class Vec2 {
public:
	typedef Real value_type;

	value_type
			x, //< The x component.
			y; //< The y component.

public:
	/**
     * Creates a new vector from component values.
     * @param x The x axis value.
     * @param y The y axis value.
     */
	explicit Vec2(value_type x = 0, value_type y = 0);

	/**
 	 * Copies a vector.
 	 * @param other The vector to copy.
 	 */
	Vec2(const Vec2& other) = default;

	/**
     * Sets the vector component values.
     * @param x The x axis value.
     * @param y The y axis value.
     */
	void set(value_type x, value_type y);

	/**
 	 * @param nth The component number.
 	 * @return the nth component value from this vector.
 	 */
	inline Real& operator[](u8 nth) {
		return *static_cast<Real*>(&x + nth);
	}

	/**
 	 * @param nth The component number.
 	 * @return the nth component value from this vector.
 	 */
	Real operator[](u8 nth) const {
		return *static_cast<const Real*>(&x + nth);
	}

public:
	/**
     * Adds another vector.
     * @param other The vector to add.
     * @return The vector sum of both vectors.
     */
	Vec2 operator + (const Vec2& other) const;

	/**
     * Subtracts another vector.
     * @param other The vector to subtract.
     * @return The subtracted vector.
     */
	Vec2 operator - (const Vec2& other) const;

	/**
     * Multiplies this by a scalar.
     * @param scalar The scalar value.
     * @return A new scaled vector.
     */
	Vec2 operator * (value_type scalar) const;

	/**
     * Divides this by a scalar.
     * @param scalar The scalar value.
     * @return A new scaled vector.
     */
	Vec2 operator / (value_type scalar) const;

	/**
     * Sets this vector to the values of another vector.
     * @param other The vector to copy the component values.
     * @return This vector for chaining.
     */
	Vec2& operator = (const Vec2& other);

	/**
     * Adds another vector.
     * @param other The vector to add.
     * @return This vector for chaining.
     */
	Vec2& operator += (const Vec2& other);

	/**
     * Subtracts another vector.
     * @param other The vector to subtract.
     * @return This vector for chaining.
     */
	Vec2& operator -= (const Vec2& other);

	/**
     * Multiplies this by a scalar.
     * @param scalar The scalar value.
     * @return This vector for chaining.
     */
	Vec2& operator *= (value_type scalar);

	/**
     * Divides this by a scalar.
     * @param scalar The scalar value.
     * @return This vector for chaining.
     */
	Vec2& operator /= (value_type scalar);

	/*
     * @return The negative vector.
     */
	Vec2 operator - () const;

	/**
     * Compares two vectors.
     * @param other The vector to compare this with.
     * @return Whether both vectors are equal.
     */
	bool operator == (const Vec2& other) const;

	/**
     * Compares two vectors.
     * @param other The vector to compare this with.
     * @return Whether both vectors are unequal.
     */
	bool operator != (const Vec2& other) const;

	/**
     * @return The length of this vector.
     */
	Real length() const;

	/**
     * @return The squared length of this vector.
     */
	Real squaredLength() const;

	/**
	 * Calculates the dot product of two vectors.
	 * @param other The vector to calculate the dot product with.
	 * @return The dot product of both vectors.
	 */
	Real dot(const Vec2& other) const;

	/**
	 * @return A normalized copy of this vector.
	 */
	Vec2 normalized() const;

	/**
	 * Normalizes the vector.
	 * @return This vector for chaining.
	 */
	Vec2& normalize();

	/**
	 * Calculates the euclidean distance between two vectors.
	 * @param other The vector to calculate the distance with.
	 * @return The distance between this and other.
	 */
	Real distance(const Vec2& other) const;

public:
	static const Vec2 ZERO; //< The zero vector (0,0).
	static const Vec2 ONE; //< The neutral vector (1,1).
	static const Vec2 INF; //< The vector representing infinity.
	static const Vec2 UNIT_X; //< The x unit vector (1,0).
	static const Vec2 UNIT_Y; //< The y unit vector (0,1).
	static const Vec2 NEGATIVE_UNIT_X; // The negative x unit vector (-1,0).
	static const Vec2 NEGATIVE_UNIT_Y; // The negative y unit vector (0,-1).
};

/**
 * Stream implementation.
 * @param stream The stream.
 * @param vector The vector to write into the stream.
 * @return The stream for chaining.
 */
std::ostream& operator << (std::ostream& stream, const Vec2& vector);

} /* namespace brew */

#endif /* BREW_VEC2_H */
