#include <iostream>
#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

struct BinaryTreeNode {
    int value;
    BinaryTreeNode *left, *right;
    BinaryTreeNode(int new_val) : value(new_val), left(NULL), right(NULL) {}
    ~BinaryTreeNode() {
        delete left;
        delete right;
        left = NULL;
        right = NULL;
    }
};

void find_and_print_sum_of_nodes(BinaryTreeNode* T, int desired_sum, int cur_sum, std::string buffer) {
    // exit if T is NULL
    if (!T) return;

    // update the ongoing sum with the current value for T
    int new_sum = cur_sum + T->value;

    // update the current path string
    std::string new_buffer = buffer + std::to_string(T->value) + " ";

    // if the desired sum is found, print the corresponding path
    if (new_sum == desired_sum) {
        std::cout << new_buffer << std::endl;
    }

    // continue down to the left subtree
    find_and_print_sum_of_nodes(T->left, desired_sum, new_sum, new_buffer);

    // continue down to the right subtree
    find_and_print_sum_of_nodes(T->right, desired_sum, new_sum, new_buffer);

    // restart from the left and right subtrees if the buffer is ""
    if (buffer.empty()) {
        find_and_print_sum_of_nodes(T->left, desired_sum, cur_sum, buffer);
        find_and_print_sum_of_nodes(T->right, desired_sum, cur_sum, buffer);
    }
}

int find_max_sum_of_nodes(BinaryTreeNode *T, int&temp_max_sum) {
    // exit if T is NULL
    if(!T) return 0;

    // derive the max sum for the left subtree
    int left_sum = find_max_sum_of_nodes(T->left, temp_max_sum);

    // derive the max sum for the right subtree
    int right_sum = find_max_sum_of_nodes(T->right, temp_max_sum);

    // compare T->value, left_sum+T->value, right_sum+T->value
    int max1 = (T->value > left_sum + T->value ? T->value : left_sum + T->value);
    max1 = (max1 > right_sum + T->value ? max1 : right_sum + T->value);

    // compare max1, left_sum+right_sum+T-value,
    int max2 = (max1 > left_sum + right_sum + T->value ? max1 : left_sum + right_sum + T->value);

    // update temp_max_sum with the new max
    temp_max_sum = temp_max_sum > max2 ? temp_max_sum : max2;

    return max1;
}

int find_max_sum_of_nodes(BinaryTreeNode *T) {
    int temp_max_sum = INT32_MIN;

    find_max_sum_of_nodes(T, temp_max_sum);

    return temp_max_sum;
}


// TESTING DESIRED SUM IMPLEMENTATION:
// Below are three tests.
bool ds_test1() {
    BinaryTreeNode* root = new BinaryTreeNode(5);
    BinaryTreeNode* root_left = new BinaryTreeNode(6);
    root->left = root_left;

    std::cout << "Desired sum of 1." << std::endl;
    std::cout << "No numbers should be printed." << std::endl;
    find_and_print_sum_of_nodes(root, 1, 0, "");
    std::cout << "Inspect to see if no numbers are returned before this point." << std::endl;
    std::cout << std::endl;

    std::cout << "Desired sum of 5." << std::endl;
    std::cout << "The number \"5\" should be printed." << std::endl;
    find_and_print_sum_of_nodes(root, 5, 0, "");
    std::cout << "Inspect to see if \"5\" was returned above." << std::endl;
    std::cout << std::endl;
    return true;
}

bool ds_test2() {
    BinaryTreeNode* root = new BinaryTreeNode(5);
    BinaryTreeNode* node1 = new BinaryTreeNode(3);
    BinaryTreeNode* node2 = new BinaryTreeNode(1);
    BinaryTreeNode* node3 = new BinaryTreeNode(-1);
    BinaryTreeNode* node4 = new BinaryTreeNode(8);
    BinaryTreeNode* node5 = new BinaryTreeNode(11);
    BinaryTreeNode* node6 = new BinaryTreeNode(18);
    BinaryTreeNode* node7 = new BinaryTreeNode(6);
    root->left = node1;
    root->right = node2;
    node1->left = node3;
    node1->right = node4;
    node2->right = node5;
    node3->left = node6;
    node4->left = node7;

    std::cout << "Desired sum of 12." << std::endl;
    std::cout << "The following should be printed: \"1 11\"." << std::endl;
    find_and_print_sum_of_nodes(root, 12, 0, "");
    std::cout << "Inspect to see if \"1 11\" was returned above." << std::endl;
    std::cout << std::endl;

    std::cout << "Desired sum of 17." << std::endl;
    std::cout << "The following should be printed: \"5 1 11\", \"3 8 6\", \"-1 18\"." << std::endl;
    find_and_print_sum_of_nodes(root, 17, 0, "");
    std::cout << "Inspect to see if \"5 1 11\", \"3 8 6\", \"-1 18\" were returned above." << std::endl;
    std::cout << std::endl;
    return true;
}

