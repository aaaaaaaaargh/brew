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

#ifndef BREW_GLCANVAS_H
#define BREW_GLCANVAS_H

#include <brew/video/VideoCanvas.h>
#include <brew/video/gl/GLContext.h>

namespace brew {

/**
 * The OpenGL implementation of the canvas.
 */
class GLCanvas : public virtual VideoCanvas {
public:
	/**
	 * Creates a new canvas.
	 * @param context The context to use for this canvas.
	 */
	explicit GLCanvas(GLContext& context);

	/**
     * Called when a frame is about to be rendered.
     */
	void onBeginFrame() override;

	/**
     * Called when a frame finished rendering.
     */
	void onEndFrame() override;
};

} /* namespace brew */

#endif /* BREW_GLCANVAS_H */
