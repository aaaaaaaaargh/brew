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

#ifndef BREW_VEC4_H
#define BREW_VEC4_H

#include <brew/core/Types.h>

namespace brew {

class Vec4 {
public:
    typedef Real value_type;

    value_type
            x, //< The x component.
            y, //< The y component.
            z, //< The z component.
            w; //< The w component.

public:
    /**
     * Creates a new vector from component values.
     * @param x The x axis value.
     * @param y The y axis value.
     * @param z The z axis value.
     * @param w The w axis value.
     */
    explicit Vec4(value_type x = 0, value_type y = 0, value_type z = 0, value_type w = 0);

    /**
     * Copies a vector.
     * @param other The vector to copy.
     */
    Vec4(const Vec4 &other) = default;

    /**
     * Sets the vector component values.
     * @param x The x axis value.
     * @param y The y axis value.
     * @param z The z axis value.
     * @param w The w axis value.
     */
    void set(value_type x, value_type y, value_type z, value_type w);

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
    Vec4 operator+(const Vec4 &other) const;

    /**
     * Subtracts another vector.
     * @param other The vector to subtract.
     * @return The subtracted vector.
     */
    Vec4 operator-(const Vec4 &other) const;

    /**
     * Multiplies this by a scalar.
     * @param scalar The scalar value.
     * @return A new scaled vector.
     */
    Vec4 operator*(const value_type &scalar) const;

    /**
     * Divides this by a scalar.
     * @param scalar The scalar value.
     * @return A new scaled vector.
     */
    Vec4 operator/(const value_type &scalar) const;

    /**
     * Sets this vector to the values of another vector.
     * @param other The vector to copy the component values.
     * @return This vector for chaining.
     */
    Vec4 &operator=(const Vec4 &other);

    /**
     * Adds another vector.
     * @param other The vector to add.
     * @return This vector for chaining.
     */
    Vec4 &operator+=(const Vec4 &other);

    /**
     * Subtracts another vector.
     * @param other The vector to subtract.
     * @return This vector for chaining.
     */
    Vec4 &operator-=(const Vec4 &other);

    /**
     * Multiplies this by a scalar.
     * @param scalar The scalar value.
     * @return This vector for chaining.
     */
    Vec4 &operator*=(const value_type &scalar);

    /**
     * Divides this by a scalar.
     * @param scalar The scalar value.
     * @return This vector for chaining.
     */
    Vec4 &operator/=(const value_type &scalar);

    /*
     * @return The negative vector.
     */
    Vec4 operator-() const;

    /**
     * Compares two vectors.
     * @param other The vector to compare this with.
     * @return Whether both vectors are equal.
     */
    bool operator==(const Vec4 &other) const;

    /**
     * Compares two vectors.
     * @param other The vector to compare this with.
     * @return Whether both vectors are unequal.
     */
    bool operator!=(const Vec4 &other) const;

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
    Real dot(const Vec4& other) const;

    /**
     * @return A normalized copy of this vector.
     */
    Vec4 normalized() const;

    /**
     * Normalizes the vector.
     * @return This vector for chaining.
     */
    Vec4& normalize();

    /**
     * Calculates the euclidean distance between two vectors.
     * @param other The vector to calculate the distance with.
     * @return The distance between this and other.
     */
    Real distance(const Vec4& other) const;


public:
    static const Vec4 ZERO; //< The zero vector (0,0,0,0).
    static const Vec4 ONE; //< The neutral vector (1,1,1,1).
    static const Vec4 INF; //< The vector representing infinity.
    static const Vec4 UNIT_X; //< The x unit vector (1,0,0,0).
    static const Vec4 UNIT_Y; //< The y unit vector (0,1,0,0).
    static const Vec4 UNIT_Z; //< The z unit vector (0,0,1,0).
    static const Vec4 UNIT_W; //< The w unit vector (0,0,0,1).
    static const Vec4 NEGATIVE_UNIT_X; // The negative x unit vector (-1,0,0,0).
    static const Vec4 NEGATIVE_UNIT_Y; // The negative y unit vector (0,-1,0,0).
    static const Vec4 NEGATIVE_UNIT_Z; // The negative z unit vector (0,0,-1,0).
    static const Vec4 NEGATIVE_UNIT_W; // The negative w unit vector (0,0,0,-1).
};

/**
 * Stream implementation.
 * @param stream The stream.
 * @param vector The vector to write into the stream.
 * @return The stream for chaining.
 */
std::ostream& operator << (std::ostream& stream, const Vec4& vector);

} /* namespace brew */

#endif /* BREW_VEC4_H */
