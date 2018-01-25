#include <gtest/gtest.h>

#include <brew/core/Tree.h>

using namespace brew;

class MyNode : public TreeNode<MyNode> {
public:
    int id = 0;
};

/**
 * This test makes sure we can get a unique context for each thread.
 */
TEST(Tree, AccessorContextProvider) {

    TreeNodeAccessorContextProvider<MyNode> testProvider;

    auto mainId = std::this_thread::get_id();

    std::thread([&] {
        auto id = std::this_thread::get_id();
        auto& ctx = testProvider.getCurrentNodeAccessorContext();

        EXPECT_EQ(id, ctx.getId());
        EXPECT_NE(mainId, ctx.getId());
    }).join();

    auto& ctx = testProvider.getCurrentNodeAccessorContext();
    EXPECT_EQ(mainId, ctx.getId());
}

TEST(Tree, ChildSetIteratorBoundaries) {

    Tree<MyNode> myTree;
    auto& root = myTree.getRootNode();

    auto& childSet = root.getChildren();

    EXPECT_EQ(0, childSet.size());

    EXPECT_EQ(childSet.begin(), childSet.end());
}

TEST(Tree, ChildSetAddChildUncommited) {

    Tree<MyNode> myTree;
    auto& root = myTree.getRootNode();

    auto& child = root.createChild();

    auto& childSet = root.getChildren();

    EXPECT_EQ(1, childSet.size());

    auto& child2 = root.createChild();

    EXPECT_EQ(2, childSet.size());
}

TEST(Tree, ChildSetIterateUncommited) {

    Tree<MyNode> myTree;
    auto& root = myTree.getRootNode();

    for (int i=0;i<10; ++i) {
        root.createChild().id = i;
    }

    auto& childSet = root.getChildren();

    EXPECT_EQ(10, childSet.size());

    // Iterate
    SizeT foundElements = 0;
    for(auto it = childSet.begin(); it != childSet.end(); ++it) {
        foundElements++;
    }

    EXPECT_EQ(10, foundElements);

    // Range based for
    foundElements = 0;
    for(auto& child : childSet) {
        EXPECT_EQ(foundElements, child.id);
        foundElements++;
    }

    EXPECT_EQ(10, foundElements);
}

TEST(Tree, ChildSetAddAndRemoveUncommited) {

    Tree<MyNode> myTree;
    auto& root = myTree.getRootNode();

    auto& child = root.createChild();

    auto& childSet = root.getChildren();

    EXPECT_EQ(1, childSet.size());

    root.deleteChild(child);

    EXPECT_EQ(0, childSet.size());
}

TEST(Tree, CommitCreateSingle) {

    Tree<MyNode> myTree;
    auto& root = myTree.getRootNode();

    auto& child = root.createChild();

    EXPECT_EQ(1, root.getChildren().size());

    myTree.commit();

    EXPECT_EQ(1, root.getChildren().size());
}

TEST(Tree, CommitDeleteSingle) {

    Tree<MyNode> myTree;
    auto& root = myTree.getRootNode();

    // Add the child and commit.
    auto& child = root.createChild();
    myTree.commit();

    // Now delete the child.
    root.deleteChild(child);
    EXPECT_EQ(0, root.getChildren().size());
    myTree.commit();
    EXPECT_EQ(0, root.getChildren().size());
}

TEST(Tree, MultipleAccessors) {

    Tree<MyNode> myTree;
    auto& root = myTree.getRootNode();

    std::thread thd1([&] {
        root.createChild();
        // Make sure we have a child in this thread.
        EXPECT_EQ(1, root.getChildren().size());
    });

    std::thread thd2([&] {
        root.createChild();
        // Make sure we have a child in this thread.
        EXPECT_EQ(1, root.getChildren().size());
    });

    thd1.join();
    thd2.join();

    // Make sure we don't have children before the commit.
    EXPECT_EQ(0, root.getChildren().size());

    // Add the child and commit.
    myTree.commit();

    EXPECT_EQ(2, root.getChildren().size());
}