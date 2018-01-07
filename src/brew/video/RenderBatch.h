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
     */
    RenderBatch() = default;

    /**
     * Creates a new render batch.
     * @param sortingCallback The sorting callback used to estimate the draw order of the elements.
     */
    explicit RenderBatch(SortingCallback sortingCallback);

    /**
     * Adds a new renderable the the batch.
     * @param renderable The renderable to add.
     */
    void add(const Renderable& renderable);

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
};

}

#endif //BREW_RENDERBATCH_H
