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

#ifndef BREW_ASSETPROCESSOR_H
#define BREW_ASSETPROCESSOR_H

#include <brew/fileio/VirtualFileSystem.h>
#include <brew/asset/AssetBundle.h>

namespace brew {

class AssetProcessorParams;
class AssetPipeline;

namespace detail {
class AbstractAssetProcessor {
    friend class brew::AssetPipeline;

protected:
    virtual void invoke(AssetPipeline& pipeline,
                        const VirtualFileSystem& vfs, AssetBundle& bundle,
                        const String& tag,
                        const AssetProcessorParams& params) = 0;

    virtual bool check(const AssetPipeline& pipeline,
                       const VirtualFileSystem& vfs,
                       const AssetBundle& bundle,
                       const String& tag,
                       const AssetProcessorParams& params) = 0;
};
} /* namespace detail */

class AssetProcessorParams {
};

/**
 * The base class for all asset processors.
 * Any asset processor must implement both the load() and canLoad() method.
 * @tparam ParamsT The asset processing parameters.
 */
template<typename ParamsT>
class AssetProcessor : public detail::AbstractAssetProcessor {
protected:
    inline void invoke(AssetPipeline& pipeline, const VirtualFileSystem& vfs, AssetBundle& bundle, const String& tag, const AssetProcessorParams& params) final {
        load(pipeline, vfs, bundle, tag, static_cast<const ParamsT&>(params));
    }

    inline bool check(const AssetPipeline& pipeline, const VirtualFileSystem& vfs, const AssetBundle& bundle, const String& tag, const AssetProcessorParams& params) final {
        return canLoad(pipeline, vfs, bundle, tag, static_cast<const ParamsT&>(params));
    }

public:
    /**
     * Loads a given asset.
     * @param assetPipeline The pipeline the asset is loaded in.
     * @param vfs The file system to read from.
     * @param bundle The bundle to store the results in.
     * @param tag The tag or filename of the asset to load.
     * @param params The processing parameters.
     */
    virtual void load(AssetPipeline& assetPipeline,
                      const VirtualFileSystem& vfs,
                      AssetBundle& bundle,
                      const String& tag,
                      const ParamsT& params) = 0;

    /**
     * Checks whether this processor can load the given asset.
     * @param assetPipeline The pipeline the asset is loaded in.
     * @param vfs The file system to read from.
     * @param bundle The bundle to store the results in.
     * @param tag The tag or filename of the asset to load.
     * @param params The processing parameters.
     */
    virtual bool canLoad(const AssetPipeline& assetPipeline,
                         const VirtualFileSystem& vfs,
                         const AssetBundle& bundle,
                         const String& tag,
                         const ParamsT& params) = 0;
};

} /* namespace brew */

#endif //BREW_ASSETPROCESSOR_H
