/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2017 random arts
 *
 *  Created on: 04.09.17
 *
 */
#ifndef BREW_PROXYOBJECTMANAGER_H
#define BREW_PROXYOBJECTMANAGER_H

#include "Exception.h"

#include <memory>
#include <mutex>
#include <queue>

namespace brew {

template<typename ProxyT, typename ObjectT> class ProxyObjectManager;

/**
 * The proxy object base class. Although it is not strongly required, this should be
 * subclassed with a more specialized type that implements the object API.
 * @tparam ObjectT The object type.
 */
template<typename ObjectT>
class ProxyObject {
private:
    typedef ProxyObjectManager<ProxyObject<ObjectT>, ObjectT> ManagerType;

public:
    /**
     * Creates a new proxy object.
     */
    ProxyObject()
            : updateRequested(false), objectReady(false) {

    }

    /**
     * @return The object.
     * @throws IllegalAccessException When called before the object has been created.
     */
    ObjectT& operator* () const {
        if(!isReady()) {
            throw IllegalAccessException("Proxied object not ready.");
        }
        return *object;
    }

    /**
     * @return Whether the object is created.
     */
    bool isReady() const {
        return objectReady;
    }

    /**
     * @return The owner of this object.
     */
    ManagerType& getOwner() const {
        return *manager;
    }

protected:
    /**
     * Requests an update of the object through the manager.
     */
    void requestUpdate() {
        std::lock_guard<std::mutex> lk(manager->objectsToProcessMutex);

        if(updateRequested || !isReady()) {
            return;
        }

        updateRequested = true;
        manager->objectsToUpdate.push(std::ref(*this));
    }

    /**
     * @return The object proxied by this instance.
     */
    ObjectT& getObject() {
        return *object;
    }

private:
    template<typename ManagerProxyT, typename ManagerObjectT> friend class ProxyObjectManager;
    std::unique_ptr<ObjectT> object;
    ManagerType* manager;
    bool updateRequested;
    bool objectReady;
};

/**
 * The proxy object manager implements a proxied factory pattern.
 * Proxy objects are created as representatives for the real resources that are initialized
 * at a later point in time.
 * This way objects may be created from within any thread that are usually very context sensitive
 * (like GPU resources for example).
 * The downside of this technique is that for each object there must be a proxy representative
 * that implements the complete public interface of the object.
 *
 * @tparam ProxyT The proxy object type, should implement the public API of the object.
 * @tparam ObjectT The real object.
 */
template<typename ProxyT, typename ObjectT>
class ProxyObjectManager {
private:
    template<typename ProxyObjectT> friend class ProxyObject;

public:
    /**
     * Allocates a new proxy object.
     * @tparam Args The constructor argument types.
     * @param args The construction arguments.
     * @return The newly created proxy object.
     */
    template<typename ... Args>
    std::shared_ptr<ProxyT> allocateObject(Args&& ... args) {
        auto obj = std::make_shared<ProxyT>(args...);
        obj->manager = reinterpret_cast<ProxyObjectManager<ProxyObject<ObjectT>, ObjectT>*>(this);

        std::lock_guard<std::mutex> lk(objectsToProcessMutex);
        objectsToInitialize.push(obj);

        return std::move(obj);
    }

public:
    /**
     * Processes the next proxy object.
     * @return Whether there are more proxy objects to be processed.
     */
    bool processObject() {
        objectsToProcessMutex.lock();

        if(objectsToInitialize.empty()) {

            if(!objectsToUpdate.empty()) {
                auto& proxy = objectsToUpdate.front();

                updateObject(proxy);

                objectsToUpdate.pop();
                objectsToProcessMutex.unlock();
                return false;
            }

            objectsToProcessMutex.unlock();
            return false;
        }

        auto proxy = objectsToInitialize.front();
        objectsToInitialize.pop();
        objectsToProcessMutex.unlock();

        proxy->object = createObject(*proxy);
        proxy->objectReady = true;

        return true;
    }

    /**
     * Processes all pending proxy objects.
     */
    void processAllObjects() {
        while(processObject());
    }

    /**
     * Creates an object instance for a proxy.
     * @param proxyObject The proxy to create the object for.
     * @return The created object.
     */
    virtual std::unique_ptr<ObjectT> createObject(ProxyT& proxyObject) = 0;

    /**
     * Updates an object of a proxy. If not overridden this will simply create a new object.
     * @param proxyObject The proxy object.
     */
    virtual void updateObject(ProxyT& proxyObject) {
        proxyObject.object = createObject(proxyObject);
    }

private:
    std::mutex objectsToProcessMutex;
    std::queue<std::shared_ptr<ProxyT> > objectsToInitialize;
    std::queue<std::reference_wrapper<ProxyT> > objectsToUpdate;
};

} /* namespace brew */


#endif //BREW_PROXYOBJECTMANAGER_H
