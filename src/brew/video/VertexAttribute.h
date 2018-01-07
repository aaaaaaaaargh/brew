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

#ifndef BREW_VERTEXATTRIBUTE_H
#define BREW_VERTEXATTRIBUTE_H

#include <brew/core/Types.h>
#include <brew/math/Vec2.h>
#include <brew/math/Vec3.h>
#include <brew/math/Vec4.h>
#include <brew/core/AbstractBuffer.h>

namespace brew {

/**
 * The base class for vertex attributes.
 */
class VertexAttribute {
public:
    typedef SizeT hash_type; //< The hash type for vertex attributes.

public:
    /**
     * The type specifiers of a vertex attribute.
     */
    enum class ComponentType {
        Byte,
        Float
    };

    /**
     * @return The hash of this attribute.
     */
    virtual hash_type getHash() const = 0;

    /**
     * @return The component type of this attribute.
     */
    virtual ComponentType getComponentType() const = 0;

    /**
     * @return The number of components this attribute consists of.
     */
    virtual SizeT getNumComponents() const;

    /**
     * @return The byte size of a single component.
     */
    virtual SizeT getComponentSize() const;

    /**
     * @return The total size of the attribute.
     */
    virtual SizeT getSize() const;
};

class VertexBuffer;

class Vec2Attribute: public VertexAttribute {
public:
    typedef Vec2 value_type; //< The value type.

public:
    /**
     * @return The component type of this attribute.
     */
    ComponentType getComponentType() const final;

    /**
     * @return The byte size of a single component.
     */
    SizeT getNumComponents() const final;

    /**
     * Writes the attribute value to a buffer.
     * @param value The value.
     * @param buffer The buffer to write to.
     * @param offset The write offset.
     */
    static void write(const Vec2& value, AbstractBuffer& buffer, SizeT offset);

    /**
     * Reads the attribute value from a buffer.
     * @param buffer The buffer to read from.
     * @param offset The read offset.
     * @return The value.
     */
    static Vec2 read(const AbstractBuffer& buffer, SizeT offset);
};

class Vec3Attribute: public VertexAttribute {
public:
    typedef Vec3 value_type; //< The value type.

public:
    /**
     * @return The component type of this attribute.
     */
    ComponentType getComponentType() const final;

    /**
     * @return The byte size of a single component.
     */
    SizeT getNumComponents() const final;

    /**
     * Writes the attribute value to a buffer.
     * @param value The value.
     * @param buffer The buffer to write to.
     * @param offset The write offset.
     */
    static void write(const Vec3& value, AbstractBuffer& buffer, SizeT offset);

    /**
     * Reads the attribute value from a buffer.
     * @param buffer The buffer to read from.
     * @param offset The read offset.
     * @return The value.
     */
    static Vec3 read(const AbstractBuffer& buffer, SizeT offset);
};

class Vec4Attribute: public VertexAttribute {
public:
    typedef Vec4 value_type; //< The value type.

public:
    /**
     * @return The component type of this attribute.
     */
    ComponentType getComponentType() const final;

    /**
     * @return The byte size of a single component.
     */
    SizeT getNumComponents() const final;

    /**
     * Writes the attribute value to a buffer.
     * @param value The value.
     * @param buffer The buffer to write to.
     * @param offset The write offset.
     */
    static void write(const Vec4& value, AbstractBuffer& buffer, SizeT offset);

    /**
     * Reads the attribute value from a buffer.
     * @param buffer The buffer to read from.
     * @param offset The read offset.
     * @return The value.
     */
    static Vec4 read(const AbstractBuffer& buffer, SizeT offset);
};

class PositionAttribute : public Vec3Attribute {
public:
    /**
     * @return The hash of this attribute.
     */
    hash_type getHash() const final;
};

class NormalAttribute : public Vec3Attribute {
public:
    /**
     * @return The hash of this attribute.
     */
    hash_type getHash() const final;
};

class TexCoordAttribute : public Vec2Attribute {
public:
    /**
     * @return The hash of this attribute.
     */
    hash_type getHash() const final;
};

} /* namespace brew */

#endif //BREW_VERTEXATTRIBUTE_H
