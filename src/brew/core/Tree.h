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

#ifndef BREW_TREE_H
#define BREW_TREE_H

#include <brew/core/Types.h>

#include <map>
#include <thread>
#include <set>
#include <mutex>

namespace brew {

template <typename NodeT>
class TreeNodeAccessorContext;

template <typename NodeT>
class Tree;

template<typename NodeT>
class TreeNodeAccessor;

template<typename NodeT>
class TreeNode;

template <typename NodeT>
class TreeNodeIterator {
private:
    typedef std::vector<std::unique_ptr<TreeNode<NodeT> > > vector_type;

public:
    TreeNodeIterator(typename vector_type::iterator currentIterator,
                     vector_type& current,
                     vector_type* next,
                     const TreeNodeAccessor<NodeT>& owner
    )
    : currentIterator(currentIterator), current(&current), next(next), owner(owner) {
        update();
    }

public:
    inline bool operator == (const TreeNodeIterator<NodeT> other) const {
        if(!this->current && !other.current) {
            // Special case. Both vectors were empty. Counts as a match.
            return true;
        }

        if(this->current == other.current && currentIterator == other.currentIterator) {
            // In the same vector and the same iterator. Match.
            return true;
        }

        // Mismatch.
        return false;
    }

    inline bool operator != (const TreeNodeIterator<NodeT> other) const {
        return !operator==(other);
    }

    TreeNodeIterator<NodeT>& operator++ () {
        currentIterator++;

        update();

        return *this;
    }

    NodeT& operator* () {
        return static_cast<NodeT&>(**currentIterator);
    }

private:
    void update() {
        if(current && currentIterator == current->end()) {
            // Enter next if possible.
            if(next && !next->empty()) {
                current = next;
                currentIterator = next->begin();
            } else {
                current = nullptr;
            }
            next = nullptr;
        }

        if(current && currentIterator != current->end()) {
            // Skip deleted nodes.
            auto& node = **currentIterator;

            if(owner.childrenDeleted.find(&node) != owner.childrenDeleted.end()) {
                // Skip this.
                currentIterator++;
                update();
            }
        }
    }

private:
    typename vector_type::iterator currentIterator;
    vector_type* current;
    vector_type* next;
    const TreeNodeAccessor<NodeT>& owner;
};

template <typename NodeT>
class TreeChildNodeSet {
public:
    TreeChildNodeSet(TreeNodeAccessor<NodeT>& accessor)
    : owner(accessor) {

    }

    SizeT size() const {
        SizeT result = 0;

        for(auto it = begin(); it != end(); ++it) {
            result++;
        }

        return result;
    }

    TreeNodeIterator<NodeT> begin() const {
        return TreeNodeIterator<NodeT>(
                owner.node.children.begin(),
                owner.node.children,
                &owner.childrenCreated,
                owner
        );
    }

    TreeNodeIterator<NodeT> end() const {
        return TreeNodeIterator<NodeT>(
                owner.childrenCreated.end(),
                owner.childrenCreated,
                nullptr,
                owner
        );
    }

private:
    TreeNodeAccessor<NodeT>& owner;
};

template<typename NodeT>
class TreeNodeAccessor {
public:
    TreeNodeAccessor(TreeNode<NodeT>& node)
    : node(node), childSet(*this) {
    }

    TreeNode<NodeT>& createChild() {
        auto node = std::make_unique<NodeT>();
        childrenCreated.emplace_back(std::move(node));
        return *childrenCreated.back();
    }

    void deleteChild(TreeNode<NodeT>& n) {
        auto it = std::find_if(childrenCreated.begin(), childrenCreated.end(), [&] (const std::unique_ptr<TreeNode<NodeT> >& ptr) {
            return ptr.get() == &n;
        });

        if(it != childrenCreated.end()) {
            // The child was just created, remove again.
            childrenCreated.erase(it);
        }

        childrenDeleted.insert(&n);
    }

    const TreeChildNodeSet<NodeT>& getChildren() const {
        return childSet;
    }

private:
    friend class Tree<NodeT>;
    friend class TreeNodeAccessorContext<NodeT>;
    friend class TreeChildNodeSet<NodeT>;
    friend class TreeNodeIterator<NodeT>;

