/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2017 random arts
 *
 *  Created on: 06.09.17
 *
 */

#ifndef BREW_GLCONTEXT_H
#define BREW_GLCONTEXT_H

#include <brew/video/VideoContext.h>
#include <brew/video/gl/GLStateInfo.h>
#include "GLStateInfo.h"

namespace brew {

class GLContext : public VideoContext {
public:
    /**
     * Creates the context and initializes the GL extensions.
     */
    GLContext();

public:
    /**
     * Creates a frame buffer handle.
     * @param frameBuffer The frame buffer instance.
     * @return The context handle of the created instance.
     */
    std::unique_ptr<FrameBufferContextHandle> createObject(FrameBuffer& frameBuffer) override;

    /**
     * Creates a texture handle.
     * @param frameBuffer The texture instance.
     * @return The context handle of the created instance.
     */
    std::unique_ptr<TextureContextHandle> createObject(Texture& texture) override;

    /**
     * Creates a shader variables handle.
     * @param shaderVariables The shader variables instance.
     * @return The context handle of the created instance.
     */
    std::unique_ptr<ShaderVariablesContextHandle> createObject(ShaderVariables& shaderVariables) override;

    /**
     * Updates a shader variables handle.
     * @param shaderVariables The shader variables instance.
     */
    void updateObject(ShaderVariables& shaderVariables) override;

public:
    /**
	 * @return The current state of GL.
	 */
    inline GLStateInfo& getStateInfo() {
        return glStateInfo;
    }

    /**
	 * @return The current state of GL.
	 */
    inline const GLStateInfo& getStateInfo() const {
        return glStateInfo;
    }

private:
    GLStateInfo glStateInfo;
};

} /* namespace brew */

#endif //BREW_GLCONTEXT_H
