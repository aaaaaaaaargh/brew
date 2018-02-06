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

#ifndef BREW_LINUXAPPLICATION_H
#define BREW_LINUXAPPLICATION_H

#include <brew/application/Application.h>
#include <brew/application/DesktopApplicationConfig.h>

#include <brew/core/Types.h>

#include <brew/video/gl/GLContext.h>
#include <brew/video/linux/GLXCanvas.h>

#include <memory>

namespace brew {

class LinuxApplicationConfig : public DesktopApplicationConfig {
public:
};

/**
 * Application implementation for linux desktop systems.
 */
class LinuxApplication : public Application<LinuxApplicationConfig> {
public:
    using Application::Application;

public:
    /**
     * Starts the application.
     */
    void start() override;

private:
    std::unique_ptr<GLContext> context;
    std::unique_ptr<GLXCanvas> canvas;
};

} /* namespace brew */

#endif //BREW_LINUXAPPLICATION_H
