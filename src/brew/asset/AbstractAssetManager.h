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

#ifndef BREW_ABSTRACTASSETMANAGER_H
#define BREW_ABSTRACTASSETMANAGER_H

#include <brew/fileio/VirtualFileSystem.h>
#include <brew/asset/AssetBundle.h>
#include <brew/asset/AssetProcessor.h>

#include <functional>

namespace brew {

class AssetPipeline;
class AssetManager;

namespace detail {

class AbstractAssetManager {
protected:
    friend class brew::AssetPipeline;
    friend class brew::AssetManager;

public:
    explicit AbstractAssetManager(std::shared_ptr<VirtualFileSystem> vfs);

public:
    inline AssetBundle& getDefaultBundle() const {
        return *defaultBundle;
    }

private:
    struct ParamsInfo {
        SizeT typeHash;
        std::shared_ptr<AssetProcessorParams> params;
    };

    struct ProcessorInvocationOptions {
        std::shared_ptr<ParamsInfo>& thisParamsInfo;
        std::vector<std::unique_ptr<ParamsInfo> >& paramsInfo;
    };

    struct ProcessorEntry {
        std::unique_ptr<AbstractAssetProcessor> processor;
        SizeT paramsTypeHash;
        std::shared_ptr<AssetProcessorParams> params;
        std::function<void(const ProcessorInvocationOptions&)> invoke;
    };

    std::shared_ptr<VirtualFileSystem> vfs;
    std::map<SizeT, ProcessorEntry> processors;
    std::unique_ptr<AssetBundle> defaultBundle;
};

} /* namespace detail */

} /* namespace brew */


#endif //BREW_ABSTRACTASSETMANAGER_H
