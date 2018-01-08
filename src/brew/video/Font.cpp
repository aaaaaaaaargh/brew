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

Font::Font(const Settings& settings)
: cache( std::make_unique<Font::Cache>() ), settings(settings)
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

    for(const auto& run : layout) {
        for(const auto& glyph : run) {
            origin.set(
                    offset.x + glyph.layout.getLeft() + run.getOffset().x,
                    offset.y + glyph.layout.getTop() + run.getOffset().y
            );

            renderGlyph(glyph.glyph.codePoint, target, origin, renderSettings);
        }
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
    return ascent + descent + linegap;
}

Font::GlyphRun::GlyphRun(const Font& font, const WideString& string, const Font::RenderSettings& renderSettings)
: font(font), string(string), renderSettings(renderSettings){
    recalculate();
}

void Font::GlyphRun::recalculate() {
    Vec2 origin;

    // Reset the calculated variables.
    width = height = 0;
    baselineOffset = 0;
    layoutOffset.set(0,0);

    glyphs.clear();

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
            baselineOffset = std::max(glyph.ascent, baselineOffset);

            glyphs.push_back(info);
        }
        catch(const NotFoundException&) {
            // Glyph does not exist, skip.
        }
    }

    // Align the bounding boxes on the baseline
    for(GlyphInfo& info : glyphs) {
        info.layout.setY(
                baselineOffset - info.glyph.ascent
        );

        // Update the image extents.
        width = std::max(width, info.layout.getRight());
        height = std::max(height, info.layout.getBottom());
    }
}

Font::GlyphInfo::GlyphInfo(const Font::Glyph& glyph)
: glyph(glyph) {}

void Font::GlyphLayout::recalculate() {
    // Reset the runs.
    runs.clear();

    std::vector<WideString> lines;

    if(renderSettings.multiline) {
        lines = string::tokenize(string, L"\n", false, false);
    } else {
        lines.push_back(string);
    }

    width = height = 0;

    Real yOffset = renderSettings.outerSpacing;
    Real maxLineWidth = 0;

    for(auto& line : lines) {
        runs.emplace_back(GlyphRun(font, line, renderSettings));
        auto& run = runs.back();

        // Adjust to the font line height.
        yOffset += font.settings.ascent - run.getBaselineOffset();

        run.layoutOffset.set(
                renderSettings.outerSpacing,
                yOffset
        );

        width = std::max(width, run.getWidth() + renderSettings.outerSpacing);

        yOffset = font.settings.getLinespace() * runs.size();

        height = yOffset - run.getBaselineOffset();

        maxLineWidth = std::max(run.getWidth(), maxLineWidth);
    }

    // Set the horizontal line alignment.


    for(auto& run : runs) {
        if(renderSettings.align == TextAlign::Center) {
            run.layoutOffset.x += (maxLineWidth - run.getWidth()) / 2;
        } else if(renderSettings.align == TextAlign::Right) {
            run.layoutOffset.x += maxLineWidth - run.getWidth();
        }
    }

    width += renderSettings.outerSpacing;
    height += renderSettings.outerSpacing;
}

Font::GlyphLayout::GlyphLayout(const Font& font, const WideString& string, const Font::RenderSettings& settings)
        : font(font), string(string), renderSettings(settings)
{
    recalculate();
}

} /* namespace brew */
