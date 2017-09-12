/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2017 r.acc
 *
 *  LocalDirectory.h
 *
 *  Created on: Feb 11, 2016
 *      Author: void
 */

#ifndef BREW_LOCALDIRECTORY_H
#define BREW_LOCALDIRECTORY_H

#include <brew/fileio/Directory.h>

namespace brew {

/**
 * A VFS directory implementation that uses the local file system.
 */
class LocalDirectory : public Directory
{
public:
	/**
	 * Creates a new directory handle.
	 * @param real_path The real local path.
	 */
	explicit LocalDirectory(const String& real_path);

public:
	/**
     * Checks for the existence of a file.
     * @param file The file name.
     * @return Whether the file exists.
     */
	bool exists(const String& file) const override;

	/**
     * Checks for the existence of a directory.
     * @param directory The directory name.
     * @return Whether the directory exists.
     */
	bool isDirectory(const String& file) const override;

	/**
     * Gets a directory instance.
     * @param directory The mount point of the directory.
     * @return The directory instance.
     */
	std::unique_ptr<Directory> getDirectory(const String& dir) const override;

	/**
     * Gets a file instance.
     * @param file The mount point of the file.
     * @return The file instance.
     */
	std::unique_ptr<File> getFile(const String& file) const override;

	/**
     * @return An array of strings containing the relative entries of this directory.
     */
	std::vector<String> getEntries() const override;

private:
	String real_path;

};

/**
 * A VFS file implementation that uses the local file system.
 */
class LocalFile : public File
{
public:
	/**
	 * Creates new new file handle.
	 * @param real_path The real path of the local file system.
	 */
	explicit LocalFile(const String& real_path);

	/**
	 * Opens a stream for this file.
	 * @param mode The open mode, can be std::ios:in or std::ios:out.
	 * @return A new file stream for this file.
	 */
	std::unique_ptr<FileStream> open(const std::ios::openmode& mode) const override;

private:
	String real_path;

};

} /* namespace brew */

#endif //BREW_FILEIO_LOCAL_LOCALDIRECTORY_H
