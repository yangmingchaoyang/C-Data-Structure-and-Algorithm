/*
双向链表节点结构和二叉树节点结构是一样的，如果你把last认为是left，
next认为是next的话。
给定一个搜索二叉树的头节点head，请转化成一条有序的双向链表，并返回链
表的头节点。
*/

#include<iostream>
#include<vector>
#include<queue>
using namespace std;

class Node{
public:
    int value;
    Node* left;
    Node* right;

    Node(int date){
        this->value=date;
        left=nullptr;
        right=nullptr;
    }
};
void inOrderToQueue(Node* head,queue<Node*>& que){
    if(head==nullptr){
        return;
    }
    inOrderToQueue(head->left,que);
    que.push(head);
    inOrderToQueue(head->right,que);
}

Node* convert1(Node* head){
    queue<Node*>que;
    inOrderToQueue(head,que);
    if(que.empty()){
        return head;
    }
    head=que.front();
    que.pop();
    Node* pre=head;
    pre->left=nullptr;
    Node* cur=nullptr;
    while(!que.empty()){
        cur=que.front();
        pre->right=cur;
        cur->left=pre;
        pre=cur;
    }
    pre->right=nullptr;
    return head;
}




