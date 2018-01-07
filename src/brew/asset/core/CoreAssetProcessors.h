/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: 07.01.18
 *
 */

#ifndef BREW_COREPROCESSORS_H
#define BREW_COREPROCESSORS_H

#include <brew/asset/AssetManager.h>
#include <brew/video/VideoContext.h>

namespace brew {

/**
 * A global registry for core processors.
 */
class CoreAssetProcessors {
public:
    CoreAssetProcessors() = delete;

public:
    /**
     * Registers all available core processors to the given asset manager.
     * @param assetManager The asset manager.
     * @param videoContext The default video context to use.
     */
    static void registerTo(AssetManager& assetManager, VideoContext& videoContext);
};

} /* namespace brew */

#endif //BREW_COREPROCESSORS_H
