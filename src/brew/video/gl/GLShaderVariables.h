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

#ifndef BREW_GLSHADERVARIABLES_H
#define BREW_GLSHADERVARIABLES_H

#include <brew/video/ShaderVariables.h>
#include <brew/video/gl/GLObject.h>
#include <brew/video/Texture.h>

namespace brew {

class GLShaderVariablesContextHandle : public ShaderVariablesContextHandle, public GLObject {
public:
    /**
     * Creates a new shader variables context handle.
     * @param context The GL context.
     * @param vars The shader variables to create the handle from.
     */
    GLShaderVariablesContextHandle(GLContext& context, ShaderVariables& vars);

    /**
     * Destructor.
     */
    ~GLShaderVariablesContextHandle();

public:
    /**
     * Creates the source code for the uniform declarations used in the given shader variable set.
     * @param shaderVariables The shader variables.
     * @return The generated source code.
     */
    static String generateUniformDeclarationSource(
            const ShaderVariablesLayout& definition,
            const String& blockName = "shaderVars"
    );

public:
    /**
     * Uploads the variables data block to the GPU memory.
     * @param vars The shader variables.
     * @param performFullSync Whether to sync the whole buffer.
     */
    void syncToGPU(ShaderVariables& vars, bool performFullSync = false);

    /**
     * Binds this buffer.
     */
    void bind();

    /**
     * Unbinds this buffer.
     */
    void unbind();

    /**
     * @return The GL uniform compatible buffer in memory.
     */
    inline const HeapBuffer& getBuffer() const {
        return *buffer;
    }

private:
    struct VariableLayout {
        SizeT offset;
        SizeT blockSize;
    };

    std::map<String, VariableLayout> layout;
    std::unique_ptr<HeapBuffer> buffer;

private:
    void initialize(ShaderVariables& vars);

    static SizeT getTypeSize(const ShaderVariablesLayout::VarDefinition& varDef);

    void writeValue(const ShaderVariablesLayout::VarDefinition& def,
                    ShaderVariablesUpdateData::AbstractValue& value);
};

} /* namespace brew */

#endif //BREW_GLSHADERVARIABLES_H
