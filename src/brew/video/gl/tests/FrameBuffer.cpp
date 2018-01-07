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

TEST_F(GLContextTest, FrameBufferCreation) {
    auto frameBuffer = context->createFrameBuffer(200, 200);
    context->processPendingOperations();
}


