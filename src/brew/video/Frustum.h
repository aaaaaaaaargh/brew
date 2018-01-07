/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 random arts
 *
 *  Created on: 02.01.2015
 *
 */

#ifndef BREW_FRUSTUM_H
#define BREW_FRUSTUM_H

#include <brew/math/Plane.h>
#include <brew/math/Matrix4.h>

namespace brew {

class BoundingBox;

/**
 * A class representing a camera frustum.
 */
class Frustum
{
public:
    /**
     * Creates a new frustum.
     */
	Frustum();

    /**
     * Updates the frustum.
     * @param inversiveProjectionView The inverse projection view matrix.
     */
	void update(const Matrix4& inverseProjectionView);

    /**
     * Checks whether a point is inside the frustum.
     * @param x The x position of the point.
     * @param y The y position of the point.
     * @param z The z position of the point.
     * @return Whether the point is inside the frustum.
     */
	bool pointInFrustum(Real x, Real y, Real z) const;

    /**
     * Checks whether a point is inside the frustum.
     * @param point The point to check.
     * @return Whether the point is inside the frustum.
     */
	inline bool pointInFrustum(const Vec3& point) const {
		return pointInFrustum(point.x, point.y, point.z);
	}

    /**
     * Checks whether a point is inside the frustum.
     * @param point The point to check.
     * @param inclusive Whether all points must be inside the frustum.
     * @return Whether the point is inside the frustum.
     */
	bool boundsInFrustum(const BoundingBox& bounds, bool inclusive = false) const;

private:
	Plane planes[6];
	const static Vec3 clipSpacePlanePoints[8];
	Vec3 planePoints[8];

};

} /* namespace brew */

#endif /* BREW_FRUSTUM_H */
