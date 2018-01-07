/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: 13.09.17
 *
 */

#include <brew/video/VertexAttributeLayout.h>

namespace brew {

VertexAttributeLayout::VertexAttributeLayout()
        : totalSize(0) {}

SizeT VertexAttributeLayout::getAttributeOffset(const VertexAttribute& attrib, SizeT nth) const {
    auto it = lookup.find(attrib.getHash());

    if(it == lookup.end() || it->second.size() <= nth) {
        throw NotFoundException("No such attribute.");
    }

    const Entry& entry = entries.at(it->second[nth]);

    return entry.offset;
}

} /* namespace brew */