bool ds_test3() {
    BinaryTreeNode* root = new BinaryTreeNode(0);
    BinaryTreeNode* node1 = new BinaryTreeNode(0);
    BinaryTreeNode* node2 = new BinaryTreeNode(0);

    root->left = node1;
    root->right = node2;

    std::cout << "Desired sum of 0." << std::endl;
    std::cout << "The following should be printed: \"0\", \"0 0\", \"0 0\", \"0\", \"0\"." << std::endl;
    find_and_print_sum_of_nodes(root, 0, 0, "");
    std::cout << "Inspect to see if \"0\", \"0 0\", \"0 0\", \"0\", \"0\" were returned above." << std::endl;
    std::cout << std::endl;

    std::cout << "Desired sum of 1." << std::endl;
    std::cout << "No numbers should be printed." << std::endl;
    find_and_print_sum_of_nodes(root, 1, 0, "");
    std::cout << "Inspect to see if no numbers are returned before this point." << std::endl;
    std::cout << std::endl;
    return true;
}

bool run_desired_sum_tests() {
    bool check = true;
    std::cout << "Testing the find_and_print_sum_of_nodes() method." << std::endl;
    std::cout << "Test 1: testing tree of 5, 6 with a desired sum of 1 and then 5." << std::endl;
    check = check && ds_test1();
    std::cout << "TEST ENDED" << std::endl; // not really possible to fail
    std::cout << std::endl;

    std::cout << "Test 2: testing tree of 5, 3, 1, -1, 8, 11, 18, 6 with a desired sum of 12 and then 17." << std::endl;
    check = check && ds_test2();
    std::cout << "TEST ENDED" << std::endl;
    std::cout << std::endl;

    std::cout << "Test 3: testing tree of 0, 0, 0 with a desired sum of 0 and then 1." << std::endl;
    check = check && ds_test3();
    std::cout << "TEST ENDED" << std::endl;
    std::cout << std::endl;
    return true;
}

bool ms_test1() {
    BinaryTreeNode* root = new BinaryTreeNode(5);
    BinaryTreeNode* node1 = new BinaryTreeNode(6);
    BinaryTreeNode* node2 = new BinaryTreeNode(-15);
    BinaryTreeNode* node3 = new BinaryTreeNode(15);
    BinaryTreeNode* node4 = new BinaryTreeNode(10);
    BinaryTreeNode* node5 = new BinaryTreeNode(-12);
    BinaryTreeNode* node6 = new BinaryTreeNode(9);
    BinaryTreeNode* node7 = new BinaryTreeNode(-5);
    root->left = node1;
    root->right = node2;
    node1->left = node3;
    node1->right = node4;
    node2->left = node5;
    node2->right = node6;
    node4->right = node7;

    ASSERT_TRUE(find_max_sum_of_nodes(root) == 31)
    ASSERT_FALSE(find_max_sum_of_nodes(root) == 32)
    ASSERT_TRUE(find_max_sum_of_nodes(node2) == 9)
    ASSERT_TRUE(find_max_sum_of_nodes(node4) == 10)

    return true;
}

bool ms_test2() {
    BinaryTreeNode* root = new BinaryTreeNode(6);
    BinaryTreeNode* node1 = new BinaryTreeNode(10);
    BinaryTreeNode* node2 = new BinaryTreeNode(4);
    BinaryTreeNode* node3 = new BinaryTreeNode(-5);
    BinaryTreeNode* node4 = new BinaryTreeNode(-6);
    BinaryTreeNode* node5 = new BinaryTreeNode(4);
    BinaryTreeNode* node6 = new BinaryTreeNode(7);
    root->left = node1;
    root->right = node2;
    node1->right = node3;
    node2->right = node4;
    node3->right = node5;
    node4->right = node6;

    ASSERT_TRUE(find_max_sum_of_nodes(root) == 21)
    ASSERT_FALSE(find_max_sum_of_nodes(root) == 22)
    ASSERT_TRUE(find_max_sum_of_nodes(node1) == 10)
    ASSERT_TRUE(find_max_sum_of_nodes(node4) == 7)
    ASSERT_TRUE(find_max_sum_of_nodes(node3) == 4)
    ASSERT_FALSE(find_max_sum_of_nodes(node3) == 0)

    return true;
}

bool ms_test3() {
    BinaryTreeNode* root = new BinaryTreeNode(1);
    BinaryTreeNode* node1 = new BinaryTreeNode(0);
    BinaryTreeNode* node2 = new BinaryTreeNode(-1);
    root->left = node1;
    node1->left = node2;

    ASSERT_TRUE(find_max_sum_of_nodes(root) == 1)
    ASSERT_TRUE(find_max_sum_of_nodes(node1) == 0)
    return true;
}

bool run_max_sum_tests() {
    std::cout << "Testing the find_max_sum_of_nodes() method." << std::endl;
    std::cout << "Test 1: find max sum of tree A from Practice Exercise guidelines." << std::endl;
    std::cout << "Tests on children of tree also run." << std::endl;
    std::cout << (ms_test1() ? "TEST PASSED" : "TEST FAILED") << std::endl;
    std::cout << std::endl;

    std::cout << "Test 2: find max sum of tree B from Practice Exercise guidelines." << std::endl;
    std::cout << "Tests on children of tree also run." << std::endl;
    std::cout << (ms_test2() ? "TEST PASSED" : "TEST FAILED") << std::endl;
    std::cout << std::endl;

    std::cout << "Test 3: find max sum of 1, 0, -1." << std::endl;
    std::cout << "Tests on children of tree also run." << std::endl;
    std::cout << (ms_test3() ? "TEST PASSED" : "TEST FAILED") << std::endl;
    std::cout << std::endl;
    return true;
}

int main() {
    run_desired_sum_tests();
    run_max_sum_tests();
    return 0;
}
