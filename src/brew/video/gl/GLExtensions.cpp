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

#include <brew/core/Exception.h>
#include <brew/video/gl/GLExtensions.h>

#if BREW_PLATFORM == BREW_PLATFORM_WINDOWS
#include "glext.h"
#elif BREW_PLATFORM == BREW_PLATFORM_LINUX
#endif

namespace brew {

void GLExtensions::init() {
#ifdef GL_VERSION_2_0
	GL20::init();
#endif
#ifdef GL_VERSION_3_0
	GL30::init();
#endif
#ifdef GL_VERSION_3_1
    GL31::init();
#endif
#ifdef GL_VERSION_3_2
	GL32::init();
#endif
}

template<typename PFNPROC>
void initExtension(const String& name, PFNPROC& ptr) {
	if (ptr != nullptr) {
		throw RuntimeException("GL extension '" + name + "' is already initialized!");
	}

	ptr = (PFNPROC) GLExtensions::getProcAddress(name);

	if (ptr == nullptr) {
		throw RuntimeException("Unable to load GL extension '" + name + "'");
	}
}

#define INIT_EXTENSION(name) initExtension(#name, _##name);

GLExtensions::ProcAddr GLExtensions::getProcAddress(const String& name) {
#if BREW_PLATFORM == BREW_PLATFORM_WINDOWS
	return wglGetProcAddress(name.c_str());
#else
	return glXGetProcAddress((const GLubyte*) name.c_str());
#endif
}

#ifdef GL_VERSION_2_0

PFNGLGENBUFFERSPROC _glGenBuffers = nullptr;
void GL20::glGenBuffers(GLsizei n, GLuint* buffers) {
	_glGenBuffers(n, buffers);
}

PFNGLDELETEBUFFERSPROC _glDeleteBuffers = nullptr;
void GL20::glDeleteBuffers(GLsizei n, GLuint* buffers) {
	_glDeleteBuffers(n, buffers);
}

PFNGLBINDBUFFERPROC _glBindBuffer = nullptr;
void GL20::glBindBuffer(GLenum target, GLuint buffer) {
	_glBindBuffer(target, buffer);
}

PFNGLDRAWBUFFERSPROC _glDrawBuffers = nullptr;
void GL20::glDrawBuffers(GLsizei n, const GLenum* bufs) {
	_glDrawBuffers(n, bufs);
}

PFNGLBUFFERDATAPROC _glBufferData = nullptr;
void GL20::glBufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage) {
	_glBufferData(target, size, data, usage);
}

PFNGLBUFFERSUBDATAPROC _glBufferSubData = nullptr;
void GL20::glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data) {
	_glBufferSubData(target, offset, size, data);
}

PFNGLBUFFERSTORAGEPROC _glBufferStorage = nullptr;
void GL20::glBufferStorage(GLenum target, GLsizeiptr size, const GLvoid* data, GLbitfield flags) {
	_glBufferStorage(target, size, data, flags);
}

PFNGLGETBUFFERSUBDATAPROC _glGetBufferSubData = nullptr;
void GL20::glGetBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, GLvoid* data) {
	_glGetBufferSubData(target, offset, size, data);
}

PFNGLCREATESHADERPROC _glCreateShader = nullptr;
GLuint GL20::glCreateShader(GLenum shaderType) {
	return _glCreateShader(shaderType);
}

PFNGLDELETESHADERPROC _glDeleteShader = nullptr;
void GL20::glDeleteShader(GLuint shader) {
	_glDeleteShader(shader);
}

PFNGLSHADERSOURCEPROC _glShaderSource = nullptr;
void GL20::glShaderSource(GLuint shader, GLsizei count, const GLchar** string, const GLint* length) {
	_glShaderSource(shader, count, string, length);
}

PFNGLCOMPILESHADERPROC _glCompileShader = nullptr;
void GL20::glCompileShader(GLuint shader) {
	_glCompileShader(shader);
}

PFNGLGETSHADERIVPROC _glGetShaderiv = nullptr;
void GL20::glGetShaderiv(GLuint shader, GLenum pname, GLint* params) {
	_glGetShaderiv(shader, pname, params);
}

PFNGLGETSHADERINFOLOGPROC _glGetShaderInfoLog = nullptr;
void GL20::glGetShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei* length, GLchar* infoLog) {
	_glGetShaderInfoLog(shader, maxLength, length, infoLog);
}

