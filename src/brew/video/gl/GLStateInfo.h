/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 Marcus v. Keil
 *
 *  Created on: 01.07.17
 *
 */

#ifndef BREW_GLSTATEINFO_H
#define BREW_GLSTATEINFO_H

#include <brew/core/Types.h>
#include <brew/video/RenderSettings.h>

#include <map>

namespace brew {

class ShaderProgram;
class Viewport;

/**
 * This structure holds information about the current GL state. It is mainly used for internal performance
 * optimizations.
 */
class GLStateInfo {
public:
    bool isTexture2DEnabled = false; //< Whether GL_TEXTURE2D is enabled.
    std::map<u8, s32> boundTextures; //< The currently bound textures.
    const ShaderProgram* currentShaderProgram = nullptr; //< The shader program in use.
    const Viewport* currentViewport = nullptr; //< The viewport in use.
    bool isScissorTestEnabled = false; //< Whether GL_SCISSOR test is enabled.
    bool isDepthTestEnabled = false; //< Whether GL_DEPTH_TEST is enabled.
    RenderSettings::BlendMode blendMode = RenderSettings::BlendMode::None; //< Whether GL_BLEND is enabled.
};

} /* namespace brew */

#endif //BREW_GLSTATEINFO_H
