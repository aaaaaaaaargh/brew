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

#ifndef BREW_GLSHADERVARIABLES_H
#define BREW_GLSHADERVARIABLES_H

#include <brew/video/ShaderVariables.h>
#include <brew/video/gl/GLObject.h>
#include <brew/video/Texture.h>

namespace brew {

class GLShaderProgramContextHandle;

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
            const String& blockName = "vars"
    );

public:
    /**
     * Uploads the variables data block to the GPU memory.
     * @param vars The shader variables.
     * @param performFullSync Whether to sync the whole buffer.
     */
    void syncToGPU(ShaderVariables& vars, bool performFullSync = false);

    /**
     * Binds this buffer to a given shader program.
     * @param shaderProgram The shader program to bind this buffer to.
     */
    void bind(const GLShaderProgramContextHandle& shaderProgram);

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

    std::map<String, std::vector<std::shared_ptr<Texture> > > boundTextures;
    std::map<String, std::vector<GLint> > boundTextureIds;
    std::vector<String> boundTextureNames;

    std::map<String, GLint> uniformLookup;

private:
    void initialize(ShaderVariables& vars);

    static SizeT getTypeSize(const ShaderVariablesLayout::VarDefinition& varDef);

    void writeValue(const ShaderVariablesLayout::VarDefinition& def,
                    ShaderVariablesUpdateData::AbstractValue& value);
};

} /* namespace brew */

#endif //BREW_GLSHADERVARIABLES_H
