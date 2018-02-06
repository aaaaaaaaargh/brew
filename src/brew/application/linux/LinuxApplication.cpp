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

#include <brew/application/linux/LinuxApplication.h>

namespace brew {

void LinuxApplication::start() {
    auto& cfg = getConfig();

    context = std::make_unique<GLContext>();
    canvas = std::make_unique<GLXCanvas>(*context);

    canvas->init(cfg.windowWidth, cfg.windowHeight);

    while(canvas->isInitialized()) {
        // TODO...
        canvas->renderFrame();
    }

    canvas->drop();
}

} /* namespace brew */
