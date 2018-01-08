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

#include <brew/video/Font.h>

#include <brew/core/Exception.h>
#include <iostream>

namespace brew {

Font::Font()
: cache( std::make_unique<Font::Cache>() )
{}

const Font::Glyph& Font::getGlyph(Font::char_type index) const {
    auto cached = cache->glyphs.find(index);

    if(cached != cache->glyphs.end()) {
        return cached->second;
    }

    // This is a new glyph, load it.
    std::unique_ptr<Glyph> newGlyph = loadGlyph(index);

    if(!newGlyph) {
        StringStream ss;
        ss << "Codepoint " << static_cast<u16>(index) << " missing in font.";
        throw NotFoundException(ss.str());
    }

    // Store it in the cache.
    cache->glyphs.insert(std::make_pair(
            index,
            *newGlyph.get()
    ));

    cached = cache->glyphs.find(index);
    return cached->second;
}

Font::GlyphLayout Font::calculateLayout(const WideString& string, const Font::RenderSettings& renderSettings) {
    GlyphLayout glyphLayout(*this, string, renderSettings);
    return glyphLayout;
}

void Font::render(const Font::GlyphLayout& layout, Pixmap& target, Vec2 offset, const Font::RenderSettings& renderSettings) {
    Vec2 origin;

    for(const auto& glyph : layout) {
        origin.set(
                offset.x + glyph.layout.getLeft(),
                offset.y + glyph.layout.getTop()
        );

        renderGlyph(glyph.glyph.codePoint, target, origin, renderSettings);
    }
}

void Font::render(const WideString& string, Pixmap& target, Vec2 offset, const Font::RenderSettings& renderSettings) {
    GlyphLayout layout = calculateLayout(string, renderSettings);
    render(layout, target, offset, renderSettings);
}

std::shared_ptr<Pixmap> Font::render(const WideString& string, const Font::RenderSettings& renderSettings) {
    GlyphLayout layout = calculateLayout(string, renderSettings);
    return render(layout, renderSettings);
}

std::shared_ptr<Pixmap> Font::render(const Font::GlyphLayout& layout, const Font::RenderSettings& renderSettings) {
    auto result = std::make_shared<Pixmap>(layout.getWidth(), layout.getHeight());
    render(layout, *result, Vec2::ZERO, renderSettings);
    return result;
}

Real Font::Settings::getLinespace() const {
    return ascent - descent + linegap;
}

Font::GlyphLayout::GlyphLayout(const Font& font, const WideString& string, const Font::RenderSettings& renderSettings)
: font(font), string(string), renderSettings(renderSettings){
    recalculate();
}

void Font::GlyphLayout::recalculate() {
    Vec2 origin;
    Real baseline = 0;

    // Reset the calculated variables.
    width = height = 0;
    layout.clear();

    origin.set(renderSettings.outerSpacing, renderSettings.outerSpacing);

    // Calculate the bounding boxes.
    for(char_type ch : string) {
        try {
            const Glyph& glyph = font.getGlyph(ch);

            GlyphInfo info(glyph);

            info.layout.set(
                    origin.x,
                    origin.y,
                    glyph.advance,
                    glyph.ascent + glyph.descent
            );

            // Update the pen position.
            origin.x += glyph.advance;

            // Update the baseline.
            baseline = std::max(glyph.ascent, baseline);

            layout.push_back(info);
        }
        catch(const NotFoundException&) {
            // Glyph does not exist, skip.
        }
    }

    // Align the bounding boxes on the baseline
    for(GlyphInfo& info : layout) {
        info.layout.setY(
                baseline - info.glyph.ascent
        );

        // Update the image extents.
        width = std::max(width, static_cast<SizeT>(info.layout.getRight()));
        height = std::max(height, static_cast<SizeT>(info.layout.getBottom()));
    }

    width += renderSettings.outerSpacing;
    height += renderSettings.outerSpacing;
}

Font::GlyphLayout::GlyphInfo::GlyphInfo(const Font::Glyph& glyph)
: glyph(glyph) {}

} /* namespace brew */
