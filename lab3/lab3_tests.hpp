#ifndef LAB3_TESTS_HPP
#define LAB3_TESTS_HPP

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

#include <algorithm>
#include <sstream>
#include <queue>

#include "lab3_priority_queue.hpp"
#include "lab3_binary_search_tree.hpp"

class PriorityQueueTest {
public:
    // PURPOSE: Tests if the new queue is valid
    bool test1() {
        PriorityQueue q(5);
        ASSERT_TRUE( q.empty());
        ASSERT_TRUE( !q.full());
        ASSERT_TRUE( q.get_size() == 0);
        return true;
    }

    // PURPOSE: Tests enqueue of one item and then dequeue of that item
    bool test2() {
        PriorityQueue p(1);
        p.enqueue(PriorityQueue::TaskItem (10, "test case 1"));
        ASSERT_FALSE(p.empty());
        ASSERT_TRUE(p.full());
        ASSERT_TRUE(p.max().priority == 10);
        p.dequeue();
        ASSERT_TRUE(p.get_size() == 0);
        ASSERT_TRUE(p.empty());
        ASSERT_FALSE(p.full());
        return true;
    }

    // PURPOSE: Tests enqueue too many
    bool test3() {
        PriorityQueue q(2);
        q.enqueue(PriorityQueue::TaskItem(5, "test case 1"));
        q.enqueue(PriorityQueue::TaskItem(10, "test case 2"));
        q.enqueue(PriorityQueue::TaskItem(20, "test case 3")); // this insertion should have failed
        ASSERT_FALSE(q.empty());
        ASSERT_TRUE(q.full());
        ASSERT_TRUE(q.get_size() == 2);
        ASSERT_TRUE(q.max().priority == 10);
        return true;
    }

    // PURPOSE: Tests enqueue too many then dequeue too many
    bool test4() {
        PriorityQueue q(2);
        q.enqueue(PriorityQueue::TaskItem(3, "test case 1"));
        q.enqueue(PriorityQueue::TaskItem(4, "test case 2"));
        q.enqueue(PriorityQueue::TaskItem(5, "test case 3"));
        ASSERT_TRUE(q.full());
        ASSERT_TRUE(q.get_size() == 2);
        q.dequeue();
        ASSERT_FALSE(q.empty());
        ASSERT_TRUE(q.get_size() == 1);
        q.dequeue();
        ASSERT_TRUE(q.empty());
        ASSERT_TRUE(q.get_size() == 0);
        q.dequeue();
        ASSERT_TRUE(q.empty());
        ASSERT_TRUE(q.get_size() == 0);
        return true;
    }
};

class BinarySearchTreeTest {
public:
    bool insert_nodes(BinarySearchTree &tree, int *in, int nin) {
        for(int i = 0; i < nin; i++) {
            ASSERT_TRUE(tree.insert(BinarySearchTree::TaskItem(in[i],"Test Task")));
        }
        return true;
    }

    // PURPOSE: Traverse the tree using breadth-first traversal
    // Output is as follows: "val1 val2 ... valN"
    std::string level_order(BinarySearchTree::TaskItem* root) {
        if (!root) {
            return "";
        }

        std::stringstream ss;
        std::queue<BinarySearchTree::TaskItem*> node_queue;
        node_queue.push(root);
        while (!node_queue.empty()) {
            BinarySearchTree::TaskItem* cur_node = node_queue.front();
            node_queue.pop();
            ss << cur_node->priority << " ";
            if (cur_node->left) {
                node_queue.push(cur_node->left);
            }
            if (cur_node->right) {
                node_queue.push(cur_node->right);
            }
        }

        std::string level_order_str = ss.str();

        return level_order_str.substr(0, level_order_str.size() - 1);
    }

    // PURPOSE: Tests if the new tree is valid
    bool test1() {
        std::string expected_tree_level_order = "";

        BinarySearchTree bst;
        ASSERT_TRUE(bst.root == NULL);
        ASSERT_TRUE(bst.size == 0 && bst.get_size() == 0);

        // compare the tree's representation to the expected tree
        std::string tree_level_order = level_order(bst.root);
        ASSERT_TRUE(tree_level_order.compare(expected_tree_level_order) == 0)
        return true;
    }

    // PURPOSE: Tests a tree with one node
    bool test2() {
        BinarySearchTree bst;

        bst.insert(BinarySearchTree::TaskItem(5, "hello"));
        ASSERT_TRUE((bst.exists(BinarySearchTree::TaskItem(5, "hello"))));
        ASSERT_TRUE(bst.get_size() == 1);
        ASSERT_TRUE(bst.max() == BinarySearchTree::TaskItem(5, "hello"));
        ASSERT_FALSE(bst.max() == BinarySearchTree::TaskItem(6, "hello"));
        ASSERT_TRUE(bst.min() == BinarySearchTree::TaskItem(5, "hello"));
        return true;
    }

