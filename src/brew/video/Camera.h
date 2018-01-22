/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: Feb 23, 2016
 *
 */

#ifndef BREW_CAMERA_H
#define BREW_CAMERA_H

#include <brew/core/Types.h>

#include <brew/math/Vec2.h>
#include <brew/math/Matrix4.h>
#include <brew/math/Quaternion.h>

#include <brew/video/Frustum.h>

namespace brew
{

class Camera {
public:
    static const Real DefaultNearClip;
    static const Real DefaultFarClip;

protected:
    /**
     * Creates a new camera.
     * @param position The camera position.
     * @param lookAt The initial look-at vector.
     * @param near The near clip distance.
     * @param far The far clip distance.
     */
	Camera(const Vec3& position = Vec3::ZERO,
           const Vec3& lookAt = Vec3::ZERO,
           Real near = DefaultNearClip,
           Real far = DefaultFarClip);

public:
	/**
	 * Updates the camera matrices.
	 * @param force Forces a rebuild even if the matrices are up-to-date.
	 */
	void update(bool force=false);

	/**
	 * Invalidates the cached states of this camera causing update() to recalculate the projection.
	 */
	void invalidate();

	/**
	 * @return the cameras projection matrix.
	 */
	inline const Matrix4& getProjectionMatrix() const
	{
		return projectionMatrix;
	}

	/**
	 * @return the cameras view matrix.
	 */
	inline const Matrix4& getViewMatrix() const
	{
		return viewMatrix;
	}

	/**
	 * @return the cameras combined matrix (that is ViewMatrix * ProjectionMatrix)
	 */
	inline const Matrix4& getCombinedMatrix() const {
		return combinedMatrix;
	}

    /**
     * @return the cameras inverse combined matrix.
     */
    inline const Matrix4 getInverseCombinedMatrix() const {
        return invCombinedMatrix;
    }

	void setNear(Real _near);

	/**
	 * @return the cameras near-plane distance.
	 */
	inline Real getNear(void) const {
	    return _near;
	}

	void setFar(Real _far);

	/**
	 * @return the far-plane distance of the camera.
	 */
	inline Real getFar() const
	{
		return _far;
	}

	/**
	 * Sets the near and far clip plane distances for this camera.
	 * @param _near the near clip plane distance
	 * @param _far the far clip plane distance
	 */
	inline void setClipping(Real _near, Real _far)
	{
		setFar(_far);
		setNear(_near);
	}

	/**
	 * Sets the view direction of the camera.
	 * @param d the direction of the camera
	 * @param ld the forward vector of the camera
	 */
	virtual void setDirection(const Vec3& d, const Vec3& ld=Vec3::NEGATIVE_UNIT_Z);

	/**
	 * Sets the cameras viewport size.
	 * @param viewportSize the size of the viewport
	 */
	void setViewportSize(const Vec2& viewportSize);

	/**
	 * @return the camera viewport size
	 */
	inline const Vec2& getViewportSize() const {
		return viewportSize;
	}

	/**
	 * @return the frustum of the camera.
	 */
	inline const Frustum& getFrustum() const
	{
		return frustum;
	}

	/**
	 * Sets the camera position.
	 * @param position The camera position.
	 */
	void setPosition(const Vec3& position);

	/**
	 * Sets the camera position.
	 * @param x The x position component.
	 * @param y The y position component.
	 * @param z The z position component.
	 */
	void setPosition(Real x, Real y, Real z);

	/**
	 * @return the camera position
	 */
	inline const Vec3& getPosition() const
	{
		return position;
	}

	void setOrientation(const Quaternion& o);

	/**
	 * @return the camera orientation
	 */
	inline const Quaternion& getOrientation() const
	{
		return orientation;
	}

	/**
	 * Sets the camera orientation to look at the given target.
	 * @param target The target to look at.
	 * @param up The up vector.
	 */
	void lookAt(const Vec3& target, const Vec3& up = Vec3::UNIT_Y);

	/**
	 * Sets the camera orientation to look at the given target.
	 * @param x The target x position component.
	 * @param y The target y position component.
	 * @param z The target z position component.
	 * @param upX The up vector x component.
	 * @param upY The up vector y component.
	 * @param upZ The up vector z component.
	 */
	void lookAt(Real x, Real y, Real z, Real upX=0, Real upY=1, Real upZ=0);

protected:
    /**
     * Called when the camera matrices need to be rebuilt.
     */
	virtual void onUpdate() = 0;

protected:
	Vec2 viewportSize;
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	Matrix4 combinedMatrix;
	Matrix4 invCombinedMatrix;

	Real _near;
	Real _far;
	Frustum frustum;

	Quaternion orientation;
	Vec3 position;

private:
	bool touched;

};

} /* namespace brew */

#endif /* BREW_CAMERA_H */
