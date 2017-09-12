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

#include <brew/core/Object.h>

namespace brew {

void Object::setAppContextFrom(const Object& other) {
    appContext = other.appContext;
}

} /* namespace brew */
