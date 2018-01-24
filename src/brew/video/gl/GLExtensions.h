/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: Birth of universe.
 *
 */

#ifndef BREW_GLEXTENSIONS_H
#define BREW_GLEXTENSIONS_H

#include <brew/core/BuildInfo.h>
#include <brew/core/Types.h>
#include <brew/core/BuildInfo.h>
#include <brew/core/String.h>

#if BREW_PLATFORM == BREW_PLATFORM_WINDOWS
#include <windows.h>
#elif BREW_PLATFORM == BREW_PLATFORM_LINUX
#include <GL/glx.h>
#endif

#include <GL/gl.h>

namespace brew {

/**
 * Class for initializing available OpenGL extensions.
 */
class GLExtensions {
public:
#if BREW_PLATFORM == BREW_PLATFORM_WINDOWS
	typedef PROC WINAPI ProcAddr;
#else
	typedef void (*ProcAddr)();
#endif

	/**
	 * Initializes all available extensions.
	 */
	static void init();

    /**
     * @param name The name of the function.
     * @return The extensions process address of the given function.
     */
	static ProcAddr getProcAddress(const String& name);
};

#ifdef GL_VERSION_2_0
/**
 * OpenGL 2.0 compatible functionality.
 */
class GL20 {
public:
	static void init();

public:
	static void glGenBuffers(GLsizei n, GLuint* buffers);
	static void glDeleteBuffers(GLsizei n, GLuint* buffers);
	static void glBindBuffer(GLenum target, GLuint buffer);
	static void glDrawBuffers(GLsizei n, const GLenum* bufs);
	static void glBufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage);
	static void glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data);
	static void glBufferStorage(GLenum target, GLsizeiptr size, const GLvoid* data, GLbitfield flags);
	static void glGetBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, GLvoid* data);
	static GLuint glCreateShader(GLenum shaderType);
	static void glDeleteShader(GLuint shader);
	static void glShaderSource(GLuint shader, GLsizei count, const GLchar** string, const GLint* length);
	static void glCompileShader(GLuint shader);
	static void glGetShaderiv(GLuint shader, GLenum pname, GLint* params);
	static void glGetShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei *length, GLchar *infoLog);
	static GLuint glCreateProgram();
	static void glDeleteProgram(GLuint program);
	static void glAttachShader(GLuint program, GLuint shader);
	static void glDetachShader(GLuint program, GLuint shader);
	static void glLinkProgram(GLuint program);
	static void glGetProgramiv(GLuint program, GLenum pname, GLint* params);
	static void glGetProgramInfoLog(GLuint program, GLsizei maxLength, GLsizei *length, GLchar *infoLog);
	static void glUseProgram(GLuint program);
	static GLint glGetUniformLocation(GLuint program, const GLchar* name);
	static void glUniform1fv(GLint location, GLsizei count, const GLfloat* value);
	static void glUniform2fv(GLint location, GLsizei count, const GLfloat* value);
	static void glUniform3fv(GLint location, GLsizei count, const GLfloat* value);
	static void glUniform4fv(GLint location, GLsizei count, const GLfloat* value);
	static void glUniform1iv(GLint location, GLsizei count, const GLint* value);
	static void glUniform1uiv(GLint location, GLsizei count, const GLuint* value);
	static void glUniform2iv(GLint location, GLsizei count, const GLint* value);
	static void glUniform3iv(GLint location, GLsizei count, const GLint* value);
	static void glUniform4iv(GLint location, GLsizei count, const GLint* value);
	static void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
	static void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer);
	static void glEnableVertexAttribArray(GLuint index);
	static void* glMapBuffer(GLenum target, GLenum access);
	static void glUnmapBuffer(GLenum target);
};
#endif // GL_VERSION_2_0

#ifdef GL_VERSION_3_0
/**
 * OpenGL 3.0 compatible functionality.
 */
class GL30: public GL20 {
public:
	static void init();

public:
	static void glGenerateMipmap(GLenum target);
	static void glGenFramebuffers(GLsizei n, GLuint *ids);
	static void glDeleteFramebuffers(GLsizei n, GLuint *ids);
	static void glFramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level);
	static void glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
	static void glBindFramebuffer(GLenum target, GLuint framebuffer);
	static void glBindFragDataLocation(	GLuint program, GLuint colorNumber, const char * name);
	static void glGenRenderbuffers(GLsizei n, GLuint *renderbuffers);
	static void glDeleteRenderbuffers(GLsizei n, GLuint *renderbuffers);
	static void glBindRenderbuffer(GLenum target, GLuint renderbuffer);
	static void glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
	static void glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
	static GLenum glCheckFramebufferStatus(GLenum target);
	static void glGenVertexArrays(GLsizei n,GLuint *arrays);
	static void glDeleteVertexArrays(GLsizei n,GLuint *arrays);
	static void glBindVertexArray(GLuint array);
	static void* glMapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
};
#endif // GL_VERSION_3_0

#ifdef GL_VERSION_3_1
/**
 * OpenGL 3.1 compatible functionality.
 */
class GL31: public GL30 {
public:
	static void init();

public:
	static GLuint glGetUniformBlockIndex(GLuint program, const GLchar* uniformBlockName);
	static void glUniformBlockBinding(GLuint program, GLuint blockIndex, GLuint bindingPoint);
    static void glBindBufferBase(GLenum target, GLuint index, GLuint buffer);
};
#endif // GL_VERSION_3_1

#ifdef GL_VERSION_3_2
/**
 * OpenGL 3.2 compatible functionality.
 */
class GL32: public GL31 {
public:
	static void init();

public:
	static void glBindSampler(GLuint unit, GLuint sampler);
};
#endif // GL_VERSION 3_2

} /* namespace brew */

#endif // BREW_GLEXTENSIONS_H
