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

#ifndef BREW_GPUBUFFER_H
#define BREW_GPUBUFFER_H

#include <brew/core/Types.h>
#include <brew/core/HeapBuffer.h>
#include <brew/core/ProxyObjectManager.h>
#include <brew/video/VideoContextObject.h>

#include <memory>
#include <vector>

namespace brew {

/**
 * A structure containing information about the synchronization updates of a GPU buffer.
 */
struct GPUBufferUpdateData {
    /**
     * A struct indicating the boundaries of a synchronization process.
     */
    struct SyncRange {
        SizeT from;
        SizeT to;
    };

    /**
     * The direction of the synchronization process.
     */
    enum class SyncDirection {
        None,
        ToGPU,
        FromGPU
    };

    std::vector<SyncRange> syncRanges;

    SyncDirection syncDirection = SyncDirection::None;
};

class GPUBufferContextHandle;

/**
 * The abstract GPU buffer implementation. Acts as a base for the more specific GPUBuffer template.
 */
class AbstractGPUBuffer : public HeapBuffer {
public:
    using HeapBuffer::HeapBuffer;

protected:
    /**
     * Syncs the buffer (or part of it) to the GPU.
     * @param offset The offset of the part to be synced.
     * @param len The length of the part to be synced.
     */
    virtual void syncToGPU(SizeT offset, SizeT len);

    /**
     * Syncs back the buffer (or part of it) from the GPU.
     * @param offset The offset of the part to be synced.
     * @param len The length of the part to be synced.
     */
    virtual void syncFromGPU(SizeT offset, SizeT len);

protected:
    void markSyncRange(SizeT from, SizeT to);

protected:
    friend class GPUBufferContextHandle;
    GPUBufferUpdateData updateData;
};

/**
 * The video context handle of a GPU buffer. Implementation is buffer specific.
 */
class GPUBufferContextHandle {
protected:
    /**
     * Allows restricted access to the protected update data of the GPU buffer.
     * @param buffer The buffer.
     * @return The update data.
     */
    static GPUBufferUpdateData& getGPUBufferUpdateData(AbstractGPUBuffer& buffer);
};

/**
 * A generic class for dealing with GPU buffers.
 * @tparam ContextHandleT The context handle type of this buffer.
 */
template<typename ContextHandleT>
class GPUBuffer : public AbstractGPUBuffer, public ProxyObject<ContextHandleT>, public VideoContextObject {
public:
    using AbstractGPUBuffer::AbstractGPUBuffer;

public:
    /**
     * Syncs the buffer (or part of it) to the GPU.
     * @param offset The offset of the part to be synced.
     * @param len The length of the part to be synced.
     * @throws IllegalStateException if the previous sync operation was not finished.
     */
    void syncToGPU(SizeT offset=0, SizeT len=0) {
        std::unique_lock<ProxyObject<ContextHandleT> > lk(*this);

        if(updateData.syncDirection == GPUBufferUpdateData::SyncDirection::FromGPU) {
            throw IllegalStateException("Cannot sync to GPU with pending read operations.");
        }

        AbstractGPUBuffer::syncToGPU(offset, len);

        lk.unlock();

        this->requestUpdate(true);
    }

    /**
     * Syncs back the buffer (or part of it) from the GPU.
     * @param offset The offset of the part to be synced.
     * @param len The length of the part to be synced.
     * @throws IllegalStateException if the previous sync operation was not finished.
     */
    void syncFromGPU(SizeT offset=0, SizeT len=0) {
        std::unique_lock<ProxyObject<ContextHandleT> > lk(*this);

        if(updateData.syncDirection == GPUBufferUpdateData::SyncDirection::ToGPU) {
            throw IllegalStateException("Cannot sync from GPU with pending write operations.");
        }

        AbstractGPUBuffer::syncFromGPU(offset, len);

        lk.unlock();

        ProxyObject<ContextHandleT>::requestUpdate(true);
    }
};

}

#endif //BREW_GPUBUFFER_H
