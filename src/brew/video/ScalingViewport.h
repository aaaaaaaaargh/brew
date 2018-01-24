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

#ifndef BREW_SCALINGVIEWPORT_H
#define BREW_SCALINGVIEWPORT_H

#include <brew/video/Viewport.h>
#include <brew/math/Scale2D.h>

namespace brew {

/**
 * A viewport implementation that applies a user defined scaling.
 */
class ScalingViewport : public Viewport {
public:
    /**
     * Creates a new scaling viewport.
     * @param scaling The scaling type to apply.
     * @param virtualSize The virtual viewport size.
     * @param camera The camera to use for this viewport.
     */
    ScalingViewport(Scale2D::Type scaling, const Vec2& virtualSize, std::shared_ptr<Camera> camera = std::shared_ptr<Camera>());

    /**
     * Creates a new scaling viewport.
     * @param scaling The scaling type to apply.
     * @param virtualWidth the virtual viewport width.
     * @param virtualHeight the virtual viewport height.
     * @param camera The camera to use for this viewport.
     */
    ScalingViewport(Scale2D::Type scaling, Real virtualWidth, Real virtualHeight, std::shared_ptr<Camera> camera = std::shared_ptr<Camera>());

public:
    /**
     * Updates the physical dimensions of the viewport.
     * @param physicalWidth The new physical width.
     * @param physicalHeight The new physical height.
     */
    void update(SizeT physicalWidth, SizeT physicalHeight) override;

public:
    /**
     * Sets the scaling type for this viewport.
     * @param scaling The scaling type.
     */
    void setScaling(Scale2D::Type scaling);

    /**
     * @return The scaling of this viewport.
     */
    inline Scale2D::Type getScaling() const {
        return scaling;
    }

private:
    Scale2D::Type scaling;
};

} /* namespace brew */

#endif //BOXQUEST_SCALINGVIEWPORT_H