    TreeNode<NodeT>& node;
    std::vector <std::unique_ptr<TreeNode<NodeT> > > childrenCreated;
    std::set <TreeNode<NodeT>* > childrenDeleted;
    TreeChildNodeSet<NodeT> childSet;
};

template<typename NodeT>
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

    TreeNodeAccessorT& getNodeAccessor(const TreeNode<NodeT>& node) {
        // Look for an existing accessor or create a new one.
        auto it = nodeAccessors.find(&node);

        if(it == nodeAccessors.end()) {
            nodeAccessors.emplace(std::make_pair(&node, std::make_unique<TreeNodeAccessorT>(const_cast<TreeNode<NodeT>&>(node))));

            it = nodeAccessors.find(&node);
        }

        return *it->second;
    }

private:
    friend class Tree<NodeT>;

    id_type id;
    std::map <const TreeNode<NodeT>*, std::unique_ptr<TreeNodeAccessorT> > nodeAccessors;
};

template<typename NodeT>
class TreeNodeAccessorContextProvider {
public:
    typedef TreeNodeAccessorContext<NodeT> TreeNodeAccessorContextT;

public:
    TreeNodeAccessorContextT& getCurrentNodeAccessorContext() {
        std::lock_guard<std::mutex> lk(mutex);
        return nodeAccessors[std::this_thread::get_id()];
    }

private:
    friend class Tree<NodeT>;
    std::map<typename TreeNodeAccessorContextT::id_type, TreeNodeAccessorContextT> nodeAccessors;
    std::mutex mutex;
};

template<typename NodeT>
class TreeNode {
private:
    typedef TreeNodeAccessorContextProvider<NodeT> TreeNodeAccessorContextProviderT;


public:
    inline const TreeChildNodeSet<NodeT>& getChildren() const {
        auto& a = getAccessor();
        return getAccessor().getChildren();
    }

    NodeT& createChild() {
        return static_cast<NodeT&>(getAccessor().createChild());
    }

    void deleteChild(NodeT& node) {
        getAccessor().deleteChild(node);
    }

protected:
    TreeNodeAccessor<NodeT>& getAccessor() {
        return contextProvider->getCurrentNodeAccessorContext().getNodeAccessor(*this);
    }

    const TreeNodeAccessor<NodeT>& getAccessor() const {
        return contextProvider->getCurrentNodeAccessorContext().getNodeAccessor(*this);
    }

private:
    friend class Tree<NodeT>;
    friend class TreeChildNodeSet<NodeT>;
    TreeNodeAccessorContextProviderT* contextProvider;

    std::vector<std::unique_ptr<TreeNode<NodeT> > > children;
};

template <typename NodeT>
class Tree {
public:
    Tree() {
        rootNode = std::make_unique<NodeT>();
        rootNode->contextProvider = &contextProvider;
    }

    NodeT& getRootNode() {
        return *rootNode;
    }

public:
    void commit() {
        for(auto& entry : contextProvider.nodeAccessors) {

            TreeNodeAccessorContext<NodeT>& accessorContext = entry.second;

            for(auto& contextEntry : accessorContext.nodeAccessors) {
                TreeNodeAccessor<NodeT>& accessor = *contextEntry.second;
                TreeNode<NodeT>& node = accessor.node;

                // Delete existing nodes.
                for(auto& nodeToDelete : accessor.childrenDeleted) {
                    auto it = std::find_if(node.children.begin(), node.children.end(), [&] (std::unique_ptr<TreeNode<NodeT> >& child) {
                       return child.get() == nodeToDelete;
                    });

                    if(it != node.children.end()) {
                        // Found the node, erase it.
                        node.children.erase(it);
                    }
                }

                // Add the new nodes.
                for(auto& newNode : accessor.childrenCreated) {
                    node.children.emplace_back(std::move(newNode));
                }
            }
        }

        // Clear the node accessors.
        contextProvider.nodeAccessors.clear();
    }

private:
    TreeNodeAccessorContextProvider<NodeT> contextProvider;
    std::unique_ptr<NodeT> rootNode;
};

} /* namespace brew */

#endif // BREW_TREE_H