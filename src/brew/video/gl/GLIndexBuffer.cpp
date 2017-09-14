/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2017 random arts
 *
 *  Created on: 13.09.17
 *
 */

#include <brew/video/gl/GLIndexBuffer.h>
#include <brew/video/gl/GLExtensions.h>
#include <iostream>

// Nasty X11 declarations.
#ifdef None
#undef None
#endif

namespace brew {

using gl = GL30;

GLIndexBufferContextHandle::GLIndexBufferContextHandle(GLContext& context, IndexBuffer& indexBuffer)
        : GLObject(context) {
    gl::glGenBuffers(1, &glId);

    // The first syncToGPU() will force-request an update, so we do not have to initialize anything here.
}

GLIndexBufferContextHandle::~GLIndexBufferContextHandle() {
    gl::glDeleteBuffers(1, &glId);
}

void GLIndexBufferContextHandle::bind() {
    gl::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glId);
}

void GLIndexBufferContextHandle::unbind() {
    gl::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GLIndexBufferContextHandle::sync(IndexBuffer& indexBuffer) {
    // Upload the initial data.
    bind();

    auto& updateData = getGPUBufferUpdateData(indexBuffer);

    // Sync to GPU.
    auto& syncRanges = updateData.syncRanges;

    if(updateData.syncDirection == GPUBufferUpdateData::SyncDirection::ToGPU) {
        if (syncRanges.empty()) {
            // No sync ranges, upload the whole buffer.
            gl::glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBuffer.getSize(), indexBuffer.getRawPointer(), GL_DYNAMIC_DRAW);
        } else {
            // Sync parts of the buffer.
            for (auto& range : syncRanges) {
                gl::glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, range.from, range.to - range.from,
                                    indexBuffer.getRawPointer() + range.from);
            }
        }

    }
    else if(updateData.syncDirection == GPUBufferUpdateData::SyncDirection::FromGPU) {
        if (syncRanges.empty()) {
            // No sync ranges, download the whole buffer.
            gl::glGetBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indexBuffer.getSize(), indexBuffer.getRawPointer());
        } else {
            // Sync parts of the buffer.
            for (auto& range : syncRanges) {
                gl::glGetBufferSubData(GL_ELEMENT_ARRAY_BUFFER, range.from, range.to - range.from,
                                    indexBuffer.getRawPointer() + range.from);
            }
        }
    }

    unbind();

    // We must reset the sync state after we're done.
    updateData.syncDirection = GPUBufferUpdateData::SyncDirection::None;
}

} /* namespace brew */
