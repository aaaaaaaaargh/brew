/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2017 r.acc
 *
 *  HeapFileSystem.h
 *
 *  Created on: Feb 23, 2016
 *      Author: void
 */

#ifndef BREW_HEAPFILESYSTEM_H
#define BREW_HEAPFILESYSTEM_H

#include <brew/core/Types.h>
#include <brew/fileio/Directory.h>

#include <map>

namespace brew {

class HeapFile;

/**
 * A VFS directory implementation that uses heap memory to provide files.
 */
class HeapDirectory : public Directory
{
public:
	/**
	 * Creates a new heap directory.
	 * @param initial_heap_data A map of keyed data vectors representing the files in this directory.
	 */
	explicit HeapDirectory(const std::map<String, std::vector<Byte> >& initial_heap_data = std::map<String, std::vector<Byte> >());

	/**
	 * Constructs a heap directory from another directory.
	 * @param base The heap directory that is the base for this directory.
	 * @param full_path
	 */
	HeapDirectory(HeapDirectory& base, const String& full_path);

public:
	typedef std::map<brew::String, std::vector<brew::Byte> > HeapDataT;

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
	HeapDataT heap_data;
	HeapDirectory& base;
	String path;
};

/**
 * File implementation for the heap file system.
 */
class HeapFile : public File
{
public:
	/**
	 * Creates a new file handle.
	 * @param buffer The heap buffer to use for this file handle.
	 */
	explicit HeapFile(std::vector<Byte>& buffer);

	/**
	 * Opens a stream for this file.
	 * @param mode The open mode, can be std::ios:in or std::ios:out.
	 * @return A new file stream for this file.
	 */
	std::unique_ptr<FileStream> open(const std::ios::openmode& mode) const override;

private:
	std::vector<Byte>& buffer;
};

} /* namespace brew */

#endif //BREW_HEAPFILESYSTEM_H
