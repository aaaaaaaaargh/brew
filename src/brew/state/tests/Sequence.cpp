/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: 02.01.18
 *
 */

#include <gtest/gtest.h>

#include <brew/core/String.h>
#include <brew/state/StateSequence.h>
#include <future>
#include <utility>

using namespace brew;

class MyState : public State {
public:
    const String id;
    SizeT& counter;

public:
    MyState() : counter(*static_cast<SizeT*>(nullptr)) {}

    explicit MyState(String id, SizeT& counter)
    : id(std::move(id)), counter(counter) {

    }

public:
    bool onAdvanceState() override {
        // Simply advance.
        ++counter;
        return true;
    }
};

/**
 * Test simple state sequences.
 */
TEST(State, SimpleSequence) {
    SizeT counter = 0;

    StateSequence seq(
               std::make_unique<MyState>("a", counter),
               std::make_unique<MyState>("b", counter),
               std::make_unique<MyState>("c", counter),
               std::make_unique<MyState>("d", counter)
           );

    EXPECT_TRUE(seq.advance());
    EXPECT_EQ(4, counter);
}

/**
 * Test nested state sequences.
 */
TEST(State, NestedSequence) {
    SizeT counter = 0;

    StateSequence seq(
            std::make_unique<MyState>("a", counter),
            std::make_unique<MyState>("b", counter),
            std::make_unique<StateSequence>(
                    std::make_unique<MyState>("0", counter),
                    std::make_unique<MyState>("1", counter),
                    std::make_unique<MyState>("2", counter)
            ),
            std::make_unique<MyState>("c", counter),
            std::make_unique<MyState>("d", counter)
    );

    EXPECT_TRUE(seq.advance());
    EXPECT_EQ(7, counter);
}

TEST(State, Tokens) {
    SizeT counter = 0;

    auto aState = std::make_unique<MyState>("a", counter);
    auto bState = std::make_unique<MyState>("b", counter);
    auto cState = std::make_unique<MyState>("c", counter);

    auto bToken1 = bState->getCompletitionToken();
    auto bToken2 = bState->getCompletitionToken();
    auto bToken3 = bState->getCompletitionToken();

    StateSequence seq(aState, bState, cState);

    // Try to advance a couple of times.
    EXPECT_FALSE(seq.advance());
    EXPECT_EQ(1, counter);

    // Release the kra- i mean token.
    bToken1.reset();

    EXPECT_FALSE(seq.advance());
    EXPECT_EQ(1, counter);

    // Release the 2nd token.
    bToken2.reset();

    EXPECT_FALSE(seq.advance());
    EXPECT_EQ(1, counter);

    // Release the last token.
    bToken3.reset();

    EXPECT_TRUE(seq.advance());
    EXPECT_EQ(3, counter);
}
