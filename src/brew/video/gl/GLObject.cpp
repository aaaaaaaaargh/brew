/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 Marcus v. Keil
 *
 *  Created on: 01.07.17
 *
 */

#include <brew/video/gl/GLContext.h>
#include <brew/video/gl/GLObject.h>

namespace brew {

GLObject::GLObject(GLContext& context)
: context(context) {}

GLStateInfo& GLObject::getGLState() {
    return context.getStateInfo();
}

} /* namespace brew */
