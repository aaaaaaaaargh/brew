/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2017 r.acc
 *
 *  BitmapFontProcessor.cpp
 *
 *  Created on: 28.05.17
 *      Author: void
 */
#include <brew/asset/core/BitmapFontProcessor.h>

#include <brew/asset/AssetManager.h>

#include <brew/video/BitmapFont.h>

namespace brew {

namespace detail {
    std::map<String, String> parseLine(String& line) {
        string::trim(line);
        line += " "; // Adding a space at the and makes parsing much easier.

        String tag = line.substr(0, line.find_first_of(' '));

        std::map<String, String> result;
        String key;

        result["_tag"] = tag;

        u8 state = 0; //< 1 := scan next key, 2 := scan value, 3 := scan quoted value

        SizeT cur = tag.length() + 1;

        while(cur < line.length()) {

            if(cur == 0) {
                break;
            }

            if(state == 0) {
                // Scan the next key
                auto end = line.find('=', cur);
                if (end == String::npos) {
                    break;
                }

                key = line.substr(cur, end - cur);
                string::trim(key);

                cur = end + 1;

                state = 1;
            }
            else {
                // Scan next value
                char endToken = ' ';
                auto start = line.find_first_not_of(' ', cur);

                if(line[start] == '"') {
                    // Found a quote, search for closing quote instead.
                    start += 1;
                    endToken = '"';
                }

                auto end = line.find(endToken, start + 1);

                String value = line.substr(start, end - start + 1);
                string::trim(value, "\"\t ");

                result[key] = value;

                cur = end + 1;

                state = 0;
            }
        }

        return result;
    };
}

void BitmapFontProcessor::load(AssetPipeline& assetPipeline,
                               const VirtualFileSystem& vfs,
                               AssetBundle& bundle,
                               const String& tag,
                               const BitmapFontProcessorParams& params) const {
    auto file = vfs.getFile(tag);
    auto fs = file->open(std::ios::in);

    getAppContext().log->stream("BitmapFontProcessor") << LogLevel::Debug << "Loading '" << tag << "' ...";

    // Get the path.
    auto pathComponents = string::tokenize(tag, VirtualFileSystem::directory_separator, true, false, true);
    pathComponents.pop_back();
    String path = string::join("", pathComponents);

    String line;

    BitmapFont::Definition fontDefinition;
    s32 baseline = 0;
    s32 lineHeight = 0;
    std::map<SizeT, std::shared_ptr<Pixmap> > pixmaps;

    // Parse the lines.
    while (std::getline(*fs.get(), line)) {
        auto values = detail::parseLine(line);
        const String& tag = values["_tag"];

        if(tag == "common") {
            baseline = std::stoi(values["base"]);
            lineHeight = std::stoi(values["lineHeight"]);
        }

        if(tag == "page") {
            String fileName = path + values["file"];
            SizeT id = std::stoul(values["id"]);

            // Load the pixmap.
            assetPipeline.load(fileName, "pixmap").getResult();

            auto pixmap = bundle.get<Pixmap>(fileName);

            pixmaps.insert(
                    std::make_pair(id, pixmap)
            );
        }

        if(tag == "char") {
            wchar_t codepoint = static_cast<wchar_t>(std::stoul(values["id"]));
            SizeT page = std::stoul(values["page"]);

            IntRect bounds(
                    std::stoi(values["x"]),
                    std::stoi(values["y"]),
                    std::stoi(values["width"]),
                    std::stoi(values["height"])
            );

            Font::Glyph glyph;

            glyph.codePoint = codepoint;
            glyph.advance = std::stoi(values["xadvance"]);
            glyph.bearing = 0;
            glyph.ascent = baseline - std::stoi(values["yoffset"]);
            glyph.descent = lineHeight - std::stoi(values["yoffset"]);

            auto pixmap = pixmaps.find(page)->second.get();

            fontDefinition.addGlyph(
                    codepoint,
                    glyph,
                    *pixmap,
                    bounds
            );
        }
    }

    // Create the font
    auto font = std::make_shared<BitmapFont>(fontDefinition);

    bundle.put(tag, font);
}

bool BitmapFontProcessor::canLoad(const AssetPipeline& assetPipeline, const VirtualFileSystem& vfs,
                                  const AssetBundle& bundle, const String& tag,
                                  const BitmapFontProcessorParams& params) const {
    return true;
}

bool BitmapFontProcessor::acceptsType(const String& typeHint) const {
    return typeHint == "font";
}

} /* namespace brew */
