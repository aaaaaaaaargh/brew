/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 Marcus v. Keil
 *
 *  Created on: Dec 14, 2015
 *
 */

#include <brew/core/HeapBuffer.h>
#include <cstring>

namespace brew {

HeapBuffer::HeapBuffer(SizeT numBytes) :
		AbstractBuffer(numBytes), buffer(new u8[numBytes]) {
	std::memset(buffer.get(), 0, numBytes);

}

void HeapBuffer::onWrite(const Byte* data, SizeT offset, SizeT len) {
	std::memcpy(buffer.get() + offset, data, len);
}

SizeT HeapBuffer::onRead(Byte* dest, SizeT offset, SizeT len) const {
	std::memcpy(dest, buffer.get() + offset, len);
	return len;
}

const Byte* HeapBuffer::getRawPointer() const {
	return buffer.get();
}

Byte* HeapBuffer::getRawPointer() {
	return buffer.get();
}

} /* namespace brew */
