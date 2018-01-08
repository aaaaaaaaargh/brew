/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: Jan 31, 2017
 *
 */

#ifndef BREW_FONT_H
#define BREW_FONT_H

#include <brew/core/Types.h>
#include <brew/core/String.h>
#include <brew/core/Rect.h>

#include <brew/math/Vec2.h>

#include <brew/video/Pixmap.h>

#include <map>
#include <memory>

namespace brew {

/**
 * Base class for rendering fonts.
 */
class Font {
public:
	typedef WideString::value_type char_type;

    struct RenderSettings {
        Real outerSpacing = 3;
    };

	/**
	 * Contains information about glyphs.
	 */
	class Glyph {
	public:
        char_type codePoint; //< The code point for this glyph.
        Real ascent; //< The maximum distance from the upper edge of the glyph to the baseline.
        Real descent; //< The maximum distance from the lower edge of the glyph to the baseline.
        Real bearing; //< The distance from the left upper edge of the glyphs bounding box to the pen position.
		Real advance; //< The amount to advance the pen position after drawing the glyph.
    };

	/**
	 * The alignment of the baseline.
	 */
	enum class BaselineAlignment {
		Horizontal, //< Align horizontally.
		Vertical //< Align vertically.
	};

	/**
	 * The font settings class.
	 */
	class Settings {
	public:
		BaselineAlignment baselineAlignment; //< The baseline alignment.
		Real ascent; //< Distance from baseline to the highest coordinate where an outline is placed.
		Real descent; //< Distance from baseline to the lowest coordinate where an outline is placed. Must be negative.
		Real linegap; //< Distance between two lines.

	public:
		/**
		 * @return The baseline-to-baseline distance of the font.
		 */
		Real getLinespace() const;

	};

	/**
	 * The GlyphLayout class contains information about the positions of glyphs in a string.
	 */
	class GlyphLayout {
	public:
        /**
         * Creates a new glyph layout.
         * @param font The font to use.
         * @param string The string to calculate a layout from.
         * @param settings The render settings.
         */
		GlyphLayout(const Font& font, const WideString& string, const RenderSettings& settings);

    public:
        struct GlyphInfo {
            GlyphInfo(const Glyph& glyph);
            const Glyph& glyph;
            RealRect layout;
        };

        typedef std::vector<GlyphInfo>::const_iterator const_iterator;

	public:
        /**
         * @return The total width of the layout.
         */
		inline SizeT getWidth() const {
            return width;
        }

        /**
         * @return THe total height of the layout.
         */
		inline SizeT getHeight() const {
            return height;
        }

        /**
         * @return An iterator for the first glyph info of the layout.
         */
        inline const_iterator begin() const {
            return layout.begin();
        }

        /**
         * @return An iterator for the last glyph info of the layout.
         */
        inline const_iterator end() const {
            return layout.end();
        }

	private:
		void recalculate();

	private:
		WideString string;
		RenderSettings renderSettings;
		const Font& font;
        std::vector<GlyphInfo> layout;
        SizeT width, height;
	};


public:
	Font();

	/**
	 * Retrieves a glyph for a given codepoint.
	 * @param codepoint The codepoint to look up.
	 * @return The glyph corresponding to the codepoint.
	 */
	const Glyph& getGlyph(char_type codepoint) const;

protected:
    /**
     * Loads a glyph for a given codepoint.
     * @param codepoint The codepoint to load.
     * @return The loaded glyph corresponding to the codepoint.
     */
    virtual std::unique_ptr<Glyph> loadGlyph(char_type codepoint) const = 0;

public:
    /**
     * Creates a layout for a given string.
     * @param string The string to calculate the layout for.
     * @param renderSettings The render settings.
     * @return The calculated glyph layout.
     */
    GlyphLayout calculateLayout(const WideString& string, const RenderSettings& renderSettings);

    /**
     * Renders a glyph to a pixmap.
     * @param codepoint The codepoint representing the glyph.
     * @param target The target pixmap to draw onto.
     * @param offset The target offset to draw to.
     * @param renderSettings The render settings to use for this glyph.
     */
    virtual void renderGlyph(char_type codepoint, Pixmap& target, const Vec2& offset, const RenderSettings& renderSettings) = 0;

    /**
     * Renders a string to an existing pixmap.
     * @param string The string to render.
     * @param target The target to render to.
     * @param offset The target render offset.
     * @param renderSettings The render settings.
     */
	void render(
			const WideString& string,
			Pixmap& target,
			Vec2 offset,
			const RenderSettings& renderSettings
	);

    /**
     * Renders a glyph layout to an existing pixmap.
     * @param layout The layout to render.
     * @param target The target to render to.
     * @param offset The target render offset.
     * @param renderSettings The render settings.
     */
    void render(
            const GlyphLayout& layout,
            Pixmap& target,
            Vec2 offset,
            const RenderSettings& renderSettings
    );

    /**
     * Renders a given string into a new pixmap.
     * @param string The string to render.
     * @param renderSettings The render settings.
     * @return The rendered pixmap.
     */
	std::shared_ptr<Pixmap> render(const WideString& string, const RenderSettings& renderSettings);

    /**
     * Renders a given layout into a new pixmap.
     * @param layout The layout to render.
     * @param renderSettings The render settings.
     * @return The rendered pixmap.
     */
	std::shared_ptr<Pixmap> render(const GlyphLayout& layout, const RenderSettings& renderSettings);

private:
    struct Cache {
        std::map<char_type, Glyph> glyphs; //< The glyph cache.
    };

    std::unique_ptr<Cache> cache;
};

} /* namespace brew */

#endif /* BREW_FONT_H */
