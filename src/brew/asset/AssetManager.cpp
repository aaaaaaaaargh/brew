/**
 *  Copyright 2015-2018 random arts
 *  Created on: 02.01.18
 */

#include "AssetManager.h"

namespace brew {

AssetManager::AssetManager(std::shared_ptr<brew::VirtualFileSystem> vfs) {
    this->vfs = vfs;
}

void AssetPipeline::makeParams(std::vector<std::shared_ptr<AssetPipeline::ParamsInfo>>& paramsInfo) {
    // Recursion tail.
}

AssetManager& AssetPipeline::getManager() {
    return static_cast<AssetManager&>(manager);
}

bool AssetPromise::getResult() {
    return promise->get_future().get();
}

}