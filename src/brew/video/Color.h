/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 random arts
 *
 *  Created on: Dec 13, 2015
 *
 */

#ifndef BREW_COLOR_H
#define BREW_COLOR_H

#include <brew/math/Vec4.h>

#include <limits>
#include <ostream>

namespace brew
{

/**
 * Color formats supported by the engine.
 */
enum class ColorFormat {
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
	RGBA32F
};

/**
 * Stream implementation for color formats.
 * @param stream The stream.
 * @param color The color.
 * @return The stream for chaining.
 */
std::ostream& operator<<(std::ostream& s, const ColorFormat& fmt);

/**
 * This class contains static methods that can be used for detailed information of color formats.
 */
class ColorFormatInfo {
private:
    ColorFormatInfo() = default;

public:
    /**
     * @return The byte size of a single channel for the given color format.
     */
    static SizeT getChannelSize(const ColorFormat& fmt);

    /**
     * @return The number of channels for the given color format.
     */
    static SizeT getNumChannels(const ColorFormat& fmt);

    /**
     * @return The total byte size of the given color format.
     */
    inline static SizeT getSize(const ColorFormat& fmt) {
        return getChannelSize(fmt) * getNumChannels(fmt);
    }
};

/**
 * Represents a color.
 */
class Color {
public:
    u8 r; //< The red component.
    u8 g; //< The green component.
    u8 b; //< The blue component.
    u8 a; //< The alpha component.

public:
    /**
     * Constructor
     * @param r The red value between [0 ... 255].
     * @param g The green value between [0 ... 255].
     * @param b The blue value between [0 ... 255].
     * @param a The alpha value between [0 ... 255].
     */
    explicit Color(u8 r = 0, u8 g = 0, u8 b = 0, u8 a = 255);

public:
    /**
     * @return The red component converted as real value in [0 ... 1].
     */
    Real rReal() const;

    /**
     * @return The green component converted as real value in [0 ... 1].
     */
    Real gReal() const;

    /**
     * @return The blue component converted as real value in [0 ... 1].
     */
    Real bReal() const;

    /**
     * @return The alpha component converted as real value in [0 ... 1].
     */
    Real aReal() const;

    /**
     * Sets the color from real values
     * @param r The red component in [0 ... 1].
     * @param g The green component in [0 ... 1].
     * @param b The blue component in [0 ... 1].
     * @param a The alpha component in [0 ... 1].
     */
    void set(Real r, Real g, Real b, Real a);

    /**
     * Sets the color from byte values
     * @param r The red component in [0 ... 255].
     * @param g The green component in [0 ... 255].
     * @param b The blue component in [0 ... 255].
     * @param a The alpha component in [0 ... 255].
     */
    void set(u8 r, u8 g, u8 b, u8 a);

    /**
     * Gets a reference to a color component.
     * @param nth The index of the component.
     * @return The value of the nth component.
     */
    u8 operator[](u8 nth) const;

    /**
     * Compares two colors for equality.
     * @param other The color to compare.
     * @return Whether both colors are equal.
     */
    bool operator==(const Color& other) const;

    /**
     * Compares two colors for equality.
     * @param other The color to compare.
     * @return Whether both colors are unequal.
     */
    inline bool operator!=(const Color& other) const {
        return !(operator==(other));
    }

    /**
     * Creates a new color instance from a chunk of data in memory.
     * @param data The data to use as raw input
     * @param fmt The color format represented by the raw data
     * @return A new color
     */
    static Color fromMemory(const Byte* data, const ColorFormat& fmt);

    /**
     * Converts the color to a raw buffer.
     * @param data The buffer to copy this color to
     * @param fmt The target color format
     */
    void toMemory(Byte* data, const ColorFormat& fmt) const;

    /**
     * Multiplies this color with a given factor
     * @param factor The multiplication factor
     * @return A new color with the multiplied version of this color
     */
    Color operator*(Real factor) const;

    /**
     * Multiplies this color with a given factor
     * @param factor The multiplication factor
     * @return This color after the multiplication operation
     */
    Color& operator*=(Real factor);

    /**
     * Converts the color into a Vec4 structure.
     * @return The converted color.
     */
    inline Vec4 toVec4() const {
        return Vec4(rReal(),
                    gReal(),
                    bReal(),
                    aReal());
    }

public:
    /**
     * Pre-defined color constants.
     */
    static const Color BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, WHITE, GRAY, YELLOW;
};

/**
 * Stream implementation for colors.
 * @param stream The stream.
 * @param color The color.
 * @return The stream for chaining.
 */
std::ostream& operator<<(std::ostream& stream, const Color& color);

} /* namespace brew */

#endif /* RA_COLOR_H */
