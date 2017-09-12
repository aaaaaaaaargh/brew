/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2017 r.acc
 *
 *  File.h
 *
 *  Created on: Feb 11, 2016
 *      Author: void
 */

#ifndef BREW_FILE_H
#define BREW_FILE_H

#include <brew/fileio/FileStream.h>

#include <memory>

namespace brew {

/**
 * The File interface. Any kind of file stream implementation must derive from this class.
 */
class File {
public:
	/**
	 * Opens a stream for this file.
	 * @param mode The open mode, can be std::ios:in or std::ios:out.
	 * @return A new file stream for this file.
	 */
	virtual std::unique_ptr<FileStream> open(const std::ios::openmode& mode = std::ios::in) const = 0;

};

} /* namespace brew */

#endif //BREW_FILE_H
