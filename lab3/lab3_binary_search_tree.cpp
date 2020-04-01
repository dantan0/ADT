#include <iostream>
#include <queue>
#include "lab3_binary_search_tree.hpp"

using namespace std;

// PURPOSE: Default/empty constructor
BinarySearchTree::BinarySearchTree() {
    root = NULL;
    size = 0;
}

// PURPOSE: Explicit destructor of the class BinarySearchTree
BinarySearchTree::~BinarySearchTree() {
    if (!root) {
        return;
    }

    // use breadth first search
    queue<BinarySearchTree::TaskItem*> node_queue;
    node_queue.push(root);

    while (!node_queue.empty()) {
        TaskItem *cur = node_queue.front();
        node_queue.pop();
        if (cur -> left) {
            node_queue.push(cur->left);
        }

        if (cur -> right){
            node_queue.push(cur->right);
        }
    }
}

// PURPOSE: Returns the number of nodes in the tree
unsigned int BinarySearchTree::get_size() const {
    return size;
}

// PURPOSE: Returns the maximum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")

// use breadth first search
BinarySearchTree::TaskItem BinarySearchTree::max() const {
    if (size == 0) {
        return TaskItem(-1, "N/A");
    }

    TaskItem *cur = root;
    while (cur->right) {
        cur = cur->right;
    }
    return *cur;
}

// PURPOSE: Returns the minimum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
// use breadth first search
BinarySearchTree::TaskItem BinarySearchTree::min() const {
    if (size == 0) {
        return TaskItem(-1, "N/A");
    }

    TaskItem *cur = root;
    while(cur -> left) {
        cur = cur->left;
    }
    return *cur;
}

// PURPOSE: Returns the tree height
unsigned int BinarySearchTree::height() const {
    int height = 0;

    if (size == 0) {
        return height;
    } else {
        int height = get_node_depth(root);
        return height;
    }
}

// PURPOSE: Prints the contents of the tree; format not specified
void BinarySearchTree::print() const {
    queue<BinarySearchTree::TaskItem*> node_queue;
    TaskItem *cur = root;
    node_queue.push(cur);

    while (!node_queue.empty()) {
        cur = node_queue.front();
        cout << cur -> priority << endl;
        node_queue.pop();

        if (cur -> left) {
            node_queue.push(cur->left);
        }

        if (cur -> right) {
            node_queue.push(cur->right);
        }
    }
}

// PURPOSE: Returns true if a node with the value val exists in the tree
// otherwise, returns false
bool BinarySearchTree::exists(BinarySearchTree::TaskItem val) const {
    queue<BinarySearchTree::TaskItem*>node_queue;
    TaskItem *cur = root;

    while (cur != NULL){
        if (val.priority < cur->priority) {
            cur = cur -> left;
        } else if (val.priority > cur->priority) {
            cur = cur -> right;
        } else if (val.priority == cur->priority) {
            return true;
        }
    }
    return false;
}

// PURPOSE: Optional helper function that returns a pointer to the root node
BinarySearchTree::TaskItem* BinarySearchTree::get_root_node() {
    return NULL;
}

// PURPOSE: Optional helper function that returns the root node pointer address
BinarySearchTree::TaskItem** BinarySearchTree::get_root_node_address() {
    return NULL;
}

// PURPOSE: Optional helper function that gets the maximum depth for a given node
int BinarySearchTree::get_node_depth( BinarySearchTree::TaskItem* n ) const {
    if (n == NULL) {
        return 0;
    }

    int max = 0;
    int lh = get_node_depth(n->left);
    int rh = get_node_depth(n->right);
    if (lh > rh) {
        max = lh;
    } else {
        max = rh;
    }
    int height = max + 1;
    return height;
}

// PURPOSE: Inserts the value val into the tree if it is unique
// returns true if successful; returns false if val already exists
bool BinarySearchTree::insert( BinarySearchTree::TaskItem val) {
    if (!root) {
        root = new TaskItem(val.priority, val.description);
        size++;
        return true;
    }

    TaskItem *cur = root;

    while (cur) {
        if (val.priority < cur->priority) {
            if (cur -> left) {
                cur = cur -> left;
            } else {
                cur -> left = new TaskItem(val.priority, val.description);
                size++;
                return true;
            }
        } else if (val.priority > cur->priority){
            if (cur -> right) {
                cur = cur -> right;
            } else {
                cur -> right = new TaskItem(val.priority, val.description);
                size++;
                return true;
            }
        } else {
            return false;
        }
    }
}


// PURPOSE: Removes the node with the value val from the tree
// returns true if successful; returns false otherwise
bool BinarySearchTree::remove(BinarySearchTree::TaskItem val ) {
    root = this->remover(root, val);
    if (root) {
        return true;
    }
    return false;
}

BinarySearchTree::TaskItem* BinarySearchTree::remover(BinarySearchTree::TaskItem* base, BinarySearchTree::TaskItem val) {
    if (!base) return base;

    if (val.priority < base->priority) {
        base->left = remover(base->left, val);
        return base;
    }
    else if (val.priority > base->priority) {
        base->right = remover(base->right, val);
        return base;
    }

    if (!base->left) {
        TaskItem* temp = base->right;
        delete base;
        base = NULL;
        size--;
        return temp;

    } else if (!base->right) {
        TaskItem* temp = base -> left;
        delete base;
        base = NULL;
        size--;
        return temp;

    } else {
        TaskItem* parent = base->right;

        TaskItem* child = base->right;

        while (child->left) {
            parent = child;
            child = child->left;
        }

        parent->left = child->right;
        base->right = child->right;

        base->priority = child->priority;
        base->description = child->description;

        delete child;
        child = NULL;
        size--;
        return base;
    }
}
