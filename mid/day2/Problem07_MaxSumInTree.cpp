/*
二叉树每个结点都有一个int型权值，给定一棵二叉树，要求计算出从根结点到
叶结点的所有路径中，权值和最大的值为多少。
*/

#include <iostream>
#include <unordered_map>
#include <stack>

using namespace std;

class Node{
public:
    int value;
    Node* left;
    Node* right;

    Node(int val){
        value=val;
        left==nullptr;
        right=nullptr;
    }
};

int process(Node* x,int pre){
    if(x==nullptr){
        return INT_MIN;
    }
    if(x->left==nullptr&&x->right==nullptr){
        return pre+x->value;
    }
    int leftMax=process(x->left,pre+x->value);
    int rightMax=process(x->right,pre+x->value);
    return max(leftMax,rightMax);
}

int maxSumRecursive(Node* head){
    return process(head,0);
}
//前序，中序，后序遍历都可以。
int maxSumUnrecursive(Node* head){
    int maxnum=0;
    unordered_map<Node*,int>sumMap;//中间使用了哈希来加速
    if(head!=nullptr){
        stack<Node*>sta;
        sta.push(head);
        sumMap[head]=head->value;
        while(!sta.empty()){
            head=sta.top();
            sta.pop();
            if(head->left==nullptr&&head->right==nullptr){
                maxnum=max(maxnum,sumMap[head]);
            }
            if(head->right!=nullptr){
                sumMap[head->right]=sumMap[head]+head->right->value;
                sta.push(head->right);
            }
            if(head->left!=nullptr){
                sumMap[head->left]=sumMap[head]+head->left->value;
                sta.push(head->left);
            }
        }
    }
    return maxnum;
    
}


