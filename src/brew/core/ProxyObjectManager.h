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
#include <iostream>
namespace brew {

/**
 * The abstract proxy base class.
 */
class AbstractProxyObject {};

template<typename ObjectT> class ProxyObject;

/**
 * The abstract proxy object manager base class.
 */
class AbstractProxyObjectManager {
private:
    template<typename ObjectT> friend class ProxyObject;

protected:
    virtual void requestUpdate(std::shared_ptr<AbstractProxyObject> obj) = 0;
};

/**
 * The proxy object base class. Although it is not strongly required, this should be
 * subclassed with a more specialized type that implements the object API.
 * @tparam ObjectT The object type.
 */
template<typename ObjectT>
class ProxyObject : public AbstractProxyObject, public std::enable_shared_from_this<ProxyObject<ObjectT> > {
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
     * @return Whether an update update is requested.
     */
    bool isUpdateRequested() const {
        return updateRequested;
    }

    /**
     * @return The owner of this object.
     */
    AbstractProxyObjectManager& getOwner() const {
        return *manager;
    }

    /**
     * Lockable implementation. Locks the object.
     */
    void lock() {
        mutex.lock();
    }

    /**
     * Lockable implementation. Unlocks the object.
     */
    void unlock() {
        mutex.unlock();
    }

    /**
     * Lockable implementation. Attempts to lock the object.
     * @return Whether the object could be locked.
     */
    bool try_lock() {
        return mutex.try_lock();
    }

protected:
    /**
     * Requests an update of the object through the manager.
     * @param force Whether to force to update the object even if it's not ready yet.
     */
    void requestUpdate(bool force = false) {
        if(updateRequested || (!force && !isReady())) {
            return;
        }

        updateRequested = true;

        manager->requestUpdate(this->shared_from_this());
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
    std::mutex mutex;
    AbstractProxyObjectManager* manager;
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
class ProxyObjectManager : public AbstractProxyObjectManager {
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
        obj->manager = this;

        std::lock_guard<std::mutex> lk(objectsToProcessMutex);

        objectsToInitialize.push(obj);

        return obj;
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
                auto proxy = objectsToUpdate.front();

                std::unique_lock<ProxyObject<ObjectT> > lk(*proxy, std::try_to_lock);

                if(lk.owns_lock()) {
                    objectsToUpdate.pop();
                    objectsToProcessMutex.unlock();

                    updateObject(*proxy);

                    proxy->updateRequested = false;
                }
                else {
                    objectsToProcessMutex.unlock();
                }

                return false;
            }

            objectsToProcessMutex.unlock();
            return false;
        }

        auto proxy = objectsToInitialize.front();
        std::unique_lock<ProxyT> lk(*proxy, std::try_to_lock);

        if(lk.owns_lock()) {
            objectsToInitialize.pop();
            objectsToProcessMutex.unlock();

            proxy->object = createObject(*proxy);
            proxy->objectReady = true;
        }
        else {
            objectsToProcessMutex.unlock();
        }

        return true;
    }

    /**
     * Processes all pending proxy objects.
     */
    void processAllObjects() {
        while(processObject());
    }

protected:
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

protected:
    void requestUpdate(std::shared_ptr<AbstractProxyObject> proxyObject) override {
        std::lock_guard<std::mutex> lk(objectsToProcessMutex);

        objectsToUpdate.push(std::static_pointer_cast<ProxyT>(proxyObject));
    }

private:
    std::mutex objectsToProcessMutex;
    std::queue<std::shared_ptr<ProxyT> > objectsToInitialize;
    std::queue<std::shared_ptr<ProxyT> > objectsToUpdate;
};

} /* namespace brew */


#endif //BREW_PROXYOBJECTMANAGER_H
