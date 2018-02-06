/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: 05.09.17
 *
 */

#ifndef BREW_GLXCANVAS_H
#define BREW_GLXCANVAS_H

#include <brew/video/gl/GLCanvas.h>
#include <brew/video/gl/GLContext.h>
#include <brew/video/linux/X11Canvas.h>

#include <GL/glx.h>

namespace brew {

/**
 * The canvas implementation for GLX targets.
 */
class GLXCanvas : public X11Canvas, public GLCanvas {
public:
	/**
	 * Creates a new GLX canvas.
	 * @param context The GL context for this canvas.
	 */
	explicit GLXCanvas(GLContext& context);

public:
	/**
     * Called when the canvas is initialized.
     */
	void onInit() override;

	/**
     * Called when the canvas is about to be destroyed.
     */
	void onDrop() override;

	/**
     * Called when a frame is about to be rendered.
     */
	void onBeginFrame() override;

	/**
     * Called when a frame finished rendering.
     */
	void onEndFrame() override;

protected:
	/**
	 * @return The X visual for this canvas.
	 */
	XVisualInfo* chooseVisual() override;

private:
	GLXContext glxContext;
};

} /* namespace brew */

#endif /* BREW_GLXCANVAS_H */
