/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2017 r.acc
 *
 *  LocalDirectory.cpp
 *
 *  Created on: Feb 11, 2016
 *      Author: void
 */

#include <brew/fileio/LocalFileSystem.h>
#include <brew/fileio/VirtualFileSystem.h>

#include <fstream>
#include <dirent.h>
#include <fcntl.h>
#include <zconf.h>

namespace brew {

LocalDirectory::LocalDirectory(const String& real_path)
: real_path(VirtualFileSystem::normalizePath(real_path+VirtualFileSystem::directory_separator)) {
	if(this->real_path.empty())
		this->real_path = "./";
}

std::unique_ptr<Directory> LocalDirectory::getDirectory(const String& dir) const {

	String path = VirtualFileSystem::normalizePath(real_path+dir);

	DIR* dh =opendir(path.c_str());
	if(!dh) {
		throw IOException("Cannot open local directory '" + path + '"');
	}
	closedir(dh);

	return std::make_unique<LocalDirectory>(path);
}

std::unique_ptr<File> LocalDirectory::getFile(const String& file) const {
	if(!exists(file))
		throw IOException("No such local file '" + real_path + file + "'");
	if(isDirectory(file))
		throw IOException("'" + real_path + file + "' is a directory.");
	return std::make_unique<LocalFile>(real_path+VirtualFileSystem::directory_separator+file);
};

std::vector<String> LocalDirectory::getEntries() const {

	std::vector<String> r;
	DIR* dh =opendir(real_path.c_str());
	dirent* e;
	while((e = readdir(dh)) != NULL) {

		String filename = e->d_name;
		if(filename == "." || filename == "..")
			continue;
		//filename = real_path + filename;
		r.push_back(filename);
	}
	closedir(dh);

	return r;
}

bool LocalDirectory::exists(const String& file) const {
	if(isDirectory(file))
		return true;

 	int ok = access((real_path + file).c_str(), F_OK);
 	return ok != -1;
}

bool LocalDirectory::isDirectory(const String& file) const {
	DIR* dh =opendir((real_path+ file).c_str());
	if(!dh)
		return false;
	closedir(dh);
	return true;
}

LocalFile::LocalFile(const String& real_path)
: real_path(real_path) {

}

std::unique_ptr<FileStream> LocalFile::open(const std::ios::openmode& mode) const {
	std::filebuf* buf = new std::filebuf();
	buf->open(real_path, mode);
	return std::make_unique<FileStream>(buf);
}

} /* namespace brew */
