/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: 13.09.17
 *
 */

#include <brew/video/gl/GLMesh.h>
#include <brew/video/gl/GLExtensions.h>
#include <brew/video/gl/GLVertexBuffer.h>
#include <brew/video/gl/GLIndexBuffer.h>

namespace brew {

using gl = GL30;

GLMeshContextHandle::GLMeshContextHandle(GLContext& context, Mesh& mesh)
        : GLObject(context) {
    gl::glGenVertexArrays(1, &glId);

    bind();

    auto& vbo = static_cast<GLVertexBufferContextHandle&>(mesh.getVertices().getContextHandle());
    vbo.bind();

    GLenum type;
    const auto& layout = mesh.getVertices().getLayout();
    GLuint idx = 0;
    for (const auto& a : layout) {
        switch (a.attribute->getComponentType()) {
            case VertexAttribute::ComponentType::Byte:
                type = GL_BYTE;
                break;
            case VertexAttribute::ComponentType::Float:
                type = GL_FLOAT;
                break;
        }
        auto stride = static_cast<GLsizei>(layout.getSize()); // Stride is always the complete row length
        SizeT offset = layout.getAttributeOffset(*a.attribute);
        gl::glEnableVertexAttribArray(idx);
        gl::glVertexAttribPointer(idx, static_cast<GLint>(a.attribute->getNumComponents()), type, GL_FALSE, stride, (GLvoid*)offset);
        idx++;
    }

    vbo.unbind();
    unbind();
}

GLMeshContextHandle::~GLMeshContextHandle() {
    gl::glDeleteBuffers(1, &glId);
}

void GLMeshContextHandle::bind() {
    gl::glBindVertexArray(glId);
}

void GLMeshContextHandle::unbind() {
    gl::glBindVertexArray(0);
}

} /* namespace brew */
