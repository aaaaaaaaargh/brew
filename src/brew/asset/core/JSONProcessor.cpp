/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 Marcus v. Keil
 *
 *  Created on: 28.09.16
 *
 */

#include <brew/asset/core/JSONProcessor.h>

namespace brew {

void brew::JSONProcessor::load(AssetPipeline& assetPipeline, const VirtualFileSystem& vfs, AssetBundle& bundle,
                               const String& tag, const JSONProcessorParams& params) const {
    auto file = vfs.getFile(tag);
    auto fs = file->open(std::ios::in);

    String line;
    String jsonStr;

    // Create one big string from the input.
    while (std::getline(*fs.get(), line)) {
        jsonStr.append(line);
    }

    getAppContext().log->stream("JSONProcessor") << LogLevel::Debug << "Loading '" << tag << "' ...";
    std::shared_ptr<json> result;

    // Parse the string.
    result = std::make_shared<json>(json::parse(jsonStr));

    bundle.put(tag, result);
}

bool JSONProcessor::canLoad(const AssetPipeline& assetPipeline, const VirtualFileSystem& vfs, const AssetBundle& bundle,
                            const String& tag, const JSONProcessorParams& params) const {
    return true;
}

bool JSONProcessor::acceptsType(const String& typeHint) const {
    return typeHint == "json";
}

} /* namespace brew */