PFNGLCREATEPROGRAMPROC _glCreateProgram = nullptr;
GLuint GL20::glCreateProgram() {
	return _glCreateProgram();
}

PFNGLDELETEPROGRAMPROC _glDeleteProgram = nullptr;
void GL20::glDeleteProgram(GLuint program) {
	_glDeleteProgram(program);
}

PFNGLATTACHSHADERPROC _glAttachShader = nullptr;
void GL20::glAttachShader(GLuint program, GLuint shader) {
	_glAttachShader(program, shader);
}

PFNGLDETACHSHADERPROC _glDetachShader = nullptr;
void GL20::glDetachShader(GLuint program, GLuint shader) {
	_glDetachShader(program, shader);
}

PFNGLLINKPROGRAMPROC _glLinkProgram = nullptr;
void GL20::glLinkProgram(GLuint program) {
	_glLinkProgram(program);
}

PFNGLGETPROGRAMIVPROC _glGetProgramiv = nullptr;
void GL20::glGetProgramiv(GLuint program, GLenum pname, GLint* params) {
	_glGetProgramiv(program, pname, params);
}

PFNGLGETPROGRAMINFOLOGPROC _glGetProgramInfoLog = nullptr;
void GL20::glGetProgramInfoLog(GLuint program, GLsizei maxLength, GLsizei* length, GLchar* infoLog) {
	_glGetProgramInfoLog(program, maxLength, length, infoLog);
}

PFNGLUSEPROGRAMPROC _glUseProgram = nullptr;
void GL20::glUseProgram(GLuint program) {
	_glUseProgram(program);
}

PFNGLGETUNIFORMLOCATIONPROC _glGetUniformLocation = nullptr;
GLint GL20::glGetUniformLocation(GLuint program, const GLchar* name) {
	return _glGetUniformLocation(program, name);
}

PFNGLUNIFORM1FVPROC _glUniform1fv = nullptr;
void GL20::glUniform1fv(GLint location, GLsizei count, const GLfloat* value) {
	_glUniform1fv(location, count, value);
}

PFNGLUNIFORM2FVPROC _glUniform2fv = nullptr;
void GL20::glUniform2fv(GLint location, GLsizei count, const GLfloat* value) {
	_glUniform2fv(location, count, value);
}

PFNGLUNIFORM3FVPROC _glUniform3fv = nullptr;
void GL20::glUniform3fv(GLint location, GLsizei count, const GLfloat* value) {
	_glUniform3fv(location, count, value);
}

PFNGLUNIFORM4FVPROC _glUniform4fv = nullptr;
void GL20::glUniform4fv(GLint location, GLsizei count, const GLfloat* value) {
	_glUniform4fv(location, count, value);
}

PFNGLUNIFORM1IVPROC _glUniform1iv = nullptr;
void GL20::glUniform1iv(GLint location, GLsizei count, const GLint* value) {
	_glUniform1iv(location, count, value);
}

PFNGLUNIFORM1UIVPROC _glUniform1uiv = nullptr;
void GL20::glUniform1uiv(GLint location, GLsizei count, const GLuint* value) {
	_glUniform1uiv(location, count, value);
}

PFNGLUNIFORM2IVPROC _glUniform2iv = nullptr;
void GL20::glUniform2iv(GLint location, GLsizei count, const GLint* value) {
	_glUniform2iv(location, count, value);
}

PFNGLUNIFORM3IVPROC _glUniform3iv = nullptr;
void GL20::glUniform3iv(GLint location, GLsizei count, const GLint* value) {
	_glUniform3iv(location, count, value);
}

PFNGLUNIFORM4IVPROC _glUniform4iv = nullptr;
void GL20::glUniform4iv(GLint location, GLsizei count, const GLint* value) {
	_glUniform4iv(location, count, value);
}

PFNGLUNIFORMMATRIX4FVPROC _glUniformMatrix4fv = nullptr;
void GL20::glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
	_glUniformMatrix4fv(location, count, transpose, value);
}

