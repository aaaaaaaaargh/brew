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

#ifndef BREW_SHADER_H
#define BREW_SHADER_H

#include <brew/core/ProxyObjectManager.h>
#include <brew/core/Exception.h>

namespace brew {

/**
 * A struct of data that is only of one-time use for the allocation of a shader program.
 */
struct ShaderAllocationData {
    std::unique_ptr<String> source;
};

class Shader;

/**
 * The video context handle of a shader. Implementation is driver specific.
 */
class ShaderContextHandle {
protected:
    /**
     * Allows restricted access to the protected allocation data of a shader.
     * @param shader The shader.
     * @return The allocation data.
     */
    static std::unique_ptr<ShaderAllocationData>& getShaderAllocationData(Shader& shader);
};

/**
 * The type a shader.
 */
enum class ShaderType {
    Vertex,
    Fragment,
    Compute,
};

/**
 * An exception indicating a compilation error with a shader.
 */
class ShaderCompileException : public Exception {
public:
    using Exception::Exception;
};

/**
 * A single shader that can be linked to a shader program.
 */
class Shader : public ProxyObject<ShaderContextHandle> {
public:
    /**
     * Constructs a new shader.
     * @param type The shader type.
     */
    Shader(ShaderType type, const String& shaderSource);

private:
    explicit Shader(ShaderType type);

public:
    /**
     * @return The type of the shader.
     */
    inline ShaderType getType() const {
        return type;
    }

private:
    friend class ShaderContextHandle;
    std::unique_ptr<ShaderAllocationData> allocationData;

    ShaderType type;
};

}

#endif //BREW_SHADER_H
