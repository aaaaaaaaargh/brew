/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 Marcus v. Keil
 *
 *  Created on: Feb 11, 2016
 *
 */

#include <brew/math/Vec4.h>
#include <brew/math/Math.h>

namespace brew {

Vec4::Vec4(value_type x, value_type y, value_type z, value_type w) :
        x(x), y(y), z(z), w(w) {}

void Vec4::set(value_type x, value_type y, value_type z, value_type w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Vec4 Vec4::operator+(const Vec4 &other) const {
    return Vec4(x + other.x, y + other.y, z + other.z, w + other.w);
}

Vec4 Vec4::operator-(const Vec4 &other) const {
    return Vec4(x - other.x, y - other.y, z - other.z, w - other.w);
}

Vec4 Vec4::operator*(const value_type &scalar) const {
    return Vec4(x * scalar, y * scalar, z * scalar, w * scalar);
}

Vec4 Vec4::operator/(const value_type &scalar) const {
    return Vec4(x / scalar, y / scalar, z / scalar, w / scalar);
}

Vec4 &Vec4::operator=(const Vec4 &other) {
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
    return *this;
}

Vec4 &Vec4::operator+=(const Vec4 &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
    return *this;
}

Vec4 &Vec4::operator-=(const Vec4 &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;
    return *this;
}

Vec4 &Vec4::operator*=(const value_type &scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

Vec4 &Vec4::operator/=(const value_type &scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    w /= scalar;
    return *this;
}

Vec4 Vec4::operator-() const {
    return Vec4(-x, -y, -z, -w);
}

bool Vec4::operator==(const Vec4 &other) const {
    return math::equals(x, other.x) && math::equals(y, other.y) && math::equals(z, other.z) && math::equals(w, other.w);
}

bool Vec4::operator!=(const Vec4 &other) const {
    return !operator==(other);
}

Real Vec4::length() const {
    return std::sqrt(x * x + y * y + z * z + w * w);
}

Real Vec4::squaredLength() const {
    return x * x + y * y + z * z + w * w;
}

Real Vec4::dot(const Vec4& other) const {
    return x * other.x + y * other.y + z * other.z + w * other.w;
}

Real Vec4::distance(const Vec4 &other) const {
    Real dX = (x - other.x);
    Real dY = (y - other.y);
    Real dZ = (z - other.z);

    return std::sqrt(dX * dX + dY * dY + dZ * dZ);
}


Vec4 Vec4::normalized() const {
    Vec4 v(*this);
    v.normalize();
    return v;
}

Vec4& Vec4::normalize() {
    Real len = length();
    x /= len;
    y /= len;
    z /= len;
    w /= len;
    return *this;
}

const Vec4 Vec4::ZERO(0,0,0,0);

const Vec4 Vec4::ONE(1,1,1,1);

const Vec4 Vec4::INF(
        std::numeric_limits<Real>::infinity(),
        std::numeric_limits<Real>::infinity(),
        std::numeric_limits<Real>::infinity(),
        std::numeric_limits<Real>::infinity()
);

const Vec4 Vec4::UNIT_X(1,0,0,0);
const Vec4 Vec4::UNIT_Y(0,1,0,0);
const Vec4 Vec4::UNIT_Z(0,0,1,0);
const Vec4 Vec4::UNIT_W(0,0,0,1);

const Vec4 Vec4::NEGATIVE_UNIT_X(-1,0,0,0);
const Vec4 Vec4::NEGATIVE_UNIT_Y(0,-1,0,0);
const Vec4 Vec4::NEGATIVE_UNIT_Z(0,0,-1,0);
const Vec4 Vec4::NEGATIVE_UNIT_W(0,0,0,-1);

} /* namespace brew */

#include <ostream>

namespace brew {

std::ostream & operator << (std::ostream &s, const brew::Vec4 &v) {
    s << "Vec4(" << v.x << "," << v.y << "," << v.z << "," << v.w << ")";
    return s;
}

} /* namespace brew */
