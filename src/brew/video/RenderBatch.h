/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: 02.01.18
 *
 */

#ifndef BREW_RENDERBATCH_H
#define BREW_RENDERBATCH_H

#include <brew/video/Renderable.h>
#include <brew/video/RenderTarget.h>
#include <brew/video/GPUExecutionContext.h>

#include <memory>
#include <list>
#include <functional>

namespace brew {

/**
 * A render batch draws a set of renderables.
 * It can be used to perform depth sorting on the elements to render before flushing it to the graphics device.
 */
class RenderBatch {
public:
    using SortingCallback = std::function<bool(const Renderable&, const Renderable&)>; //< The sorting callback.

public:
    /**
     * Creates a new render batch without draw order.
     * @param settings The render settings to use for draw calls in this batch.
     */
    explicit RenderBatch(const RenderSettings& settings = RenderSettings::Defaults);

    /**
     * Creates a new render batch.
     * @param sortingCallback The sorting callback used to estimate the draw order of the elements.
     * @param settings The render settings to use for draw calls in this batch.
     */
    explicit RenderBatch(SortingCallback sortingCallback, const RenderSettings& settings = RenderSettings::Defaults);

    /**
     * @return A reference to the render settings of this batch.
     */
    inline RenderSettings& getRenderSettings() {
        return settings;
    }

    /**
     * Adds a new renderable the the batch.
     * @param renderable The renderable to add.
     */
    void add(const Renderable& renderable);

    /**
     * Adds renderables from a provider.
     * @param renderable The renderable provider to add the renderables from.
     */
    void add(const RenderableProvider& provider);

    /**
     * Flushes the batch and executes the drawing on the GPU.
     * @param target The render target to use for drawing.
     * @param viewport The viewport to use for rendering.
     * @param context The execution context for the GPU instructions.
     */
    void flush(const RenderTarget& target, const Viewport& viewport, GPUExecutionContext& context);

private:
    SortingCallback sortingCallback;
    std::list<Renderable> renderables;
    RenderSettings settings;
};

}

#endif //BREW_RENDERBATCH_H
