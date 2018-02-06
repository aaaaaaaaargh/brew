/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 Marcus v. Keil
 *
 *  Created on: 03.01.18
 *
 */

#include <brew/video/Shader.h>

namespace brew {

std::unique_ptr<ShaderAllocationData>& ShaderContextHandle::getShaderAllocationData(Shader& shader) {
    return shader.allocationData;
}

Shader::Shader(ShaderType type) :
        type(type),
        allocationData(std::make_unique<ShaderAllocationData>()) {
}

Shader::Shader(ShaderType type, const String& shaderSource)
: Shader(type) {
    allocationData->source = std::make_unique<String>(shaderSource);
}

}


