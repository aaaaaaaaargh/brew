/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2017 r.acc
 *
 *  OrthoCamera.h
 *
 *  Created on: Mar 19, 2016
 *      Author: void
 */

#ifndef BREW_ORTHOCAMERA_H_
#define BREW_ORTHOCAMERA_H_

#include <brew/video/Camera.h>

namespace brew {

/**
 * A camera class that is using orthographic projection.
 */
class OrthoCamera : public Camera {
public:
	/**
	 * Creates a new orthograpic camera.
	 * @param zoom The camera zoom level.
     * @param position The initial camera position.
     * @param lookAt The initial camera look-at vector.
     * @param near The near clip distance.
     * @param far The far clip distance.
	 */
	explicit OrthoCamera(Real zoom = 1.0,
				const Vec3& position = Vec3::ZERO,
				const Vec3& lookAt = Vec3::ZERO,
				Real near = 0,
				Real far= DefaultFarClip);

	/**
	 * Sets this cameras zoom level.
	 * @param zoom The zoom level.
	 */
	void setZoom(Real zoom);

	/**
	 * @return The camera zoom.
	 */
	inline Real getZoom() const {
		return zoom;
	}

protected:
	/**
     * Called when the camera matrices need to be rebuilt.
     */
	virtual void onUpdate();

private:
	Real zoom;

};

} /* namespace brew */

#endif /* BREW_ORTHOCAMERA_H_ */
