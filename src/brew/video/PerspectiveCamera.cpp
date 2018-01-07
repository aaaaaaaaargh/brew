/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2017 r.acc
 *
 *  PerspectiveCamera.cpp
 *
 *  Created on: Mar 19, 2016
 *      Author: void
 */

#include <brew/video/PerspectiveCamera.h>

#include <brew/math/Math.h>

namespace brew {

/**
 * Default field of view angle should about 60-70 degrees.
 */
const Real PerspectiveCamera::DefaultFOV = 67.0;

PerspectiveCamera::PerspectiveCamera(	Real fov,
										const Vec3& position, 
										const Vec3& lookAt, 
										Real near, 
										Real far
									):
										Camera(position, lookAt, near, far),
										fov(fov) {

}

void PerspectiveCamera::onUpdate() {

	// Calculate the aspect ratio of our viewport.
	Real aspect = viewportSize.x / viewportSize.y;

	// Next, calulate the projection matrix.
	projectionMatrix.setToProjection(std::abs(_near), std::abs(_far), fov, aspect);

	// This is our forward vector pointing in the camera view direction.
	Vec3 forward = orientation * Vec3::UNIT_Z;

	// This is the up vector up the camera
	Vec3 up = orientation * Vec3::UNIT_Y;

	// Prepare an inverse translation matrix for shifting the camera to the correct point in scene space.
	Matrix4 translation;
	translation.setToTransform(-position, Quaternion::IDENTITY, Vec3::ONE);

	// Now apply a lookat matrix ...
	viewMatrix.setToLookAt(forward, up);

	// ... and multiply both together.
	viewMatrix *= translation;

	// Finally, create the combined matrix (the product of projection and view matrices)
	combinedMatrix = projectionMatrix * viewMatrix;

	// The inverse combined matrix is also required ...
	invCombinedMatrix = combinedMatrix.getInverted();

	// ... for frustum calculations.
	frustum.update(invCombinedMatrix);

}

void PerspectiveCamera::setFOV(Real fov) {
	this->fov = fov;
	invalidate();
}

} /* namespace brew */
