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

#ifndef BREW_GLGPUEXECUTIONCONTEXT_H
#define BREW_GLGPUEXECUTIONCONTEXT_H

#include <brew/video/GPUExecutionContext.h>

namespace brew {

class GLGPUExecutionContext : public GPUExecutionContext {
public:
    using GPUExecutionContext::GPUExecutionContext;

    /**
     * Renders a single element.
     * @param target The render target to render the element to.
     * @param renderable The renderable element.
     * @param viewport The viewport to use for rendering.
     */
    void renderElement(const RenderTarget& target, const Renderable& renderable, const Viewport& viewport) override;
};

} /* namespace brew */

#endif //BREW_GLGPUEXECUTIONCONTEXT_H
