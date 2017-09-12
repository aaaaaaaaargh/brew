/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2017 r.acc
 *
 *  HeapFileSystem.cpp
 *
 *  Created on: Feb 23, 2016
 *      Author: void
 */

#include <brew/fileio/HeapFileSystem.h>
#include <brew/fileio/VirtualFileSystem.h>

#include <algorithm>

namespace brew {

HeapDirectory::HeapDirectory(const std::map<String, std::vector<Byte> >& initial_heap_data) :
		base(*this), path(".")
{
	for (auto& pair : initial_heap_data)
	{
		String np = VirtualFileSystem::normalizePath("./" + pair.first);
		heap_data.insert(std::make_pair(np, pair.second));
	}
}

HeapDirectory::HeapDirectory(HeapDirectory& base, const String& full_path) :
		base(base), path(full_path)
{

}

std::unique_ptr<Directory> HeapDirectory::getDirectory(const String& dir) const
{
	if (!isDirectory(dir))
		throw IOException("No such heap directory '" + path + VirtualFileSystem::directory_separator + dir + "'");

	String p = VirtualFileSystem::normalizePath(path + VirtualFileSystem::directory_separator + dir);
	return std::make_unique<HeapDirectory>(base, p);
}

std::unique_ptr<File> HeapDirectory::getFile(const String& file) const
{
	if (!exists(file) || isDirectory(file))
		throw IOException("No such heap file '" + path + VirtualFileSystem::directory_separator + file + "'");
	String full_file = VirtualFileSystem::normalizePath(path + VirtualFileSystem::directory_separator + file);
	auto p = base.heap_data.find(full_file);
	if(p == base.heap_data.end())
		throw IOException("No such local file '" + path+ VirtualFileSystem::directory_separator + file + "'");
	return std::make_unique<HeapFile>(p->second);
}
;

std::vector<String> HeapDirectory::getEntries() const
{
	std::vector<String> result;
	for (auto& pair : base.heap_data)
	{
		auto o = pair.first.find(path);
		if (o == 0)
		{
			// Starts with this path ...
			o += path.length();
			SizeT count = 0;
			String n = pair.first.substr(o);
			if(!n.empty() && n.find(VirtualFileSystem::directory_separator) == 0)
				n.erase(0, 1);

			while (o != String::npos)
			{
				o = pair.first.find_first_of(VirtualFileSystem::directory_separator, o + 1);
				count++;
			}

			// ... and does at least have two trailing slashes.
			if (count <= 1)
			{
				// Simple file name
				result.push_back(n);
			}
			else
			{
				// Directory
				n.erase(n.find_first_of(VirtualFileSystem::directory_separator), n.length());
				if (std::find(std::begin(result), std::end(result), n) == result.end()) {
					result.push_back(n);
				}
			}
		}
	}
	return result;
}

bool HeapDirectory::exists(const String& file) const
{
	if(isDirectory(file))
		return true;

	String full_file = VirtualFileSystem::normalizePath(path + VirtualFileSystem::directory_separator + file);
	return base.heap_data.find(full_file) != base.heap_data.end();
}

bool HeapDirectory::isDirectory(const String& file) const
{
	String full_file = VirtualFileSystem::normalizePath(path + VirtualFileSystem::directory_separator + file);

	for (auto& p : base.heap_data)
	{
		if (p.first.find(full_file) == 0) // Starts with file name, could be a directory
		{
			if(p.first.length() == full_file.length())
				return false; // Is a file

			auto o = p.first.find(VirtualFileSystem::directory_separator, full_file.length());
			if(o == full_file.length())
				return true;
			if (o == String::npos)
				return true;

		}

	}
	return false;
}

HeapFile::HeapFile(std::vector<Byte>& buffer) :
		buffer(buffer)
{

}

struct buffer_wrapper : std::stringbuf
{
	explicit buffer_wrapper(std::vector<Byte>& vec) {
		char* beg = reinterpret_cast<char*>(&vec[0]);
		this->setg(beg, beg, beg + vec.size());
	}
};

std::unique_ptr<FileStream> HeapFile::open(const std::ios::openmode& mode) const
{
	return std::make_unique<FileStream>(new buffer_wrapper(buffer));
}

} /* namespace brew */
