/*
反转单向和双向链表
【题目】 分别实现反转单向链表和反转双向链表的函数
【要求】 如果链表长度为N，时间复杂度要求为O(N)，额外空间复杂度要求为
O(1)
*/
#include <iostream>

using namespace std;
//默认析构函数是一个空函数体的析构函数，不需要手动编写，编译器会自动为你生成。
//由于Node类没有使用new关键字进行内存分配，因此默认的析构函数就足够了。
class Node{
public:
    int value;
    Node* next;

    Node(int data):value(data){};

};


class DoubleNode{
public:
    int value;
    DoubleNode* last;
    DoubleNode* next;

    DoubleNode(int data):value(data){};
};




Node* reverseNode(Node* head){
    if(head==nullptr||head->next==nullptr){
        return head;
    }
    Node* pre=nullptr;
    Node* next=nullptr;
    while(head!=nullptr){
        next=head->next;
        head->next=pre;
        pre=head;
        head=next;
    }
    return pre;
}

DoubleNode* reverseDoubleNode(DoubleNode* head){
    if(head==nullptr||head->next==nullptr){
        return head;
    }
    DoubleNode* pre=nullptr;
    DoubleNode* next=nullptr;
    while(head!=nullptr){
        next=head->next;
        head->next=pre;
        head->last=next;
        pre=head;
        head=next;
    }
    return pre;
}