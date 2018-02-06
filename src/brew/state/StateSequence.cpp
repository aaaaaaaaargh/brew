/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 Marcus v. Keil
 *
 *  Created on: 09.01.18
 *
 */

#include <brew/state/StateSequence.h>

namespace brew {

void StateSequence::setStates() {
    // Recursion tail
}

bool StateSequence::isDone() const {
    return currentState == states.end();
}

State& StateSequence::getCurrentState() const {
    return **currentState;
}

void StateSequence::onEnterState() {
    currentState = states.begin();
}

bool StateSequence::onAdvanceState() {
    if (isDone()) {
        return true;
    }

    // Try to advance as far as we can.
    while (!isDone()) {
        auto& state = getCurrentState();

        if (!state.advance()) {
            break;
        }

        ++currentState;
    }

    // Only advance if we reached the last state.
    return isDone();
}

void StateSequence::setLooping(bool isLooping) {
    this->isLooping = isLooping;
}

std::unique_ptr<StateCompletitionToken> State::getCompletitionToken() {
    return std::make_unique<StateCompletitionToken>(*this);
}
} /* namespace brew */