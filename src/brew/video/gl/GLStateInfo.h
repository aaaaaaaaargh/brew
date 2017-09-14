/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2017 random arts
 *
 *  Created on: 01.07.17
 *
 */

#ifndef BREW_GLSTATEINFO_H
#define BREW_GLSTATEINFO_H

#include <brew/core/Types.h>

#include <map>

namespace brew {

/**
 * This structure holds information about the current GL state. It is mainly used for internal performance
 * optimizations.
 */
class GLStateInfo {
public:
    bool isTexture2DEnabled = false; //< Whether GL_TEXTURE2D is enabled.
    u8 activeTextureUnit = 0; //< The active texture unit.
    std::map<u8, s32> boundTextures; //< The currently bound textures.
   // const ShaderProgram* currentShaderProgram = nullptr; //< The shader program in use.
    bool isScissorTestEnabled = false; //< Whether GL_SCISSOR test is enabled.
    bool isDepthTestEnabled = false; //< Whether GL_DEPTH_TEST is enabled.
    bool isBlendingEnabled = false; //< Whether GL_BLEND is enabled.
};

} /* namespace brew */

#endif //BREW_GLSTATEINFO_H
