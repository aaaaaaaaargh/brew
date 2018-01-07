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

#include <brew/video/gl/tests/GLContextTest.h>
#include <brew/core/BuildInfo.h>

#if BREW_PLATFORM == BREW_PLATFORM_LINUX
#include <brew/video/linux/GLXCanvas.h>
#endif //BREW_PLATFORM

#define BREW_GL_TEST_CANVAS_WIDTH 300
#define BREW_GL_TEST_CANVAS_HEIGHT 300

using namespace brew;

std::unique_ptr<brew::GLCanvas> GLContextTest::createCanvas(GLContext& context) {
#if BREW_PLATFORM == BREW_PLATFORM_LINUX
        return std::move(std::make_unique<GLXCanvas>(context));
#endif //BREW_PLATFORM
}

void GLContextTest::SetUp() {
    context = std::make_unique<GLContext>();

    // Make sure we selected a context.
    EXPECT_TRUE(context);

    canvas = createCanvas(*context);

    // Make sure we selected a canvas.
    EXPECT_TRUE(canvas);

    canvas->init(BREW_GL_TEST_CANVAS_WIDTH, BREW_GL_TEST_CANVAS_HEIGHT);
}

void GLContextTest::TearDown() {
    canvas->drop();

    canvas.reset();
    context.reset();
}

TEST_F(GLContextTest, SetUpAndTearDown) {

}