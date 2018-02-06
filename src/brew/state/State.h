/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: 09.01.18
 *
 */

#ifndef BREW_STATE_H
#define BREW_STATE_H

#include <brew/core/Types.h>

#include <memory>
#include <atomic>
#include <brew/core/Object.h>

namespace brew {

class State;

/**
 * A state completion token blocks a state from advancing until it is released.
 */
class StateCompletitionToken {
    friend class State;

public:
    /**
     * Creates a new completion token. Prefer to use State::getCompletiionToken() instead.
     * @param owner The token owner.
     */
    explicit StateCompletitionToken(State& owner);

    /**
     * Releases the token and unblocks the state.
     */
    ~StateCompletitionToken();

private:
    State& owner;
};

/**
 * A single state in a sequence.
 */
class State : public Object {
    friend class StateCompletitionToken;

public:
    /**
     * Creates a new state.
     */
    State();

public:
    /**
     * Gets a completion token that prevents the state from advancing as long as its not released.
     * @return A pointer to a new completion token.
     */
    std::unique_ptr<StateCompletitionToken> getCompletitionToken();

    /**
     * Tries to advance the state. Either blocks if there are unreleased completion tokens or onAdvanceState() returns false.
     * Also, this method calls onEnterState() the first time it was invoked.
     * @return Whether the state has advanced.
     */
    bool advance();

protected:
    /**
     * Callback triggered when the state is entered for the first time. This can be used for creating completion tokens.
     */
    virtual void onEnterState() {};

    /**
     * Callback for advancing the state. Will only be invoked if there are no blocking completion tokens.
     * @return Whether the state is ready to advance.
     */
    virtual bool onAdvanceState() = 0;

private:
    std::atomic<SizeT> numActiveTokens;
    bool entered;
};

} /* namespace brew */


#endif //BREW_STATE_H