    // PURPOSE: Tests insert, remove, and size on linear list formation with three elements
    bool test3() {
        BinarySearchTree bst;

        bst.insert(BinarySearchTree::TaskItem(5, "hello"));
        bst.insert(BinarySearchTree::TaskItem(6, "hello1"));
        bst.insert(BinarySearchTree::TaskItem(7, "hello2"));
        ASSERT_TRUE((bst.exists(BinarySearchTree::TaskItem(5, "hello"))))
        ASSERT_TRUE(bst.get_size() == 3)
        ASSERT_TRUE(bst.max() == BinarySearchTree::TaskItem(7, "hello2"))
        ASSERT_FALSE(bst.max() == BinarySearchTree::TaskItem(6, "hello1"))
        ASSERT_TRUE(bst.min() == BinarySearchTree::TaskItem(5, "hello"))

        bst.remove(BinarySearchTree::TaskItem(7, "hello2"));
        ASSERT_FALSE(bst.min() == BinarySearchTree::TaskItem(6, "hello1"))
        ASSERT_TRUE(bst.get_size() == 2)
        ASSERT_TRUE(bst.max() == BinarySearchTree::TaskItem(6, "hello1"))

        bst.remove(BinarySearchTree::TaskItem(6, "hello1"));
        ASSERT_FALSE(bst.min() == BinarySearchTree::TaskItem(6, "hello1"))
        ASSERT_TRUE(bst.get_size() == 1)
        ASSERT_TRUE(bst.max() == BinarySearchTree::TaskItem(5, "hello"))

        bst.remove(BinarySearchTree::TaskItem(5, "hello"));
        ASSERT_TRUE(bst.get_size() == 0)
        return true;
    }

    // PURPOSE: Tests removal of a node with one child
    bool test4() {
        BinarySearchTree bst;

        bst.insert(BinarySearchTree::TaskItem(5, "hello"));
        bst.insert(BinarySearchTree::TaskItem(6, "hello1"));
        ASSERT_TRUE(bst.max() == BinarySearchTree::TaskItem(6, "hello1"))
        ASSERT_TRUE( bst.min() == BinarySearchTree::TaskItem(5, "hello"))
        ASSERT_TRUE(bst.get_size() == 2)

        bst.remove(BinarySearchTree::TaskItem(5, "hello"));
        ASSERT_TRUE(bst.get_size() == 1)
        ASSERT_TRUE(bst.min() == BinarySearchTree::TaskItem(6, "hello1"))
        ASSERT_TRUE(bst.max() == BinarySearchTree::TaskItem(6, "hello1"))
        ASSERT_FALSE(bst.min() == BinarySearchTree::TaskItem(5, "hello"))
        return true;
    }

    // PURPOSE: Tests insert of multiple elements and remove till nothing remains
    bool test5() {
        BinarySearchTree bst;

        bst.insert(BinarySearchTree::TaskItem(5, "hello"));
        bst.insert(BinarySearchTree::TaskItem(4, "hello1"));
        bst.insert(BinarySearchTree::TaskItem(6, "hello2"));
        bst.insert(BinarySearchTree::TaskItem(7, "hello3"));

        ASSERT_TRUE(bst.get_size() == 4)
        ASSERT_TRUE(bst.min() == BinarySearchTree::TaskItem(4, "hello1"))
        ASSERT_TRUE(bst.max() == BinarySearchTree::TaskItem(7, "hello3"))
        ASSERT_FALSE(bst.min() == BinarySearchTree::TaskItem(6, "hello2"))

        bst.remove(BinarySearchTree::TaskItem(5, "hello"));
        ASSERT_FALSE(bst.get_size() == 4)
        ASSERT_TRUE(bst.get_size() == 3)

        bst.remove(BinarySearchTree::TaskItem(4, "hello1"));
        ASSERT_FALSE(bst.get_size() == 3)
        ASSERT_TRUE(bst.get_size() == 2)
        ASSERT_FALSE(bst.min() == BinarySearchTree::TaskItem(4, "hello1"))
        ASSERT_TRUE(bst.min() == BinarySearchTree::TaskItem(6, "hello2"))

        bst.remove(BinarySearchTree::TaskItem(6, "hello2"));
        ASSERT_FALSE(bst.get_size() == 2)
        ASSERT_TRUE(bst.get_size() == 1)
        ASSERT_FALSE(bst.min() == BinarySearchTree::TaskItem(4, "hello1"))
        ASSERT_FALSE(bst.min() == BinarySearchTree::TaskItem(6, "hello2"))
        ASSERT_TRUE(bst.min() == BinarySearchTree::TaskItem(7, "hello3"))
        ASSERT_TRUE(bst.max() == BinarySearchTree::TaskItem(7, "hello3"))

        bst.remove(BinarySearchTree::TaskItem(7, "hello3"));
        ASSERT_TRUE(bst.get_size() == 0)
        return true;
    }

