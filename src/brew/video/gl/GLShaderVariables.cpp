/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: 08.09.17
 *
 */

#include <brew/video/gl/GLShaderVariables.h>
#include <brew/video/gl/GLShaderProgram.h>
#include <brew/video/gl/GLExtensions.h>
#include <brew/video/gl/GLTexture.h>
#include <cstring>

namespace brew {

using gl = GL30;

GLShaderVariablesContextHandle::GLShaderVariablesContextHandle(GLContext& context, ShaderVariables& vars)
: GLObject(context) {
    gl::glGenBuffers(1, &glId);

    initialize(vars);

    // Allocate the buffer on the GPU.
    gl::glBindBuffer(GL_UNIFORM_BUFFER, glId);
    gl::glBufferData(GL_UNIFORM_BUFFER, buffer->getSize(), nullptr, GL_DYNAMIC_DRAW);
    gl::glBindBuffer(GL_UNIFORM_BUFFER, 0);

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

    gl::glBindBuffer(GL_UNIFORM_BUFFER, glId);

    for(auto& value : updates.values) {
        // Copy the updated value to our buffer.
        writeValue(vars.getDefinition().getDefinition(value.first), *value.second);
    }

    if(performFullSync) {
        // Copy the full buffer.

        // Map the buffer to the host memory.
        void* mappedBufferStorage = gl::glMapBufferRange(GL_UNIFORM_BUFFER, 0, buffer->getSize(), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
        std::memcpy(mappedBufferStorage, buffer->getRawPointer(), buffer->getSize());
        gl::glUnmapBuffer(GL_UNIFORM_BUFFER);
    }
    else {
        for(auto& value : updates.values) {
            // Copy this part of the buffer.
            VariableLayout& layout = this->layout[value.first];

            if(layout.blockSize == 0) {
                // Textures are stored outside of the buffer so their block size is zero.
                continue;
            }

            //gl::glBufferSubData(GL_UNIFORM_BUFFER, layout.offset, layout.blockSize, buffer->getRawPointer() + layout.offset);

            void* mappedBufferStorage = gl::glMapBufferRange(GL_UNIFORM_BUFFER, layout.offset, layout.blockSize, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);
            std::memcpy(mappedBufferStorage, buffer->getRawPointer() + layout.offset, layout.blockSize);
            gl::glUnmapBuffer(GL_UNIFORM_BUFFER);

            /*if(mappedBufferStorage) {
                // Copy to host mapped area.
                std::memcpy(mappedBufferStorage + layout.offset, buffer->getRawPointer() + layout.offset, layout.blockSize);
            } else {

            }*/
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
            auto& val = static_cast<ShaderVariablesUpdateData::Value<std::shared_ptr<Texture> >&>(value);

            boundTextures[def.getName()] = val.elements;
            auto& ids = boundTextureIds[def.getName()];
            ids.clear();

            // Keep track of the GL ids.
            for(auto& tex : val.elements) {
                auto& glTex = static_cast<GLTextureContextHandle&>(tex->getContextHandle());
                GLuint id = glTex.getGLId();
                ids.push_back(id);
            }
            break;
        }
    }
}

void GLShaderVariablesContextHandle::bind(const GLShaderProgramContextHandle& shaderProgram) {
    gl::glBindBuffer(GL_UNIFORM_BUFFER, glId);

    u8 textureUnit = 0;

    for(auto& name : boundTextureNames) {
        std::vector<GLint> activeTextureUnits;

        for(auto& tex : boundTextures[name]) {
            auto& glTex = static_cast<GLTextureContextHandle&>(tex->getContextHandle());
            glTex.bind(textureUnit);
            activeTextureUnits.push_back(textureUnit++);
        }

        auto& ids = boundTextureIds[name];

        auto locationIterator = uniformLookup.find(name);
        if(locationIterator == uniformLookup.end()) {
            auto loc = gl::glGetUniformLocation(shaderProgram.getGLId(), name.c_str());

            uniformLookup.insert(std::make_pair(name, loc));
            locationIterator = uniformLookup.find(name);
        }

        auto location = locationIterator->second;

        gl::glUniform1iv(location, ids.size(), &activeTextureUnits[0]);
    }
}

void GLShaderVariablesContextHandle::unbind() {
    gl::glBindBuffer(GL_UNIFORM_BUFFER, 0);

    u8 textureUnit = 0;

    for(auto& name : boundTextureNames) {
        for (auto& tex : boundTextures[name]) {
            GLTextureContextHandle::unbind(getContext(), textureUnit++);
        }
    }
}

void GLShaderVariablesContextHandle::initialize(ShaderVariables& vars) {
    auto& definition = vars.getDefinition();

    SizeT dataSize = 0;

    layout.clear();

    for(auto& varDef : definition) {
        if(varDef.getType() == ShaderVarType::Texture) {
            // Sampler2D is not allowed in uniform blocks, so we need to keep them out of the buffer.
            boundTextureNames.push_back(varDef.getName());
            continue;
        }

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

    StringStream samplers;

    for(auto& var : definition) {
        SizeT arrayDims = var.getNumElements();

        if(var.getType() == ShaderVariables::VarType::Texture) {
            samplers << "uniform sampler2D " << var.getName() << ";";

            if(arrayDims > 1) {
                samplers << "[" << arrayDims << "]";
            }
            continue;
        }

        String typeDeclaration;

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
                typeDeclaration = "vec2";
                break;
            case ShaderVariables::VarType::Vec3:
                typeDeclaration = "vec3";
                break;
            case ShaderVariables::VarType::Vec4:
                typeDeclaration = "vec4";
                break;
            case ShaderVariables::VarType::Matrix4:
                typeDeclaration = "mat4";
                break;
            default:
                throw NotSupportedException("Unsupported shader variable type.");
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
    result << samplers.str();

    return result.str();
}

} /* namespace brew */
