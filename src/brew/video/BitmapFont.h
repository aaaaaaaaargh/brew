/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: May 27, 2017
 *
 */

#ifndef BREW_BITMAPFONT_H
#define BREW_BITMAPFONT_H

#include <brew/video/Font.h>
#include <brew/video/PixmapAtlas.h>
#include <brew/video/VideoContext.h>

#include <brew/core/Rect.h>

#include <memory>

namespace brew {

/**
 * Implementation for bitmap fonts. The result of a rendered string will be a new pixmap.
 */
class BitmapFont : public Font {
public:
    /**
     * The bitmap font definition class.
     */
    class Definition {
    public:
        /**
         * Adds a new glyph to the bitmap font definition.
         * @param codepoint The codepoint representing the glyph.
         * @param glyph The glyph information.
         * @param source The source pixmap.
         * @param bounds The source pixmap boundaries or IntRect::INF for the whole pixmap.
         * @return This instance for chaining.
         */
        Definition& addGlyph(char_type codepoint, Glyph glyph, const Pixmap& source, const IntRect& bounds = IntRect::INF);

    private:
        friend class BitmapFont;

        struct GlyphInfo {
            char_type codepoint;
            Glyph glyph;
            const Pixmap& source;
            IntRect bounds;
        };

        std::map<char_type, GlyphInfo> glyphs;
    };

public:
    /**
     * Constructs a new bitmap font from a given definition.
     * @param context The video context to create the bitmap font data in.
     * @param definition The bitmap font definition.
     */
    explicit BitmapFont(const Definition& definition);

protected:
    /**
     * Loads a glyph for a given codepoint.
     * @param codepoint The codepoint to load.
     * @return The loaded glyph corresponding to the codepoint.
     */
    std::unique_ptr<Glyph> loadGlyph(char_type codepoint) const override;

public:
    /**
     * Renders a glyph to a pixmap.
     * @param codepoint The codepoint representing the glyph.
     * @param target The target pixmap to draw onto.
     * @param offset The target offset to draw to.
     * @param renderSettings The render settings to use for this glyph.
     */
    void renderGlyph(char_type codepoint, Pixmap &target, const Vec2& offset, const RenderSettings &renderSettings) override;

    /**
     * @return The generated pixmap.
     */
    inline const Pixmap& getPixmap() const {
        return atlas.getPixmap();
    }

private:
    PixmapAtlas atlas;
    std::map<char_type, Glyph> generatedGlyphs;
};

} /* namespace brew */

#endif //BREW_BITMAPFONT_H
