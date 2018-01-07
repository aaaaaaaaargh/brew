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

#include <brew/core/Object.h>

namespace brew {

void Object::setAppContextFrom(const Object& other) {
    appContext = other.appContext;
}

} /* namespace brew */
