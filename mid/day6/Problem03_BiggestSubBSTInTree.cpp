/*找到一棵二叉树中，最大的搜索二叉子树，返回最大搜索二叉子树的节点个数*/
#include <iostream>
#include <vector>
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
    bool issALLBST;
    int maxSubSTSize;
    int max;
    int min;

    Info(bool is,int size,int mi,int ni){
        this->issALLBST=is;
        this->maxSubSTSize=size;
        this->min=mi;
        this->max=ni;
    }
};

Info* process(Node* x){
    if(x==nullptr){
        return nullptr;
    }
    Info* leftInfo=process(x->left);
    Info* rightInfo=process(x->right);

    int min=x->value;
    int max=x->value;

    if(leftInfo!=nullptr){
        min=std::min(min,leftInfo->min);
        max=std::max(max,leftInfo->max);
    }
    if(rightInfo!=nullptr){
        min=std::min(min,rightInfo->min);
        max=std::max(max,rightInfo->max);
    }
    int maxSubBSTSize=0;
    if(leftInfo!=nullptr){
        maxSubBSTSize=leftInfo->maxSubSTSize;
    }
    if(rightInfo!=nullptr){
        maxSubBSTSize=std::max(maxSubBSTSize,rightInfo->maxSubSTSize);
    }
    bool isALLBST=false;
    if((leftInfo==nullptr?true:leftInfo->issALLBST)&&(rightInfo==nullptr?true:rightInfo->issALLBST)&&
    (leftInfo==nullptr?true:leftInfo->max<x->value)&&(rightInfo==nullptr?true:rightInfo->min>x->value)){
        maxSubBSTSize=(leftInfo==nullptr?0:leftInfo->maxSubSTSize)+(rightInfo==nullptr?0:rightInfo->maxSubSTSize)+1;
        isALLBST=true;
    }
    // 释放 Info 对象的内存
    delete leftInfo;
    delete rightInfo;

    return new Info(isALLBST,maxSubBSTSize,min,max);

}


int main() {
    // 构建一个简单的二叉树
    Node* root = new Node(10);
    root->left = new Node(5);
    root->right = new Node(15);
    root->left->left = new Node(1);
    root->left->right = new Node(8);
    root->right->right = new Node(7);

    // 调用 process 函数计算最大二叉搜索子树的信息
    Info* result = process(root);

    // 打印计算结果
    std::cout << "Is BST: " << (result->issALLBST ? "true" : "false") << std::endl;
    std::cout << "Max Subtree Size: " << result->maxSubSTSize << std::endl;
    std::cout << "Min Value: " << result->min << std::endl;
    std::cout << "Max Value: " << result->max << std::endl;

    // 释放内存
    delete root;
    delete result;

    return 0;
}
