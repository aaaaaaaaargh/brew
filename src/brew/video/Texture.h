/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: 08.09.17
 *
 */

#ifndef BREW_TEXTURE_H
#define BREW_TEXTURE_H

#include <brew/core/ProxyObjectManager.h>
#include <brew/video/Color.h>
#include <brew/video/Pixmap.h>
#include <brew/core/Rect.h>

namespace brew {

/**
 * Texture formats supported by the engine.
 */
enum class TextureFormat {
    /**
     * Chroma (1 channel) signed value, 8, 16 and 32 bit per channel.
     */
    C8I, C16I, C32I,

    /**
     * Chroma (1 channel) unsigned signed value, 8, 16 and 32 bit per channel.
     */
    C8U, C16U, C32U,

    /**
     * Chroma (1 channel) floating point, 32 bit.
     */
    C32F,

    /**
     * RGB (3 channels) signed value, 8, 16 and 32 bit per channel.
     */
    RGB8I, RGB16I, RGB32I,

    /**
     * RGB (3 channels) unsigned value, 8, 16 and 32 bit per channel.
     */
    RGB8U, RGB16U, RGB32U,

    /**
     * RGB (3 channels) floating point, 32 bit per channel.
     */
    RGB32F,

    /**
     * RGBA (4 channels) signed value, 8, 16 and 32 bit per channel.
     */
    RGBA8I, RGBA16I, RGBA32I,

    /**
     * RGBA (4 channels) unsigned value, 8, 16 and 32 bit per channel.
     */
    RGBA8U, RGBA16U, RGBA32U,

    /**
     * RGBA (4 channels) floating point, 32 bit per channel.
     */
    RGBA32F,

    /**
     * Depth texture format.
     */
    Depth
};

/**
 * The texture filtering types.
 */
enum class TextureFiltering {
    None, //< No filtering.
    Bilinear //< Bilinear filtering.
};

class Texture;

/**
 * A struct of data that is only of one-time use for the allocation of a texture.
 */
struct TextureAllocationData {
    std::shared_ptr<Pixmap> pixmap;
    Color initialColor;
};

/**
 * The video context handle of a texture. Implementation is driver specific.
 */
class TextureContextHandle {
protected:
    /**
     * Allows restricted access to the protected allocation data of a texture.
     * @param texture The texture.
     * @return The allocation data.
     */
    static std::unique_ptr<TextureAllocationData>& getTextureAllocationData(Texture& texture);
};

/**
 * A class representing textures.
 */
class Texture : public ProxyObject<TextureContextHandle> {
public:
    /**
     * Creates a new empty texture.
     * @param width The width of the texture.
     * @param height The height of the texture.
     * @param format The texture format.
     * @param filtering The texture filtering.
     * @param numMipMaps The number of mip-maps to generator for this texture.
     */
    Texture(SizeT width,
            SizeT height,
            Color initialColor,
            TextureFormat format,
            TextureFiltering filtering,
            u8 numMipMaps
    );

    /**
     * Creates a new texture from a pixmap.
     * @param pixmap The pixmap to use.
     * @param format The texture format.
     * @param filtering The texture filtering.
     */
    Texture(std::shared_ptr<Pixmap> pixmap,
            TextureFormat format,
            TextureFiltering filtering,
            u8 numMipMaps
    );

public:
    static const TextureFormat DefaultTextureFormat;
    static const TextureFiltering DefaultTextureFiltering;
    static const u8 DefaultMipMaps;

public:
    /**
     * @return The width of the frame buffer.
     */
    inline SizeT getWidth() const {
        return width;
    }

    /**
     * @return The height of the frame buffer.
     */
    inline SizeT getHeight() const {
        return height;
    }

    /**
     * @return The format of this texture.
     */
    inline TextureFormat getTextureFormat() const {
        return format;
    }

    /**
     * @return The filtering type of this texture.
     */
    inline TextureFiltering getFiltering() const {
        return filtering;
    }

    /**
     * @return The number of mip-maps generated for this texture.
     */
    inline u8 getNumMipMaps() const {
        return numMipMaps;
    }

    /**
     * @return The context handle of this instance.
     */
    inline TextureContextHandle& getContextHandle() {
        return getObject();
    }

private:
    friend class TextureContextHandle;
    std::unique_ptr<TextureAllocationData> allocationData;

    SizeT width, height;
    TextureFormat format;
    TextureFiltering filtering;
    u8 numMipMaps;
};

class TextureRegion : public RealRect {
public:
    explicit TextureRegion(std::shared_ptr<Texture> texture);
    TextureRegion(std::shared_ptr<Texture> texture, const Rect& region);

    inline const std::shared_ptr<Texture>& getTexture() const {
        return texture;
    }

private:
    std::shared_ptr<Texture> texture;
};

} /* namespace brew */

#endif //BREW_TEXTURE_H
