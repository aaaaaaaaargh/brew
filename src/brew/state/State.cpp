/**
 *  Copyright 2015-2018 random arts
 *  Created on: 09.01.18
 */

#include <brew/state/State.h>

namespace brew {

StateCompletionToken::StateCompletionToken(State& owner) :
        owner(owner) {
    owner.numActiveTokens++;
}

StateCompletionToken::~StateCompletionToken() {
    owner.numActiveTokens--;
}

State::State() : numActiveTokens(0), entered(false) {
}

bool State::advance() {
    if(!entered) {
        entered = true;
        onEnterState();
    }

    if (numActiveTokens > 0) {
        return false;
    }

    if(onAdvanceState()) {
        entered = false;
        return true;
    }

    return false;
}

} /* namespace brew */
