/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 random arts
 *
 *  Created on: 08.09.17
 *
 */

#ifndef BREW_GLTEXTURE_H
#define BREW_GLTEXTURE_H

#include <brew/video/Texture.h>
#include <brew/video/gl/GLObject.h>

namespace brew {

/**
 * GL implementation of the texture context handle.
 */
class GLTextureContextHandle : public TextureContextHandle, public GLObject {
public:
    /**
     * Creates a new texture context handle.
     * @param context The GL context.
     * @param texture The texture to create the handle from.
     */
    GLTextureContextHandle(GLContext& context, Texture& texture);

    /**
     * Destructor.
     */
    ~GLTextureContextHandle();

public:
    /**
     * Converts a BREW texture format into its corresponding GL texture format.
     * @param fmt The BREW texture format.
     * @return The corresponding GL color format.
     */
    static GLint getGLFormat(TextureFormat fmt);

    /**
     * Retrieves the GL component type for a given texture format.
     * @param fmt The BREW texture format.
     * @return The corresponding GL component type.
     */
    static GLint getGLComponentType(TextureFormat fmt);

public:
    /**
     * Binds the texture.
     * @param textureUnit The texture unit to bind this texture to.
     */
    void bind(u8 textureUnit);

    /**
     * Unbinds a texture from a given texture unit.
     */
    static void unbind(GLContext& ctx, u8 textureUnit);


private:
    u8 boundTextureUnit;
};

} /* namespace brew */

#endif //BREW_GLTEXTURE_H
