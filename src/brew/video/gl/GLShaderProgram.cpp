/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 Marcus v. Keil
 *
 *  Created on: 03.01.18
 *
 */

#include <brew/video/gl/GLShaderProgram.h>
#include <brew/video/gl/GLShader.h>
#include <brew/video/gl/GLExtensions.h>

namespace brew {

using gl = GL20;

GLShaderProgramContextHandle::GLShaderProgramContextHandle(GLContext& context, ShaderProgram& shaderProgram)
: GLObject(context) {
    glId = gl::glCreateProgram();

    auto& allocationData = getShaderProgramAllocationData(shaderProgram);

    // Copy the shaders and clear the allocation data.
    auto shaders = allocationData->shaders;
    allocationData.reset();

    for(auto& shader : shaders) {
        auto& glShader = static_cast<GLShaderContextHandle&>(**shader);
        gl::glAttachShader(glId, glShader.getGLId());
    }

    gl::glLinkProgram(glId);

    // Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint status = 0;
    gl::glGetProgramiv(glId, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint maxLength = 0;
        gl::glGetProgramiv(glId, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        gl::glGetProgramInfoLog(glId, maxLength, &maxLength, &infoLog[0]);

        // We don't need the program anymore.
        gl::glDeleteProgram(glId);

        String errorMessage(infoLog.begin(), infoLog.end());
        throw ShaderCompileException(errorMessage);
    }

    // Always detach shaders after a successful link.
    for(auto& shader : shaders) {
        auto& glShader = static_cast<GLShaderContextHandle&>(**shader);
        gl::glDetachShader(glId, glShader.getGLId());
    }
}

GLShaderProgramContextHandle::~GLShaderProgramContextHandle() {
    gl::glDeleteProgram(glId);
}

void GLShaderProgramContextHandle::bind() {
    gl::glUseProgram(glId);
}

void GLShaderProgramContextHandle::unbind() {
    gl::glUseProgram(0);
}

}