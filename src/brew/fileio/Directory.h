/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2017 r.acc
 *
 *  Directory.h
 *
 *  Created on: Feb 11, 2016
 *      Author: void
 */

#ifndef BREW_DIRECTORY_H
#define BREW_DIRECTORY_H

#include <brew/core/Types.h>
#include <brew/core/Exception.h>
#include <brew/fileio/File.h>

#include <memory>
#include <vector>

namespace brew {

/**
 * The directory interface. Any type of directory that can be mounted in a VFS must inherit this base class.
 */
class Directory {
public:
    virtual ~Directory() = default;

    /**
     * Checks for the existence of a file.
     * @param file The file name.
     * @return Whether the file exists.
     */
    virtual bool exists(const String& file) const = 0;

    /**
     * Checks for the existence of a directory.
     * @param directory The directory name.
     * @return Whether the directory exists.
     */
    virtual bool isDirectory(const String& directory) const = 0;

    /**
     * Gets a directory instance.
     * @param directory The mount point of the directory.
     * @return The directory instance.
     */
    virtual std::unique_ptr<Directory> getDirectory(const String& directory) const = 0;

    /**
	 * Gets a file instance.
	 * @param file The mount point of the file.
	 * @return The file instance.
	 */
    virtual std::unique_ptr<File> getFile(const String& file) const = 0;

    /**
     * @return An array of strings containing the relative entries of this directory.
     */
    virtual std::vector<String> getEntries() const = 0;
};

} /* namespace brew */

#endif //BREW_DIRECTORY_H
