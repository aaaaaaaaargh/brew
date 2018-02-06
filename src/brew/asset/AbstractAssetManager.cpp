/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 Marcus v. Keil
 *
 *  Created on: 07.01.18
 *
 */

#include <brew/asset/AbstractAssetManager.h>

namespace brew {

namespace detail {

AbstractAssetManager::AbstractAssetManager(std::shared_ptr<brew::VirtualFileSystem> vfs) :
        vfs(vfs), defaultBundle(std::make_unique<AssetBundle>()) {
}

} /* namespace detail */

} /* namespace brew */
