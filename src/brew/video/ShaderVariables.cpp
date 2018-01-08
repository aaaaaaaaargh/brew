/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: 11.09.17
 *
 */

#include <brew/video/ShaderVariables.h>

#include <algorithm>

namespace brew {

const String ShaderVariables::BuiltInCombinedCameraMatrix = "combinedCamera";
const String ShaderVariables::BuiltInWorldTransformMatrix = "worldTransform";

ShaderVariablesLayout::VarDefinition::VarDefinition(const ShaderVariablesLayout& owner)
        : owner(owner){}

SizeT ShaderVariablesLayout::VarDefinition::getIndex() const {
    auto it = std::find(owner.orderedLookup.begin(), owner.orderedLookup.end(), name);
    return static_cast<SizeT>(it - owner.orderedLookup.begin());
}

ShaderVariablesLayout::ShaderVariablesLayout(bool registerBuiltInVars) {
    if(registerBuiltInVars) {
        define<Matrix4>(ShaderVariables::BuiltInCombinedCameraMatrix);
        define<Matrix4>(ShaderVariables::BuiltInWorldTransformMatrix);
    }
}

ShaderVariablesLayout& ShaderVariablesLayout::define(ShaderVariablesLayout::VarType type,
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

void ShaderVariablesLayout::undefine(const String& name) {
    auto it = lookup.find(name);

    if(it == lookup.end()) {
        throw NotFoundException("No such variable '" + name + "'.");
    }

    auto orderedIt = std::find(orderedLookup.begin(), orderedLookup.end(), name);
    orderedLookup.erase(orderedIt);

    lookup.erase(it);
}

const ShaderVariablesLayout::VarDefinition& ShaderVariablesLayout::getDefinition(const String& name) const {
    auto it = lookup.find(name);

    if(it == lookup.end()) {
        throw NotFoundException("No such variable '" + name + "'.");
    }

    return it->second;
}

ShaderVariablesLayout::const_iterator ShaderVariablesLayout::begin() const {
    return const_iterator(*this, orderedLookup.begin());
}

ShaderVariablesLayout::const_iterator ShaderVariablesLayout::end() const {
    return const_iterator(*this, orderedLookup.end());
}

ShaderVariablesLayout::const_iterator::const_iterator(const ShaderVariablesLayout& owner,
                                                          std::vector<String>::const_iterator orderedIterator)
: owner(owner), orderedIterator(orderedIterator) {}

ShaderVariablesLayout::const_iterator::element_type ShaderVariablesLayout::const_iterator::operator*() const {
    return owner.getDefinition(*orderedIterator);
}

ShaderVariablesLayout::const_iterator& ShaderVariablesLayout::const_iterator::operator++() {
    ++orderedIterator;
    return *this;
}

ShaderVariablesLayout::const_iterator& ShaderVariablesLayout::const_iterator::operator++(int) {
    orderedIterator++;
    return *this;
}


ShaderVariablesLayout::const_iterator ShaderVariablesLayout::const_iterator::operator+(SizeT increment) const {
    return const_iterator(owner, orderedIterator+increment);
}

bool ShaderVariablesLayout::const_iterator::operator==(const ShaderVariablesLayout::const_iterator& other) const {
    return orderedIterator == other.orderedIterator;
}

bool ShaderVariablesLayout::const_iterator::operator!=(const ShaderVariablesLayout::const_iterator& other) const {
    return orderedIterator != other.orderedIterator;
}

template<> ShaderVariablesLayout::VarType ShaderVariablesLayout::getType<u8>() {
    return VarType::u8;
}

template<> ShaderVariablesLayout::VarType ShaderVariablesLayout::getType<u16>() {
    return VarType::u16;
}

template<> ShaderVariablesLayout::VarType ShaderVariablesLayout::getType<u32>() {
    return VarType::u32;
}

template<> ShaderVariablesLayout::VarType ShaderVariablesLayout::getType<u64>() {
    return VarType::u64;
}

template<> ShaderVariablesLayout::VarType ShaderVariablesLayout::getType<s8>() {
    return VarType::s8;
}

template<> ShaderVariablesLayout::VarType ShaderVariablesLayout::getType<s16>() {
    return VarType::s16;
}

template<> ShaderVariablesLayout::VarType ShaderVariablesLayout::getType<s32>() {
    return VarType::s32;
}

template<> ShaderVariablesLayout::VarType ShaderVariablesLayout::getType<s64>() {
    return VarType::s64;
}

template<> ShaderVariablesLayout::VarType ShaderVariablesLayout::getType<Real>() {
    return VarType::Real;
}

template<> ShaderVariablesLayout::VarType ShaderVariablesLayout::getType<Vec2>() {
    return VarType::Vec2;
}

template<> ShaderVariablesLayout::VarType ShaderVariablesLayout::getType<Vec3>() {
    return VarType::Vec3;
}

template<> ShaderVariablesLayout::VarType ShaderVariablesLayout::getType<Vec4>() {
    return VarType::Vec4;
}

template<> ShaderVariablesLayout::VarType ShaderVariablesLayout::getType<Matrix4>() {
    return VarType::Matrix4;
}

template<> ShaderVariablesLayout::VarType ShaderVariablesLayout::getType<std::shared_ptr<Texture> >() {
    return VarType::Texture;
}

ShaderVariables::ShaderVariables(const ShaderVariablesLayout& definition)
: definition(definition) {}

ShaderVariablesUpdateData& ShaderVariablesContextHandle::getShaderVariablesUpdateData(ShaderVariables& shaderVariables) {
    return shaderVariables.updateData;
}

} /* namespace brew */

