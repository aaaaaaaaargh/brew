/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2017 random arts
 *
 *  Created on: Dec 14, 2015
 *
 */

#include "AbstractBuffer.h"
#include "Exception.h"

namespace brew {

void AbstractBuffer::copyTo(AbstractBuffer& target, SizeT targetOffset, SizeT srcOffset, SizeT length) const {
  SizeT len = length;
  if (len == 0) {
    if (srcOffset >= getSize()) {
      throw BufferOverflowException("Buffer overflow while copying, source buffer offset invalid.");
    }
    len = getSize() - srcOffset;
  }

  if (targetOffset + len > target.getSize()) {  // Target buffer is too small
    throw BufferOverflowException("Buffer overflow while copying, target buffer is too small.");
  }

  if (srcOffset + len > target.getSize()) {  // This buffer is too small
    throw BufferOverflowException("Buffer overflow while copying, source buffer is too small.");
  }

  const SizeT bufferSize = 1024;  // Fixed buffer size.
  SizeT remaining = len;
  SizeT read = 0;
  Byte* buffer = new Byte[bufferSize];

  while (remaining > 0) {
    SizeT o = srcOffset + read;
    SizeT l = std::min(remaining, bufferSize);
    remaining -= l;
    read += l;

    this->read(buffer, o, l);
    target.write(buffer, 0, l);
  }

  delete[] buffer;
}

void AbstractBuffer::write(const Byte* data, SizeT offset, SizeT len) {
  if (offset + len > size) {
    throw BufferOverflowException("Buffer overflow while writing.");
  }
  return onWrite(data, offset, len);
}

SizeT AbstractBuffer::read(Byte* dest, SizeT offset, SizeT len) const {
  if (offset + len > size) {
    throw BufferOverflowException("Buffer overflow while reading.");
  }
  return onRead(dest, offset, len);
}

} /* namespace brew */
