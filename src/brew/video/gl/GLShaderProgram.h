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

#ifndef BREW_GLSHADERPROGRAM_H
#define BREW_GLSHADERPROGRAM_H

#include <brew/video/ShaderProgram.h>
#include <brew/video/gl/GLObject.h>

namespace brew {

/**
 * GL implementation of a shader context handle.
 */
class GLShaderProgramContextHandle : public ShaderProgramContextHandle, public GLObject {
public:
    /**
     * Creates a new shader program context handle.
     * @param context The GL context.
     * @param shader The shader program to create the handle from.
     */
    GLShaderProgramContextHandle(GLContext& context, ShaderProgram& shaderProgram);

    /**
     * Destructor.
     */
    ~GLShaderProgramContextHandle();

public:
    /**
     * Binds the shader program.
     */
    void bind();

    /**
     * Unbinds the shader program.
     */
    void unbind();
};

} /* namespace brew */

#endif //BREW_GLSHADERPROGRAM_H
