/*
判断一个链表是否为回文结构
【题目】给定一个单链表的头节点head，请判断该链表是否为回文结构。
【例子】1->2->1，返回true； 1->2->2->1，返回true；15->6->15，返回true；
1->2->3，返回false。
【例子】如果链表长度为N，时间复杂度达到O(N)，额外空间复杂度达到O(1)。
*/
#include <iostream>
#include <stack>

struct Node {
    int value;
    Node* next;

    Node(int value) {
        this->value = value;
        next = nullptr;
    }
};
//判断该链表是否是回文结构
bool isPalindrome1(Node* head) {//使用堆栈
    std::stack<Node*> stack;
    Node* cur = head;
    while (cur != nullptr) {
        stack.push(cur);
        cur = cur->next;
    }
    while (head != nullptr) {
        if (head->value != stack.top()->value) {
            return false;
        }
        stack.pop();
        head = head->next;
    }
    return true;
}


bool isPalindrome2(Node* head){//使用快慢指针
    if(head==nullptr||head->next==nullptr){
        return true;
    }
    Node* left=head;
    Node* cur=head->next;
    while(cur->next!=nullptr&&cur->next->next!=nullptr){//当循环结束后，right 指针会指向中间节点或者中间偏下节点，
        left=left->next;
        cur=cur->next->next;
    }
    std::stack<Node*>stack;
    while(left!=nullptr){
        stack.push(left);
        left=left->next;
    }
    while(!stack.empty()){
        if(head->value!=stack.top()->value){
            return false;
        }
        head=head->next;
        stack.pop();
    }
    return true;
}

//前两种方式都使用到了额外的空间
bool isPalindrome3(Node* head){
    if(head==nullptr||head->next==nullptr){
        return head;
    }
    Node* n1=head;
    Node* n2=head;
    while(n2->next!=nullptr&&n2->next->next!=nullptr){
        n1=n1->next;
        n2=n2->next->next;
    }
    Node* n3=n1;
    n1=n1->next;
    n3->next==nullptr;
    while(n1!=nullptr){
        n2=n1->next;
        n1->next=n3;
        n3=n1;
        n1=n2;
    }
    n1=n3;
    n2=head;
    bool res=true;
    while(n2!=nullptr){
        if(n2->value!=n3->value){
            res=false;
        }
        n2=n2->next;
        n3=n3->next;
    }
    n3=n1->next;
    n1->next=nullptr;
    while(n3!=nullptr){
        n2=n3->next;
        n3->next=n1;
        n1=n3;
        n3=n2;
    }
    return res;
}

int main() {
    Node* list1 = new Node(1);
    list1->next = new Node(2);
    list1->next->next = new Node(3);
    list1->next->next->next = new Node(2);
    list1->next->next->next->next = new Node(1);

    Node* list2 = new Node(1);
    list2->next = new Node(2);
    list2->next->next = new Node(3);
    list2->next->next->next = new Node(4);

    if (isPalindrome2(list1)) {
        std::cout << "List 1 is a palindrome." << std::endl;
    } else {
        std::cout << "List 1 is not a palindrome." << std::endl;
    }

    if (isPalindrome2(list2)) {
        std::cout << "List 2 is a palindrome." << std::endl;
    } else {
        std::cout << "List 2 is not a palindrome." << std::endl;
    }

    // Clean up memory
    // ...

    return 0;
}