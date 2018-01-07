/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: Dec 30, 2015
 *
 */

#ifndef BREW_PIXMAP_H
#define BREW_PIXMAP_H

#include <brew/video/Color.h>
#include <brew/core/HeapBuffer.h>

#include <functional>

namespace brew
{

/**
 * A class representing a pixmap in memory.
 */
class Pixmap
{

public:
	/**
	 * Creates a new pixmap.
	 * @param width The width of the pixmap.
	 * @param height The height of the pixmap.
	 * @param format The color format to use.
	 */
	Pixmap(const SizeT& width, const SizeT& height, const ColorFormat& format = ColorFormat::RGBA8U);

	/**
	 * Copy constructs a pixmap.
	 * @param other The pixmap to copy.
	 */
	Pixmap(const Pixmap& other);

	/**
	 * Copy constructs a pixmap.
	 * @param other The pixmap to copy.
	 * @param format The color format to convert the new pixmap into.
	 */
	Pixmap(const Pixmap& other, const ColorFormat& format);

	/**
	 * Creates a new pixmap from a raw byte buffer, size must be at least width * height * sizeof(format).
	 * @param rawBuffer The buffer.
	 * @param width The width of the pixmap.
	 * @param height The height of the pixmap.
	 * @param format The format.
	 */
	Pixmap(const Byte* rawBuffer, const SizeT& width, const SizeT& height, const ColorFormat& format);

public:
	/**
	 * Retrieves the color for a given pixel.
	 * @param x The x position of the pixel.
	 * @param y The y position of the pixel.
	 * @return The color at the given pixel.
	 */
	Color getPixel(const SizeT& x, const SizeT& y) const;

	/**
	 * Sets the color for a pixel.
	 * @param x The x position of the pixel.
	 * @param y The y position of the pixel.
	 * @param newColor The new color for the pixel.
	 */
	void setPixel(const SizeT& x, const SizeT& y, const Color& newColor);

	/**
	 * Clears the pixmap to a plain color.
	 * @param color The color to fill the pixmap with.
	 */
	void clear(const Color& color);

	/**
	 * Calculates the buffer offset for a pixel.
	 * @param x The x position of the pixel.
	 * @param y The y position of the pixel.
	 * @return The pixel buffer offset.
	 */
	SizeT getPixelOffset(const SizeT& x, const SizeT& y) const;

	/**
	 * @return The width of this pixmap.
	 */
	inline const SizeT& getWidth() const {
		return width;
	}

	/**
	 * @return The height of this pixmap.
	 */
	inline const SizeT& getHeight() const {
		return height;
	}

	/**
	 * @return The color format of this pixmap.
	 */
	inline const ColorFormat& getFormat() const {
		return format;
	}

	/**
	 * @return A reference to the internal pixel buffer.
	 */
	inline HeapBuffer& getPixelBuffer() {
		return buffer;
	}

	/**
	 * @return A const reference to the internal pixel buffer.
	 */
	inline const HeapBuffer& getPixelBuffer() const {
		return buffer;
	}

	/**
	 * Blits this pixmap onto another.
	 * If all arguments are set to 0, the whole image will be blit.
	 * @param target The pixmap to blit onto.
	 * @param targetX The target x position.
	 * @param targetY The target y position.
	 * @param sourceX The source x position.
	 * @param sourceY The source y position.
	 * @param sourceWidth The width of the area to blit.
	 * @param sourceHeight The height of the area to blit.
	 */
    void blit(
            Pixmap& target,
            s32 targetX = 0,
            s32 targetY = 0,
            s32 sourceX = 0,
            s32 sourceY = 0,
            s32 sourceWidth = 0,
            s32 sourceHeight = 0
    ) const;

	/**
	 * Creates a flipped copy of this pixmap.
	 * @param horizontal Whether to flip horizontal.
	 * @param vertical Whether to flip vertical.
	 * @return The flipped result.
	 */
	Pixmap flipped(bool horizontal, bool vertical) const;

	/**
	 * A filter callback function that can be used to perform an action on a per-pixel basis.
	 * The first two arguments of the callback are the x and y position of the pixel.
	 * The third argument is the pixel color. Changing this color will have an effect on the pixmap.
	 */
	typedef std::function<void(SizeT, SizeT, Color&)> FilterCallback;

	/**
	 * Applies a filter for the pixmap by calling a function for each pixel.
	 * @param callback The callback to invoke for each pixel.
	 */
	void applyFilter(FilterCallback callback);

private:
	SizeT width;
	SizeT height;
	ColorFormat format;
	HeapBuffer buffer;
};

} /* namespace brew */

#endif /* BREW_PIXMAP_H */
