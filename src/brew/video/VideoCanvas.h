/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 random arts
 *
 *  Created on: Aug 20, 2016
 *
 */

#ifndef BREW_VIDEOCANVAS_H
#define BREW_VIDEOCANVAS_H

#include <brew/core/Object.h>
#include <brew/video/VideoContext.h>
#include <brew/video/RenderTarget.h>

namespace brew {

/**
 * The base class for video canvas objects.
 */
class VideoCanvas : public RenderTarget, public Object {
public:
    /**
     * Constructor
     * @param context the context to use for this canvas. This instance MUST be compatible to the current canvas.
     */
    explicit VideoCanvas(VideoContext& context);

public:
    /**
     * @return the physical canvas width
     */
    SizeT getWidth() const override {
        return width;
    }

    /**
     * @return the physical canvas height
     */
    SizeT getHeight() const override {
        return height;
    }

public:
    /**
     * Initializes the canvas.
     * @param width the physical width
     * @param height the physical height
     */
    void init(const SizeT& width, const SizeT& height);

    /**
     * Drops (destroys) the canvas.
     */
    void drop();

    /**
     * Message pump callback. Should be called once inside the render loop.
     * The actual purpose of this method is OS specific.
     */
    void pumpMessages();

    /**
     * @return true if this canvas was initialized
     */
    bool isInitialized() const {
        return inited;
    }

public:
    /**
     * Renders a frame.
     */
    void renderFrame() final;

protected:
    /**
     * Called when the canvas is initialized.
     */
    virtual void onInit() = 0;

    /**
     * Called when the canvas is about to be destroyed.
     */
    virtual void onDrop() = 0;

    /**
     * Callback for processing messages from the underlying window system.
     */
    virtual void onPumpMessages() = 0;

    /**
     * Called when a frame is about to be rendered.
     */
    virtual void onBeginFrame() = 0;

    /**
     * Called when a frame finished rendering.
     */
    virtual void onEndFrame() = 0;

protected:
    SizeT width, height;
    bool inited;
};

} /* namespace brew */

#endif //BREW_VIDEOCANVAS_H
