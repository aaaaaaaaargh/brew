/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 Marcus v. Keil
 *
 *  Created on: 07.09.17
 *
 */

#include <gtest/gtest.h>

#include <brew/video/VertexAttribute.h>
#include <brew/video/VertexAttributeLayout.h>
#include <brew/core/Exception.h>

using namespace brew;

class CustomAttrib1 : public VertexAttribute {
public:
    hash_type getHash() const override {
        return 123456;
    }

    ComponentType getComponentType() const override {
        return ComponentType::Float;
    }

    SizeT getNumComponents() const override {
        return 8;
    }
};

TEST(VertexAttributeLayout, DefineSimpleLayout) {
    VertexAttributeLayout layout;
    layout.add<CustomAttrib1>();

    EXPECT_EQ(8 * 4, layout.getSize());
}

TEST(VertexAttributeLayout, GetNonExistingAttribute) {
    VertexAttributeLayout layout;

    EXPECT_THROW(layout.getAttributeOffset<CustomAttrib1>(), NotFoundException);

    layout.add<CustomAttrib1>();

    EXPECT_NO_THROW(layout.getAttributeOffset<CustomAttrib1>());
}

TEST(VertexAttributeLayout, IterateOverLayout) {
    VertexAttributeLayout layout;

    layout.add<CustomAttrib1>();
    layout.add<CustomAttrib1>();
    layout.add<CustomAttrib1>();
    layout.add<CustomAttrib1>();

    SizeT i=0;

    for(auto& entry : layout) {
        EXPECT_EQ(entry.attribute->getHash(), CustomAttrib1().getHash());
        i++;
    }

    EXPECT_EQ(4, i);
}

TEST(VertexAttributeLayout, GetAttributeOffsets) {
    VertexAttributeLayout layout;

    layout.add<CustomAttrib1>();
    layout.add<CustomAttrib1>();
    layout.add<CustomAttrib1>();
    layout.add<CustomAttrib1>();

    EXPECT_EQ(0, layout.getAttributeOffset<CustomAttrib1>(0));
    EXPECT_EQ(32, layout.getAttributeOffset<CustomAttrib1>(1));
    EXPECT_EQ(64, layout.getAttributeOffset<CustomAttrib1>(2));
    EXPECT_EQ(96, layout.getAttributeOffset<CustomAttrib1>(3));

    EXPECT_EQ(128, layout.getSize());
}