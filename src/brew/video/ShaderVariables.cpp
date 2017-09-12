/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2017 random arts
 *
 *  Created on: 11.09.17
 *
 */

#include <brew/video/ShaderVariables.h>

#include <algorithm>

namespace brew {

ShaderVariablesDefinition::VarDefinition::VarDefinition(const ShaderVariablesDefinition& owner)
        : owner(owner){}

SizeT ShaderVariablesDefinition::VarDefinition::getIndex() const {
    auto it = std::find(owner.orderedLookup.begin(), owner.orderedLookup.end(), name);
    return static_cast<SizeT>(it - owner.orderedLookup.begin());
}

ShaderVariablesDefinition& ShaderVariablesDefinition::define(ShaderVariablesDefinition::VarType type,
                                                             const String& name,
                                                             SizeT numElements) {
    auto orderedLookupIterator = std::find(orderedLookup.begin(), orderedLookup.end(), name);

    if(orderedLookupIterator != orderedLookup.end()) {
        undefine(name);
        orderedLookup.insert(orderedLookupIterator, name);
    } else {
        orderedLookup.push_back(name);
    }

    VarDefinition def(*this);
    def.name = name;
    def.type = type;
    def.numElements = numElements;

    lookup.insert(std::make_pair(name, def));

    return *this;
}

void ShaderVariablesDefinition::undefine(const String& name) {
    auto it = lookup.find(name);

    if(it == lookup.end()) {
        throw NotFoundException("No such variable '" + name + "'.");
    }

    auto orderedIt = std::find(orderedLookup.begin(), orderedLookup.end(), name);
    orderedLookup.erase(orderedIt);

    lookup.erase(it);
}

const ShaderVariablesDefinition::VarDefinition& ShaderVariablesDefinition::getDefinition(const String& name) const {
    auto it = lookup.find(name);

    if(it == lookup.end()) {
        throw NotFoundException("No such variable '" + name + "'.");
    }

    return it->second;
}

ShaderVariablesDefinition::const_iterator ShaderVariablesDefinition::begin() const {
    return const_iterator(*this, orderedLookup.begin());
}

ShaderVariablesDefinition::const_iterator ShaderVariablesDefinition::end() const {
    return const_iterator(*this, orderedLookup.end());
}

ShaderVariablesDefinition::const_iterator::const_iterator(const ShaderVariablesDefinition& owner,
                                                          std::vector<String>::const_iterator orderedIterator)
: owner(owner), orderedIterator(orderedIterator) {}

ShaderVariablesDefinition::const_iterator::element_type ShaderVariablesDefinition::const_iterator::operator*() const {
    return owner.getDefinition(*orderedIterator);
}

ShaderVariablesDefinition::const_iterator& ShaderVariablesDefinition::const_iterator::operator++() {
    ++orderedIterator;
    return *this;
}

ShaderVariablesDefinition::const_iterator& ShaderVariablesDefinition::const_iterator::operator++(int) {
    orderedIterator++;
    return *this;
}


ShaderVariablesDefinition::const_iterator ShaderVariablesDefinition::const_iterator::operator+(SizeT increment) const {
    return const_iterator(owner, orderedIterator+increment);
}

bool ShaderVariablesDefinition::const_iterator::operator==(const ShaderVariablesDefinition::const_iterator& other) const {
    return orderedIterator == other.orderedIterator;
}

bool ShaderVariablesDefinition::const_iterator::operator!=(const ShaderVariablesDefinition::const_iterator& other) const {
    return orderedIterator != other.orderedIterator;
}

template<> ShaderVariablesDefinition::VarType ShaderVariablesDefinition::getType<u8>() {
    return VarType::u8;
}

template<> ShaderVariablesDefinition::VarType ShaderVariablesDefinition::getType<u16>() {
    return VarType::u16;
}

template<> ShaderVariablesDefinition::VarType ShaderVariablesDefinition::getType<u32>() {
    return VarType::u32;
}

template<> ShaderVariablesDefinition::VarType ShaderVariablesDefinition::getType<u64>() {
    return VarType::u64;
}

template<> ShaderVariablesDefinition::VarType ShaderVariablesDefinition::getType<s8>() {
    return VarType::s8;
}

template<> ShaderVariablesDefinition::VarType ShaderVariablesDefinition::getType<s16>() {
    return VarType::s16;
}

template<> ShaderVariablesDefinition::VarType ShaderVariablesDefinition::getType<s32>() {
    return VarType::s32;
}

template<> ShaderVariablesDefinition::VarType ShaderVariablesDefinition::getType<s64>() {
    return VarType::s64;
}

template<> ShaderVariablesDefinition::VarType ShaderVariablesDefinition::getType<Real>() {
    return VarType::Real;
}

template<> ShaderVariablesDefinition::VarType ShaderVariablesDefinition::getType<Vec2>() {
    return VarType::Vec2;
}

template<> ShaderVariablesDefinition::VarType ShaderVariablesDefinition::getType<Vec3>() {
    return VarType::Vec3;
}

template<> ShaderVariablesDefinition::VarType ShaderVariablesDefinition::getType<Vec4>() {
    return VarType::Vec4;
}

template<> ShaderVariablesDefinition::VarType ShaderVariablesDefinition::getType<Matrix4>() {
    return VarType::Matrix4;
}

template<> ShaderVariablesDefinition::VarType ShaderVariablesDefinition::getType<Texture>() {
    return VarType::Texture;
}

ShaderVariables::ShaderVariables(const ShaderVariablesDefinition& definition)
: definition(definition) {}

ShaderVariablesUpdateData& ShaderVariablesContextHandle::getShaderVariablesUpdateData(ShaderVariables& shaderVariables) {
    return shaderVariables.updateData;
}

} /* namespace brew */

