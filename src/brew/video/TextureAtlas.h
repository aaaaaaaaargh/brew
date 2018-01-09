/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2017 r.acc
 *
 *  TextureAtlas.h
 *
 *  Created on: Dec 31, 2016
 *      Author: void
 */

#ifndef BREW_TEXTUREATLAS_H_
#define BREW_TEXTUREATLAS_H_

#include <brew/video/Texture.h>

#include <map>

namespace brew {
namespace video {

class TextureAtlasException : public Exception {
	using Exception::Exception;
};

class TextureAtlas {
public:
	TextureAtlas();
	virtual ~TextureAtlas();

	void addRegion(const String& name, const Texture2DRegion& region);

	Texture2DRegion findRegion(const String& name) const;

	typedef std::map<String, Texture2DRegion>::const_iterator const_iterator;
	typedef std::map<String, Texture2DRegion>::iterator iterator;

	inline iterator begin() {
		return texture2DRegions.begin();
	}

	inline iterator end() {
		return texture2DRegions.end();
	}

	inline const_iterator cbegin() const {
		return texture2DRegions.cbegin();
	}

	inline const_iterator cend() const {
		return texture2DRegions.cend();
	}

private:
	std::map<String, Texture2DRegion > texture2DRegions;
};

}
}

#endif /* BREW_TEXTUREATLAS_H_ */
