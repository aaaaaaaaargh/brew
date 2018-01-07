/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 random arts
 *
 *  Created on: 13.09.17
 *
 */

#include <brew/video/gl/GLVertexBuffer.h>
#include <brew/video/gl/GLExtensions.h>

// Nasty X11 declarations.
#ifdef None
#undef None
#endif

namespace brew {

using gl = GL30;

GLVertexBufferContextHandle::GLVertexBufferContextHandle(GLContext& context, VertexBuffer& vertexBuffer)
        : GLObject(context) {
    gl::glGenBuffers(1, &glId);

    // The first syncToGPU() will force-request an update, so we do not have to initialize anything here.
}

GLVertexBufferContextHandle::~GLVertexBufferContextHandle() {
    gl::glDeleteBuffers(1, &glId);
}

void GLVertexBufferContextHandle::bind() {
    gl::glBindBuffer(GL_ARRAY_BUFFER, glId);
}

void GLVertexBufferContextHandle::unbind() {
    gl::glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GLVertexBufferContextHandle::sync(VertexBuffer& vertexBuffer) {
    // Upload the initial data.
    bind();

    auto& updateData = getGPUBufferUpdateData(vertexBuffer);

    // Sync to GPU.
    auto& syncRanges = updateData.syncRanges;

    if(updateData.syncDirection == GPUBufferUpdateData::SyncDirection::ToGPU) {
        if (syncRanges.empty()) {
            // No sync ranges, upload the whole buffer.
            gl::glBufferData(GL_ARRAY_BUFFER, vertexBuffer.getSize(), vertexBuffer.getRawPointer(), GL_DYNAMIC_DRAW);
        } else {
            // Sync parts of the buffer.
            for (auto& range : syncRanges) {
                gl::glBufferSubData(GL_ARRAY_BUFFER, range.from, range.to - range.from,
                                    vertexBuffer.getRawPointer() + range.from);
            }
        }

    }
    else if(updateData.syncDirection == GPUBufferUpdateData::SyncDirection::FromGPU) {
        if (syncRanges.empty()) {
            // No sync ranges, download the whole buffer.
            gl::glGetBufferSubData(GL_ARRAY_BUFFER, 0, vertexBuffer.getSize(), vertexBuffer.getRawPointer());
        } else {
            // Sync parts of the buffer.
            for (auto& range : syncRanges) {
                gl::glGetBufferSubData(GL_ARRAY_BUFFER, range.from, range.to - range.from,
                                    vertexBuffer.getRawPointer() + range.from);
            }
        }
    }

    unbind();

    // We must reset the sync state after we're done.
    updateData.syncDirection = GPUBufferUpdateData::SyncDirection::None;
}

} /* namespace brew */
