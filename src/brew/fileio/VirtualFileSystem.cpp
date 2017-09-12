/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2017 r.acc
 *
 *  VirtualFileSystem.cpp
 *
 *  Created on: Feb 11, 2016
 *      Author: void
 */

#include <brew/fileio/VirtualFileSystem.h>
#include <brew/fileio/LocalFileSystem.h>
#include <brew/core/String.h>

namespace brew {

const String VirtualFileSystem::directory_separator = "/";

void VirtualFileSystem::mount(const String& mount_point, std::unique_ptr<Directory> dir) {
	mountPoints.insert(std::make_pair(mount_point, std::move(dir)));
}

void VirtualFileSystem::mountLocal(const String& mount_point, const String& localPath) {
	mount(mount_point, std::make_unique<LocalDirectory>(localPath));
}

void VirtualFileSystem::unmount(const String& mount_point) {
	auto it = mountPoints.find(mount_point);
	if(it != mountPoints.end()) {
		mountPoints.erase(it);
		return;
	}

	throw IOException("No mount point found for directory '" + mount_point + "'");
}

std::unique_ptr<Directory> VirtualFileSystem::getDirectory(const String& dir) const {
	String ndir = normalizePath(dir);
	auto components = string::tokenize(ndir, directory_separator, false, false, true);
	if(components.empty() || components.front() != "/")
		components.insert(components.begin(), "/");

	ndir.clear();

	std::vector<String> mount_points_to_check;

	for(auto& c : components) {
		ndir += c;
		if(c != directory_separator || mount_points_to_check.empty())
			mount_points_to_check.push_back(ndir);
	}

	for(auto it = mount_points_to_check.rbegin(); it != mount_points_to_check.rend(); ++it) {
		auto mountIt = mountPoints.find(*it);
		if(mountIt != mountPoints.end()) { // Found
			ndir.erase(0, mountIt->first.length()); // Cut the found part of the path
			return mountIt->second->getDirectory(ndir);
		}
	}

	throw IOException("No mount point found for directory '" + dir + "'");

}

std::unique_ptr<File> VirtualFileSystem::getFile(const String& path) const {
	String ndir = normalizePath(path);
	auto pos = ndir.find_last_of(directory_separator);
	auto dn = ndir.substr(0,pos);
	auto dir = getDirectory(dn);
	auto filename = path.substr(pos+1);
	return dir->getFile(filename);
}

String VirtualFileSystem::normalizePath(const String& path) {
	// since find_first_of seeks for any char in the given string, we need to make substring checks here
	auto components = string::tokenize(path, directory_separator, true, false, true);

	String r;
	size_t n = 0;
	for(auto it=components.begin(); it != components.end();){

		if((*it == "." || it->empty()) && it != components.begin()) {
			it = components.erase(it);
		}
		else if(n >= 3 && *it == "..") {
			it = components.erase(it-3, it+1);
			++it;
			++n;
		}
		else if(n > 0 && *it == directory_separator && *(it-1) == directory_separator) {
			it = components.erase(it);
		}
		else {
			++it;
			++n;
		}

	}

	for(auto& comp : components) {
		r += comp;
	}

	return r;
}

} /* namespace brew */
