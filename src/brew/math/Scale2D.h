/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: 24.01.18
 *
 */

#ifndef BREW_SCALE2D_H
#define BREW_SCALE2D_H

#include <brew/math/Vec2.h>

namespace brew {

/**
 * A utility class for scaling 2D vectors.
 */
class Scale2D {
public:
    Scale2D() = delete;

    /**
     * The available scaling types.
     */
    enum class Type {
        Fit, //< Scale to fit the target while maintain the sources aspect ratio.
        Fill, //< Scale to fill the target while maintain the sources aspect ratio.
        FillX, //< Scale to fill the target width while maintain the sources aspect ratio.
        FillY, //< Scale to fill the target height while maintain the sources aspect ratio.
        Stretch, //< Stretch the source to fill the whole target.
        StretchX, //< Stretch the source to fill the target width.
        StretchY, //< Stretch the source to fill the target height.
        None //< Do not scale the source.
    };

public:
    /**
     * Applies a scaling on a source.
     * @param type The scaling type.
     * @param source The source to scale from.
     * @param target The target to scale to.
     * @return The scaled source vector.
     */
    static Vec2 apply(Scale2D::Type type, const Vec2& source, const Vec2& target);
};

} /* namespace brew */

#endif //BREW_SCALE2D_H
