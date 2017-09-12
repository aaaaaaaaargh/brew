/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2017 random arts
 *
 *  Created on: Aug 22, 2016
 *
 */

#ifndef BREW_GLOBJECT_H
#define BREW_GLOBJECT_H

#include <GL/gl.h>
#include <brew/video/gl/GLStateInfo.h>

namespace brew {

class GLContext;

/**
 * A class that contains information about objects managed by the GL.
 */
class GLObject {
	friend class GLContext;

protected:
	GLuint glId;
	GLContext& context;

public:
	/**
	 * Creates a new GL object.
	 * @param context The owning context.
	 */
	explicit GLObject(GLContext& context);

	/**
	 * @return This objects OpenGL ID.
	 */
	inline GLuint getGLId() const {
		return glId;
	}

	/**
	 * @return The GL context of this object.
	 */
	inline GLContext& getContext() {
		return context;
	}

	/**
	 * @return The current state of the owning GL context.
	 */
	GLStateInfo& getGLState();

};

} /* namespace brew */

#endif /* BREW_GLOBJECT_H */
