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

#include <brew/math/Vec2.h>
#include <brew/math/Math.h>

namespace brew {

Vec2::Vec2(value_type x, value_type y) :
		x(x), y(y) {

}

void Vec2::set(value_type x, value_type y) {
	this->x = x;
	this->y = y;
}

Vec2 Vec2::operator+(const Vec2& other) const {
	return Vec2(x + other.x, y + other.y);
}

Vec2 Vec2::operator-(const Vec2& other) const {
	return Vec2(x - other.x, y - other.y);
}

Vec2 Vec2::operator*(value_type scalar) const {
	return Vec2(x * scalar, y * scalar);
}

Vec2 Vec2::operator/(value_type scalar) const {
	return Vec2(x / scalar, y / scalar);
}

Vec2& Vec2::operator=(const Vec2& other) {
	x = other.x;
	y = other.y;
	return *this;
}

Vec2& Vec2::operator+=(const Vec2& other) {
	x += other.x;
	y += other.y;
	return *this;
}

Vec2& Vec2::operator-=(const Vec2& other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

Vec2& Vec2::operator*=(value_type scalar) {
	x *= scalar;
	y *= scalar;
	return *this;
}

Vec2& Vec2::operator/=(value_type scalar) {
	x /= scalar;
	y /= scalar;
	return *this;
}

Vec2 Vec2::operator-() const {
	return Vec2(-x, -y);
}

bool Vec2::operator==(const Vec2& other) const {
	return math::equals(x, other.x) && math::equals(y, other.y);
}

bool Vec2::operator!=(const Vec2& other) const {
	return !operator==(other);
}

Real Vec2::length() const {
	return sqrt(x * x + y * y);
}

Real Vec2::squaredLength() const {
	return x * x + y * y;
}

Real Vec2::dot(const Vec2& other) const {
	return x * other.x + y * other.y;
}

Real Vec2::distance(const Vec2& other) const {
	Real dX = (x - other.x);
	Real dY = (y - other.y);

	return std::sqrt(dX * dX + dY * dY);
}


Vec2 Vec2::normalized() const {
	Vec2 v(*this);
	v.normalize();
	return v;
}

Vec2& Vec2::normalize() {
	Real len = length();
	x /= len;
	y /= len;
	return *this;
}

const Vec2 Vec2::ZERO(0, 0);

const Vec2 Vec2::ONE(1, 1);

const Vec2 Vec2::INF(
		std::numeric_limits<Real>::infinity(),
		std::numeric_limits<Real>::infinity()
);

const Vec2 Vec2::UNIT_X(1, 0);
const Vec2 Vec2::UNIT_Y(0, 1);

const Vec2 Vec2::NEGATIVE_UNIT_X(-1, 0);
const Vec2 Vec2::NEGATIVE_UNIT_Y(0, -1);

} /* namespace brew */

#include <ostream>

namespace brew {

std::ostream & operator << (std::ostream &s, const brew::Vec2 &v) {
	s << "Vec2(" << v.x << "," << v.y << ")";
	return s;
}

} /* namespace brew */

