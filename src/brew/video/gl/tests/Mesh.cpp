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

#include <brew/video/gl/tests/GLContextTest.h>

using namespace brew;

TEST_F(GLContextTest, MeshCreation) {
    VertexAttributeLayout layout;
    layout.add<PositionAttribute>();

    auto vertexBuffer = context->createVertexBuffer(4, layout);
    auto indexBuffer = context->createIndexBuffer(4);

    auto mesh = context->createMesh(vertexBuffer, indexBuffer);

    context->processPendingOperations();

    EXPECT_TRUE(mesh->isReady());
}
