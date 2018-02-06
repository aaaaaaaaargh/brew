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

#ifndef BREW_ANDROIDAPPLICATION_H
#define BREW_ANDROIDAPPLICATION_H

#include <brew/application/Application.h>

namespace brew {

class AndroidApplicationConfig {

};

/**
 * Application implementation for android systems.
 */
class AndroidApplication : public Application<AndroidApplicationConfig> {
public:
    using Application::Application;
};

} /* namespace brew */

#endif //BREW_ANDROIDAPPLICATION_H