PFNGLVERTEXATTRIBPOINTERPROC _glVertexAttribPointer = nullptr;
void GL20::glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer) {
	_glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

PFNGLENABLEVERTEXATTRIBARRAYPROC _glEnableVertexAttribArray = nullptr;
void GL20::glEnableVertexAttribArray(GLuint index) {
	_glEnableVertexAttribArray(index);
}

PFNGLMAPBUFFERPROC _glMapBuffer = nullptr;
void* GL20::glMapBuffer(GLenum target, GLenum access) {
	return _glMapBuffer(target, access);
}

PFNGLUNMAPBUFFERPROC _glUnmapBuffer = nullptr;
void GL20::glUnmapBuffer(GLenum target) {
	_glUnmapBuffer(target);
}

void GL20::init() {
	INIT_EXTENSION(glGenBuffers);
	INIT_EXTENSION(glDeleteBuffers);
	INIT_EXTENSION(glBindBuffer);
	INIT_EXTENSION(glDrawBuffers);
	INIT_EXTENSION(glBufferData);
	INIT_EXTENSION(glBufferSubData);
	INIT_EXTENSION(glBufferStorage);
	INIT_EXTENSION(glGetBufferSubData);
	INIT_EXTENSION(glCreateShader);
	INIT_EXTENSION(glDeleteShader);
	INIT_EXTENSION(glShaderSource);
	INIT_EXTENSION(glCompileShader);
	INIT_EXTENSION(glGetShaderiv);
	INIT_EXTENSION(glGetShaderInfoLog);
	INIT_EXTENSION(glCreateProgram);
	INIT_EXTENSION(glDeleteProgram);
	INIT_EXTENSION(glAttachShader);
	INIT_EXTENSION(glDetachShader);
	INIT_EXTENSION(glLinkProgram);
	INIT_EXTENSION(glGetProgramiv);
	INIT_EXTENSION(glGetProgramInfoLog);
	INIT_EXTENSION(glUseProgram);
	INIT_EXTENSION(glGetUniformLocation);
	INIT_EXTENSION(glUniform1fv);
	INIT_EXTENSION(glUniform2fv);
	INIT_EXTENSION(glUniform3fv);
	INIT_EXTENSION(glUniform4fv);
	INIT_EXTENSION(glUniform1iv);
	INIT_EXTENSION(glUniform1uiv);
	INIT_EXTENSION(glUniform2iv);
	INIT_EXTENSION(glUniform3iv);
	INIT_EXTENSION(glUniform4iv);
	INIT_EXTENSION(glUniformMatrix4fv);
	INIT_EXTENSION(glVertexAttribPointer);
	INIT_EXTENSION(glEnableVertexAttribArray);
	INIT_EXTENSION(glMapBuffer);
	INIT_EXTENSION(glUnmapBuffer);
}

#endif // GL_VERSION_2_0

#ifdef GL_VERSION_3_0

PFNGLGENERATEMIPMAPPROC _glGenerateMipmap = nullptr;
void GL30::glGenerateMipmap(GLenum target) {
	_glGenerateMipmap(target);
}

PFNGLGENFRAMEBUFFERSPROC _glGenFramebuffers = nullptr;
void GL30::glGenFramebuffers(GLsizei n, GLuint* ids) {
	_glGenFramebuffers(n, ids);
}

PFNGLDELETEFRAMEBUFFERSPROC _glDeleteFramebuffers = nullptr;
void GL30::glDeleteFramebuffers(GLsizei n, GLuint* ids) {
	_glDeleteFramebuffers(n, ids);
}

PFNGLFRAMEBUFFERTEXTUREPROC _glFramebufferTexture = nullptr;
void GL30::glFramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level) {
	_glFramebufferTexture(target, attachment, texture, level);
}

PFNGLFRAMEBUFFERTEXTURE2DPROC _glFramebufferTexture2D = nullptr;
void GL30::glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) {
	_glFramebufferTexture2D(target, attachment, textarget, texture, level);
}

PFNGLBINDFRAMEBUFFERPROC _glBindFramebuffer = nullptr;
void GL30::glBindFramebuffer(GLenum target, GLuint framebuffer) {
	_glBindFramebuffer(target, framebuffer);
}

PFNGLBINDFRAGDATALOCATIONPROC _glBindFragDataLocation = nullptr;
void GL30::glBindFragDataLocation(GLuint program, GLuint colorNumber, const char* name) {
	_glBindFragDataLocation(program, colorNumber, name);
}

PFNGLGENRENDERBUFFERSPROC _glGenRenderbuffers = nullptr;
void GL30::glGenRenderbuffers(GLsizei n, GLuint* renderbuffers) {
	_glGenRenderbuffers(n, renderbuffers);
}

