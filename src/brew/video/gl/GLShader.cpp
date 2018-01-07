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

#include <brew/video/gl/GLShader.h>
#include <brew/video/gl/GLExtensions.h>

namespace brew {

using gl = GL20;

GLShaderContextHandle::GLShaderContextHandle(GLContext& context, Shader& shader)
    : GLObject(context) {
    GLenum shaderType = getGLType(shader.getType());

    glId = gl::glCreateShader(shaderType);

    auto& allocationData = getShaderAllocationData(shader);

    if(allocationData->source) {
        // We have plain text source code.
        auto& src = *allocationData->source;

        const GLchar* glSrc = src.c_str();
        auto glLen = static_cast<GLint>(src.length());

        gl::glShaderSource(glId, 1, &glSrc, &glLen);
    }

    gl::glCompileShader(glId);

    GLint status = 0;
    gl::glGetShaderiv(glId, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint maxLength = 0;
        gl::glGetShaderiv(glId, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(static_cast<unsigned long>(maxLength));
        gl::glGetShaderInfoLog(glId, maxLength, &maxLength, &infoLog[0]);

        // We don't need the shader anymore.
        gl::glDeleteShader(glId);

        String errorMessage(infoLog.begin(), infoLog.end());
        throw ShaderCompileException(errorMessage);
    }
}

GLShaderContextHandle::~GLShaderContextHandle() {
    gl::glDeleteShader(glId);
}

GLenum GLShaderContextHandle::getGLType(ShaderType type) {
    switch(type) {
        case ShaderType::Vertex:
            return GL_VERTEX_SHADER;
        case ShaderType::Fragment:
            return GL_FRAGMENT_SHADER;
        default:
            throw NotSupportedException("Unsupported shader type.");
    }
}

}