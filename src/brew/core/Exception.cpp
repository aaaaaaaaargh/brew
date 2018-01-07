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

#include "brew/core/Exception.h"

namespace brew {

Exception::Exception(const String& what)
: message(what) {}

Exception::Exception(const char* what)
: message(what) {}

const char* Exception::what() const throw() {
    return message.c_str();
}

} /* namespace brew */