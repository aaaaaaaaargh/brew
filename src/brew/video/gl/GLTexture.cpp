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

#include <brew/core/Types.h>
#include <brew/video/gl/GLContext.h>
#include <brew/video/gl/GLTexture.h>
#include <brew/video/gl/GLExtensions.h>

/**
 * X.h defines "None", which is also a texture filtering type, so we need to un-define this here.
 */
#undef None

namespace brew {

using gl = GL30;


GLint GLTextureContextHandle::getGLFormat(TextureFormat fmt) {
    switch (fmt) {
        case TextureFormat::C8I:
        case TextureFormat::C16I:
        case TextureFormat::C32I:
        case TextureFormat::C8U:
        case TextureFormat::C16U:
        case TextureFormat::C32U:
        case TextureFormat::C32F:
            return GL_RED;

        case TextureFormat::RGB8I:
        case TextureFormat::RGB16I:
        case TextureFormat::RGB32I:
        case TextureFormat::RGB8U:
        case TextureFormat::RGB16U:
        case TextureFormat::RGB32U:
        case TextureFormat::RGB32F:
            return GL_RGB;

        case TextureFormat::RGBA8I:
        case TextureFormat::RGBA16I:
        case TextureFormat::RGBA32I:
        case TextureFormat::RGBA8U:
        case TextureFormat::RGBA16U:
        case TextureFormat::RGBA32U:
        case TextureFormat::RGBA32F:
            return GL_RGBA;

        case TextureFormat::Depth:
            return GL_DEPTH_ATTACHMENT;
    }
}

GLint GLTextureContextHandle::getGLComponentType(TextureFormat fmt) {
    switch (fmt) {
        case TextureFormat::C8I:
        case TextureFormat::RGB8I:
        case TextureFormat::RGBA8I:
            return GL_BYTE;
        case TextureFormat::C8U:
        case TextureFormat::RGB8U:
        case TextureFormat::RGBA8U:
            return GL_UNSIGNED_BYTE;
        case TextureFormat::C16I:
        case TextureFormat::RGB16I:
        case TextureFormat::RGBA16I:
            return GL_SHORT;
        case TextureFormat::C16U:
        case TextureFormat::RGB16U:
        case TextureFormat::RGBA16U:
            return GL_UNSIGNED_SHORT;
        case TextureFormat::C32I:
        case TextureFormat::RGB32I:
        case TextureFormat::RGBA32I:
            return GL_INT;
        case TextureFormat::C32U:
        case TextureFormat::RGB32U:
        case TextureFormat::RGBA32U:
            return GL_UNSIGNED_INT;
        case TextureFormat::C32F:
        case TextureFormat::RGB32F:
        case TextureFormat::RGBA32F:
            return GL_FLOAT;
        case TextureFormat::Depth:
            return GL_DEPTH_ATTACHMENT;
    }
}

GLTextureContextHandle::GLTextureContextHandle(GLContext& context, Texture& texture)
: GLObject(context) {

    GLStateInfo& glState = getContext().getStateInfo();
    if(!glState.isTexture2DEnabled) {
        glEnable(GL_TEXTURE_2D);
        glState.isTexture2DEnabled = true;
    }

    glGenTextures(1, &glId);

    glBindTexture(GL_TEXTURE_2D, glId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    GLint filterType;

    switch(texture.getFiltering()) {
        case TextureFiltering::None:
            filterType = GL_NEAREST;
            break;
        case TextureFiltering::Bilinear:
            filterType = GL_LINEAR;
            break;
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterType);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterType);

    GLint internalFormat = GL_RGBA; // Force the internal format to RGBA (for now, will change with the support of depth textures)
    GLint componentType;
    GLint format;
    Byte* pixelBuffer;
    TextureFormat inputFormat = texture.getTextureFormat();

    std::unique_ptr<TextureAllocationData>& allocationData = getTextureAllocationData(texture);
    const std::shared_ptr<Pixmap>& pixmap = allocationData->pixmap;

    if (pixmap) {
        TextureFormat pixmapFormat = static_cast<TextureFormat>(pixmap->getFormat());
        format = getGLFormat(pixmapFormat);
        componentType = getGLComponentType(pixmapFormat);
        pixelBuffer = const_cast<Byte*>(pixmap->getPixelBuffer().getRawPointer());
    } else if(inputFormat == TextureFormat::Depth) {
        format = GL_DEPTH_COMPONENT;
        internalFormat = GL_DEPTH_COMPONENT32;
        componentType = GL_FLOAT;
        pixelBuffer = nullptr;
    } else {
        format = getGLFormat(inputFormat);
        componentType = getGLComponentType(inputFormat);
        SizeT pixelSize = ColorFormatInfo::getSize(static_cast<ColorFormat>(inputFormat));
        SizeT byteSize = texture.getWidth() * texture.getHeight() * pixelSize;
        pixelBuffer = new Byte[byteSize];

        for (SizeT i = 0; i < byteSize; i += pixelSize) {
            allocationData->initialColor.toMemory(pixelBuffer + i, static_cast<ColorFormat>(inputFormat));
        }
    }

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, texture.getWidth(), texture.getHeight(), 0, format, componentType, pixelBuffer);

    if(inputFormat == TextureFormat::Depth) {
        //logStream("GLTexture") << LogLevel::Debug << "Generated depth texture (id:=" << glId << ", dims:=" << dims.getWidth()
        //                       << "x" << dims.getHeight() << ")";
    }
    else {
        //logStream("GLTexture") << LogLevel::Debug << "Generated texture (id:=" << glId << ", dims:=" << dims.getWidth()
        //                       << "x" << dims.getHeight() << ")";
    }

    u8 numMipmaps = texture.getNumMipMaps();

    if(numMipmaps > 0) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, numMipmaps - 1);
        gl::glGenerateMipmap(GL_TEXTURE_2D);
    }

    // Clean up
    if (!pixmap) {
        delete[] pixelBuffer;
    }

    allocationData.reset();

    glBindTexture(GL_TEXTURE_2D, 0);

    if(glState.isTexture2DEnabled) {
        glEnable(GL_TEXTURE_2D);
        glState.isTexture2DEnabled = false;
    }
}

GLTextureContextHandle::~GLTextureContextHandle() {
    glDeleteTextures(1, &glId);
}

void GLTextureContextHandle::bind(u8 textureUnit) {
    GLStateInfo& glState = getContext().getStateInfo();

    if(!glState.isTexture2DEnabled) {
        glEnable(GL_TEXTURE_2D);
        glState.isTexture2DEnabled = true;
    }

    if(glState.boundTextures[textureUnit] != glId) {
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        glBindTexture(GL_TEXTURE_2D, glId);
        glState.boundTextures[textureUnit] = glId;
    }
}

void GLTextureContextHandle::unbind(GLContext& ctx, u8 textureUnit) {
    GLStateInfo& glState = ctx.getStateInfo();

    if(glState.boundTextures[textureUnit] != 0) {
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        glBindTexture(GL_TEXTURE_2D, 0);
        glState.boundTextures[textureUnit] = 0;
    }

    if(glState.isTexture2DEnabled) {
        glEnable(GL_TEXTURE_2D);
        glState.isTexture2DEnabled = false;
    }
}

} /* namespace brew */