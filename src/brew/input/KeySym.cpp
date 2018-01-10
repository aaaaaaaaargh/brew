/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: Nov 15, 2016
 *
 */

#include <brew/core/Types.h>
#include <brew/input/KeySym.h>

namespace brew {

std::ostream& operator << (std::ostream& os, const KeySym& kc) {

	if(kc >= KeySym::A && kc <= KeySym::Z) {
		os << (char)('A' + (static_cast<SizeT>(kc) - static_cast<SizeT>(KeySym::A)));
	}
	if(kc >= KeySym::a && kc <= KeySym::z) {
		os << (char)('a' + (static_cast<SizeT>(kc) - static_cast<SizeT>(KeySym::a)));
	}

	// TODO...

	return os;
}

} /* namespace brew */




