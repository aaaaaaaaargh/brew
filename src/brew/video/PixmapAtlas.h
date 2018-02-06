/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 Marcus v. Keil
 *
 *  Created on: 27.05.17
 *
 */

#ifndef BREW_PIXMAPATLAS_H
#define BREW_PIXMAPATLAS_H

#include <brew/core/String.h>
#include <brew/core/Exception.h>
#include <brew/core/Rect.h>
#include <brew/video/Pixmap.h>

#include <map>

namespace brew {

/**
 * A class for generating pixmap atlases.
 */
class PixmapAtlas {
public:
    /**
     * Adds a new pixmap to the atlas.
     * @param name The name of the atlas region.
     * @param source The source pixmap.
     * @param bounds The source bounds or Rect::INF to use the whole pixmap.
     * @return this instance for chaining.
     */
    PixmapAtlas& add(const String& name, const Pixmap& source, const IntRect& bounds = IntRect::INF);

public:
    /**
     * Generates the atlas pixmap.
     * @param forcePowerOfTwoDims Whether the generated pixmap should always have width and height that
     *                            are powers of two (4, 16, 32, 64, 128, 256...).
     * @return The generated pixmap.
     */
    const Pixmap& generate(bool forcePowerOfTwoDims = true);

public:
    /**
     * @return The generated pixmap.
     * @throws PixmapAtlasException if the pixmap has not been generated yet.
     */
    const Pixmap& getPixmap() const;

    /**
     * Retrieves a previously defined region.
     * @param regionName The name of the region.
     * @return The region bounds.
     * @throws PixmapAtlasException if the pixmap has not been generated yet.
     * @throws PixmapAtlasException if the region is not defined.
     */
    const IntRect& find(const String& regionName);

private:
    struct RegionDefinition {
        const Pixmap* source;
        IntRect bounds;
    };

    /**
     * Checks if a region is already blocked.
     * @param area The region to test.
     * @param blockedRegions A list of blocked regions.
     * @return IntRect::INF if the region is not blocked or the blocking region.
     */
    static const IntRect& getBlockingRegion(
            const IntRect& region, const std::vector<IntRect>& blockedRegions
    );

    std::map<String, RegionDefinition> regionDefinitions; //< Region definition cache, cleared on generate().

    std::map<String, IntRect> generatedRegions; //< Generated regions lookup.

    std::unique_ptr<Pixmap> result; //< The generated result.

};

} /* namespace brew */

#endif //BREW_PIXMAPATLAS_H
