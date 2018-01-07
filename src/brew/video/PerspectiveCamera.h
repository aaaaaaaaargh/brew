/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 random arts
 *
 *  Created on: Mar 19, 2016
 *
 */

#ifndef BREW_PERSPECTIVECAMERA_H
#define BREW_PERSPECTIVECAMERA_H

#include <brew/video/Camera.h>

namespace brew {

/**
 * A camera for perspective projection.
 */
class PerspectiveCamera : public Camera {
public:
	static const Real DefaultFOV; //< The default field of view.

public:
    /**
     * Creates a new perspective camera.
     * @param fov The field of view for the camera projection.
     * @param position The initial camera position.
     * @param lookAt The initial camera look-at vector.
     * @param near The near clip distance.
     * @param far The far clip distance.
     */
	PerspectiveCamera(
			Real fov=PerspectiveCamera::DefaultFOV,
            const Vec3& position = Vec3::ZERO,
            const Vec3& lookAt = Vec3::ZERO,
            Real near = DefaultNearClip,
            Real far = DefaultFarClip);

public:
    /**
     * Sets the cameras field of view.
     * @param fov The new field of view parameter value.
     */
	void setFOV(Real fov);

	/**
	 * @return The camera field of view.
	 */
	inline Real getFOV() const
	{
		return fov;
	}

protected:
    /**
     * Called when the camera matrices need to be rebuilt.
     */
	virtual void onUpdate();

	Real fov;

};

} /* namespace brew */

#endif /* BREW_PERSPECTIVECAMERA_H */
