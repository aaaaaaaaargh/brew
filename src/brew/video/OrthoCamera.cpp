/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2017 r.acc
 *
 *  OrthoCamera.cpp
 *
 *  Created on: Mar 19, 2016
 *      Author: void
 */

#include <brew/video/OrthoCamera.h>

namespace brew {

OrthoCamera::OrthoCamera(Real zoom,
                         const Vec3& position,
                         const Vec3& lookAt,
                         Real near,
                         Real far) :
        Camera(position, lookAt, near, far),
        zoom(1.0) {
}

void OrthoCamera::onUpdate() {
    const Real halfViewportWidth = 0.5;
    const Real halfViewportHeight = 0.5;

    projectionMatrix.setToOrtho(zoom * -halfViewportWidth, zoom * halfViewportWidth, zoom * -halfViewportHeight,
                                zoom * halfViewportHeight, _near, _far);

    Vec3 forward = orientation * Vec3::UNIT_Z;
    Vec3 up = orientation * Vec3::UNIT_Y;

    Matrix4 translation;
    translation.setToTransform(-position, Quaternion::IDENTITY, Vec3::ONE);

    viewMatrix.setToLookAt(forward, up);
    viewMatrix *= translation;

    combinedMatrix = projectionMatrix * viewMatrix; // Create the combined projection view matrix

    invCombinedMatrix = combinedMatrix.getInverted();

    frustum.update(invCombinedMatrix);

}

} /* namespace brew */
