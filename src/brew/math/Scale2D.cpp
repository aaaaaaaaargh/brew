/**
 *  Copyright 2015-2018 random arts
 *  Created on: 24.01.18
 */

#include "Scale2D.h"

brew::Vec2 brew::Scale2D::apply(brew::Scale2D::Type type, const brew::Vec2& source, const brew::Vec2& target) {
    Vec2 result;

    switch(type) {
        case Type::Fit: {
            Real targetRatio = target.y / target.x;
            Real sourceRatio = source.y / source.x;
            Real scale = targetRatio > sourceRatio
                    ? target.x / source.x
                    : target.y / source.y;

            result.set(
                    source.x * scale,
                    source.y * scale
            );

            break;
        }

        case Type::Fill: {
            Real targetRatio = target.y / target.x;
            Real sourceRatio = source.y / source.x;
            Real scale = targetRatio < sourceRatio
                         ? target.x / source.x
                         : target.y / source.y;

            result.set(
                    source.x * scale,
                    source.y * scale
            );

            break;
        }

        case Type::FillX: {
            Real scale = target.x / source.x;

            result.set(
                    source.x * scale,
                    source.y * scale
            );

            break;
        }

        case Type::FillY: {
            Real scale = target.y / source.y;

            result.set(
                    source.x * scale,
                    source.y * scale
            );

            break;
        }

        case Type::Stretch:
            result = target;
            break;

        case Type::StretchX:
            result.set(
                    target.x,
                    source.y
            );
            break;

        case Type::StretchY:
            result.set(
                    source.x,
                    target.y
            );
            break;

        case Type::None:
            result = source;
            break;
    }

    return result;
}
