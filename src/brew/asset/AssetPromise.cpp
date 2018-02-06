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

#include <brew/asset/AssetPromise.h>

namespace brew {

AssetPromise::AssetPromise(std::shared_ptr<AssetPipeline>&& pipeline, std::shared_ptr<std::promise<bool> >&& promise)
        : pipeline(pipeline), promise(promise) {

}

AssetPromise::result_type AssetPromise::getResult() const {
    return promise->get_future().get();
}

} /* namespace brew */
