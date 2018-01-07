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

#ifndef BREW_GLCONTEXTTEST_H
#define BREW_GLCONTEXTTEST_H

#include <brew/video/gl/GLCanvas.h>

#include <gtest/gtest.h>

/**
 * A class for GL context related tests.
 */
class GLContextTest : public ::testing::Test {
public:
private:
    static std::unique_ptr<brew::GLCanvas> createCanvas(brew::GLContext& context);

protected:
    /**
     * Sets up the test context.
     */
    void SetUp() override;

    /**
     * Tears down the test context.
     */
    void TearDown() override;

    std::unique_ptr<brew::GLContext> context;
    std::unique_ptr<brew::GLCanvas> canvas;
};

#endif //BREW_GLCONTEXTTEST_H
