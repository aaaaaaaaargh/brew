/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2017 r.acc
 *
 *  VirtualFileSystem.h
 *
 *  Created on: Feb 11, 2016
 *      Author: void
 */

#ifndef BREW_VIRTUALFILESYSTEM_H
#define BREW_VIRTUALFILESYSTEM_H

#include <brew/core/Types.h>
#include <brew/core/Exception.h>

#include "Directory.h"

#include <memory>
#include <map>

namespace brew {

/**
 * The virtual file system main class.
 * The VFS provides access to local or remote resources by mounting the resource locations into
 * an abstract file and directory tree.
 */
class VirtualFileSystem
{
public:
    /**
     * Mounts a new directory at the given mount point.
     * @param mount_point The mount point, a unix compatible pathname.
     * @param directory The directory instance to mount.
     */
	void mount(const String& mount_point, std::unique_ptr<Directory> directory);

    /**
     * Unmounts the mounted resource at the given mount point.*
     * @param mount_point The mount point.
     * @throws IOException if the mount point does not exist.
     */
	void unmount(const String& mount_point);

    /**
     * Mounts a local path at the given mount point. This is a shorthand for mount() with a
     * LocalDirectory instance.
     * @param mount_point The mount point, a unix compatible pathname.
     * @param localPath The path of the local directory.
     */
	void mountLocal(const String& mount_point, const String& localPath);

    /**
     * Gets a directory instance for a given path.
     * @param path The path.
     * @return The directory that the path resolves to.
     */
	std::unique_ptr<Directory> getDirectory(const String& path) const;

    /**
     * Gets a file instance for a given path.
     * @param path The file path.
     * @return The file that the path resolves to.
     */
	std::unique_ptr<File> getFile(const String& path) const;

    /**
     * Normalizes a path by resolving /.. and /. components .
     * @param path The path.
     * @return The normalized path.
     */
	static String normalizePath(const String& path);

public:
    /**
     * The operating system dependent directory separator symbol.
     */
	static const String directory_separator;

private:
	std::map<String, std::unique_ptr<Directory> > mountPoints;

};

} /* namespace brew */

#endif //BREW_VIRTUALFILESYSTEM_H
