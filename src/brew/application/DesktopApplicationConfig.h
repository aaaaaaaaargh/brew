/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: 31.01.18
 *
 */

#ifndef BREW_DESKTOPAPPLICATIONCONFIG_H
#define BREW_DESKTOPAPPLICATIONCONFIG_H

#include <brew/core/Types.h>

namespace brew {

/**
 * Basic configuration for desktop applications.
 */
class DesktopApplicationConfig {
public:
    SizeT windowWidth = 640;
    SizeT windowHeight = 480;
    bool fullscreen = false;
};

} /* namespace brew */

#endif //BREW_DESKTOPAPPLICATIONCONFIG_H
