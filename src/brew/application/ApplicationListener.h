/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 Marcus v. Keil
 *
 *  Created on: 31.01.18
 *
 */

#ifndef BREW_APPLICATIONLISTENER_H
#define BREW_APPLICATIONLISTENER_H

#include <brew/core/Object.h>

namespace brew {

/**
 * The listener class for the application.
 */
class ApplicationListener : public Object {
public:
    /**
     * Called when the app is about to start.
     */
    virtual void onStart() {};

    /**
     * Called when the app is being paused.
     */
    virtual void onPause() {};

    /**
     * Called when the app is being resumed.
     */
    virtual void onResume() {};

    /**
     * Called when the app is about to close.
     */
    virtual void onQuit() {};
};

} /* namespace brew */

#endif //BREW_APPLICATIONLISTENER_H
