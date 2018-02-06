/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 Marcus v. Keil
 *
 *  Created on: 08.01.18
 *
 */

#ifndef BREW_EXTENDVIEWPORT_H
#define BREW_EXTENDVIEWPORT_H

#include <brew/video/Viewport.h>

namespace brew {

/**
 * A viewport implementation that extends as the canvas resizes.
 */
class ExtendViewport : public Viewport {
public:
    /**
     * Creates a new extending viewport.
     * @param minVirtualWidth The minimum virtual width.
     * @param minVirtualHeight The minimum virtual height.
     * @param maxVirtualWidth The maximum virtual width.
     * @param maxVirtualHeight The maximum virtual height.
     * @param camera The camera to use.
     */
    ExtendViewport(Real minVirtualWidth, Real minVirtualHeight, Real maxVirtualWidth=0, Real maxVirtualHeight=0, std::shared_ptr<Camera> camera = std::shared_ptr<Camera>());

    /**
     * Creates a new extending viewport.
     * @param minVirtualSize The minimum virtual size.
     * @param maxVirtualSize The maximum virtual size.
     * @param camera The camera to use.
     */
    explicit ExtendViewport(const Vec2& minSize, const Vec2& maxSize = Vec2::ZERO, std::shared_ptr<Camera> camera = std::shared_ptr<Camera>());

    /**
     * Updates the physical dimensions of the viewport.
     * @param physicalWidth The new physical width.
     * @param physicalHeight The new physical height.
     */
    void update(SizeT physicalWidth, SizeT physicalHeight) override;

    /**
     * @return The minimum virtual size.
     */
    inline const Vec2& getMinimumVirtualSize() const {
        return minVirtualSize;
    }

    /**
     * Sets the minimum virtual size.
     * @param minSize The minimum size.
     */
    void setMinimumVirtualSize(const Vec2& minSize);

    /**
     * @return The maximum virtual size.
     */
    inline const Vec2& getMaximumVirtualSize() const {
        return maxVirtualSize;
    }

    /**
     * Sets the maximum virtual size.
     * @param maxSize The maximum size.
     */
    void setMaximumVirtualSize(const Vec2& maxSize);

private:
    Vec2 minVirtualSize, maxVirtualSize;
};

} /* namespace brew */

#endif //BREW_EXTENDVIEWPORT_H
