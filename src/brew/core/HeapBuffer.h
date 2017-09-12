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

#ifndef BREW_HEAPBUFFER_H
#define BREW_HEAPBUFFER_H

#include "Types.h"
#include "AbstractBuffer.h"

#include <memory>

namespace brew
{

/**
 * A heap buffer is a data buffer that resides in heap space (RAM) only.
 * Use it for anything volatile.
 */
class HeapBuffer: public AbstractBuffer
{
public:
	/**
	 * Creates a new heap buffer.
	 * @param numBytes The size of the buffer in bytes.
	 */
	HeapBuffer(const SizeT& numBytes);

	/**
	 * Writes an object into the buffer.
	 * @tparam T The object type, must be interpretable as raw pointer and support sizeof() calls.
	 * @param object The object to write.
	 * @param offset The target offset in the buffer.
	 */
	template<typename T>
	inline void writeObject(const T& object, const SizeT& offset)
	{
		AbstractBuffer::write(reinterpret_cast<const Byte*>(&object), offset, sizeof(object));
	}

	/**
	 * Reads an object from the buffer.
	 * @tparam T The object type, must be interpretable as raw pointer and support sizeof() calls.
	 * @param object The object to read to.
	 * @param offset The source offset in the buffer.
	 */
	template<typename T>
	inline void readObject(T& object, const SizeT& offset)
	{
		AbstractBuffer::read(reinterpret_cast<Byte*>(&object), offset, sizeof(object));
	}

	/**
	 * @return The buffer as raw pointer.
	 */
	virtual Byte* getRawPointer();

	/**
	 * @return The buffer as raw pointer.
	 */
	virtual const Byte* getRawPointer() const;

protected:
	virtual void onWrite(const Byte* data, const SizeT& offset, const SizeT& len);
	virtual SizeT onRead(Byte* dest, const SizeT& offset, const SizeT& len) const;

private:
	std::unique_ptr<u8[]> buffer;

};

} /* namespace brew */

#endif //BREW_HEAPBUFFER_H
