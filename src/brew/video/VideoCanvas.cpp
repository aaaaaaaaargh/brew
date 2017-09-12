/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2017 random arts
 *
 *  Created on: 06.09.17
 *
 */

#include <brew/video/VideoCanvas.h>

namespace brew {


VideoCanvas::VideoCanvas(VideoContext& ctx) :
        width(0), height(0), inited(false), context(ctx) {

}

void VideoCanvas::init(const SizeT& width, const SizeT& height) {
    if(inited) {
        throw IllegalStateException("Canvas already initialized.");
    }

    inited = true;

    this->width = width;
    this->height = height;

    onInit();
}

void VideoCanvas::drop() {
    if(!inited) {
        throw IllegalStateException("Cannot drop canvas, not initialized.");
    }

    inited=false;

    onDrop();
}

void VideoCanvas::pumpMessages() {
    if(!inited) {
        return;
    }

    onPumpMessages();
}

void VideoCanvas::renderFrame() {
    if(!inited) {
        return;
    }

    onBeginFrame();

    context.processPendingOperations();

    {
        RenderEvent e(*this, RenderEvent::Type::BeginFrame);
        fireRenderEvent(e);
    }

    {
        RenderEvent e(*this, RenderEvent::Type::EndFrame);
        fireRenderEvent(e);
    }

    onEndFrame();
}

} /* namespace brew */