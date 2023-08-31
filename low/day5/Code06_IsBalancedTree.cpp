//判断是否是平衡二叉树
//(对于任意一个节点，其左子树和右子树的高度差（即左子树高度减去右子树高度的绝对值）不超过1，并且其左子树和右子树也都是平衡二叉树。)
#include <iostream>


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

class Info{
public:
    bool isBanlanced;
    int height;
    Info(bool b,int h){
        this->isBanlanced=b;
        this->height=h;
    }
};

Info* process(Node* X){
    if(X==nullptr){
        return new Info(true,0);
    }
    Info* leftInfo=process(X->left);
    Info* rightInfo=process(X->right);
    int height=std::max(leftInfo->height,rightInfo->height)+1;
    bool isBalanced=true;
    if(!leftInfo->isBanlanced||!rightInfo->isBanlanced||std::abs(leftInfo->height-rightInfo->height)>1){
        isBalanced=false;
    }
    return new Info(isBalanced,height);

}


bool isBalanced2(Node* head){
    return process(head)->isBanlanced;
}

int main() {
    // 创建一个平衡二叉树
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);

    // 执行平衡性判断
    bool isBalanced = isBalanced2(root);

    // 输出结果
    if (isBalanced) {
        std::cout << "The tree is balanced." << std::endl;
    } else {
        std::cout << "The tree is not balanced." << std::endl;
    }

    // 释放二叉树内存
    delete root->left->left;
    delete root->left->right;
    delete root->left;
    delete root->right;
    delete root;

    return 0;
}