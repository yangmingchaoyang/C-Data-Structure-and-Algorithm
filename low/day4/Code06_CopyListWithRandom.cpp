/*
复制含有随机指针节点的链表
【题目】一种特殊的单链表节点类描述如下
class Node {
int value;
Node next;
Node rand;
Node(int val) {
value = val;
}
}
rand指针是单链表节点结构中新增的指针，rand可能指向链表中的任意一个节
点，也可能指向null。给定一个由Node节点类型组成的无环单链表的头节点
head，请实现一个函数完成这个链表的复制，并返回复制的新链表的头节点。
【要求】时间复杂度O(N)，额外空间复杂度O(1)
*/
#include <iostream>
#include <unordered_map>

class Node {
public:
    int value;
    Node* next;
    Node* rand;

    Node(int data) {
        this->value = data;
        this->next = nullptr;
        this->rand = nullptr;
    }
};

Node* copyListWithRand1(Node* head) {//使用哈希寻找的快
    std::unordered_map<Node*, Node*> map;
    Node* cur = head;
    while (cur != nullptr) {
        map[cur] = new Node(cur->value);
        cur = cur->next;
    }
    cur = head;
    while (cur != nullptr) {
        map[cur]->next = map[cur->next];//因为这句代码的出错导致链表的连接出错。
        map[cur]->rand = map[cur->rand];
        cur = cur->next;
    }
    return map[head];
}

//使用链表夹在链表之间，最后拆分。
Node* copyListWithRand2(Node* head){
    if(head==nullptr){
        return nullptr;
    }
    Node* cur=head;//指当前链表的值
    Node* next=nullptr;//保存当前链表的下一个值
    while(cur!=nullptr){
        next=cur->next;
        Node* copyNode=new Node(cur->value);//复制当前链表的值
        cur->next=copyNode;
        copyNode->next=next;
        cur=next;
    }
    cur=head;
    while(cur!=nullptr){
        next=cur->next->next;
        Node* copyNode=cur->next;
        copyNode->rand=cur->rand!=nullptr?cur->rand:nullptr;
        cur=next;
    }
    Node* res=head->next;
    Node* copyNode=nullptr;
    cur=head;
    while(cur!=nullptr){
        next=cur->next->next;
        copyNode=cur->next;//
        cur->next=next;
        copyNode->next=next!=nullptr?next->next:nullptr;
        cur=next;
    }
    return res;
} 



void freeList(Node* head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    // Usage example
    Node* head = new Node(1);
    head->next = new Node(2);
    head->rand = head->next;
    head->next->next = new Node(3);
    head->next->rand = head;

    Node* copiedHead = copyListWithRand2(head);

    // Print the copied list values and random node values
    Node* cur = head;
    while (cur != nullptr) {
        std::cout << "Node value: " << cur->value << std::endl;
        if (cur->rand != nullptr)
            std::cout << "Random node value: " << cur->rand->value << std::endl;
        else
            std::cout << "Random node value: nullptr" << std::endl;
        cur = cur->next;
    }

    cur = copiedHead;
    while (cur != nullptr) {
        std::cout << "Node value: " << cur->value << std::endl;
        if (cur->rand != nullptr)
            std::cout << "Random node value: " << cur->rand->value << std::endl;
        else
            std::cout << "Random node value: nullptr" << std::endl;
        cur = cur->next;
    }


    // Free the memory allocated for the original and copied lists
    freeList(head);
    freeList(copiedHead);

    return 0;
}