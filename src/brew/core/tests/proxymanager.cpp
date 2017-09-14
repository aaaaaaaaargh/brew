#include <gtest/gtest.h>

#include <brew/core/ProxyObjectManager.h>

using namespace brew;

class FooObject {
public:
    SizeT objectValue = 0;
};

class Bar {
public:
    SizeT bar = 0;
};

class FooProxy : public ProxyObject<FooObject>, public Bar {
public:
    SizeT proxyValue = 0;
    SizeT* proxyDroppedCount = nullptr;

public:
    ~FooProxy() {
        if(proxyDroppedCount) {
            (*proxyDroppedCount)++;
        }
    }

public:
    void requestUpdate(bool force) {
        ProxyObject::requestUpdate(force);
        bar = 1234;
    }
};

class FooManager : public ProxyObjectManager<FooProxy, FooObject> {
public:
    std::shared_ptr<FooProxy> createOne() {
        auto proxy = std::move(allocateObject());
        proxy->proxyValue = 12345;
        return proxy;
    }

protected:
    std::unique_ptr<FooObject> createObject(FooProxy& proxyObject) override {
        auto object = std::make_unique<FooObject>();
        object->objectValue = proxyObject.proxyValue;
        return std::move(object);
    }

    void updateObject(FooProxy& proxyObject) override {

    }
};

TEST(ProxyManager, CorrectObjectReadyState) {
	FooManager manager;

    auto proxy = manager.createOne();

    EXPECT_FALSE(proxy->isReady());
    EXPECT_THROW(proxy->operator*(), IllegalAccessException);

    manager.processObject();

    EXPECT_TRUE(proxy->isReady());
    EXPECT_NO_THROW(proxy->operator*());
}

TEST(ProxyManager, ObjectInitialization) {
    FooManager manager;

    auto proxy = manager.createOne();

    manager.processObject();

    FooObject& obj = **proxy;

    EXPECT_EQ(12345, proxy->proxyValue);
    EXPECT_EQ(proxy->proxyValue, obj.objectValue);
}

TEST(ProxyManager, ProcessAllObjects) {
    FooManager manager;

    std::vector<std::shared_ptr<FooProxy> > proxies;

    for(SizeT i=0; i<100; ++i) {
        proxies.push_back( manager.createOne() );
    }

    manager.processAllObjects();

    for(SizeT i=0; i<100; ++i) {
        EXPECT_EQ(proxies[i]->proxyValue, (**proxies[i]).objectValue);
    }
}

TEST(ProxyManager, DropProxies) {
    FooManager manager;

    std::vector<std::shared_ptr<FooProxy> > proxies;

    SizeT proxyDroppedCount = 0;

    for(SizeT i=0; i<100; ++i) {
        proxies.push_back( manager.createOne() );
        proxies.back()->proxyDroppedCount = &proxyDroppedCount;
    }

    proxies.clear();

    EXPECT_EQ(0, proxyDroppedCount);

    manager.processObject();

    EXPECT_EQ(1, proxyDroppedCount);

    manager.processAllObjects();

    EXPECT_EQ(100, proxyDroppedCount);
}

TEST(ProxyManager, UpdateProxy) {
    FooManager manager;

    auto proxy = manager.createOne();

    proxy->requestUpdate(true);

    manager.processObject();

    EXPECT_TRUE(proxy->isReady());
    EXPECT_NO_THROW(proxy->operator*());
    EXPECT_EQ(1234, proxy->bar);
}

