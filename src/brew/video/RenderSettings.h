/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 Marcus v. Keil
 *
 *  Created on: 23.01.18
 *
 */

#ifndef BREW_RENDERSETTINGS_H
#define BREW_RENDERSETTINGS_H

namespace brew {

/**
 * A settings structure for rendering elements.
 */
struct RenderSettings {
    enum class BlendMode {
        None,
        SourceAlphaToOneMinusSourceAlpha,
    };

    BlendMode blendMode = BlendMode::SourceAlphaToOneMinusSourceAlpha;

    static const RenderSettings Defaults; //< The default render settings.
};

} /* namespace brew */

#endif // BREW_RENDERSETTINGS_H