PFNGLDELETERENDERBUFFERSPROC _glDeleteRenderbuffers = nullptr;
void GL30::glDeleteRenderbuffers(GLsizei n, GLuint* renderbuffers) {
	_glDeleteRenderbuffers(n, renderbuffers);
}

PFNGLBINDRENDERBUFFERPROC _glBindRenderbuffer = nullptr;
void GL30::glBindRenderbuffer(GLenum target, GLuint renderbuffer) {
	_glBindRenderbuffer(target, renderbuffer);
}

PFNGLRENDERBUFFERSTORAGEPROC _glRenderbufferStorage = nullptr;
void GL30::glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height) {
	_glRenderbufferStorage(target, internalformat, width, height);
}

PFNGLFRAMEBUFFERRENDERBUFFERPROC _glFramebufferRenderbuffer = nullptr;
void GL30::glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) {
	_glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
}

PFNGLCHECKFRAMEBUFFERSTATUSPROC _glCheckFramebufferStatus = nullptr;
GLenum GL30::glCheckFramebufferStatus(GLenum target) {
	return _glCheckFramebufferStatus(target);
}

PFNGLGENVERTEXARRAYSPROC _glGenVertexArrays = nullptr;
void GL30::glGenVertexArrays(GLsizei n, GLuint *arrays) {
	_glGenVertexArrays(n, arrays);
}

PFNGLDELETEVERTEXARRAYSPROC _glDeleteVertexArrays = nullptr;
void GL30::glDeleteVertexArrays(GLsizei n, GLuint *arrays) {
	_glDeleteVertexArrays(n, arrays);
}

PFNGLBINDVERTEXARRAYPROC _glBindVertexArray = nullptr;
void GL30::glBindVertexArray(GLuint array) {
	_glBindVertexArray(array);
}

PFNGLMAPBUFFERRANGEPROC _glMapBufferRange = nullptr;
void* GL30::glMapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access) {
	return _glMapBufferRange(target, offset, length, access);
}

void GL30::init() {
	INIT_EXTENSION(glGenerateMipmap);
	INIT_EXTENSION(glGenFramebuffers);
	INIT_EXTENSION(glDeleteFramebuffers);
	INIT_EXTENSION(glFramebufferTexture);
	INIT_EXTENSION(glFramebufferTexture2D);
	INIT_EXTENSION(glBindFramebuffer);
	INIT_EXTENSION(glBindFragDataLocation);
	INIT_EXTENSION(glGenRenderbuffers);
	INIT_EXTENSION(glDeleteRenderbuffers);
	INIT_EXTENSION(glBindRenderbuffer);
	INIT_EXTENSION(glRenderbufferStorage);
	INIT_EXTENSION(glFramebufferRenderbuffer);
	INIT_EXTENSION(glCheckFramebufferStatus);
	INIT_EXTENSION(glGenVertexArrays);
	INIT_EXTENSION(glDeleteVertexArrays);
	INIT_EXTENSION(glBindVertexArray);
	INIT_EXTENSION(glMapBufferRange);
}

#endif // GL_VERSION_3_0

#ifdef GL_VERSION_3_1

PFNGLGETUNIFORMBLOCKINDEXPROC _glGetUniformBlockIndex;
GLuint GL31::glGetUniformBlockIndex(GLuint program, const GLchar* uniformBlockName) {
	return _glGetUniformBlockIndex(program, uniformBlockName);
}

PFNGLUNIFORMBLOCKBINDINGPROC _glUniformBlockBinding;
void GL31::glUniformBlockBinding(GLuint program, GLuint blockIndex, GLuint bindingPoint) {
	_glUniformBlockBinding(program, blockIndex, bindingPoint);
}

PFNGLBINDBUFFERBASEPROC _glBindBufferBase;
void GL31::glBindBufferBase(GLenum target, GLuint index, GLuint buffer) {
    _glBindBufferBase(target, index, buffer);
}

void GL31::init() {
	INIT_EXTENSION(glGetUniformBlockIndex);
	INIT_EXTENSION(glUniformBlockBinding);
    INIT_EXTENSION(glBindBufferBase);
}

#endif // GL_VERSION_3_1

#ifdef GL_VERSION_3_2

PFNGLBINDSAMPLERPROC _glBindSampler = nullptr;
void GL32::glBindSampler(GLuint unit, GLuint sampler) {
	_glBindSampler(unit, sampler);
}

void GL32::init() {
	INIT_EXTENSION(glBindSampler);
}

#endif // GL_VERSION_3_2

} /* namespace brew */
