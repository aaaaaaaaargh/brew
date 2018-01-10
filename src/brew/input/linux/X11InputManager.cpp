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

#include <brew/input/KeySym.h>
#include <brew/input/linux/X11InputManager.h>
#include <X11/XKBlib.h>

namespace brew {

KeySym convertX11KeySym(::KeySym sym) {

    if (sym >= 65 && sym <= 90) { // A-Z
        return static_cast<KeySym>(static_cast<SizeT>(KeySym::A) + (sym - 97));
    }

    if (sym >= 97 && sym <= 122) { // a-z
        return static_cast<KeySym>(static_cast<SizeT>(KeySym::a) + (sym - 97));
    }

    if (sym >= 48 && sym <= 57) { // 0-9
        return static_cast<KeySym>(static_cast<SizeT>(KeySym::Digit0) + (sym - 48));
    }

    // TODO: Add proper keysyms here.

    switch(sym) {
        case 0x020: return KeySym::Space;
        case 0xFF0D: return KeySym::Return;
        case 0xFF1B: return KeySym::Escape;
        default: return KeySym::Undefined;
    }
}

X11InputManager::X11InputManager() {
    // Add keyboard and mouse devices
    auto keyboard = std::make_unique<InputDevice>(static_cast<u16>(KeySym::Undefined), 0);
    auto mouse = std::make_unique<InputDevice>(5, 2);

    registerDevice(std::move(keyboard));

    /**
     * Create keyboard mappings in signals 0-255.
     */
    for(u8 i=0; i< 255;++i) {
        addButtonMapping(i, getKeyboard(), i);
    }

    registerDevice(std::move(mouse));

    /**
     * Create mouse mappings (axes 0,1, buttons 256-258)
     */
    addMultiAxisMapping(0, 1, getMouse(), 0, 1);

    addButtonMapping(0, getMouse(), 256);
    addButtonMapping(1, getMouse(), 257);
    addButtonMapping(2, getMouse(), 258);

}

void X11InputManager::onXEvent(const XEvent &evt) {

    switch (evt.type) {
        case ButtonPress: {
            auto state = static_cast<u16>(evt.xbutton.button);
            try {
            devices[1]->setDigital(state, true);
            } catch(const NotFoundException&) {}
            break;
        }

        case ButtonRelease: {
            auto state = static_cast<u16>(evt.xbutton.button);
            try {
                devices[1]->setDigital(state, false);
            } catch(const NotFoundException&) {}
            break;
        }

        case MotionNotify: {
            try {
                devices[1]->setAnalog2D(0, 1, evt.xmotion.x, evt.xmotion.y);
            } catch(const NotFoundException&) {}
            break;
        }

        case KeyPress: {
            auto key = convertX11KeySym(XkbKeycodeToKeysym(
                    evt.xkey.display,
                    static_cast<KeyCode>(evt.xkey.keycode),
                    0,
                    (evt.xkey.state & ShiftMask) ? 1 : 0
            ));
            try {
                devices[0]->setDigital(static_cast<u16>(key), true);
            } catch(const NotFoundException&) {}
            break;
        }

        case KeyRelease: {
            if (XEventsQueued(evt.xkey.display, QueuedAfterReading)) {
                XEvent nev{};
                XPeekEvent(evt.xkey.display, &nev);
                if (nev.type == KeyPress && nev.xkey.time == evt.xkey.time && nev.xkey.keycode == evt.xkey.keycode) {
                    // Skip auto-repeats
                    break;
                }
            }

            auto key = convertX11KeySym(XkbKeycodeToKeysym(
                    evt.xkey.display,
                    static_cast<KeyCode>(evt.xkey.keycode),
                    0,
                    (evt.xkey.state & ShiftMask) ? 1 : 0
            ));

            try {
                devices[0]->setDigital(static_cast<u16>(key), false);
            } catch(const NotFoundException&) {}
            break;
        }
        default:
            break;
    }
}

} /* namespace brew */
