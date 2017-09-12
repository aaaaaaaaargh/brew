/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2017 random arts
 *
 *  Created on: 08.09.17
 *
 */

#include <brew/video/Texture.h>

namespace brew {

const TextureFormat Texture::DefaultTextureFormat = TextureFormat::RGBA8U;
const TextureFiltering Texture::DefaultTextureFiltering = TextureFiltering::Bilinear;
const u8 Texture::DefaultMipMaps = 4;

Texture::Texture(SizeT width, SizeT height,
                 Color initialColor,
                 TextureFormat format,
                 TextureFiltering filtering,
                 u8 numMipMaps)
        : width(width), height(height), format(format), filtering(filtering), numMipMaps(numMipMaps) {
    allocationData = std::make_unique<TextureAllocationData>();
    allocationData->initialColor = initialColor;
}

Texture::Texture(std::unique_ptr<Pixmap> pixmap, TextureFormat format, TextureFiltering filtering, u8 numMipMaps)
        : width(width), height(height), format(format), filtering(filtering), numMipMaps(numMipMaps) {
    allocationData = std::make_unique<TextureAllocationData>();
    allocationData->pixmap = std::move(pixmap);
}

std::unique_ptr<TextureAllocationData>& TextureContextHandle::getTextureAllocationData(Texture& texture) {
    return texture.allocationData;
}

} /* namespace brew */
