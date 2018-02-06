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

#include <brew/video/PixmapAtlas.h>
#include <brew/core/Exception.h>

#include <algorithm>

namespace brew {

PixmapAtlas& PixmapAtlas::add(const String &name, const Pixmap &source, const IntRect &bounds) {
    result.reset(); // Clear any generated result.
    generatedRegions.clear(); // Clear the generated regions lookup.

    RegionDefinition def = {
            &source,
            bounds
    };

    regionDefinitions.insert(
            std::make_pair(name, def)
    );

    return *this;
}

const Pixmap& PixmapAtlas::generate(bool forcePowerOfTwoDims) {
    result.reset(); // Clear any generated result.
    generatedRegions.clear(); // Clear the generated regions lookup.

    /**
     * Sort the pixmaps by total pixel count, from largest to smallest.
     */
    std::vector<std::pair<String, RegionDefinition> > sortedRegions;

    for(const auto& def : regionDefinitions) {
        sortedRegions.push_back(def);
    }

    if (sortedRegions.empty()) {
        throw IllegalStateException("No atlas regions defined.");
    }

    s32 minWidth = 256;
    s32 minHeight = 0;

    std::sort(sortedRegions.begin(), sortedRegions.end(),
        [&minWidth] (const auto& a, const auto& b) -> bool {
            const s32 aPixels = a.second.bounds.getWidth() * a.second.bounds.getHeight();
            const s32 bPixels = b.second.bounds.getWidth() * b.second.bounds.getHeight();

            // Store the minimum width our atlas pixmap has to provide.
            minWidth = std::max(a.second.bounds.getWidth(), minWidth);

            return aPixels > bPixels;
        }
    );

    // Estimate the result width.
    s32 resultWidth =
            static_cast<s32> (forcePowerOfTwoDims ? std::pow(2, std::ceil(std::log(minWidth) / std::log(2) )) // Next power of two.
                                            : minWidth);
    s32 resultHeight = 0;

    std::vector<IntRect> resultLayout;

    s32 x = 0, y = 0;
    s32 padding = 3;

    // Scanline-iterate over the results and put them into the image.
    for(const auto& defPair : sortedRegions) {
        const RegionDefinition& def = defPair.second;
        const String& codepointAnsi = defPair.first;

        s32 paddedSizeX = def.bounds.getWidth() + 2 * padding;
        s32 paddedSizeY = def.bounds.getHeight() + 2 * padding;

        IntRect paddedRegion(x, y, paddedSizeX, paddedSizeY);

        bool foundFreePosition = true;
        bool first = true;

        while( !foundFreePosition || first ) {
            foundFreePosition = true;
            first = false;

            paddedRegion.setX(x);
            paddedRegion.setY(y);

            const IntRect& blockedRegion = getBlockingRegion(
                    paddedRegion,
                    resultLayout
            );

            if(blockedRegion != IntRect::INF) {
                // This space is already blocked, advance x.
                x = blockedRegion.getRight();
                if (x + paddedSizeX >= resultWidth) {
                    // Next line
                    y++;
                    x = 0;
                }

                foundFreePosition = false;
                continue;
            }

        }

        resultHeight = std::max(resultHeight, y + paddedSizeY);

        // Add the image at (x,y).
        resultLayout.push_back(
                paddedRegion
        );

        generatedRegions.insert(
                std::make_pair(
                        codepointAnsi,
                        IntRect(
                                x + padding, y + padding,
                                def.bounds.getWidth(), def.bounds.getHeight()
                        )
                )
        );
    }

    // Force power of two height.
    resultHeight = static_cast<s32> (forcePowerOfTwoDims ? std::pow(2, std::ceil(std::log(resultHeight) / std::log(2) )) // Next power of two.
                                          : resultHeight);

    // Finally, create the image.
    result = std::make_unique<Pixmap>(
            static_cast<SizeT>(resultWidth),
            static_cast<SizeT>(resultHeight)
    );

    for(SizeT i=0; i < resultLayout.size(); ++i) {
        const IntRect& target = resultLayout[i];
        const IntRect& source = sortedRegions[i].second.bounds;
        const Pixmap& sourcePixmap = *sortedRegions[i].second.source;

        const s32 sourceOffsetX = source.getLeft();
        const s32 sourceOffsetY = source.getTop();

        const s32 targetOffsetX = target.getLeft() + padding;
        const s32 targetOffsetY = target.getTop() + padding;

        sourcePixmap.blit(*result.get(),
            targetOffsetX, targetOffsetY, sourceOffsetX, sourceOffsetY, source.getWidth(), source.getHeight()
        );
    }

    if(!result) {
        throw RuntimeException("Unable to generate pixmap atlas result.");
    }

    return *result.get();
}

const Pixmap& PixmapAtlas::getPixmap() const {
    if(!result) {
        throw IllegalStateException("Atlas has not been generated.");
    }

    return *result.get();
}

const IntRect& PixmapAtlas::find(const String& regionName) {
    if(!result) {
        throw IllegalStateException("Atlas has not been generated.");
    }

    auto iterator = generatedRegions.find(regionName);

    if(iterator == generatedRegions.end()) {
        throw NotFoundException("No such region.");
    }

    return iterator->second;
}

const IntRect& PixmapAtlas::getBlockingRegion(const IntRect& area, const std::vector<IntRect>& blockedRegions) {
    s32 x2 = area.getRight();
    s32 y2 = area.getBottom();

    for(s32 y = area.getTop(); y < y2; ++y) {
        for (s32 x = area.getLeft(); x < x2; ++x) {
            for (const auto& blockedRegion : blockedRegions) {
                if(blockedRegion.contains(x,y)) {
                    return blockedRegion;
                }
            }
        }
    }

    return IntRect::INF;
}

} /* namespace brew */