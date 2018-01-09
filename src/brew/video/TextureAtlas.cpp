/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2017 r.acc
 *
 *  TextureAtlas.cpp
 *
 *  Created on: Dec 31, 2016
 *      Author: void
 */

#include <brew/video/TextureAtlas.h>

namespace brew {
namespace video {

TextureAtlas::TextureAtlas() {
	// TODO Auto-generated constructor stub

}

TextureAtlas::~TextureAtlas() {
	// TODO Auto-generated destructor stub
}

void TextureAtlas::addRegion(const String& name, const Texture2DRegion& region) {
	texture2DRegions.insert(std::make_pair(name, region));
}

Texture2DRegion TextureAtlas::findRegion(const String& name) const {
	auto it = texture2DRegions.find(name);
	if(it == texture2DRegions.end())
		BREW_THROW(TextureAtlasException("No such texture region '" + name + "'"));

	return it->second;
}

}
}

