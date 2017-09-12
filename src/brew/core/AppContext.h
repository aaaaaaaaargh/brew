/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2017 random arts
 *
 *  Created on: 07.09.17
 *
 */

#ifndef BREW_APPCONTEXT_H
#define BREW_APPCONTEXT_H

#include <brew/core/Log.h>

#include <memory>

namespace brew {

/**
 * The app context holds global data for the execution context of the app. It can be shared by
 * any class that is deriving from the Object class.
 */
class AppContext {
public:
    AppContext();

    std::unique_ptr<AbstractLog> log;
};

} /* namespace brew */


#endif //BREW_APPCONTEXT_H
