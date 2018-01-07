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

#ifndef BREW_GPUEXECUTIONCONTEXT_H
#define BREW_GPUEXECUTIONCONTEXT_H

#include <brew/video/Renderable.h>
#include <brew/video/RenderTarget.h>
#include <brew/video/Viewport.h>

namespace brew {

class VideoContext;

/**
 * The execution context for an atomic set of GPU instructions.
 * Depending on the backend of the video driver the execution could either be
 * sequential or non-blocking.
 */
class GPUExecutionContext {
public:
    /**
     * Creates a new GPU execution context.
     * @param context The video context that owns the execution context.
     */
    explicit GPUExecutionContext(VideoContext& context);

public:
    /**
     * Renders a single element.
     * @param target The render target to render the element to.
     * @param renderable The renderable element.
     * @param viewport The viewport to use for rendering.
     */
    virtual void renderElement(const RenderTarget& target, const Renderable& renderable, const Viewport& viewport) = 0;

private:
    VideoContext& context;
};

}

#endif //BREW_GPUEXECUTIONCONTEXT_H
