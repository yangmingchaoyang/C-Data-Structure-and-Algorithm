/*
两个单链表相交的一系列问题
【题目】给定两个可能有环也可能无环的单链表，头节点head1和head2。请实
现一个函数，如果两个链表相交，请返回相交的 第一个节点。如果不相交，返
回null
【要求】如果两个链表长度之和为N，时间复杂度请达到O(N)，额外空间复杂度
请达到O(1)。
*/
#include <iostream>


class Node{
public:
    int value;
    Node* next;;

    Node(int data){
        this->value=data;
        this->next=nullptr;
    }
};
//判断一个链表是否有环
Node* getLoopNode(Node* head){
    if(head==nullptr||head->next==nullptr||head->next->next==nullptr){//环需要至少3个点
        return nullptr;
    }
    Node* n1=head->next;
    Node* n2=head->next->next;
    while(n1!=n2){
        if(n2->next==nullptr||n2->next->next==nullptr){
            return nullptr;
        }
        n2=n2->next->next;
        n1=n1->next;
    }
    n2=head;//n2从头开始
    while(n1!=n2){
        n1=n1->next;
        n2=n2->next;
    }
    return n1;
}
//如果两个链表无环，返回第一个相交的节点，如果不相交，返回null
Node* noLoop(Node* head1,Node* head2){//两个链表无环，他们最后的部分一定相交。
    if(head1==nullptr||head2==nullptr){
        return nullptr;
    }
    Node* cur1=head1;
    Node* cur2=head2;
    int n=0;
    while(cur1->next!=nullptr){
        n++;
        cur1=cur1->next;
    }
    while(cur2->next!=nullptr){
        n--;
        cur2=cur2->next;
    }
    if(cur1!=cur2){//相交代表他们的最后一个节点一定相同
        return nullptr;
    }
    cur1=n>0?head1:head2;
    cur2=cur1==head1?head2:head1;
    n=std::abs(n);
    while(n!=0){
        n--;
        cur1=cur1->next;
    }
    while(cur1!=cur2){
        cur1=cur1->next;
        cur2=cur2->next;
    }
    return cur1;
}

Node* bothLoop(Node* head1,Node* loop1,Node* head2,Node* loop2){
    Node* cur1=nullptr;
    Node* cur2=nullptr;
    if(loop1==loop2){
        cur1=head1;
        cur2=head2;
        int n=0;
        while(cur1!=loop1){
            n++;
            cur1=cur1->next;
        }
        while(cur2!=loop2){
            n--;
            cur2=cur2->next;
        }
        cur1=n>0?head1:head2;
        cur2=cur1==head1?head2:head1;
        n=std::abs(n);
    while(n!=0){
        n--;
        cur1=cur1->next;
    }
    while(cur1!=cur2){
        cur1=cur1->next;
        cur2=cur2->next;
    }
    return cur1;
    }else{
        cur1=loop1->next;
        while(cur1!=loop1){
            if(cur1==loop2){
                return loop1;//一定在环内相交
            }
            cur1=cur1->next;
        }
        return nullptr;
    }
}

Node* getIntersectNode(Node* head1,Node* head2){
    if(head1==nullptr||head2==nullptr){
        return nullptr;
    }
    Node* loop1=getLoopNode(head1);
    Node* loop2=getLoopNode(head2);
    if(loop1==nullptr&&loop2==nullptr){
        return noLoop(head1,head2);
    }
    if(loop1!=nullptr&&loop2!=nullptr){
        return bothLoop(head1,loop1,head2,loop2);
    }
    return nullptr;
}


int main() {
    // 创建第一个链表: 1 -> 2 -> 3 -> 4 -> 5
    Node* head1 = new Node(1);
    head1->next = new Node(2);
    head1->next->next = new Node(3);
    head1->next->next->next = new Node(4);
    head1->next->next->next->next = new Node(5);

    // 创建第二个链表: 6 -> 7 -> 8 -> 9 -> 10
    Node* head2 = new Node(6);
    head2->next = new Node(7);
    head2->next->next = new Node(8);
    head2->next->next->next = new Node(9);
    head2->next->next->next->next = new Node(10);

    // 使两个链表在节点3相交
    head2->next->next->next->next->next = head1->next->next;

    // 找到交点节点
    Node* intersectionNode = getIntersectNode(head1, head2);

    if (intersectionNode != nullptr) {
        std::cout << "链表在值为 " << intersectionNode->value << " 的节点相交" << std::endl;
    } else {
        std::cout << "链表不相交" << std::endl;
    }

    // 释放内存
    delete head1;
    delete head2;

    return 0;
}