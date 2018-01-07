/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 random arts
 *
 *  Created on: 07.09.17
 *
 */

#include <gtest/gtest.h>

#include <brew/video/gl/tests/GLContextTest.h>

using namespace brew;

TEST_F(GLContextTest, VertexBufferCreation) {
    VertexAttributeLayout layout;
    layout.add<PositionAttribute>();

    auto buffer = context->createVertexBuffer(2, layout);

    EXPECT_EQ(sizeof(Vec3) * 2, buffer->getSize());

    Vec3 a, b;

    a.set(1,2,3);
    b.set(4,5,6);

    buffer->write<PositionAttribute>(0, a);
    buffer->write<PositionAttribute>(1, b);

    Vec3 ra = buffer->read<PositionAttribute>(0);
    Vec3 rb = buffer->read<PositionAttribute>(1);

    EXPECT_EQ(a, ra);
    EXPECT_EQ(b, rb);
}

TEST_F(GLContextTest, VertexBufferSync) {
    VertexAttributeLayout layout;
    layout.add<PositionAttribute>();

    auto buffer = context->createVertexBuffer(1, layout);

    buffer->write<PositionAttribute>(0, Vec3(1,2,3));

    buffer->syncToGPU();

    EXPECT_THROW(buffer->syncFromGPU(), IllegalStateException);

    context->processPendingOperations();

    buffer->write<PositionAttribute>(0, Vec3(0,0,0));

    buffer->syncFromGPU();

    context->processPendingOperations();

    EXPECT_EQ(Vec3(1,2,3), buffer->read<PositionAttribute>(0));
}


