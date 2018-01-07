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

#include <brew/asset/AssetBundle.h>

using namespace brew;

/**
 * Tests insert, remove and retrieve operations for bundles.
 */
TEST(Asset, BundleCRUD) {
    AssetBundle bundle;

    bundle.put<int>("foo", 1234);
    bundle.put<String>("foo", "FoO!");

    ASSERT_EQ(1234, bundle.get<int>("foo"));
    ASSERT_EQ("FoO!", bundle.get<String>("foo"));

    bundle.removeAll("foo");

    ASSERT_THROW(bundle.get<int>("foo"), NotFoundException);
}
