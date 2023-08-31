/*
用于判断给定的二叉树是否是完全二叉树（Complete Binary Tree，CBT）。完全二叉树是一种特殊的二叉树，除了最后一层外，其他层的节点都必须填满，最后一层的节点尽量靠左排列。
*/
#include <iostream>
#include <queue>

class Node {
public:
    int value;
    Node* left;
    Node* right;

    Node(int data) : value(data), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    bool isCBT(Node* head) {
        if (head == nullptr) {
            return true;
        }
        std::queue<Node*> q;
        bool leaf = false;//leaf 是一个布尔标志，表示已经遇到了叶子节点。一旦遇到了叶子节点，leaf 会被设置为 true。
        Node* l = nullptr;
        Node* r = nullptr;
        q.push(head);//这个是正常排序
        while (!q.empty()) {
            head = q.front();
            q.pop();
            l = head->left;
            r = head->right;
            if ((leaf && (l != nullptr || r != nullptr)) || (l == nullptr && r != nullptr)) {
                return false;
            }
            if (l != nullptr) {
                q.push(l);
            }
            if (r != nullptr) {//这里为空代表下一层是叶子节点
                q.push(r);
            } else {
                leaf = true;//当叶子节点为true，那么这个树应该结束
            }
        }
        return true;
    }
};

int main() {
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);

    Solution solution;
    if (solution.isCBT(root)) {
        std::cout << "The given tree is a complete binary tree." << std::endl;
    } else {
        std::cout << "The given tree is not a complete binary tree." << std::endl;
    }

    // Clean up memory (deallocate nodes)
    // ...

    return 0;
}
