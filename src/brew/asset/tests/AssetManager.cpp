/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: 02.01.18
 *
 */

#include <gtest/gtest.h>

#include <brew/asset/AssetManager.h>
#include <brew/fileio/HeapFileSystem.h>

using namespace brew;

class AType {};
class BType {};
class CType {};
class DType {};

class ATypeProcessorParams : public AssetProcessorParams {};

class ATypeProcessor : public AssetProcessor<ATypeProcessorParams> {
public:
    bool canLoad(const AssetPipeline& pipeline, const VirtualFileSystem& vfs, const AssetBundle& bundle, const String& tag, const ATypeProcessorParams& params) const override {
        return tag.find("aFile") != String::npos;
    };

    void load(AssetPipeline& pipeline, const VirtualFileSystem& vfs, AssetBundle& bundle, const String& tag, const ATypeProcessorParams& params) const override {
        bundle.put(tag, std::make_shared<AType>());
    };
};

class BTypeProcessorParams : public AssetProcessorParams {};

class BTypeProcessor : public AssetProcessor<BTypeProcessorParams> {
public:
    bool canLoad(const AssetPipeline& pipeline, const VirtualFileSystem& vfs, const AssetBundle& bundle, const String& tag, const BTypeProcessorParams& params) const override {
        return tag.find("bFile") != String::npos;
    };

    void load(AssetPipeline& pipeline, const VirtualFileSystem& vfs, AssetBundle& bundle, const String& tag, const BTypeProcessorParams& params) const override {
        pipeline.load("aFile", "");

        bundle.put(tag, std::make_shared<BType>());
    };
};

TEST(Asset, LoadSimpleAsset) {
    auto vfs = std::make_shared<VirtualFileSystem>();

    auto heapDir = std::make_unique<HeapDirectory>();

    heapDir->addFile("aFile", "A file.");

    vfs->mount("/dynamic", std::move(heapDir));

    AssetManager am(vfs);

    ATypeProcessorParams aTypeProcessorParams;
    am.registerProcessor<ATypeProcessor>(aTypeProcessorParams);

    auto result = am.load("/dynamic/aFile", "");

    //auto result = am.load<AType>("/dynamic/aFile", "", aTypeProcessorParams);

    EXPECT_TRUE(result.getResult());
}

TEST(Asset, LoadAssetWithoutLoader) {
    auto vfs = std::make_shared<VirtualFileSystem>();

    auto heapDir = std::make_unique<HeapDirectory>();

    heapDir->addFile("aFile", "A file.");

    vfs->mount("/dynamic", std::move(heapDir));

    AssetManager am(vfs);

    auto result = am.load("/dynamic/aFile", "");

    EXPECT_FALSE(result.getResult());
}

TEST(Asset, LoadRecursive) {
    auto vfs = std::make_shared<VirtualFileSystem>();

    auto heapDir = std::make_unique<HeapDirectory>();

    heapDir->addFile("aFile", "A file.");
    heapDir->addFile("bFile", "B file.");

    vfs->mount("/dynamic", std::move(heapDir));

    AssetManager am(vfs);

    ATypeProcessorParams aTypeProcessorParams;
    am.registerProcessor<ATypeProcessor>(aTypeProcessorParams);

    BTypeProcessorParams bTypeProcessorParams;
    am.registerProcessor<BTypeProcessor>(bTypeProcessorParams);

    auto result = am.load("/dynamic/bFile", "");

    EXPECT_TRUE(result.getResult());
}