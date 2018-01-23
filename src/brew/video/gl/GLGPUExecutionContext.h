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

#ifndef BREW_GLGPUEXECUTIONCONTEXT_H
#define BREW_GLGPUEXECUTIONCONTEXT_H

#include <brew/video/GPUExecutionContext.h>
#include <brew/video/gl/GLObject.h>

namespace brew {

class GLGPUExecutionContext : public GPUExecutionContext, public GLObject {
public:
    GLGPUExecutionContext(GLContext& ctx);

    /**
     * Renders a single element.
     * @param target The render target to render the element to.
     * @param renderable The renderable element.
     * @param viewport The viewport to use for rendering.
     * @param settings The render settings for the draw call.
     */
    void renderElement(const RenderTarget& target, const Renderable& renderable, const Viewport& viewport, const RenderSettings& settings) override;
};

} /* namespace brew */

#endif //BREW_GLGPUEXECUTIONCONTEXT_H
