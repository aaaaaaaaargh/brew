/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 random arts
 *
 *  Created on: 02.01.18
 *
 */

#include <brew/video/RenderBatch.h>
#include <brew/video/VideoContext.h>

namespace brew {

RenderBatch::RenderBatch(SortingCallback sortingCallback) :
        sortingCallback(sortingCallback) {
}

void RenderBatch::add(const Renderable& renderable) {
    renderables.push_back(renderable);
}

void RenderBatch::flush(const RenderTarget& target, const Viewport& viewport, GPUExecutionContext& context) {
    if(sortingCallback) {
        renderables.sort(sortingCallback);
    }

    for(Renderable& renderable : renderables) {
        context.renderElement(target, renderable, viewport);
    }

    renderables.clear();
}

}
