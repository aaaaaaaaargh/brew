/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 random arts
 *
 *  Created on: 03.01.18
 *
 */

#include <brew/video/ShaderProgram.h>
#include <set>

namespace brew {

ShaderProgram::ShaderProgram(std::initializer_list<std::shared_ptr<Shader> > shaders) {
    // Make sure we do not link more than one shader for each type.
    std::set<ShaderType> usedTypes;
    for(auto& shader : shaders) {
        if(usedTypes.find(shader->getType()) != usedTypes.end()) {
            throw InvalidArgumentException("Cannot link multiple shaders of the same type.");
        }
        usedTypes.insert(shader->getType());
    }

    usedTypes.clear();

    allocationData = std::make_unique<ShaderProgramAllocationData>();
    allocationData->shaders = shaders;
}

std::unique_ptr<ShaderProgramAllocationData>& ShaderProgramContextHandle::getShaderProgramAllocationData(ShaderProgram& shaderProgram) {
    return shaderProgram.allocationData;
}
}