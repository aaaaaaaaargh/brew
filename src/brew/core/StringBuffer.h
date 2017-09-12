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
	virtual void onWrite(const Byte* data, const SizeT& offset, const SizeT& len);
	virtual SizeT onRead(Byte* dest, const SizeT& offset, const SizeT& len) const;

private:
	String string;

};

} /* namespace brew */

#endif /* BREW_STRINGBUFFER_H_ */
