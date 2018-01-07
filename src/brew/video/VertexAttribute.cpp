/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 random arts
 *
 *  Created on: 13.09.17
 *
 */

#include <brew/video/VertexAttribute.h>

#include <functional>

namespace brew {

SizeT VertexAttribute::getNumComponents() const {
    return 1;
}

SizeT VertexAttribute::getComponentSize() const {
    switch(getComponentType()) {
        case ComponentType::Byte: return 1;
        case ComponentType::Float: return 4;
    }
}

SizeT VertexAttribute::getSize() const {
    return getComponentSize() * getNumComponents();
}


VertexAttribute::ComponentType Vec2Attribute::getComponentType() const {
    return ComponentType::Float;
}

SizeT Vec2Attribute::getNumComponents() const {
    return 2;
}

void Vec2Attribute::write(const Vec2& value, AbstractBuffer& buffer, SizeT offset) {
    buffer.write(reinterpret_cast<const Byte*>(&value.x), offset, sizeof(Vec2::value_type)*2);
}

Vec2 Vec2Attribute::read(const AbstractBuffer& buffer, SizeT offset) {
    value_type value;
    buffer.read(reinterpret_cast<Byte*>(&value.x), offset, sizeof(Vec2::value_type)*2);
    return value;
}

VertexAttribute::ComponentType Vec3Attribute::getComponentType() const {
    return ComponentType::Float;
}

SizeT Vec3Attribute::getNumComponents() const {
    return 3;
}

void Vec3Attribute::write(const Vec3& value, AbstractBuffer& buffer, SizeT offset) {
    buffer.write(reinterpret_cast<const Byte*>(&value.x), offset, sizeof(Vec3::value_type)*3);
}

Vec3 Vec3Attribute::read(const AbstractBuffer& buffer, SizeT offset) {
    value_type value;
    buffer.read(reinterpret_cast<Byte*>(&value.x), offset, sizeof(Vec3::value_type)*3);
    return value;
}

VertexAttribute::ComponentType Vec4Attribute::getComponentType() const {
    return ComponentType::Float;
}

SizeT Vec4Attribute::getNumComponents() const {
    return 4;
}

void Vec4Attribute::write(const Vec4& value, AbstractBuffer& buffer, SizeT offset) {
    buffer.write(reinterpret_cast<const Byte*>(&value.x), offset, sizeof(Vec4::value_type)*4);
}

Vec4 Vec4Attribute::read(const AbstractBuffer& buffer, SizeT offset) {
    value_type value;
    buffer.read(reinterpret_cast<Byte*>(&value.x), offset, sizeof(Vec4::value_type)*4);
    return value;
}

VertexAttribute::hash_type PositionAttribute::getHash() const {
    return std::hash<String>{}("position");
}

VertexAttribute::hash_type NormalAttribute::getHash() const {
    return std::hash<String>{}("normal");
}

VertexAttribute::hash_type TexCoordAttribute::getHash() const {
    return std::hash<String>{}("texCoord");
}
} /* namespace brew */
