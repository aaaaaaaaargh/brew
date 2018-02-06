/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 Marcus v. Keil
 *
 *  Created on: Feb 23, 2016
 *
 */

#include <brew/video/Camera.h>

#include <brew/math/Math.h>

namespace brew {

const Real Camera::DefaultNearClip = 1.0f;
const Real Camera::DefaultFarClip = 100.0f;

Camera::Camera(const Vec3& position, const Vec3& lookAt, Real near, Real far) :
        _far(far), _near(near), position(position), touched(true), orientation(Quaternion::IDENTITY),
        viewportSize(0, 0) {
    this->lookAt(lookAt);
}

void Camera::invalidate() {
    touched = true;
}

void Camera::update(bool force) {
    if (!touched && !force)
        return;

    touched = false;

    onUpdate();

}

void Camera::setDirection(const Vec3& vec, const Vec3& ld) {
    // Do nothing if given a zero vector
    // (Replaced assert since this could happen with auto tracking camera and
    //  camera passes through the lookAt point)
    if (vec == Vec3::ZERO)
        return;

    Vec3 zAdjustVec = vec.normalized();

    Quaternion targetWorldOrientation;

    bool fixedYaw = true;

    if (fixedYaw) {
        Vec3 xVec = Vec3::UNIT_Y.cross(zAdjustVec);
        xVec.normalize();

        Vec3 yVec = zAdjustVec.cross(xVec);
        yVec.normalize();

        targetWorldOrientation.setFromAxes(xVec, yVec, zAdjustVec);
    } else {
        // Get axes from current quaternion
        Vec3 axes[3];
        orientation.toAxes(axes[0], axes[1], axes[2]);
        Quaternion rotQuat;
        if ((axes[2] + zAdjustVec).squaredLength() < math::EPSILON) {
            // Oops, a 180 degree turn (infinite possible rotation axes)
            // Default to yaw i.e. use current UP
            rotQuat.setFromAxisAngle(axes[1], math::PI);
        } else {
            // Derive shortest arc to new direction
            rotQuat = Quaternion::getRotationTo(axes[2], zAdjustVec);

        }
        targetWorldOrientation = rotQuat * orientation;
    }

    orientation = targetWorldOrientation;
    invalidate();
}

void Camera::setViewportSize(const Vec2& viewportSize) {
    this->viewportSize = viewportSize;
    invalidate();
}

void Camera::setFar(Real _far) {
    this->_far = _far;
    invalidate();
}

void Camera::setNear(Real _near) {
    this->_near = _near;
    invalidate();
}

void Camera::setPosition(const Vec3& position) {
    this->position = position;
    invalidate();
}

void Camera::setPosition(Real x, Real y, Real z) {
    this->position.set(x, y, z);
    invalidate();
}

void Camera::setOrientation(const Quaternion& o) {
    orientation = o;
    invalidate();
}

void Camera::lookAt(const Vec3& p, const Vec3& up) {
    orientation.setToLookAt(p - position, up);
    invalidate();
}

void Camera::lookAt(Real x, Real y, Real z, Real upX, Real upY, Real upZ) {
    lookAt(Vec3(x,y,z), Vec3(upX, upY, upZ));
}

/*
Ray Camera::getCameraRay(const Vector2f& position) const
{
	Vec3 o(position.x * mViewport.getDimensions().x, position.y * mViewport.getDimensions().y, 0);
	Vec3 d(position.x * mViewport.getDimensions().x, position.y * mViewport.getDimensions().y, 1);

	o = unproject(o);
	d = unproject(d);
	d -= o;
	d.normalize();

	Ray ray(o, d);
	return ray;
}*/

} /* namespace brew */
