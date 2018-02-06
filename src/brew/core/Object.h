/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 Marcus v. Keil
 *
 *  Created on: 07.09.17
 *
 */

#ifndef BREW_OBJECT_H
#define BREW_OBJECT_H

#include <brew/core/AppContext.h>

#include <memory>

namespace brew {

class Object {
public:
    /**
     * Creates an object with a new app context.
     */
    Object() : appContext(std::make_shared<AppContext>()) {}

    /**
     * Creates an instance from another object.
     * @tparam T The instance type.
     * @tparam Args The construction argument types.
     * @param other The object to create from.
     * @param args The construction arguments.
     * @return The newly created object.
     */
    template <typename T, typename ... Args>
    static std::unique_ptr<T> createFrom(const Object& other, Args && ... args) {
        auto obj = std::make_unique<T>(args...);
        obj->appContext = other.appContext;
        return std::move(obj);
    }

    /**
     * Creates a shared instance from another object.
     * @tparam T The instance type.
     * @tparam Args The construction argument types.
     * @param other The object to create from.
     * @param args The construction arguments.
     * @return The newly created object.
     */
    template <typename T, typename ... Args>
    static std::shared_ptr<T> createSharedFrom(const Object& other, Args && ... args) {
        auto obj = std::make_shared<T>(args...);
        obj->appContext = other.appContext;
        return obj;
    }

public:
    /**
     * Exchanges this objects app context.
     * @param other The object to share the app context from.
     */
    void setAppContextFrom(const Object& other);

    /**
     * @return This objects app context.
     */
    inline const AppContext& getAppContext() const {
        return *appContext;
    }

private:
    std::shared_ptr<AppContext> appContext;
};

} /* namespace brew */

#endif //PROJECT_OBJECT_H
