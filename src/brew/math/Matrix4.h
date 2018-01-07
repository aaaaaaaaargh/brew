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

#ifndef BREW_MATRIX4_H
#define BREW_MATRIX4_H

#include <brew/math/Vec4.h>
#include <brew/math/Vec3.h>
#include <brew/math/Quaternion.h>

namespace brew {

/**
 * This class represents a 4x4 matrix.
 */
class Matrix4 {
public:
    /**
     * Creates a new matrix.
     * @param a00 The cell at [0,0].
     * @param a10 The cell at [1,0].
     * @param a20 The cell at [2,0].
     * @param a30 The cell at [3,0].
     * @param a01 The cell at [0,1].
     * @param a11 The cell at [1,1].
     * @param a21 The cell at [2,1].
     * @param a31 The cell at [3,1].
     * @param a02 The cell at [0,2].
     * @param a12 The cell at [1,2].
     * @param a22 The cell at [2,2].
     * @param a32 The cell at [3,2].
     * @param a03 The cell at [0,3].
     * @param a13 The cell at [1,3].
     * @param a23 The cell at [2,3].
     * @param a33 The cell at [3,3].
     */
	Matrix4(Real a00, Real a10, Real a20, Real a30,
			Real a01, Real a11, Real a21, Real a31,
			Real a02, Real a12, Real a22, Real a32,
			Real a03, Real a13, Real a23, Real a33);

    /**
     * Creates a new matrix from four column vectors.
     * @param column0 The first column.
     * @param column1 The second column.
     * @param column2 The third column.
     * @param column3 The fourth column.
     */
	Matrix4(const Vec4& column0, const Vec4& column1, const Vec4& column2, const Vec4& column3);

    /**
     * Creates a copy of another matrix.
     * @param other The matrix to copy.
     */
	Matrix4(const Matrix4& other = Matrix4::ID);

public:
	/**
	 * Accesses a column.
	 * @param column The column to return.
	 * @return The raw data at the given column.
	 */
	Real* operator [] (SizeT column);

    /**
	 * Accesses a column.
	 * @param column The column to return.
	 * @return The raw data at the given column.
	 */
	const Real* operator [] (SizeT column) const;

    /**
     * @return A raw pointer to the data.
     */
	inline Real* getRawPointer() {
		return &a[0];
	}

    /**
     * @return A raw pointer to the data.
     */
	inline const Real* getRawPointer() const {
		return &a[0];
	}

    /**
     * A reference to a value.
     * @param column The column of the value.
     * @param row The row of the value.
     * @return The value at the given cell.
     */
	Real& at(SizeT column, SizeT row);

    /**
     * A reference to a value.
     * @param column The column of the value.
     * @param row The row of the value.
     * @return The value at the given cell.
     */
	Real at(SizeT column, SizeT row) const;

public:
    /**
     * @return The determinant of this matrix.
     */
	Real getDeterminant() const;

    /**
     * Inverts this matrix.
     * @return This matrix for chaining.
     */
	Matrix4& invert();

    /**
     * @return An inverted copy of this matrix.
     */
	inline Matrix4 getInverted() const
	{
		Matrix4 m(*this);
		m.invert();
		return m;
	}

    /**
     * Transposes this matrix.
     * @return This matrix for chaining.
     */
	Matrix4& transpose();

    /**
     * @return A transposed copy of this matrix.
     */
	inline Matrix4 getTransposed() const
	{
		Matrix4 m(*this);
		m.transpose();
		return m;
	}

public:
    /**
     * Compares another matrix with this one.
     * @param other The matrix to compare.
     * @return Whether both matrices are equal.
     */
    bool operator == (const Matrix4& other) const;

    /**
     * Compares another matrix with this one.
     * @param other The matrix to compare.
     * @return Whether both matrices are unequal.
     */
    inline bool operator != (const Matrix4& other) const {
        return !operator ==(other);
    }

	/**
	 * Performs a multiplication where this matrix is the left-handed value of the operation.
	 * @param other The matrix to multiply with.
	 * @return The result of the multiplication.
	 */
	Matrix4 operator * (const Matrix4& other) const;

    /**
	 * Performs an multiplication where this matrix is the left-handed value of the operation.
     * The result of the multiplication will be assigned to this matrix.
	 * @param other The matrix to multiply with.
	 * @return This matrix for chaining.
	 */
	Matrix4& operator *= (const Matrix4& other);

    /**
     * Multiplies a vector with this matrix.
     * @param vector The vector to multiply.
     */
	void apply(Vec3& vector) const;

    /**
     * Multiplies a vector with this matrix.
     * @param vector The vector to multiply.
     * @return The multiplied result.
     */
    inline Vec3 operator * (const Vec3& other) const {
        Vec3 result(other);
		apply(result);
        return result;
    }

    /**
     * Multiplies a vector with this matrix.
     * @param vector The vector to multiply.
     */
	void apply(Vec4& vector) const;

    /**
     * Multiplies a vector with this matrix.
     * @param vector The vector to multiply.
     * @return The multiplied result.
     */
    inline Vec4 operator * (const Vec4& other) const {
        Vec4 result(other);
        apply(result);
        return result;
    }

public:
    /**
     * Set the values from another matrix.
     * @param other The matrix to copy the values from.
     */
    Matrix4& operator = (const Matrix4& other);

    /**
     * Sets this to a projection matrix.
     * @param near The near clipping plane distance.
     * @param far The far clipping plane distance.
     * @param fov The field of view.
     * @param aspectRatio The cameras aspect ratio.
     */
    void setToProjection(Real near, Real far, Real fov, Real aspectRatio);

    /**
     * Sets this to a orthographics projection matrix.
     * @param left The left offset of the viewport.
     * @param right The right offset of the viewport.
     * @param bottom The bottom offset of the viewport.
     * @param top The top offset of the viewport.
     * @param near The near clipping plane distance.
     * @param far The far clipping plane distance.
     */
    void setToOrtho(Real left, Real right, Real bottom, Real top, Real near, Real far);

    /**
     * Sets this to a look-at matrix.
     * @param direction The direction to look at.
     * @param up The up vector of the camera.
     */
    void setToLookAt(const Vec3& direction, const Vec3& up);

    /**
     * Sets this to a transform matrix.
     * @param translate The translation component.
     * @param orientation The orientation component.
     * @param scale The scale component.
     */
	void setToTransform(const Vec3& translate, const Quaternion& orientation, const Vec3& scale);

private:
	Real __attribute__ ((aligned (16))) a[16];

public:
    static const Matrix4 ZERO; //< The zero matrix.
    static const Matrix4 ID; //< The identity matrix.
};

/**
 * Stream implementation.
 * @param stream The stream.
 * @param vector The vector to write into the stream.
 * @return The stream for chaining.
 */
std::ostream& operator << (std::ostream& s, const Matrix4& mat);

}
/* namespace brew */

#endif /* BREW_MATRIX4_H */
