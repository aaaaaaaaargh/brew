/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: Nov 15, 2016
 *
 */

#ifndef BREW_X11INPUTMANAGER_H
#define BREW_X11INPUTMANAGER_H

#include <brew/input/InputManager.h>
#include <brew/video/linux/X11Canvas.h>

namespace brew {

/**
 * An input manager implementation for the X11 environment.
 */
class X11InputManager : public InputManager, public X11Listener {
public:
    /**
     * Creates a new X11 input manager.
     */
	X11InputManager();

    /**
     * Processes an XEvent dispatched by the X server.
     * @param event
     */
    void onXEvent(const XEvent& event) override;

    /**
     * @return The keyboard device.
     */
    inline const InputDevice& getKeyboard() const {
        return getDevice(0);
    }

    /**
     * @return The mouse device.
     */
    inline const InputDevice& getMouse() const {
        return getDevice(1);
    }
};

} /* namespace brew */

#endif /* BREW_X11INPUTMANAGER_H */