    // PURPOSE: Tests removal of root node when both children of root have two children
    bool test6() {
        BinarySearchTree bst;

        bst.insert(BinarySearchTree::TaskItem(4, "hello1"));
        bst.insert(BinarySearchTree::TaskItem(6, "hello2"));
        bst.insert(BinarySearchTree::TaskItem(5, "hello"));
        bst.insert(BinarySearchTree::TaskItem(7, "hello3"));
        bst.insert(BinarySearchTree::TaskItem(2, "hello4"));
        bst.insert(BinarySearchTree::TaskItem(1, "hello5"));
        bst.insert(BinarySearchTree::TaskItem(3, "hello6"));
        ASSERT_TRUE(bst.get_size() == 7)
        ASSERT_FALSE(bst.min() == BinarySearchTree::TaskItem(4, "hello1"))
        ASSERT_TRUE(bst.max() == BinarySearchTree::TaskItem(7, "hello3"))

        bst.remove(BinarySearchTree::TaskItem(4, "hello1"));
        ASSERT_TRUE(bst.get_size() == 6)
        ASSERT_FALSE(bst.exists(BinarySearchTree::TaskItem(4, "hello1")))
        ASSERT_TRUE(bst.exists(BinarySearchTree::TaskItem(5, "hello")))

        return true;
    }

    // PURPOSE: Tests depth with many inserts and some removes
    bool test7() {
        BinarySearchTree bst;

        bst.insert(BinarySearchTree::TaskItem(4, "hello1"));
        bst.insert(BinarySearchTree::TaskItem(6, "hello2"));
        bst.insert(BinarySearchTree::TaskItem(5, "hello"));
        bst.insert(BinarySearchTree::TaskItem(7, "hello3"));
        bst.insert(BinarySearchTree::TaskItem(2, "hello4"));
        bst.insert(BinarySearchTree::TaskItem(1, "hello5"));
        bst.insert(BinarySearchTree::TaskItem(3, "hello6"));

        ASSERT_FALSE(bst.height() == 1)
        ASSERT_FALSE(bst.height() == 2)
        ASSERT_TRUE(bst.height() == 3)
        ASSERT_TRUE(bst.get_node_depth(bst.root->left) == 2)
        ASSERT_TRUE(bst.get_node_depth(bst.root->right) == 2)
        ASSERT_FALSE(bst.get_node_depth(bst.root->left->left) == 2)
        ASSERT_FALSE(bst.get_node_depth(bst.root->right->left) == 2)

        bst.remove(BinarySearchTree::TaskItem(6, "hello2"));
        bst.remove(BinarySearchTree::TaskItem(5, "hello"));
        ASSERT_TRUE(bst.height() == 3)
        ASSERT_TRUE(bst.get_node_depth(bst.root->right) == 1)

        bst.remove(BinarySearchTree::TaskItem(2, "hello4"));
        bst.remove(BinarySearchTree::TaskItem(1, "hello5"));
        ASSERT_TRUE(bst.height() == 2)
        ASSERT_FALSE(bst.height() == 3)
        return true;
    }

    // PURPOSE: Tests lots of inserts and removes
    bool test8() {
        BinarySearchTree bst;

        bst.insert(BinarySearchTree::TaskItem(4, "hello1"));
        bst.insert(BinarySearchTree::TaskItem(6, "hello2"));
        bst.insert(BinarySearchTree::TaskItem(5, "hello"));
        bst.insert(BinarySearchTree::TaskItem(7, "hello3"));
        bst.insert(BinarySearchTree::TaskItem(2, "hello4"));
        bst.insert(BinarySearchTree::TaskItem(1, "hello5"));
        bst.insert(BinarySearchTree::TaskItem(3, "hello6"));

        ASSERT_TRUE(bst.height() == 3)

        bst.remove(BinarySearchTree::TaskItem(6, "hello2"));
        bst.remove(BinarySearchTree::TaskItem(5, "hello"));
        ASSERT_TRUE(bst.height() == 3)
        ASSERT_FALSE(bst.exists(BinarySearchTree::TaskItem(6, "hello2")))
        ASSERT_FALSE(bst.exists(BinarySearchTree::TaskItem(5, "hello")))
        ASSERT_TRUE(bst.exists(BinarySearchTree::TaskItem(2, "hello4")))

        bst.insert(BinarySearchTree::TaskItem(6, "hello2"));
        bst.insert(BinarySearchTree::TaskItem(5, "hello"));
        bst.remove(BinarySearchTree::TaskItem(2, "hello4"));
        bst.remove(BinarySearchTree::TaskItem(1, "hello5"));
        ASSERT_TRUE(bst.height() == 4)
        ASSERT_FALSE(bst.exists(BinarySearchTree::TaskItem(2, "hello4")))
        ASSERT_FALSE(bst.exists(BinarySearchTree::TaskItem(1, "hello5")))
        ASSERT_TRUE(bst.exists(BinarySearchTree::TaskItem(6, "hello2")))
        ASSERT_TRUE(bst.exists(BinarySearchTree::TaskItem(5, "hello")))
        return true;
    }
};
#endif