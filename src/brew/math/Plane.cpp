/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 Marcus v. Keil
 *
 *  Created on: 02.01.2015
 *
 */

#include <brew/math/Plane.h>
#include <brew/math/Math.h>

namespace brew
{

Plane::Plane() :
		normal(Vec3::ZERO), d(0.0f)
{

}

Plane::Plane(const Plane& other) :
		normal(other.normal), d(other.d)
{
}

Plane::Plane(const Vec3& normal, Real d) :
		normal(normal), d(d)
{
	this->normal.normalize();
}

Plane::Plane(const Vec3& normal, const Vec3& point) :
		normal(normal)
{
	this->normal.normalize();
	d = -normal.dot(point);

}

Plane::Plane(const Vec3& point1, const Vec3& point2,
		const Vec3& point3)
{
	set(point1, point2, point3);
}

void Plane::set(const Plane& other)
{
	normal = other.normal;
	d = other.d;
}

void Plane::set(const Vec3& point1, const Vec3& point2,
		const Vec3& point3)
{
	normal = (point1 - point2).cross(
			Vec3(point2.x - point3.x, point2.y - point3.y,
					point2.z - point3.z)).normalize();
	d = -point1.dot(normal);
}

void Plane::set(Real nx, Real ny, Real nz, Real d)
{
	normal.set(nx, ny, nz);
	normal.normalize();
	this->d = d;
}

void Plane::set(const Vec3& point, const Vec3& normal)
{
	this->normal = normal;
	this->normal.normalize();
	d = -point.dot(normal);
}

Plane::PlaneSide Plane::getFacingSide(const Vec3& point) const
{
	Real dist = normal.dot(point) + d;

	if (math::equals(dist, 0))
		return PlaneSide::OnPlane;
	else if (dist < 0)
		return PlaneSide::Back;
	else
		return PlaneSide::Front;
}

bool Plane::isFrontFacing(const Vec3& direction)
{
	Real dot = normal.dot(direction);
	return dot <= 0;
}

} /* namespace ra */
