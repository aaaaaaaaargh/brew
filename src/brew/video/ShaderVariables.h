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

#ifndef BREW_SHADERVARIABLES_H
#define BREW_SHADERVARIABLES_H

#include <brew/core/Types.h>
#include <brew/core/String.h>
#include <brew/core/ProxyObjectManager.h>
#include <brew/math/Vec2.h>
#include <brew/math/Vec3.h>
#include <brew/math/Vec4.h>
#include <brew/math/Matrix4.h>
#include <brew/video/Texture.h>

#include <initializer_list>
#include <map>
#include <vector>
#include <tuple>

namespace brew {

/**
 * The ShadersVariablesDefinition class is required to initialize the shader variables layout before
 * creating them through the driver.
 */
class ShaderVariablesDefinition {
public:
    /**
     * The type of a variable.
     */
    enum class VarType {
        u8, u16, u32, u64,
        s8, s16, s32, s64,
        Real,
        Matrix4,
        Vec2, Vec3, Vec4,
        Texture
    };

    /**
     * This class holds information about defined variables.
     */
    class VarDefinition {
        friend class ShaderVariablesDefinition;
    private:
        explicit VarDefinition(const ShaderVariablesDefinition& owner);

        const ShaderVariablesDefinition& owner;
        VarType type;
        String name;
        SizeT numElements;

    public:
        /**
         * @return The type of the variable.
         */
        inline VarType getType() const {
            return type;
        }

        /**
         * @return The name of the variable.
         */
        inline const String& getName() const {
            return name;
        }

        /**
         * @return The number of elements.
         */
        inline SizeT getNumElements() const {
            return numElements;
        }

        /**
         * @return The definition index of this variable.
         */
        SizeT getIndex() const;
    };

public:
    /**
     * Iterator implementation for shader variable definitions.
     */
    class const_iterator {
    public:
        const_iterator(const ShaderVariablesDefinition& owner, std::vector<String>::const_iterator orderedIterator);

    public:
        typedef const VarDefinition& element_type;

        element_type operator* () const;

        const_iterator& operator++ ();
        const_iterator& operator++ (int);

        const_iterator operator+ (SizeT increment) const;

        bool operator == (const const_iterator& other) const;
        bool operator != (const const_iterator& other) const;

    private:
        const ShaderVariablesDefinition& owner;
        std::vector<String>::const_iterator orderedIterator;
    };

    /**
     * @return An iterator to the first variable.
     */
    const_iterator begin() const;

    /**
     * @return An iterator past the last variable.
     */
    const_iterator end() const;

public:
    /**
     * Defines a new array variable.
     * @param type The variable type.
     * @param name The name of the variable.
     * @param numElements The number of array elements or 1 if the variable is not an array.
     * @return This instance for chaining.
     */
    ShaderVariablesDefinition& define(VarType type, const String& name, SizeT numElements=1);

    /**
     * Defines a new array variable.
     * @tparam T The variable type.
     * @param name The name of the variable.
     * @param numElements The number of array elements or 1 if the variable is not an array.
     * @return This instance for chaining.
     * @throws InvalidArgumentException in case the native type is not supported.
     */
    template<typename T>
    ShaderVariablesDefinition& define(const String& name, SizeT numElements=1) {
        return define(getType<T>(), name, numElements);
    }

    /**
     * Undefines a variable.
     * @param name The variable name.
     */
    void undefine(const String& name);

