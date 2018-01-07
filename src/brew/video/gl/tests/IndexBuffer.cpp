/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: 07.09.17
 *
 */

#include <gtest/gtest.h>

#include <brew/video/gl/tests/GLContextTest.h>

using namespace brew;

TEST_F(GLContextTest, IndexBufferCreation) {
    auto buffer = context->createIndexBuffer(8);

    EXPECT_EQ(sizeof(IndexBuffer::index_type) * buffer->getNumIndices(), buffer->getSize());

    buffer->write(0, 1234);
    buffer->write(5, 5678);

    IndexBuffer::index_type a, b;

    a = buffer->read(0);
    b = buffer->read(5);

    EXPECT_EQ(1234, a);
    EXPECT_EQ(5678, b);
}

TEST_F(GLContextTest, IndexBufferSync) {
    auto buffer = context->createIndexBuffer(8);

    buffer->write(3, 1234);

    buffer->syncToGPU();

    EXPECT_THROW(buffer->syncFromGPU(), IllegalStateException);

    context->processPendingOperations();

    buffer->write(3, 0);

    buffer->syncFromGPU();

    context->processPendingOperations();

    EXPECT_EQ(1234, buffer->read(3));
}