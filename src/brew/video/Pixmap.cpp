/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 Marcus v. Keil
 *
 *  Created on: Dec 30, 2015
 *
 */

#include <brew/video/Pixmap.h>
#include <brew/math/Math.h>

#include <cstring>

namespace brew
{

Pixmap::Pixmap(const SizeT& width, const SizeT& height, const ColorFormat& format)
: width(width), height(height), format(format), buffer(width * height * ColorFormatInfo::getSize(format))
{

}

Pixmap::Pixmap(const Pixmap& other)
: Pixmap(other, other.format)
{

}

Pixmap::Pixmap(const Pixmap& other, const ColorFormat& format)
: Pixmap(other.width, other.height, format)
{
	if(format == other.format) {
		std::memcpy(buffer.getRawPointer(), other.buffer.getRawPointer(), buffer.getSize());
		return;
	}

	for(SizeT y = 0; y < height; ++y) {
		for(SizeT x = 0; x < width; ++x) {
			// Todo
		}
	}
}

Pixmap::Pixmap(const Byte* rawBuffer, const SizeT& width, const SizeT& height, const ColorFormat& fmt)
: Pixmap(width, height, fmt)
{
	std::memcpy(buffer.getRawPointer(), rawBuffer, buffer.getSize());
}

Color Pixmap::getPixel(const SizeT& x, const SizeT& y) const
{
	SizeT offset = getPixelOffset(x, y);
	SizeT len = ColorFormatInfo::getSize(format);
	Byte* tmp = new Byte[len];
	buffer.read(tmp, offset, len);
	Color col = Color::fromMemory(tmp, format);
	delete [] tmp;
	return col;
}

void Pixmap::setPixel(const SizeT& x, const SizeT& y, const Color& c)
{
	SizeT offset = getPixelOffset(x, y);
	SizeT len = ColorFormatInfo::getSize(format);
	Byte* tmp = new Byte[len];
	c.toMemory(tmp, format);
	buffer.write(tmp, offset, len);
	delete [] tmp;
}

void Pixmap::clear(const Color& col) {
	SizeT len = ColorFormatInfo::getSize(format);
	Byte* tmp = new Byte[len];
	col.toMemory(tmp, format);
	for(SizeT i=0;i<width * height;++i) {
		buffer.write(tmp, i * len, len);
	}
	delete [] tmp;
}

SizeT Pixmap::getPixelOffset(const SizeT& x, const SizeT& y) const
{
	return (y * width + x) * ColorFormatInfo::getSize(format);
}

void Pixmap::blit(
        Pixmap& target,
        s32 targetX, s32 targetY,
        s32 sourceX, s32 sourceY,
        s32 sourceWidth, s32 sourceHeight) const {

    // Normalize source width.
    if(sourceWidth == 0) {
        // A value of 0 means full source width.
        sourceWidth = static_cast<s32>(getWidth());
    }
    else if(sourceWidth < 0) {
        // A negative value means full source width minus the given absolute value.
        sourceWidth = static_cast<s32>(getWidth()) + sourceWidth;
    }

    if(targetX < 0) {
        // Negative target offset, clip source width.
        sourceWidth += targetX;
        if(sourceWidth <= 0) {
            return;
        }
        targetX = 0;
    }

    if(targetX >= target.getWidth()) {
        // Draw outside of target bounds.
        return;
    }

    if(target.getWidth() <= targetX + sourceWidth) {
        // Clip overlaps.
        sourceWidth = static_cast<s32>(target.getWidth()) - targetX;
    }

    sourceWidth = math::clamp(sourceWidth, 0, getWidth());

    if(sourceWidth == 0) {
        // Nothing to draw.
        return;
    }

    // Normalize source height.
    if(sourceHeight == 0) {
        // A value of 0 means full source height.
        sourceHeight = static_cast<s32>(getHeight());
    }
    else if(sourceHeight < 0) {
        // A negative value means full source width minus the given absolute value.
        sourceHeight = static_cast<s32>(getHeight()) + sourceHeight;
    }

    if(targetY < 0) {
        // Negative target offset, clip source height.
        sourceHeight += targetY;
        if(sourceHeight <= 0) {
            return;
        }
        targetY = 0;
    }

    if(targetY >= target.getHeight()) {
        // Draw outside of target bounds.
        return;
    }

    if(target.getHeight() <= targetY + sourceHeight) {
        // Clip overlaps.
        sourceHeight = static_cast<s32>(target.getHeight()) - targetY;
    }

    sourceHeight = math::clamp(sourceHeight, 0, getHeight());

    if(sourceHeight == 0) {
        // Nothing to draw.
        return;
    }

    // Blit the pixmap.
    for(s32 y = 0; y < sourceHeight; ++y) {
        for(s32 x = 0; x < sourceWidth; ++x) {
            target.setPixel(
                    targetX + x,targetY + y,
                    getPixel(sourceX +x, sourceY + y)
            );
        }
    }
}

Pixmap Pixmap::flipped(bool horizontal, bool vertical) const {
    Pixmap result(width, height, format);

    for(SizeT y = 0; y < height; ++y) {
        for(SizeT x = 0; x < width; ++x) {
            SizeT srcX = horizontal ? width - 1 - x : x;
            SizeT srcY = vertical ? height - 1 - y : y;

            Color src = getPixel(srcX,srcY);

            result.setPixel(x,y, src);
        }
    }

    return result;
}

void Pixmap::applyFilter(FilterCallback callback) {
    for(SizeT y = 0; y < height; ++y) {
        for (SizeT x = 0; x < width; ++x) {
            Color col = getPixel(x,y);
            callback(x,y, col);
            setPixel(x,y, col);
        }
    }
}

} /* namespace brew */
