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

#include <brew/math/BoundingBox.h>

#include <limits>

namespace brew {

BoundingBox::Corner BoundingBox::corner(bool upperX, bool upperY, bool upperZ) {

	if (upperX) {
		if (upperY) {
			if (upperZ)
				return Corner::XYZ;
			else
				return Corner::XYz;
		} else {
			if (upperZ)
				return Corner::XyZ;
			else
				return Corner::Xyz;
		}
	} else {
		if (upperY) {
			if (upperZ)
				return Corner::xYZ;
			else
				return Corner::xYz;
		} else {
			if (upperZ)
				return Corner::xyZ;
			else
				return Corner::xyz;
		}
	}

}

BoundingBox::BoundingBox() :
		min(Vec3::ZERO), max(Vec3::ZERO) {
}

BoundingBox::BoundingBox(const Vec3& min, const Vec3& max) :
		min(min), max(max) {
}

BoundingBox& BoundingBox::operator =(const BoundingBox& other) {
	min = other.min;
	max = other.max;
	return *this;
}

BoundingBox& BoundingBox::operator +=(const BoundingBox& other) {
	if (!isFinite()) {
		return operator =(other);
	}

	min.set(std::min(min.x, other.min.x), std::min(min.y, other.min.y), std::min(min.z, other.min.z));
	max.set(std::max(max.x, other.max.x), std::max(max.y, other.max.y), std::max(max.z, other.max.z));
	return *this;
}

BoundingBox BoundingBox::operator +=(const Vec3& point) {
	if (!isFinite()) {
		set(point, point);
		return *this;
	}

	min.set(std::min(min.x, point.x), std::min(min.y, point.y), std::min(min.z, point.z));
	max.set(std::max(max.x, point.x), std::max(max.y, point.y), std::max(max.z, point.z));
	return *this;
}

BoundingBox BoundingBox::operator +(const BoundingBox& other) const {
	BoundingBox bb(*this);
	bb += other;
	return bb;
}

BoundingBox BoundingBox::operator +(const Vec3& point) const {
	BoundingBox bb(*this);
	bb += point;
	return bb;
}

BoundingBox BoundingBox::operator*=(const Matrix4& transform) {
	Real x0 = min.x, y0 = min.y, z0 = min.z, x1 = max.x, y1 = max.y, z1 = max.z;
	this->operator=(BoundingBox::INF);
	Vec3 tmpVector;

	auto foo = transform * tmpVector;

	tmpVector.set(x0, y0, z0);
	this->operator+=(transform * tmpVector);

	tmpVector.set(x0, y0, z1);
	this->operator+=(transform * tmpVector);

	tmpVector.set(x0, y1, z0);
	this->operator+=(transform * tmpVector);

	tmpVector.set(x0, y1, z1);
	this->operator+=(transform * tmpVector);

	tmpVector.set(x1, y0, z0);
	this->operator+=(transform * tmpVector);

	tmpVector.set(x1, y0, z1);
	this->operator+=(transform * tmpVector);

	tmpVector.set(x1, y1, z0);
	this->operator+=(transform * tmpVector);

	tmpVector.set(x1, y1, z1);
	this->operator+=(transform * tmpVector);
}

BoundingBox BoundingBox::operator*(const Matrix4& transform) const {
	BoundingBox bb(*this);
	bb *= transform;
	return bb;
}

bool BoundingBox::operator==(const BoundingBox& other) const {
	return other.min == min && other.max == max;
}

void BoundingBox::set(const Vec3& min, const Vec3& max) {
    this->max = max;
    this->min = min;
}

bool BoundingBox::contains(const Vec3& point) const {
	if (!isFinite())
		return false;

	return min.x <= point.x && min.y <= point.y && min.z <= point.z && max.x >= point.x && max.y >= point.y && max.z >= point.z;
}

bool BoundingBox::contains(const BoundingBox& other) const {
	if (!isFinite())
		return false;

	return contains(other.min) && contains(other.max);
}

bool BoundingBox::intersects(const BoundingBox& other) const {
	if (!isFinite())
		return false;

	return (max.x > other.min.x && min.x < other.max.x && max.y > other.min.y && min.y < other.max.y && max.z > other.min.z && min.z < other.max.z);
}

Vec3 BoundingBox::getCorner(const Corner& corner) const {
	switch (corner) {
	case Corner::xyz:
		return min;
	case Corner::Xyz:
		return Vec3(max.x, min.y, min.z);
	case Corner::xYz:
		return Vec3(min.x, max.y, min.z);
	case Corner::xyZ:
		return Vec3(min.x, min.y, max.z);
	case Corner::XYz:
		return Vec3(max.x, max.y, min.z);
	case Corner::XyZ:
		return Vec3(max.x, min.y, max.z);
	case Corner::xYZ:
		return Vec3(min.x, max.y, max.z);
	case Corner::XYZ:
		return max;
	default:
		return Vec3::ZERO;
	}
}

Vec3 BoundingBox::getCenter() const {
	return min + (max - min) * 0.5f;
}

bool BoundingBox::isFinite() const {
	return min.x <= max.x && min.y <= max.y && min.z <= max.z;
}

const BoundingBox BoundingBox::INF = BoundingBox(
        Vec3(std::numeric_limits<Real>().max(), std::numeric_limits<Real>().max(), std::numeric_limits<Real>().max()),
        Vec3(std::numeric_limits<Real>().min(), std::numeric_limits<Real>().min(), std::numeric_limits<Real>().min())
);

void BoundingBox::setMinimum(const Vec3& min) {
	this->min = min;
}

void BoundingBox::setMaximum(const Vec3& max) {
	this->max = max;
}

std::ostream& operator << (std::ostream& stream, const BoundingBox& bbox) {
	if(bbox.isFinite()) {
		stream << "BoundingBox(min: " << bbox.min << ", max: " << bbox.max << ")";
	}
	else {
		stream << "BoundingBox(infinite)";
	}
	return stream;
}

} /* namespace brew */
