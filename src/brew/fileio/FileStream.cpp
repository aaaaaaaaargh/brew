/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2017 r.acc
 *
 *  FileStream.cpp
 *
 *  Created on: Feb 11, 2016
 *      Author: void
 */

#include "FileStream.h"

namespace brew {

FileStream::FileStream(std::streambuf* streambuf)
: std::istream(streambuf)
{
}

FileStream::~FileStream()
{
	delete(_M_streambuf);
}

SizeT FileStream::getSize() {
	auto o = tellg();
	seekg(0, end);
	auto len = tellg() - o;
	seekg(o, beg);
	return len;
}

} /* namespace brew */
