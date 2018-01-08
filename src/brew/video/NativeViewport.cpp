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

#include <brew/video/NativeViewport.h>

namespace brew {

NativeViewport::NativeViewport(Real unitsPerPixel, std::shared_ptr<Camera> camera) :
        Viewport(0,0, camera), unitsPerPixel(unitsPerPixel) {

}

void NativeViewport::update(SizeT physicalWidth, SizeT physicalHeight) {
    Viewport::update(physicalWidth, physicalHeight);
    setVirtualSize(physicalWidth * unitsPerPixel, physicalHeight * unitsPerPixel);
}

void NativeViewport::setUnitsPerPixel(Real unitsPerPixel) {
    this->unitsPerPixel = unitsPerPixel;
}

} /* namespace brew */