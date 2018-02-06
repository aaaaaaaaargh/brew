/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 Marcus v. Keil
 *
 *  Created on: Dec 31, 2016
 *
 */

#ifndef BREW_TEXTUREATLAS_H
#define BREW_TEXTUREATLAS_H

#include <brew/video/Texture.h>

#include <map>

namespace brew {

class TextureAtlas {
public:
	void addRegion(const String& name, const TextureRegion& region);

	TextureRegion findRegion(const String& name) const;

	typedef std::map<String, TextureRegion>::const_iterator const_iterator;
	typedef std::map<String, TextureRegion>::iterator iterator;

	inline iterator begin() {
		return textureRegions.begin();
	}

	inline iterator end() {
		return textureRegions.end();
	}

	inline const_iterator cbegin() const {
		return textureRegions.cbegin();
	}

	inline const_iterator cend() const {
		return textureRegions.cend();
	}

private:
	std::map<String, TextureRegion > textureRegions;
};

} /* namespace brew */

#endif //BREW_TEXTUREATLAS_H
