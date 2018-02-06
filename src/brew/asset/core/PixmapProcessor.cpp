/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 Marcus v. Keil
 *
 *  Created on: 07.01.18
 *
 */

#include <brew/asset/core/PixmapProcessor.h>
#include <brew/video/Color.h>
#include <brew/video/Pixmap.h>
#include <algorithm>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace brew {

/**
 * IO read wrapper for BREW file streams.
 * @param user A pointer to the FileStream.
 * @param data The data to read from.
 * @param size The number of bytes to read.
 * @return The number of bytes read.
 */
int stbi_stream_wrapper_read(void *user, char *data, int size) {
    FileStream* stream = static_cast<FileStream*>(user);
    stream->read(data, size);
    return size;
}

/**
 * IO seekg wrapper for BREW file streams.
 * @param user A pointer to the FileStream.
 * @param n The number of bytes to seek forward.
 */
void stbi_stream_wrapper_skip(void *user, int n) {
    FileStream* stream = static_cast<FileStream*>(user);
    stream->seekg(n, stream->cur);
}

/**
 * IO EOF wrapper for BREW file streams.
 * @param user A pointer to the FileStream.
 * @return Whether the stream has the EOF flag set.
 */
int stbi_stream_wrapper_eof(void *user) {
    FileStream* stream = static_cast<FileStream*>(user);
    return stream->eof();
}

// Define the callbacks.
static const stbi_io_callbacks stbi_stream_wrapper_callbacks = { stbi_stream_wrapper_read, stbi_stream_wrapper_skip, stbi_stream_wrapper_eof };

void PixmapProcessor::load(AssetPipeline& assetPipeline,
                           const VirtualFileSystem& vfs,
                           AssetBundle& bundle,
                           const String& tag,
                           const PixmapProcessorParams& params) const {
    auto file = vfs.getFile(tag);
    auto fs = file->open(std::ios::in);

    getAppContext().log->stream("PixmapProcessor") << LogLevel::Debug << "Loading '" << tag << "' ...";

    int x, y, comp;

    // Try to load the image using our IO wrappers.
    auto result = stbi_load_from_callbacks(&stbi_stream_wrapper_callbacks, static_cast<void*>(fs.get()), &x, &y, &comp, 4);

    if (!result) {
        // Failed to load the image for some reason.
        const char* why = stbi_failure_reason();
        throw RuntimeException(String("Unable to load image: ") + why);
    }

    // Set the color format for our pixmap to match the stb_image conventions.
    ColorFormat fmt = ColorFormat::RGBA8U;

    auto pixmap = std::make_shared<Pixmap>(result, x, y, fmt);

    if(params.invertYAxis) {
        pixmap = std::make_shared<Pixmap>(pixmap->flipped(false, true));
    }

    bundle.put(tag, pixmap);

    // Cleanup.
    stbi_image_free(result);

}

bool PixmapProcessor::canLoad(const AssetPipeline& assetPipeline,
                              const VirtualFileSystem& vfs,
                              const AssetBundle& bundle,
                              const String& tag,
                              const PixmapProcessorParams& params) const {
    std::string ifile = tag;
    std::transform(ifile.begin(), ifile.end(), ifile.begin(), ::tolower);

    String pattern = ".png";

    bool matches = std::mismatch(pattern.rbegin(), pattern.rend(), ifile.rbegin() ).first == pattern.rend();

    if(!matches) {
        return false;
    }

    try {
        vfs.getFile(tag);
    }
    catch(...) {
        // File not found.
        return false;
    }

    return true;
}

bool PixmapProcessor::acceptsType(const String& typeHint) const {
    return typeHint == "pixmap";
}
} /* namespace brew */
