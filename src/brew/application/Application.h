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

#ifndef BREW_APPLICATION_H
#define BREW_APPLICATION_H

namespace brew {

/**
 * The base Application class.
 * @tparam ConfigT The application config structure type.
 */
template<typename ConfigT>
class Application {
public:
    explicit Application(const ConfigT& config)
            : config(config) {
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
};

} /* namespace brew */

#endif //BREW_PLATFORM_H
