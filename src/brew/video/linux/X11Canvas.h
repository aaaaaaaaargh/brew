/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: Aug 21, 2016
 *
 */

#ifndef BREW_X11CANVAS_H
#define BREW_X11CANVAS_H

#include <brew/video/VideoCanvas.h>

#include <brew/core/EventSource.h>

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

namespace brew {

/**
 * A listener for X11 related events.
 */
class X11Listener {
public:
	/**
     * Processes an XEvent dispatched by the X server.
     * @param event
     */
	virtual void onXEvent(const XEvent& evt) = 0;
};

/**
 * Canvas implementation for X11 windows.
 */
class X11Canvas : public virtual VideoCanvas {
	BREW_EVENTSOURCE(X11Listener, XEvent);

public:
	/**
	 * Creates a new X11 canvas.
	 * @param context The video context to use with this canvas.
	 */
	X11Canvas(VideoContext& context);

public:
	/**
     * Called when the canvas is initialized.
     */
	void onInit() override;

	/**
     * Called when the canvas is about to be destroyed.
     */
	void onDrop() override;

	/**
     * Callback for processing messages from the underlying window system.
     */
	void onPumpMessages() override;

protected:
	/**
	 * @return The X visual for this canvas.
	 */
	virtual XVisualInfo* chooseVisual() = 0;

protected:
	Window parent;
	Display* display;
	Colormap cmap;
	XVisualInfo* visual;
	Window win;
	Atom wmDeleteMessage;
};

} /* namespace brew */

#endif /* BREW_X11CANVAS_H */
