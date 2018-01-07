/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: Apr 4, 2016
 *
 */

#ifndef BREW_STRINGBUFFER_H_
#define BREW_STRINGBUFFER_H_

#include <brew/core/String.h>
#include <brew/core/HeapBuffer.h>

namespace brew
{

/**
 * A buffer for strings.
 */
class StringBuffer : public AbstractBuffer
{
public:
	/**
	 * Creates a new string buffer.
	 * @param str The string this buffer should contain.
	 */
	StringBuffer(const String& str);

	/**
	 * @return The buffer contents, represented as string.
	 */
	inline const String& getString() const {
		return string;
	}

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
	String string;

};

} /* namespace brew */

#endif /* BREW_STRINGBUFFER_H_ */
