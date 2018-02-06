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

#ifndef BREW_APPLICATION_H
#define BREW_APPLICATION_H

#include <brew/core/Object.h>
#include <brew/application/ApplicationListener.h>

namespace brew {

/**
 * The base Application class.
 * @tparam ConfigT The application config structure type.
 */
template<typename ConfigT>
class Application : public Object {
public:
    explicit Application(std::unique_ptr<ApplicationListener> && listener, const ConfigT& config)
            : config(config), listener(std::move(listener)) {
    }

public:
    /**
     * Starts the application life cycle.
     */
    virtual void start() = 0;

public:
    /**
     * @return The application configuration.
     */
    inline const ConfigT& getConfig() const {
        return config;
    }

private:
    ConfigT config;

protected:
    std::unique_ptr<ApplicationListener> listener;
};

} /* namespace brew */

#endif //BREW_PLATFORM_H
