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

#include <brew/math/Vec3.h>
#include <brew/math/Math.h>

namespace brew {

Vec3::Vec3(value_type x, value_type y, value_type z) :
		x(x), y(y), z(z) {

}

void Vec3::set(value_type x, value_type y, value_type z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vec3 Vec3::operator +(const Vec3& other) const {
	return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3 Vec3::operator -(const Vec3& other) const {
	return Vec3(x - other.x, y - other.y, z - other.z);
}

Vec3 Vec3::operator *(value_type scalar) const {
	return Vec3(x * scalar, y * scalar, z * scalar);
}

Vec3 Vec3::operator /(value_type scalar) const {
	return Vec3(x / scalar, y / scalar, z / scalar);
}

Vec3& Vec3::operator =(const Vec3& other) {
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}

Vec3& Vec3::operator +=(const Vec3& other) {
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

Vec3& Vec3::operator -=(const Vec3& other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

Vec3& Vec3::operator *=(value_type scalar) {
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}

Vec3& Vec3::operator /=(value_type scalar) {
	x /= scalar;
	y /= scalar;
	z /= scalar;
	return *this;
}

Vec3 Vec3::operator - () const {
	return Vec3(-x,-y,-z);
}

bool Vec3::operator ==(const Vec3& other) const {
	return math::equals(x, other.x) && math::equals(y, other.y) && math::equals(z, other.z);
}

bool Vec3::operator !=(const Vec3& other) const {
	return !operator==(other);
}

Real Vec3::length() const {
	return std::sqrt(x * x + y * y + z * z);
}

Real Vec3::squaredLength() const {
	return x * x + y * y + z * z;
}

Real Vec3::dot(const Vec3& other) const {
	return x * other.x + y * other.y + z * other.z;
}

Vec3 Vec3::cross(const Vec3& other) const {
	return Vec3(y*other.z - other.y * z, z * other.x - other.z * x, x * other.y - other.x * y);
}

Real Vec3::distance(const Vec3 &other) const {
	Real dX = (x - other.x);
	Real dY = (y - other.y);
	Real dZ = (z - other.z);

	return std::sqrt(dX * dX + dY * dY + dZ * dZ);
}


Vec3 Vec3::normalized() const {
	Vec3 v(*this);
	v.normalize();
	return v;
}

Vec3& Vec3::normalize() {
	Real len = length();
	x /= len;
	y /= len;
	z /= len;
	return *this;
}

const Vec3 Vec3::ZERO(0,0,0);

const Vec3 Vec3::ONE(1,1,1);

const Vec3 Vec3::INF(
        std::numeric_limits<Real>::infinity(),
        std::numeric_limits<Real>::infinity(),
        std::numeric_limits<Real>::infinity()
);

const Vec3 Vec3::UNIT_X(1,0,0);
const Vec3 Vec3::UNIT_Y(0,1,0);
const Vec3 Vec3::UNIT_Z(0,0,1);

const Vec3 Vec3::NEGATIVE_UNIT_X(-1,0,0);
const Vec3 Vec3::NEGATIVE_UNIT_Y(0,-1,0);
const Vec3 Vec3::NEGATIVE_UNIT_Z(0,0,-1);

} /* namespace brew */

#include <ostream>

namespace brew {

std::ostream& operator << (std::ostream& s, const Vec3& v) {
	s << "Vec3("<<v.x<<","<<v.y<<","<<v.z<<")";
	return s;
}

} /* namespace brew */



