/*
给定一棵二叉树的头节点head，可以从树中的任何一点出发，如果走的话只能向下，
也可以选择随时停止，所形成的轨迹叫做一条路径，路径上所有值的累加和叫作路径
和。求这棵树上的最大路径和。
*/
#include<iostream>
using namespace std;

class Node{
public:
    int value;
    Node* left;
    Node* right;

    Node(int val){
        value=val;
        left=nullptr;
        right=nullptr;
    }
};

class ReturnType{
public:
    int maxPathSumAll;
    int maxPathSumHead;
    int maxValue;

    ReturnType(int all,int fromHead,int max){
        maxPathSumAll=all;//表示包括当前节点的最大路径和。
        maxPathSumHead=fromHead;//表示以当前节点为路径起点的最大路径和。
        maxValue=max;//表示以当前节点为根的子树中的最大节点值。
    }
};

ReturnType process(Node* x){
    if(x==nullptr){
        return ReturnType(0,0,INT_MIN);
    }
    ReturnType leftData=process(x->left);
    ReturnType rightData=process(x->right);
    int maxValue=max(x->value,max(leftData.maxValue,rightData.maxValue));
    int maxPathSumHead=max(leftData.maxPathSumHead,rightData.maxPathSumHead)+x->value;
    maxPathSumHead=max(x->value,maxPathSumHead);//以当前子树为根的最大值。
    int maxPathSumAll=max(max(leftData.maxPathSumAll,rightData.maxPathSumAll),maxPathSumHead);
    return ReturnType(maxPathSumAll,maxPathSumHead,maxValue);
}

int maxPathSum(Node* head){
    if(head==nullptr){
        return 0;
    }
    ReturnType allData=process(head);
    return allData.maxValue<0?allData.maxValue:allData.maxPathSumAll;
}


int main() {
    // Create a binary tree for testing
    Node* root = new Node(10);
    root->left = new Node(2);
    root->right = new Node(10);
    root->left->left = new Node(20);
    root->left->right = new Node(1);
    root->right->right = new Node(-25);
    root->right->right->left = new Node(3);
    root->right->right->right = new Node(4);

    int result = maxPathSum(root);
    std::cout << "Max Path Sum: " << result << std::endl;

    // Clean up memory (release nodes)
    delete root->right->right->right;
    delete root->right->right->left;
    delete root->right->right;
    delete root->right;
    delete root->left->right;
    delete root->left->left;
    delete root->left;
    delete root;

    return 0;
}