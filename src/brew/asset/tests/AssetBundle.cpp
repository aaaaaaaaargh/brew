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

#include <brew/asset/AssetBundle.h>

using namespace brew;

/**
 * Tests insert, remove and retrieve operations for bundles.
 */
TEST(Asset, BundleCRUD) {
    AssetBundle bundle;

    bundle.put("foo", std::make_shared<int>(1234));
    bundle.put("foo", std::make_shared<String>("FoO!"));

    ASSERT_EQ(1234, *bundle.get<int>("foo"));
    ASSERT_EQ("FoO!", *bundle.get<String>("foo"));

    bundle.removeAll("foo");

    ASSERT_THROW(bundle.get<int>("foo"), NotFoundException);
}