    /**
     * Gets the definition of a variable.
     * @param name The variable name.
     * @return The definition of the variable.
     */
    const VarDefinition& getDefinition(const String& name) const;

public:
    /**
     * Gets a shader variable type for a given native type.
     * @tparam T The native type.
     * @return The shader variable enum type.
     * @throws InvalidArgumentException in case the native type is not supported.
     */
    template<typename T>
    static VarType getType() {
        throw InvalidArgumentException("Incompatible shader variable type.");
    }

private:
    std::vector<String> orderedLookup;
    std::map<String, VarDefinition> lookup;
};

template<> ShaderVariablesDefinition::VarType ShaderVariablesDefinition::getType<u8>();
template<> ShaderVariablesDefinition::VarType ShaderVariablesDefinition::getType<u16>();
template<> ShaderVariablesDefinition::VarType ShaderVariablesDefinition::getType<u32>();
template<> ShaderVariablesDefinition::VarType ShaderVariablesDefinition::getType<u64>();

template<> ShaderVariablesDefinition::VarType ShaderVariablesDefinition::getType<s8>();
template<> ShaderVariablesDefinition::VarType ShaderVariablesDefinition::getType<s16>();
template<> ShaderVariablesDefinition::VarType ShaderVariablesDefinition::getType<s32>();
template<> ShaderVariablesDefinition::VarType ShaderVariablesDefinition::getType<s64>();

template<> ShaderVariablesDefinition::VarType ShaderVariablesDefinition::getType<Real>();

template<> ShaderVariablesDefinition::VarType ShaderVariablesDefinition::getType<Vec2>();
template<> ShaderVariablesDefinition::VarType ShaderVariablesDefinition::getType<Vec3>();
template<> ShaderVariablesDefinition::VarType ShaderVariablesDefinition::getType<Vec4>();

template<> ShaderVariablesDefinition::VarType ShaderVariablesDefinition::getType<Matrix4>();
template<> ShaderVariablesDefinition::VarType ShaderVariablesDefinition::getType<Texture>();

/**
 * A structure containing information about the value changes since the last GPU sync operation.
 */
struct ShaderVariablesUpdateData {
public:
    class AbstractValue {};

    template<typename T>
    class Value : public AbstractValue {
    public:
        std::vector<T> elements;
    };

    std::map<String, std::unique_ptr<AbstractValue> > values;
};

class ShaderVariables;

/**
 *  The video context handle of a shader variables set. Implementation is driver specific.
 */
class ShaderVariablesContextHandle {
protected:
    /**
     * Allows restricted access to the protected update data of a shader variables set.
     * @param shaderVariables The shader variables.
     * @return The update data.
     */
    static ShaderVariablesUpdateData& getShaderVariablesUpdateData(ShaderVariables& shaderVariables);
};

class ShaderVariables : public ProxyObject<ShaderVariablesContextHandle> {
public:
    /**
     * Creates a new shader variables set.
     * @param definition The variables definition.
     */
    explicit ShaderVariables(const ShaderVariablesDefinition& definition);

public:
    typedef ShaderVariablesDefinition::VarType VarType;

    /**
     * Sets a shader variable.
     * @tparam T The variable type.
     * @param name The name of the variable.
     * @param value The new value.
     * @throws InvalidArgumentException if the type of the variable mismatches the defined type.
     */
    template<typename T>
    void set(const String& name, T value) {
        VarType type = ShaderVariablesDefinition::getType<T>();

        const auto& definition = this->definition.getDefinition(name);

        if(definition.getType() != type) {
            throw InvalidArgumentException("Shader variable type mismatch for '" + name + '"');
        }

        if(definition.getNumElements() != 1) {
            throw InvalidArgumentException("Shader variable array size mismatch for '" + name + '"');
        }

        auto vars = std::make_unique<ShaderVariablesUpdateData::Value<T> >();
        vars->elements.push_back(value);

        updateData.values.emplace(std::make_pair(name, std::move(vars)));
        requestUpdate();
    }

    /**
     * Sets a shader variable array.
     * @tparam T The variable type.
     * @param name The name of the variable.
     * @param value The new values.
     * @throws InvalidArgumentException if the type of the variable mismatches the defined type.
     */
    template<typename T>
    void set(const String& name, std::initializer_list<T> values) {
        VarType type = ShaderVariablesDefinition::getType<T>();

        const auto& definition = this->definition.getDefinition(name);

        if(definition.getType() != type) {
            throw InvalidArgumentException("Shader variable type mismatch for '" + name + '"');
        }

        if(definition.getNumElements() != values.size()) {
            throw InvalidArgumentException("Shader variable array size mismatch for '" + name + '"');
        }

        auto vars = std::make_unique<ShaderVariablesUpdateData::Value<T> >();
        vars->elements = values;

        updateData.values.emplace(std::make_pair(name, std::move(vars)));
        requestUpdate();
    }

public:
    /**
     * @return The current pending updates for the next GPU sync operation.
     *         Warning: This method is not thread safe and should only be used for debugging purposes.
     */
    inline const ShaderVariablesUpdateData& getShaderVariableUpdates() const {
        return updateData;
    }

    /**
     * @return The shader variables definition.
     */
    inline const ShaderVariablesDefinition& getDefinition() const {
        return definition;
    }

private:
    ShaderVariablesDefinition definition;

    friend class ShaderVariablesContextHandle;
    ShaderVariablesUpdateData updateData;
};

} /* namespace brew */

#endif //BREW_SHADERVARIABLES_H
