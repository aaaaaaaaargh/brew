/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: 06.01.18
 *
 */

#include <brew/video/Viewport.h>
#include <brew/video/PerspectiveCamera.h>

namespace brew {

void Viewport::setVirtualSize(Real width, Real height) {
    virtualSize.set(width, height);
    camera->setViewportSize(virtualSize);
}

Viewport::Viewport(Real virtualWidth, Real virtualHeight, std::shared_ptr<Camera> camera) :
    physicalX(0), physicalY(0),
    physicalWidth(0), physicalHeight(0),
    camera(camera) {
    if(!camera) {
        // No camera provided, create a default one.
        this->camera = std::make_shared<PerspectiveCamera>();
    }

    setVirtualSize(virtualWidth, virtualHeight);
}

void Viewport::update(SizeT physicalWidth, SizeT physicalHeight) {
    setPhysicalSize(physicalWidth, physicalHeight);
}

void Viewport::setPhysicalBounds(SizeT x, SizeT y, SizeT width, SizeT height) {
    physicalX = x;
    physicalY = y;
    physicalWidth = width;
    physicalHeight = height;
}

void Viewport::setCamera(std::shared_ptr<Camera> camera) {
    this->camera = camera;
    this->camera->setViewportSize(virtualSize);
}

Vec3 Viewport::unproject(const Vec2& screenCoords, bool useFarPlane) const {
    Real x = screenCoords.x, y = screenCoords.y;
    x = x - physicalX;
    y = physicalHeight - y - 1.0f;
    y = y - physicalY;

    Vec3 v;

    v.x = (2.0f * x) / physicalWidth - 1.0f;
    v.y = (2.0f * y) / physicalHeight - 1.0f;
    v.z = 2.0f * v.z - 1.0f;

    return camera->getInverseCombinedMatrix() * v;
}

Vec2 Viewport::project(const Vec3& worldCoords) const {
    Vec3 v = camera->getCombinedMatrix() * worldCoords;

    v.x = physicalWidth * (v.x + 1.0f) / 2.0f + physicalX;
    v.y = physicalHeight* (v.y + 1.0f) / 2.0f + physicalY;
    v.z = (v.z + 1.0f) / 2.0f;

    return Vec2(v.x, v.y);
}

/**
 * Native viewport implementation.
 */

NativeViewport::NativeViewport(Real unitsPerPixel, std::shared_ptr<Camera> camera) :
        Viewport(0,0, camera), unitsPerPixel(unitsPerPixel) {

}

void NativeViewport::update(SizeT physicalWidth, SizeT physicalHeight) {
    Viewport::update(physicalWidth, physicalHeight);
    setVirtualSize(physicalWidth * unitsPerPixel, physicalHeight * unitsPerPixel);
}

void NativeViewport::setUnitsPerPixel(Real unitsPerPixel) {
    this->unitsPerPixel = unitsPerPixel;
}

} /* namespace brew */