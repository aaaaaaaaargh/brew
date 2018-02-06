/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 Marcus v. Keil
 *
 *  Created on: 02.01.18
 *
 */

#include <brew/video/RenderBatch.h>
#include <brew/video/VideoContext.h>

#include <utility>

namespace brew {

RenderBatch::RenderBatch(const RenderSettings& settings) :
        settings(settings) {

}

RenderBatch::RenderBatch(SortingCallback sortingCallback, const RenderSettings& settings) :
        sortingCallback(std::move(sortingCallback)), settings(settings) {
}

void RenderBatch::add(const Renderable& renderable) {
    renderables.push_back(renderable);
}

void RenderBatch::add(const RenderableProvider& provider) {
    provider.getRenderables(renderables);
}

void RenderBatch::flush(const RenderTarget& target, const Viewport& viewport, GPUExecutionContext& context) {
    if (sortingCallback) {
        renderables.sort(sortingCallback);
    }

    for (Renderable& renderable : renderables) {
        context.renderElement(target, renderable, viewport, settings);
    }

    renderables.clear();
}

} /* namespace brew */
