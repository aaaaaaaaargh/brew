/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 Marcus v. Keil
 *
 *  Created on: Feb 11, 2016
 *
 */

#include <gtest/gtest.h>

#include <brew/math/Math.h>

using namespace brew;

TEST(Math, EpsilonEquality) {
    Real a = 0.1f;
    Real b = 0.01f;

    ASSERT_TRUE(math::equals(a, b, 0.1f));
    ASSERT_FALSE(math::equals(a, b, 0.01f));
}

TEST(Math, ConvertDegreeRadians) {
    ASSERT_FLOAT_EQ(math::deg2Rad(180.0f), math::PI);
    ASSERT_FLOAT_EQ(math::rad2Deg(math::PI), 180.0f);
}
