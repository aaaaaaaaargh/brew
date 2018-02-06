/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 Marcus v. Keil
 *
 *  Created on: 02.01.18
 *
 */

#include <gtest/gtest.h>

#include <brew/asset/AssetManager.h>
#include <brew/fileio/HeapFileSystem.h>

using namespace brew;

class AType {
public:
    String paramsId;
};

class BType {};
class CType {};
class DType {};

class ATypeProcessorParams : public AssetProcessorParams {
public:
    String id;
};

class ATypeProcessor : public AssetProcessor<ATypeProcessorParams> {
public:
    bool canLoad(const AssetPipeline& pipeline, const VirtualFileSystem& vfs, const AssetBundle& bundle, const String& tag, const ATypeProcessorParams& params) const override {
        return tag.find("aFile") != String::npos;
    };

    void load(AssetPipeline& pipeline, const VirtualFileSystem& vfs, AssetBundle& bundle, const String& tag, const ATypeProcessorParams& params) const override {
        auto a = std::make_shared<AType>();
        a->paramsId = params.id;
        bundle.put(tag, a);
    };
};

class BTypeProcessorParams : public AssetProcessorParams {};

class BTypeProcessor : public AssetProcessor<BTypeProcessorParams> {
public:
    bool canLoad(const AssetPipeline& pipeline, const VirtualFileSystem& vfs, const AssetBundle& bundle, const String& tag, const BTypeProcessorParams& params) const override {
        return tag.find("bFile") != String::npos;
    };

    void load(AssetPipeline& pipeline, const VirtualFileSystem& vfs, AssetBundle& bundle, const String& tag, const BTypeProcessorParams& params) const override {
        pipeline.load("/dynamic/aFile", "");

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

TEST(Asset, PassParamsSimple) {
    auto vfs = std::make_shared<VirtualFileSystem>();

    auto heapDir = std::make_unique<HeapDirectory>();

    heapDir->addFile("aFile", "A file.");

    vfs->mount("/dynamic", std::move(heapDir));

    AssetManager am(vfs);

    ATypeProcessorParams aTypeProcessorParams;
    aTypeProcessorParams.id = "MyId";
    am.registerProcessor<ATypeProcessor>(aTypeProcessorParams);

    am.load("/dynamic/aFile", "").getResult();

    auto asset = am.getDefaultBundle().get<AType>("/dynamic/aFile");

    EXPECT_EQ(aTypeProcessorParams.id, asset->paramsId);
}

TEST(Asset, PassParamsRecursive) {
    auto vfs = std::make_shared<VirtualFileSystem>();

    auto heapDir = std::make_unique<HeapDirectory>();

    heapDir->addFile("aFile", "A file.");
    heapDir->addFile("bFile", "B file.");

    vfs->mount("/dynamic", std::move(heapDir));

    AssetManager am(vfs);

    ATypeProcessorParams aTypeProcessorParams;
    aTypeProcessorParams.id = "MyId";

    am.registerProcessor<ATypeProcessor>(aTypeProcessorParams);

    BTypeProcessorParams bTypeProcessorParams;
    am.registerProcessor<BTypeProcessor>(bTypeProcessorParams);

    am.load("/dynamic/bFile", "", aTypeProcessorParams).getResult();

    auto asset = am.getDefaultBundle().get<AType>("/dynamic/aFile");

    EXPECT_EQ(aTypeProcessorParams.id, asset->paramsId);
}