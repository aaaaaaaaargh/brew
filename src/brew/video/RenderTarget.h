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

#ifndef BREW_RENDERTARGET_H
#define BREW_RENDERTARGET_H

#include <brew/core/EventSource.h>
#include <brew/core/Rect.h>

namespace brew {

class RenderTarget;

/**
 * An class for render events.
 */
class RenderEvent {
public:
    enum class Type {
        BeginFrame, //< A frame is about to be rendered.
        EndFrame, //< A frame is about to be finished.
        Resize //< The render target is about to be resized.
    };

public:
	/**
	 * Creates a a new render event.
	 * @param renderTarget The render target that fires the event.
	 * @param type The event type.
	 */
	RenderEvent(RenderTarget& renderTarget, const Type& type);

	RenderTarget& renderTarget; //< The render target that fired the event.

	Type type; //< The event type.
	IntRect dimensions; //< The new dimensions for the resize event.
};

/**
 * An event listener class for render events.
 */
class RenderListener {

public:
	/**
	 * Invoked when a render event is fired.
	 * @param event The event.
	 */
	virtual void onRenderEvent(const RenderEvent& event);

	/**
	 * Invoked when a begin frame event is fired.
	 * @param event The event.
	 */
	virtual void onBeginFrame(const RenderEvent& event) {};

	/**
	 * Invoked when an end frame event is fired.
	 * @param event The event.
	 */
	virtual void onEndFrame(const RenderEvent& event) {};

	/**
	 * Invoked when a resize event is fired.
	 * @param event The event.
	 */
	virtual void onResize(const RenderEvent& event) {};
};

class RenderTarget {
	BREW_EVENTSOURCE(RenderListener, RenderEvent);

	virtual ~RenderTarget() = default;

public:
	/**
	 * A callback that can be used to render a frame without an attached render listener.
	 */
	typedef std::function<void(const RenderEvent&)> RenderFrameCallback;

	/**
	 * Renders a frame. Invokes all registered render listeners.
	 */
	virtual void renderFrame() = 0;

	/**
	 * @return The width of the render target in pixels.
	 */
	virtual SizeT getWidth() const = 0;

	/**
	 * @return The height of the render target in pixels.
	 */
	virtual SizeT getHeight() const = 0;

};

} /* namespace brew */

#endif /* BREW_RENDERTARGET_H */
