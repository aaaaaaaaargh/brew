/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: Feb 23, 2016
 *
 */

#ifndef BREW_RECT_H
#define BREW_RECT_H

#include <brew/math/Vec2.h>
#include <brew/math/Vec4.h>
#include <brew/math/Math.h>

namespace brew {

/**
 * A template class for rectangles.
 * @tparam value_type The value type, defaults to Real.
 */
template<typename value_type = Real>
class Rect {
private:
	value_type x,y,w,h;

public:
	/**
	 * Creates a new rectangle.
	 * @param x The x offset.
	 * @param y The y offset.
	 * @param width The width.
	 * @param height The height.
	 */
	Rect(value_type x=0, value_type y=0, value_type width=0, value_type height=0) {
		set(x,y,width,height);
	}

public:
	/**
	 * Sets the rectangles offset and dimensions.
	 * @param x The x offset.
	 * @param y The y offset.
	 * @param width The width.
	 * @param height The height.
	 */
	void set(value_type x, value_type y, value_type width, value_type height) {
		this->x = x;
		this->y = y;
		this->w = width;
		this->h = height;

		normalize();
	}

	/**
	 * Sets the rectangles x offset.
	 * @param x The x offset.
	 */
	void setX(value_type x) {
		this->x = x;
		normalize();
	}

	/**
	 * Sets the rectangles y offset.
	 * @param y The y offset.
	 */
	void setY(value_type y) {
		this->y = y;
		normalize();
	}

	/**
	 * Sets the rectangles width.
	 * @param w The width.
	 */
	void setWidth(value_type w) {
		this->w = w;
		normalize();
	}

	/**
	 * Sets the rectangles height.
	 * @param h The height.
	 */
	void setHeight(value_type h) {
		this->h = h;
		normalize();
	}

	/**
	 * @return A newly created Vec4 from this rectangle.
	 */
	Vec4 toVec4() const {
		return Vec4(getLeft(), getTop(), getWidth(), getHeight());
	}

	/**
	 * @return The minimum (top left) of this rectangle.
	 */
	Vec2 getMinimum() const {
		return Vec2(getLeft(), getTop());
	}

	/**
	 * @return The maximum (bottom right) of this rectangle.
	 */
	Vec2 getMaximum() const {
		return Vec2(getRight(), getBottom());
	}

	/**
	 * @return The left offset of this rectangle.
	 */
	value_type getLeft() const {
		return x;
	}

	/**
	 * @return The right offset of this rectangle.
	 */
	value_type getRight() const {
		return x+w;
	}

	/**
	 * @return The top offset of this rectangle.
	 */
	value_type getTop() const {
		return y;
	}

	/**
	 * @return The bottom offset of this rectangle.
	 */
	value_type getBottom() const {
		return y+h;
	}

	/**
	 * @return The width of this rectangle.
	 */
	value_type getWidth() const {
		return w;
	}

	/**
	 * @return The height of this rectangle.
	 */
	value_type getHeight() const {
		return h;
	}

	/**
	 * @return Whether this rectangle has a finite size.
	 */
	bool isFinite() const {
		return !math::equals(w, 0) && !math::equals(h, 0);
	}

	/**
	 * @return A raw pointer to this rectangles components.
	 */
	const value_type* getRaw() const {
		return &x;
	}

	/**
	 * Checks if a given point is inside the rectangle.
	 * @param x The x position of the point.
	 * @param y The y position of the point.
	 * @return Whether the given point is inside the rectangle.
	 */
	bool contains(value_type x, value_type y) const {
		return
				x >= this->x && x < this->getRight() &&
				y >= this->y && y < this->getBottom();
	}

	/**
	 * Compares two rectangles.
	 * @param other The other rectangle to compare.
	 * @return Whether both rectangles are equal.
	 */
	bool operator == (const Rect<value_type>& other) const {
		return other.x == x && other.y == y && other.w == w && other.h == h;
	}

	/**
	 * Compares two rectangles.
	 * @param other The other rectangle to compare.
	 * @return Whether both rectangles are unequal.
	 */
    bool operator != (const Rect<value_type>& other) const {
        return other.x != x || other.y != y || other.w != w || other.h != h;
    }

private:
	void normalize() {
		value_type x2 = x + w;
		value_type y2 = y + h;

		if (x > x2) {
			x = x2;
			w = -w;
		}

		if (y > y2) {
			y = y2;
			h = -y;
		}
	}

public:
	static const Rect INF;
};

template<typename value_type>
const Rect<value_type> Rect<value_type>::INF(0, 0, 0, 0);

typedef Rect<s32> IntRect;
typedef Rect<Real> RealRect;

/**
 * Stream implementation.
 * @param stream The stream.
 * @param vector The vector to write into the stream.
 * @return The stream for chaining.
 */
template<typename value_type>
std::ostream& operator << (std::ostream& stream, const Rect<value_type>& rect) {
	stream << "[" << rect.getLeft() << ", " << rect.getTop() << ", " << rect.getWidth() << "x" << rect.getHeight() << "]";
	return stream;
}

} /* namespace brew */

#endif /* BREW_RECT_H */
