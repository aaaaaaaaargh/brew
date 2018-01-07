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

#ifndef BREW_VERTEXATTRIBUTELAYOUT_H
#define BREW_VERTEXATTRIBUTELAYOUT_H

#include <brew/core/Types.h>
#include <brew/core/Exception.h>
#include <brew/video/VertexAttribute.h>

#include <memory>
#include <vector>
#include <map>

namespace brew {

/**
 * A class for defining attribute layouts of vertex buffers.
 */
class VertexAttributeLayout {
public:
    /**
     * Creates a new vertex attribute layout.
     */
    VertexAttributeLayout();

    /**
     * Adds a new vertex attribute to the layout.
     * @tparam VertexAttributeT The type of the vertex attribute.
     * @return This layout for chaining.
     */
    template<typename VertexAttributeT>
    VertexAttributeLayout& add() {
        Entry e;
        e.attribute = std::make_shared<VertexAttributeT>();
        if(entries.empty()) {
            e.offset = 0;
        }
        else {
            e.offset = entries.back().offset + entries.back().attribute->getSize();
        }

        lookup[e.attribute->getHash()].push_back(entries.size());

        entries.push_back(e);

        totalSize += e.attribute->getSize();

        return *this;
    }

public:
    /**
     * @return The total size of the attribute layout.
     */
    inline SizeT getSize() const {
        return totalSize;
    }

    /**
     * Gets the byte offset of an attribute.
     * @tparam VertexAttributeT The attribute type.
     * @param nth The index if multiple attributes of the same type are defined in the layout.
     * @return The byte offset of the given attribute type.
     * @throws NotFoundException if the attribute type does not exist.
     */
    template<typename VertexAttributeT>
    SizeT getAttributeOffset(SizeT nth = 0) const {
        VertexAttributeT attrib;
        auto it = lookup.find(attrib.getHash());

        if(it == lookup.end() || it->second.size() <= nth) {
            throw NotFoundException("No such attribute.");
        }

        const Entry& entry = entries.at(it->second[nth]);

        return entry.offset;
    }

    /**
     * Gets the byte offset of an attribute.
     * @param attribute The attribute.
     * @param nth The index if multiple attributes of the same type are defined in the layout.
     * @return The byte offset of the given attribute type.
     * @throws NotFoundException if the attribute type does not exist.
     */
    SizeT getAttributeOffset(const VertexAttribute& attribute, SizeT nth = 0) const;

    /**
     * Gets the size of an attribute.
     * @tparam VertexAttributeT The attribute type.
     * @return The size of the attribute.
     */
    template<typename VertexAttributeT>
    SizeT getAttributeSize() const {
        VertexAttributeT attrib;
        return attrib.getSize();
    }

public:
    /**
     * A layout entry.
     */
    struct Entry {
        std::shared_ptr<VertexAttribute> attribute; //< The attribute type of this entry.
        SizeT offset; //< The attribute offset.
    };

    typedef std::vector<Entry>::const_iterator const_iterator;

    inline const_iterator begin() const {
        return entries.begin();
    }

    inline const_iterator end() const {
        return entries.end();
    }

private:
    std::vector<Entry> entries;
    std::map<VertexAttribute::hash_type, std::vector< SizeT > > lookup;
    SizeT totalSize;
};

} /* namespace brew */

#endif //BREW_VERTEXATTRIBUTELAYOUT_H
