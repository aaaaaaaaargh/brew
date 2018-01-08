/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: 08.01.18
 *
 */

#ifndef BREW_NATIVEVIEWPORT_H
#define BREW_NATIVEVIEWPORT_H

#include <brew/video/Viewport.h>

namespace brew {

/**
 * A viewport implementation that uses the native resolution of the canvas.
 */
class NativeViewport : public Viewport {
public:
    /**
     * Creates a new native viewport.
     * @param unitsPerPixel The units per pixel ratio.
     * @param camera The camera to use.
     */
    NativeViewport(Real unitsPerPixel = 1, std::shared_ptr<Camera> camera = std::shared_ptr<Camera>());

    /**
     * Updates the physical dimensions of the viewport.
     * @param physicalWidth The new physical width.
     * @param physicalHeight The new physical height.
     */
    void update(SizeT physicalWidth, SizeT physicalHeight) override;

    /**
     * Sets the units per pixel ratio.
     * @param unitsPerPixel The new ratio.
     */
    void setUnitsPerPixel(Real unitsPerPixel);

    /**
     * @return This viewports units per pixel ratio.
     */
    inline Real getUnitsPerPixel() const {
        return unitsPerPixel;
    }

private:
    Real unitsPerPixel;
};

} /* namespace brew */

#endif //BREW_NATIVEVIEWPORT_H
