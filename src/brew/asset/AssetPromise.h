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

#ifndef BREW_ASSETPROMISE_H
#define BREW_ASSETPROMISE_H

#include <memory>
#include <future>

namespace brew {

class AssetPipeline;

/**
 * A promise that is fulfilled once the requested asset is loaded or an error occurred during the loading process.
 */
class AssetPromise {
public:
    typedef bool result_type; //< The result type of the promise.

private:
    friend class AssetPipeline;

    AssetPromise(
            std::shared_ptr<AssetPipeline> && pipeline,
            std::shared_ptr<std::promise<result_type> > && promise
    );

public:
    /**
     * @return The result of the loading operation.
     */
    result_type getResult() const;

private:
    std::shared_ptr<std::promise<bool> > promise;
    std::shared_ptr<AssetPipeline> pipeline;
};

} /* namespace brew */

#endif //BREW_ASSETPROMISE_H
