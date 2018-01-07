/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: Aug 21, 2016
 *
 */

#include <brew/video/linux/GLXCanvas.h>

namespace brew {

GLXCanvas::GLXCanvas(GLContext& ctx) :
		X11Canvas(ctx), GLCanvas(ctx), VideoCanvas(ctx), glxContext(nullptr) {

}

XVisualInfo* GLXCanvas::chooseVisual() {
	GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
	return glXChooseVisual(display, 0, att);
}

void GLXCanvas::onInit() {
	X11Canvas::onInit();

	glxContext = glXCreateContext(display, visual, nullptr, GL_TRUE);
	glXMakeCurrent(display, win, glxContext);

}

void GLXCanvas::onDrop() {
	if (glxContext != nullptr) {
        glXDestroyContext(display, glxContext);
    }
    
	glxContext = nullptr;
	X11Canvas::onDrop();
}

void GLXCanvas::onBeginFrame() {
	if (glXGetCurrentContext() != glxContext) {
		glXMakeCurrent(display, win, glxContext);
	}

	GLCanvas::onBeginFrame();
}

void GLXCanvas::onEndFrame() {
	GLCanvas::onEndFrame();
	glXSwapBuffers(display, win);
}

} /* namespace brew */
