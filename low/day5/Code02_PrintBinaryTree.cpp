/*
如何直观的打印一颗二叉树
*/
#include <iostream>
#include <string>
class Node{
public:
    int value;
    Node* left;
    Node* right;

    Node(int v){
        this->value=v;
        this->left=nullptr;
        this->right=nullptr;
    }
};
std::string getSpace(int num) {
    std::string space = " ";
    std::string result = "";
    for (int i = 0; i < num; i++) {
        result += space;
    }
    return result;
}

/*
height 二叉树层数

*/
void printInOrder(Node* head, int height, std::string to, int len) {
    if (head == nullptr) {
        return;
    }
    printInOrder(head->right, height + 1, "v", len);
    std::string val = to + std::to_string(head->value) + to;
    int lenM = val.length();
    int lenL = (len - lenM) / 2;
    int lenR = len - lenM - lenL;
    val = getSpace(lenL) + val + getSpace(lenR);
    std::cout << getSpace(height * len) + val << std::endl;
    printInOrder(head->left, height + 1, "^", len);
}


void printTree(Node* head) {
    std::cout << "Binary Tree" << std::endl;
    printInOrder(head, 0, "H", 17);
    std::cout << std::endl;
}


int main() {
    // 创建一个二叉树
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);

    // 打印二叉树
    printTree(root);

    // 释放二叉树内存
    delete root->right->left;
    delete root->right->right;
    delete root->left->left;
    delete root->left->right;
    delete root->left;
    delete root->right;
    delete root;

    return 0;
}
