/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2017 r.acc
 *
 *  FileStream.h
 *
 *  Created on: Feb 11, 2016
 *
 */

#ifndef BREW_FILESTREAM_H
#define BREW_FILESTREAM_H

#include <brew/core/Types.h>

#include <istream>

namespace brew
{

/**
 * A stream implementation for files in the VFS.
 */
class FileStream : public std::istream
{

public:
	/**
	 * Creates a new file stream.
	 * @param streambuf The source where to read/write the data from/to.
	 */
	explicit FileStream(std::streambuf* streambuf);

	/**
	 * Destructs the file stream.
	 */
	~FileStream() override;

	/**
	 * @return The size of the stream (if determinate).
	 */
	SizeT getSize();
};

} /* namespace brew */

#endif //BREW_FILESTREAM_H
