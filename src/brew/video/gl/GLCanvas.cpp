/*
 * GLCanvas.cpp
 *
 *  Created on: Aug 22, 2016
 *      Author: void
 */

#include <brew/video/gl/GLCanvas.h>
#include <GL/gl.h>

namespace brew {

GLCanvas::GLCanvas(GLContext& ctx)
: VideoCanvas(ctx) {

}

void GLCanvas::onBeginFrame() {
    auto& stateInfo = static_cast<GLContext&>(getContext()).getStateInfo();
    stateInfo.currentViewport = nullptr;
    stateInfo.currentShaderProgram = nullptr;

    glClear(GL_COLOR_BUFFER_BIT);
}

void GLCanvas::onEndFrame() {

}

} /* namespace brew */
