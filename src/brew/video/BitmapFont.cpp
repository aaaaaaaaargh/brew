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

#include <brew/video/BitmapFont.h>

namespace brew {

BitmapFont::BitmapFont(const Definition& definition)
: Font(definition.settings) {
    // Create the pixmap atlas.
    for (const auto& glyph : definition.glyphs) {
        const IntRect& source = glyph.second.bounds;
        const Pixmap& sourcePixmap = glyph.second.source;

        WideString codepointUTF;
        codepointUTF += glyph.first;
        String codepointAnsi = string::toString(codepointUTF);
        atlas.add(codepointAnsi, sourcePixmap, source);
    }

    const Pixmap& pixmap = atlas.generate(true);

    // Propagate the glyph lookup.
    for (const auto& glyph : definition.glyphs) {
        generatedGlyphs[glyph.first] = glyph.second.glyph;
    }
}

std::unique_ptr<Font::Glyph> BitmapFont::loadGlyph(Font::char_type codepoint) const {
    auto it = generatedGlyphs.find(codepoint);
    if(it == generatedGlyphs.end()) {
        return std::unique_ptr<Glyph>();
    }
    return std::make_unique<Glyph>(it->second);
}

void BitmapFont::renderGlyph(Font::char_type codepoint, Pixmap &target, const Vec2& offset,
                             const Font::RenderSettings &renderSettings) {
    Glyph glyph = getGlyph(codepoint);
    WideString codepointUTF;
    codepointUTF += codepoint;
    String codepointAnsi = string::toString(codepointUTF);

    auto glyphPixmapRegion = atlas.find(codepointAnsi);

    const Pixmap& pixmap = atlas.getPixmap();

    pixmap.blit(
            target,
            static_cast<s32>(offset.x + renderSettings.outerSpacing), static_cast<s32>(offset.y + renderSettings.outerSpacing),
            glyphPixmapRegion.getLeft(), glyphPixmapRegion.getTop(),
            glyphPixmapRegion.getWidth(), glyphPixmapRegion.getHeight()
    );
}

BitmapFont::Definition & BitmapFont::Definition::addGlyph(
        Font::char_type codepoint,
        Glyph glyph,
        const Pixmap &source,
        const IntRect &bounds) {

    IntRect realBounds;
    if(bounds.isFinite()) {
        realBounds = bounds;
    }
    else {
        realBounds.set(
                0,0,
                static_cast<s32>(source.getWidth()),
                static_cast<s32>(source.getHeight())
        );
    }

    GlyphInfo info = {
            codepoint,
            glyph,
            source,
            realBounds
    };

    glyphs.insert(
            std::make_pair(
                    codepoint,
                    info
            )
    );

    // Update the settings
    settings.ascent = std::max(glyph.ascent, settings.ascent);
    settings.descent = std::max(glyph.descent, settings.descent);

    return *this;
}

} /* namespace brew */