// 如何判断一颗二叉树是否是搜索二叉树？

#include <iostream>
#include <vector>
#include <list>

class Node {
public:
    int value;
    Node* left;
    Node* right;

    Node(int data) : value(data), left(nullptr), right(nullptr) {}
};

class Solution {
public:
//搜索二叉树需要中序遍历
    bool isBST(Node* head) {
        if (head == nullptr) {
            return true;
        }
        std::list<Node*> inOrderList;
        process(head, inOrderList);
        int pre = INT_MIN;
        //二叉搜索树中序遍历后，其值是从小到大排列的
        for (Node* cur : inOrderList) {
            if (pre >= cur->value) {
                return false;
            }
            pre = cur->value;
        }
        return true;
    }

    void process(Node* node, std::list<Node*>& inOrderList) {
        if (node == nullptr) {
            return;
        }
        process(node->left, inOrderList);
        inOrderList.push_back(node);
        process(node->right, inOrderList);
    }
};

int main() {
    Node* root = new Node(4);
    root->left = new Node(2);
    root->right = new Node(5);
    root->left->left = new Node(1);
    root->left->right = new Node(3);

    Solution solution;
    if (solution.isBST(root)) {
        std::cout << "The given tree is a BST." << std::endl;
    } else {
        std::cout << "The given tree is not a BST." << std::endl;
    }

    // Clean up memory (deallocate nodes)
    // ...

    return 0;
}