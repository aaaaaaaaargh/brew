/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 random arts
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

TEST(Asset, BundleCRUD) {
    AssetBundle bundle;

    bundle.put<int>("foo", 1234);
    bundle.put<String>("foo", "FoO!");

    ASSERT_EQ(1234, bundle.get<int>("foo"));
    ASSERT_EQ("FoO!", bundle.get<String>("foo"));

    bundle.removeAll("foo");

    ASSERT_THROW(bundle.get<int>("foo"), NotFoundException);
}

TEST(Asset, LoadSimpleAsset) {
    auto vfs = std::make_shared<VirtualFileSystem>();

    auto heapDir = std::make_unique<HeapDirectory>();

    heapDir->addFile("testFile", "This is just a test.");

    vfs->mount("/dynamic", std::move(heapDir));

    AssetManager am(vfs);

    am.load<AType>("/dynamic/testFile", [] (AType& asset) {
        std::cout << "Loaded!\n";
    });

}
