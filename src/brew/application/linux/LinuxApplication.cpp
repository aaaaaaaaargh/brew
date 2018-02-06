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

#include <brew/application/linux/LinuxApplication.h>

namespace brew {

void LinuxApplication::start() {
    auto& cfg = getConfig();

    context = std::make_unique<GLContext>();
    canvas = std::make_unique<GLXCanvas>(*context);

    canvas->init(cfg.windowWidth, cfg.windowHeight);

    listener->onStart();

    while(canvas->isInitialized()) {
        canvas->pumpMessages();

        // TODO ...

        canvas->renderFrame();
    }

    listener->onQuit();
}

} /* namespace brew */
