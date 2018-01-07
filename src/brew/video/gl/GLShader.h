/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: 03.01.18
 *
 */

#ifndef BREW_GLSHADER_H
#define BREW_GLSHADER_H

#include <brew/video/Shader.h>
#include <brew/video/gl/GLObject.h>

namespace brew {

/**
 * GL implementation of a shader context handle.
 */
class GLShaderContextHandle : public ShaderContextHandle, public GLObject {
public:
    /**
     * Creates a new shader context handle.
     * @param context The GL context.
     * @param shader The shader to create the handle from.
     * @throws NotSupportedException if the given type is not supported.
     */
    GLShaderContextHandle(GLContext& context, Shader& shader);

    /**
     * Destructor.
     */
    ~GLShaderContextHandle();

public:
    /**
     * Converts a BREW shader types into its corresponding GL type.
     * @param type The BREW shader type.
     * @return The corresponding GL shader type.
     * @throws NotSupportedException if the given type is not supported.
     */
    static GLenum getGLType(ShaderType type);
};

} /* namespace brew */

#endif //BREW_GLSHADER_H
