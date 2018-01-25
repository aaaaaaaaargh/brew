/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: 25.01.18
 *
 */

#ifndef BREW_UIRENDERER_H
#define BREW_UIRENDERER_H

#include <brew/video/Renderable.h>

#include <mutex>
#include <thread>

namespace brew {

template <typename NodeT>
class TreeNodeAccessorContext;

template <typename NodeT>
class TreeNodeAccessor {
public:
    NodeT& createChild() {

    }

    void deleteChild(NodeT& n) {

    }

private:
    friend class TreeNodeAccessorContext<NodeT>;

    std::vector<std::unique_ptr<NodeT> > childrenCreated;
    std::vector<std::unique_ptr<NodeT> > childrenDeleted;
};

template <typename NodeT>
class TreeNodeAccessorContext {
public:
    typedef std::thread::id id_type;
    typedef TreeNodeAccessor<NodeT> TreeNodeAccessorT;

public:
    TreeNodeAccessorContext() : nodeAccessors() {
        this->id = std::this_thread::get_id();
    }

    inline id_type getId() const {
        return id;
    }

    TreeNodeAccessorT& getNodeAccessor(const NodeT& node) {
        // Look for an existing accessor or create a new one.
        return nodeAccessors[std::ref(node)];
    }

private:
    id_type id;
    std::map<std::reference_wrapper<const NodeT>, TreeNodeAccessorT> nodeAccessors;
};

template <typename NodeT>
class TreeNodeAccessorContextProvider {
public:
    typedef TreeNodeAccessorContext<NodeT> TreeNodeAccessorContextT;

public:
    TreeNodeAccessorContextT& getCurrentNodeAccessorContext() {
        return nodeAccessors[std::this_thread::get_id()];
    }

private:
    std::map<typename TreeNodeAccessorContextT::id_type, TreeNodeAccessorContextT> nodeAccessors;
};

template <typename NodeT>
class TreeNode {
public:
    typedef TreeNodeAccessorContextProvider<NodeT> TreeNodeAccessorContextProviderT;

protected:
    explicit TreeNode(TreeNodeAccessorContextProviderT& contextProvider)
    : contextProvider(contextProvider) {

    }

    TreeNodeAccessor<NodeT>& getAccessor() const {
        return contextProvider.getCurrentNodeAccessorContext().getNodeAccessor(*this);
    }

private:
    TreeNodeAccessorContextProviderT& contextProvider;
};

class UINode : public TreeNode<UINode> {
public:
    using TreeNode<UINode>::TreeNode;
};

/*
template<typename NodeT> class MutableTree;

template<typename NodeT>
class MutableTreeNode {
public:
    virtual std::unique_ptr<NodeT> clone() const = 0;

    NodeT& createChild() {
        auto node = std::make_unique<NodeT>();

        if(node->owner) {
            // Already connected.
        }

        node->owner = owner;
        node->parent = this;

        std::lock_guard<std::mutex> lk(mutex);
        children.emplace_back(node);

        return *node;
    }

    void removeChild(NodeT& node) {

    }

    void removeAllChildren() {

    }

private:
    MutableTree<NodeT>* owner = nullptr;

    std::mutex mutex;

    std::vector<std::unique_ptr<NodeT> > children;
    NodeT* parent = nullptr;
};

template<typename NodeT>
class MutableTree {
public:
    MutableTree() {
        rootNode = std::make_unique<NodeT>();
        rootNode->owner = this;
    }

private:
    std::unique_ptr<NodeT> rootNode;
};

class UIElement : public MutableTreeNode<UIElement> {

};

class UITree : public MutableTree<UIElement> {

};*/

class UIRenderer : public RenderableProvider {
public:
    /**
     * Obtains a list of renderables from this provider.
     * @param result An array containing the results.
     */
    void getRenderables(std::list<Renderable>& result) const override;

public:
};

} /* namespace brew */

#endif //BREW_UIRENDERER_H
