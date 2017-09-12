/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2017 random arts
 *
 *  Created on: 07.09.17
 *
 */

#include <gtest/gtest.h>

#include <brew/video/gl/tests/GLContextTest.h>
#include <brew/video/gl/GLShaderVariables.h>

using namespace brew;

TEST_F(GLContextTest, SetShaderVars) {
    ShaderVariablesDefinition shaderDef;
    shaderDef.define<Real>("foo");

    auto shaderVars = context->createShaderVariables(shaderDef);

    EXPECT_EQ(0, shaderVars->getShaderVariableUpdates().values.size());

    shaderVars->set<Real>("foo", 1234);

    EXPECT_EQ(1, shaderVars->getShaderVariableUpdates().values.size());

    context->processPendingOperations();

    EXPECT_EQ(0, shaderVars->getShaderVariableUpdates().values.size());
}

TEST_F(GLContextTest, UpdateShaderVars) {
    ShaderVariablesDefinition shaderDef;
    shaderDef.define<Real>("foo");

    auto shaderVars = context->createShaderVariables(shaderDef);

    shaderVars->set<Real>("foo", 1234);

    context->processPendingOperations();

    EXPECT_EQ(0, shaderVars->getShaderVariableUpdates().values.size());

    shaderVars->set<Real>("foo", 1234);
    EXPECT_EQ(1, shaderVars->getShaderVariableUpdates().values.size());

    context->processPendingOperations();

    EXPECT_EQ(0, shaderVars->getShaderVariableUpdates().values.size());
}

TEST_F(GLContextTest, CreateShaderVarsBufferWithSingleValue) {
    ShaderVariablesDefinition shaderDef;
    shaderDef.define<Real>("foo");

    auto shaderVars = context->createShaderVariables(shaderDef);

    shaderVars->set<Real>("foo", 1234);

    context->processPendingOperations();

    GLShaderVariablesContextHandle& handle = static_cast<GLShaderVariablesContextHandle&>(**shaderVars);

    EXPECT_EQ(sizeof(Real), handle.getBuffer().getSize());

    const Byte* buffer = handle.getBuffer().getRawPointer();
    const Real result = *reinterpret_cast<const Real*>(buffer);

    EXPECT_FLOAT_EQ(1234, result);
}

TEST_F(GLContextTest, CreateShaderVarsBufferWithArray) {
    ShaderVariablesDefinition shaderDef;
    shaderDef.define<Real>("foo", 3);

    auto shaderVars = context->createShaderVariables(shaderDef);

    shaderVars->set<Real>("foo", {12.0f, 34.0f, 56.0f});

    context->processPendingOperations();

    GLShaderVariablesContextHandle& handle = static_cast<GLShaderVariablesContextHandle&>(**shaderVars);

    EXPECT_EQ(sizeof(Real) * 3, handle.getBuffer().getSize());

    const Byte* buffer = handle.getBuffer().getRawPointer();
    const Real val0 = *reinterpret_cast<const Real*>(buffer);
    const Real val1 = *reinterpret_cast<const Real*>(buffer+4);
    const Real val2 = *reinterpret_cast<const Real*>(buffer+8);

    EXPECT_FLOAT_EQ(12, val0);
    EXPECT_FLOAT_EQ(34, val1);
    EXPECT_FLOAT_EQ(56, val2);
}

TEST_F(GLContextTest, UpdateShaderVarsBuffer) {
    ShaderVariablesDefinition shaderDef;
    shaderDef.define<Real>("foo");

    auto shaderVars = context->createShaderVariables(shaderDef);

    shaderVars->set<Real>("foo", 1234);

    context->processPendingOperations();

    shaderVars->set<Real>("foo", 3456);

    context->processPendingOperations();

    GLShaderVariablesContextHandle& handle = static_cast<GLShaderVariablesContextHandle&>(**shaderVars);

    EXPECT_EQ(sizeof(Real), handle.getBuffer().getSize());

    const Byte* buffer = handle.getBuffer().getRawPointer();
    const Real result = *reinterpret_cast<const Real*>(buffer);

    EXPECT_FLOAT_EQ(3456, result);
}


