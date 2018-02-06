/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 Marcus v. Keil
 *
 *  Created on: Sep 7, 2016
 *
 */

#include <brew/video/RenderTarget.h>
#include "VideoContext.h"

namespace brew {

RenderEvent::RenderEvent(RenderTarget& rt, const Type& t) :
		renderTarget(rt), type(t) {

}

void RenderListener::onRenderEvent(const RenderEvent& evt) {
	switch(evt.type) {
	case RenderEvent::Type::BeginFrame:
		onBeginFrame(evt);
		break;
	case RenderEvent::Type::EndFrame:
		onEndFrame(evt);
		break;
	case RenderEvent::Type::Resize:
		onResize(evt);
		break;
	}
}

RenderTarget::RenderTarget(VideoContext& context)
: context(context) {

}

} /* namespace brew */
