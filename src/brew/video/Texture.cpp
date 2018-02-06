/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 Marcus v. Keil
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

Texture::Texture(std::shared_ptr<Pixmap> pixmap, TextureFormat format, TextureFiltering filtering, u8 numMipMaps)
        : width(pixmap->getWidth()), height(pixmap->getHeight()), format(format), filtering(filtering), numMipMaps(numMipMaps) {
    allocationData = std::make_unique<TextureAllocationData>();
    allocationData->pixmap = pixmap;
}

std::unique_ptr<TextureAllocationData>& TextureContextHandle::getTextureAllocationData(Texture& texture) {
    return texture.allocationData;
}

TextureRegion::TextureRegion(std::shared_ptr<Texture> texture, const Rect& region)
    : texture(texture), Rect(region) {

}

TextureRegion::TextureRegion(std::shared_ptr<Texture> texture)
    : texture(texture) {
    set(0,0, texture->getWidth(), texture->getHeight());
}

} /* namespace brew */
