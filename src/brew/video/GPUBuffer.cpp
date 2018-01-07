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

#include <brew/video/GPUBuffer.h>

namespace brew {

void AbstractGPUBuffer::markSyncRange(SizeT from, SizeT to) {
    auto& syncRanges = updateData.syncRanges;

    if(from == 0 && (to == 0 || to == getSize())) {
        // Sync the whole buffer, remove any sync ranges recorded so far.
        syncRanges.clear();
        return;
    }

    syncRanges.push_back({ from, to });

    bool found = true;
    const static SizeT mergeThreshold = 64;

    while(found) {
        found=false;

        for(SizeT i=0; i < syncRanges.size(); ++i) {
            for(SizeT j=0; j < syncRanges.size(); ++j) {
                if(i != j
                   && syncRanges[i].from < syncRanges[j].to + mergeThreshold
                   && syncRanges[j].from <= syncRanges[i].to + mergeThreshold
                        ) {
                    // These ranges are overlapping, merge.
                    syncRanges[i].from = std::min(syncRanges[i].from, syncRanges[j].from);
                    syncRanges[i].to = std::min(syncRanges[i].to, syncRanges[j].to);

                    syncRanges.erase(syncRanges.begin() + j);

                    found=true;
                    break;
                }
            }

            if(found) {
                break;
            }
        }
    }

    if(syncRanges.size() == 1 && syncRanges.front().from == 0 && syncRanges.front().to == getSize()) {
        // The whole buffer should be updated.
        syncRanges.clear();
    }
}

void AbstractGPUBuffer::syncToGPU(SizeT offset, SizeT len) {
    markSyncRange(offset, offset + len);
    updateData.syncDirection = GPUBufferUpdateData::SyncDirection::ToGPU;
}

void AbstractGPUBuffer::syncFromGPU(SizeT offset, SizeT len) {
    markSyncRange(offset, offset + len);
    updateData.syncDirection = GPUBufferUpdateData::SyncDirection::FromGPU;
}

GPUBufferUpdateData& GPUBufferContextHandle::getGPUBufferUpdateData(AbstractGPUBuffer& buffer) {
    return buffer.updateData;
}

} /* namespace brew */
