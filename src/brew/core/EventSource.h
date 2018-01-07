/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: 04.09.17
 *
 */

#ifndef BREW_EVENTSOURCE_H
#define BREW_EVENTSOURCE_H

#include <vector>
#include <memory>
#include <algorithm>

/**
 * Declares a new event source.
 * This adds addFoo() and removeFoo() methods to the class as well as a fireFoo(EventT&) method that can be used
 * to propagate events.
 * @param ListenerT The event listener type.
 * @param EventT The event type.
 * @param ListenerName The name of the listener.
 * @param EventName The name of the event.
 */
#define BREW_EVENTSOURCE_NAMED(ListenerT, EventT, ListenerName, EventName) \
    public: \
        typedef std::shared_ptr<ListenerT> ListenerName##Ptr; \
    private: \
        std::vector<ListenerT##Ptr> _ep##ListenerName##s; \
    public: \
        void add##ListenerName(const ListenerName##Ptr& ptr) { \
            remove##ListenerName(ptr); \
            _ep##ListenerName##s.push_back(ptr); \
        } \
        void remove##ListenerName(const ListenerName##Ptr& ptr) { \
            auto it = std::find(_ep##ListenerName##s.begin(),  _ep##ListenerName##s.end(), ptr); \
            if(it !=  _ep##ListenerName##s.end()) _ep##ListenerName##s.erase(it); \
        } \
    public: \
        void fire##EventName(EventT& event) { \
            for(auto& l : _ep##ListenerName##s) { \
               l->on##EventName(event); \
            } \
        } \
		\

#define _BREW_EVENTSOURCE_(ListenerT, EventT) \
	BREW_EVENTSOURCE_NAMED(ListenerT, EventT, ListenerT, EventT)

#define _BREW_EVENTSOURCE_N(x, A, FUNC, ...)  FUNC

/**
 * Declares a new event source.
 * This adds addFoo() and removeFoo() methods to the class as well as a fireFoo(EventT&) method that can be used
 * to propagate events.
 * @param ListenerT The event listener type.
 * @param EventT The event type.
 */
#define BREW_EVENTSOURCE(ListenerT, EventT, ...) \
		_BREW_EVENTSOURCE_N(,##__VA_ARGS__,\
		BREW_EVENTSOURCE_NAMED(ListenerT, EventT, __VA_ARGS__),\
		_BREW_EVENTSOURCE_(ListenerT, EventT))\

#endif // BREW_EVENTSOURCE_H
