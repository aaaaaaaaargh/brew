/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: Dec 31, 2016
 *
 */

#include <brew/video/TextureAtlas.h>

namespace brew {

void TextureAtlas::addRegion(const String& name, const TextureRegion& region) {
	textureRegions.insert(std::make_pair(name, region));
}

TextureRegion TextureAtlas::findRegion(const String& name) const {
	auto it = textureRegions.find(name);
	if(it == textureRegions.end()) {
		throw NotFoundException("No such texture region '" + name + "'");
    }

	return it->second;
}

} /* namespace brew */

