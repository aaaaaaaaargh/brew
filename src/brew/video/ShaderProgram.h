/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: 03.01.18
 *
 */

#ifndef PROJECT_SHADERPROGRAM_H
#define PROJECT_SHADERPROGRAM_H

#include <brew/core/ProxyObjectManager.h>
#include <brew/video/Shader.h>
#include <brew/video/VideoContextObject.h>

namespace brew {

/**
 * A struct of data that is only of one-time use for the allocation of a shader program.
 */
struct ShaderProgramAllocationData {
    std::vector<
            std::shared_ptr<Shader>
    > shaders;
};

class ShaderProgram;

/**
 * The video context handle of a shader program. Implementation is driver specific.
 */
class ShaderProgramContextHandle {
protected:
    /**
     * Allows restricted access to the protected allocation data of a shader program.
     * @param shaderProgram The shader program.
     * @return The allocation data.
     */
    static std::unique_ptr<ShaderProgramAllocationData>& getShaderProgramAllocationData(ShaderProgram& shaderProgram);
};

/**
 * A shader program that can be linked from multiple compiled shaders.
 */
class ShaderProgram : public ProxyObject<ShaderProgramContextHandle>, public VideoContextObject {
public:
    ShaderProgram(std::initializer_list<std::shared_ptr<Shader> > shaders);

private:
    friend class ShaderProgramContextHandle;
    std::unique_ptr<ShaderProgramAllocationData> allocationData;
};

}

#endif //PROJECT_SHADERPROGRAM_H
