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

#ifndef BREW_STATESEQUENCE_H
#define BREW_STATESEQUENCE_H

#include <brew/core/Types.h>
#include <brew/state/State.h>

#include <vector>
#include <memory>

namespace brew {

/**
 * A sequence of states to advance. The sequence is a state itself meaning it can be nested.
 */
class StateSequence : public State {
public:
    /**
     * Creates a new state sequence from the given set of states.
     * @tparam States A variadic type of unique state pointers.
     * @param states A set of unique pointers holding the states.
     */
    template<typename... States>
    explicit StateSequence(States&& ... states)
    : isLooping(false) {
        setStates(states...);
    }

public:
    /**
     * @return The current state, if any.
     */
    State& getCurrentState() const;

public:
    /**
     * @return Whether the sequence is completed.
     */
    bool isDone() const;

    /**
     * Sets the looping behaviour of this sequence. Looping will cause isDone() to never be true.
     * @param isLooping Whether the sequence should loop after reaching the last state.
     */
    void setLooping(bool isLooping);

protected:
    bool onAdvanceState() final;

    void onEnterState() final;

private:
    void setStates();

    template<typename S0, typename... States>
    void setStates(S0&& s0, States&& ... states) {
        this->states.emplace_back(std::move(s0));
        setStates(states...);
    }

private:
    typedef std::vector<std::unique_ptr<State> > StatesContainer;
    StatesContainer states;
    typename StatesContainer::iterator currentState;
    bool isLooping;
};

} /* namespace brew */

#endif //BREW_STATESEQUENCE_H
