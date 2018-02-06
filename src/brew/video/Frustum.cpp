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

#include <brew/video/Frustum.h>

#include <brew/math/BoundingBox.h>

namespace brew {

const Vec3 Frustum::clipSpacePlanePoints[8] = {
        /* near clip plane */
        Vec3(-1, -1, -1),
        Vec3(1, -1, -1),
        Vec3(1, 1, -1),
        Vec3(-1, 1, -1),

        /* far clip plane */
        Vec3(-1, -1, 1),
        Vec3(1, -1, 1),
        Vec3(1, 1, 1),
        Vec3(-1, 1, 1),
        };

Frustum::Frustum() {
    for (u8 i = 0; i < 6; i++) {
        planes[i] = Plane(Vec3::ZERO, 0);
    }
}

void Frustum::update(const Matrix4& inverseProjectionView) {
    for (SizeT i = 0; i < 8; ++i) {
        Vec3& v = planePoints[i];
        v = clipSpacePlanePoints[i];
        v = inverseProjectionView * v;
    }

    planes[0].set(planePoints[1], planePoints[0], planePoints[2]);
    planes[1].set(planePoints[4], planePoints[5], planePoints[7]);
    planes[2].set(planePoints[0], planePoints[4], planePoints[3]);
    planes[3].set(planePoints[5], planePoints[1], planePoints[6]);
    planes[4].set(planePoints[2], planePoints[3], planePoints[6]);
    planes[5].set(planePoints[4], planePoints[0], planePoints[1]);

}

bool Frustum::pointInFrustum(Real x, Real y, Real z) const {
    for (u8 i = 0; i < 6; i++) {
        Plane::PlaneSide result = planes[i].getFacingSide(x, y, z);
        if (result == Plane::PlaneSide::Back)
            return false;
    }
    return true;
}

inline bool checkBoundsInFrustumExclusive(const Plane* planes, const BoundingBox& bounds) {
    for (u8 i = 0; i < 6; i++) {
        if (planes[i].getFacingSide(bounds.getCorner(BoundingBox::Corner::xyz)) == Plane::PlaneSide::Back)
            continue;
        if (planes[i].getFacingSide(bounds.getCorner(BoundingBox::Corner::xyZ)) == Plane::PlaneSide::Back)
            continue;
        if (planes[i].getFacingSide(bounds.getCorner(BoundingBox::Corner::xYz)) == Plane::PlaneSide::Back)
            continue;
        if (planes[i].getFacingSide(bounds.getCorner(BoundingBox::Corner::xYZ)) == Plane::PlaneSide::Back)
            continue;
        if (planes[i].getFacingSide(bounds.getCorner(BoundingBox::Corner::Xyz)) == Plane::PlaneSide::Back)
            continue;
        if (planes[i].getFacingSide(bounds.getCorner(BoundingBox::Corner::XyZ)) == Plane::PlaneSide::Back)
            continue;
        if (planes[i].getFacingSide(bounds.getCorner(BoundingBox::Corner::XYz)) == Plane::PlaneSide::Back)
            continue;
        if (planes[i].getFacingSide(bounds.getCorner(BoundingBox::Corner::XYZ)) == Plane::PlaneSide::Back)
            continue;

        /**
         * At least one theoretically visible point is sufficient for non-inclusive tests.
         */
        return true;
    }

    // None of the points are visible.
    return false;
}

inline bool checkBoundsInFrustumInclusive(const Plane* planes, const BoundingBox& bounds) {
    for (u8 i = 0; i < 6; i++) {
        if (planes[i].getFacingSide(bounds.getCorner(BoundingBox::Corner::xyz)) != Plane::PlaneSide::Back)
            continue;
        if (planes[i].getFacingSide(bounds.getCorner(BoundingBox::Corner::xyZ)) != Plane::PlaneSide::Back)
            continue;
        if (planes[i].getFacingSide(bounds.getCorner(BoundingBox::Corner::xYz)) != Plane::PlaneSide::Back)
            continue;
        if (planes[i].getFacingSide(bounds.getCorner(BoundingBox::Corner::xYZ)) != Plane::PlaneSide::Back)
            continue;
        if (planes[i].getFacingSide(bounds.getCorner(BoundingBox::Corner::Xyz)) != Plane::PlaneSide::Back)
            continue;
        if (planes[i].getFacingSide(bounds.getCorner(BoundingBox::Corner::XyZ)) != Plane::PlaneSide::Back)
            continue;
        if (planes[i].getFacingSide(bounds.getCorner(BoundingBox::Corner::XYz)) != Plane::PlaneSide::Back)
            continue;
        if (planes[i].getFacingSide(bounds.getCorner(BoundingBox::Corner::XYZ)) != Plane::PlaneSide::Back)
            continue;

        /**
         * At least one invisible point is found, so this box cannot be inclusive.
         */
        return false;
    }

    // All points are visible.
    return true;
}

bool Frustum::boundsInFrustum(const BoundingBox& bounds, bool inclusive) const {
    return inclusive ? checkBoundsInFrustumInclusive(planes, bounds) : checkBoundsInFrustumExclusive(planes, bounds);
}

} /* namespace brew */
