/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2017 random arts
 *
 *  Created on: 08.09.17
 *
 */

#include <brew/video/gl/GLShaderVariables.h>
#include <brew/video/gl/GLExtensions.h>
#include <brew/video/gl/GLTexture.h>

namespace brew {

using gl = GL30;

GLShaderVariablesContextHandle::GLShaderVariablesContextHandle(GLContext& context, ShaderVariables& vars)
: GLObject(context) {
    gl::glGenBuffers(1, &glId);

    initialize(vars);

    syncToGPU(vars, true);
}

GLShaderVariablesContextHandle::~GLShaderVariablesContextHandle() {
    gl::glDeleteBuffers(1, &glId);
}

void GLShaderVariablesContextHandle::syncToGPU(ShaderVariables& vars, bool performFullSync) {
    auto& updates = getShaderVariablesUpdateData(vars);
    if(updates.values.empty() && !performFullSync) {
        // Nothing to sync.
        return;
    }

    bind();

    for(auto& value : updates.values) {
        // Copy the updated value to our buffer.
        writeValue(vars.getDefinition().getDefinition(value.first), *value.second);
    }

    if(performFullSync) {
        // Copy the full buffer.
        gl::glBufferData(GL_UNIFORM_BUFFER, buffer->getSize(), buffer->getRawPointer(), GL_DYNAMIC_DRAW);
    }
    else {
        for(auto& value : updates.values) {
            // Copy this part of the buffer.
            VariableLayout& layout = this->layout[value.first];
            gl::glBufferSubData(GL_UNIFORM_BUFFER, layout.offset, layout.blockSize, buffer->getRawPointer() + layout.offset);
        }
    }

    unbind();

    // Clear the update data.
    updates.values.clear();
}

void GLShaderVariablesContextHandle::writeValue(
        const ShaderVariablesLayout::VarDefinition& def,
        ShaderVariablesUpdateData::AbstractValue& value) {

    VariableLayout& layout = this->layout[def.getName()];

    switch(def.getType()) {
        case ShaderVariables::VarType::u8: {
            auto& val = static_cast<const ShaderVariablesUpdateData::Value<u8>&>(value);
            buffer->write(&val.elements[0], layout.offset, val.elements.size());
            break;
        }
        case ShaderVariables::VarType::u16: {
            auto& val = static_cast<const ShaderVariablesUpdateData::Value<u16>&>(value);
            buffer->write(&val.elements[0], layout.offset, val.elements.size());
            break;
        }
        case ShaderVariables::VarType::u32: {
            auto& val = static_cast<const ShaderVariablesUpdateData::Value<u32>&>(value);
            buffer->write(&val.elements[0], layout.offset, val.elements.size());
            break;
        }
        case ShaderVariables::VarType::u64:{
            auto& val = static_cast<const ShaderVariablesUpdateData::Value<u64>&>(value);
            buffer->write(&val.elements[0], layout.offset, val.elements.size());
            break;
        }
        case ShaderVariables::VarType::s8:{
            auto& val = static_cast<const ShaderVariablesUpdateData::Value<s8>&>(value);
            buffer->write(&val.elements[0], layout.offset, val.elements.size());
            break;
        }
        case ShaderVariables::VarType::s16:{
            auto& val = static_cast<const ShaderVariablesUpdateData::Value<s16>&>(value);
            buffer->write(&val.elements[0], layout.offset, val.elements.size());
            break;
        }
        case ShaderVariables::VarType::s32:{
            auto& val = static_cast<const ShaderVariablesUpdateData::Value<s32>&>(value);
            buffer->write(&val.elements[0], layout.offset, val.elements.size());
            break;
        }
        case ShaderVariables::VarType::s64:{
            auto& val = static_cast<const ShaderVariablesUpdateData::Value<s64>&>(value);
            buffer->write(&val.elements[0], layout.offset, val.elements.size());
            break;
        }
        case ShaderVariables::VarType::Real:{
            auto& val = static_cast<const ShaderVariablesUpdateData::Value<Real>&>(value);
            buffer->write(&val.elements[0], layout.offset, val.elements.size());
            break;
        }
        case ShaderVariables::VarType::Vec2:{
            auto& val = static_cast<const ShaderVariablesUpdateData::Value<Vec2>&>(value);
            buffer->write(&val.elements[0], layout.offset, val.elements.size());
            break;
        }
        case ShaderVariables::VarType::Vec3:{
            auto& val = static_cast<const ShaderVariablesUpdateData::Value<Vec3>&>(value);
            buffer->write(&val.elements[0], layout.offset, val.elements.size());
            break;
        }
        case ShaderVariables::VarType::Vec4:{
            auto& val = static_cast<const ShaderVariablesUpdateData::Value<Vec4>&>(value);
            buffer->write(&val.elements[0], layout.offset, val.elements.size());
            break;
        }
        case ShaderVariables::VarType::Matrix4:{
            auto& val = static_cast<const ShaderVariablesUpdateData::Value<Matrix4>&>(value);
            buffer->write(&val.elements[0], layout.offset, val.elements.size());
            break;
        }
        case ShaderVariables::VarType::Texture:{
            auto& val = static_cast<ShaderVariablesUpdateData::Value<Texture>&>(value);
            SizeT i=0;
            for(auto& tex : val.elements) {
                auto& glTex = static_cast<GLTextureContextHandle&>(tex.getContextHandle());
                GLuint id = glTex.getGLId();
                buffer->write(&id, layout.offset, sizeof(GLuint) * i);
                i++;
            }
            break;
        }
    }
}

void GLShaderVariablesContextHandle::bind() {
    gl::glBindBuffer(GL_UNIFORM_BUFFER, glId);
}

void GLShaderVariablesContextHandle::unbind() {
    gl::glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void GLShaderVariablesContextHandle::initialize(ShaderVariables& vars) {
    auto& definition = vars.getDefinition();

    SizeT dataSize = 0;

    layout.clear();

    for(auto& varDef : definition) {
        SizeT typeSize = getTypeSize(varDef);

        VariableLayout layout;
        layout.offset = dataSize;
        layout.blockSize = typeSize * varDef.getNumElements();

        this->layout.insert(std::make_pair(varDef.getName(), layout));

        dataSize += typeSize * varDef.getNumElements();
    }

    buffer = std::make_unique<HeapBuffer>(dataSize);
}

SizeT GLShaderVariablesContextHandle::getTypeSize(const ShaderVariablesLayout::VarDefinition& varDef) {
    SizeT typeSize;

    switch(varDef.getType()) {
        case ShaderVariables::VarType::u8:
            typeSize = sizeof(u8);
            break;
        case ShaderVariables::VarType::u16:
            typeSize = sizeof(u16);
            break;
        case ShaderVariables::VarType::u32:
            typeSize = sizeof(u32);
            break;
        case ShaderVariables::VarType::u64:
            typeSize = sizeof(u64);
            break;

        case ShaderVariables::VarType::s8:
            typeSize = sizeof(s8);
            break;
        case ShaderVariables::VarType::s16:
            typeSize = sizeof(s16);
            break;
        case ShaderVariables::VarType::s32:
            typeSize = sizeof(s32);
            break;
        case ShaderVariables::VarType::s64:
            typeSize = sizeof(s64);
            break;

        case ShaderVariables::VarType::Real:
            typeSize = sizeof(Real);
            break;

        case ShaderVariables::VarType::Vec2:
            typeSize = sizeof(Vec2);
            break;
        case ShaderVariables::VarType::Vec3:
            typeSize = sizeof(Vec3);
            break;
        case ShaderVariables::VarType::Vec4:
            typeSize = sizeof(Vec4);
            break;

        case ShaderVariables::VarType::Matrix4:
            typeSize = sizeof(Matrix4);
            break;

        case ShaderVariables::VarType::Texture:
            typeSize = sizeof(GLuint);
            break;
    }

    return typeSize;
}

String GLShaderVariablesContextHandle::generateUniformDeclarationSource(
        const ShaderVariablesLayout& definition,
        const String& blockName
) {
    StringStream result;
    result << "layout (std140) uniform ";
    result << blockName;
    result << "{";

    for(auto& var : definition) {
        String typeDeclaration;
        SizeT arrayDims = var.getNumElements();

        switch(var.getType()) {
            case ShaderVariables::VarType::u8:
            case ShaderVariables::VarType::u16:
            case ShaderVariables::VarType::u32:
            case ShaderVariables::VarType::u64:
                typeDeclaration = "int";
                break;
            case ShaderVariables::VarType::s8:
            case ShaderVariables::VarType::s16:
            case ShaderVariables::VarType::s32:
            case ShaderVariables::VarType::s64:
                typeDeclaration = "uint";
                break;
            case ShaderVariables::VarType::Real:
                typeDeclaration = "float";
                break;
            case ShaderVariables::VarType::Vec2:
                typeDeclaration = "float";
                arrayDims *= 2;
                break;
            case ShaderVariables::VarType::Vec3:
                typeDeclaration = "float";
                arrayDims *= 3;
                break;
            case ShaderVariables::VarType::Vec4:
                typeDeclaration = "float";
                arrayDims *= 4;
                break;
            case ShaderVariables::VarType::Matrix4:
                typeDeclaration = "float";
                arrayDims *= 16;
                break;
            case ShaderVariables::VarType::Texture:
                typeDeclaration = "sampler2D";
                break;
        }

        StringStream ss;

        ss << typeDeclaration;

        ss << " " << var.getName();

        if(arrayDims > 1) {
            ss << "[" << arrayDims << "]";
        }

        ss << ";";

        result << ss.str();
    }

    result << "};";

    return result.str();
}

} /* namespace brew */
