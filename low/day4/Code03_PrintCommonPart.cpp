/*
打印两个有序链表的公共部分
【题目】 给定两个有序链表的头指针head1和head2，打印两个链表的公共部分。
【要求】 如果两个链表的长度之和为N，时间复杂度要求为O(N)，额外空间复
杂度要求为O(1)
*/

#include<iostream>
#include <vector>

class Node{
public: 
    int value;
    Node* next;
    Node(int value):value(value),next(nullptr){}
};

void printCommonPart(Node* head1,Node* head2){
    while(head1!=nullptr||head2!=nullptr){
        if(head1->value<head2->value){
            head1=head1->next;
        }else if(head1->value>head2->value){
            head2=head2->next;
        }else{
            std::cout<<head1->value+" ";
            head1=head1->next;
            head2=head2->next;
        }
    }
    std::cout<<std::endl;
}