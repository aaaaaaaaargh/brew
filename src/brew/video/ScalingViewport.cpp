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

#include <brew/video/ScalingViewport.h>
#include <brew/math/Math.h>

#include <utility>

namespace brew {


ScalingViewport::ScalingViewport(Scale2D::Type scaling, const Vec2& virtualSize, std::shared_ptr<Camera> camera)
: Viewport(virtualSize, std::move(camera)), scaling(scaling) {
}

ScalingViewport::ScalingViewport(Scale2D::Type scaling,
                                 Real virtualWidth, Real virtualHeight,
                                 std::shared_ptr<Camera> camera)
: Viewport(virtualWidth, virtualHeight, std::move(camera)), scaling(scaling){
}

void ScalingViewport::update(SizeT physicalWidth, SizeT physicalHeight) {
    Vec2 scaled = Scale2D::apply(scaling,
                                 getVirtualSize(),
                                 Vec2(physicalWidth, physicalHeight));

    auto viewportWidth = static_cast<SizeT>(std::round(scaled.x));
    auto viewportHeight = static_cast<SizeT>(std::round(scaled.y));

    setPhysicalBounds(
            (physicalWidth - viewportWidth) / 2,
            (physicalHeight - viewportHeight) / 2,
            viewportWidth, viewportHeight
    );
}

void ScalingViewport::setScaling(Scale2D::Type scaling) {
    this->scaling = scaling;
}

} /* namespace brew */
