/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2017 random arts
 *
 *  Created on: Apr 4, 2016
 *
 */

#include <brew/core/StringBuffer.h>
#include <cstring>
#include <iostream>

namespace brew
{

StringBuffer::StringBuffer(const String& str)
: AbstractBuffer(str.length()+1), string(str)
{

}

void StringBuffer::onWrite(const Byte* data, const SizeT& offset, const SizeT& len) {
	const char* d = reinterpret_cast<const char*>(data);
	string.replace(offset, len, d);
}

SizeT StringBuffer::onRead(Byte* dest, const SizeT& offset, const SizeT& len) const {
	std::memcpy(dest, string.c_str()+offset, len);
	return len;
}


} /* namespace brew */
