/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: 08.09.17
 *
 */

#include <brew/core/AppContext.h>

namespace brew {

AppContext::AppContext()
: log(std::make_unique<StreamLog>()){
}

} /* namespace brew */
