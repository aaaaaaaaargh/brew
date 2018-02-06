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
	explicit HeapBuffer(SizeT numBytes);

	/**
	 * Writes an object into the buffer.
	 * @tparam T The object type, must be interpretable as raw pointer and support sizeof() calls.
	 * @param object The object to write.
	 * @param offset The target offset in the buffer.
	 */
	template<typename T>
	inline void writeObject(const T& object, SizeT offset)
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
	inline void readObject(T& object, SizeT offset)
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
	/**
     * Writes data into the buffer.
     * @param data A pointer to the data to write.
     * @param offset The offset to write the data to.
     * @param len The size of the data.
     */
	void onWrite(const Byte* data, SizeT offset,
						 SizeT len) override;

	/**
     * Reads data from the buffer.
     * @param dest A raw pointer to the destination.
     * @param offset The offset to read from.
     * @param len The size of the data.
     * @return The number of bytes read.
     */
	 SizeT onRead(Byte* dest, SizeT offset,
						 SizeT len) const override;

private:
	std::unique_ptr<u8[]> buffer;

};

} /* namespace brew */

#endif //BREW_HEAPBUFFER_H
