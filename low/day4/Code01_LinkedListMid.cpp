#include <iostream>
//快慢指针
//使用容器

/*
链表的限制设定问题可以有不同的解决方法，具体取决于问题的具体要求和约束。下面列举一些常见的链表限制设定问题及其解决方法：

链表长度限制：

如果链表长度有限制，可以使用一个计数器来跟踪链表中的节点数量，并在插入和删除节点时进行更新。当链表达到设定的长度限制时，可以禁止继续插入新节点，或者在插入新节点时根据需要删除旧节点，以保持链表长度不超过限制。
链表节点值的限制：

如果链表节点的值有限制，可以在插入新节点时进行检查，确保新节点的值满足设定的限制条件。如果不满足条件，可以选择不插入新节点或者在插入新节点前对其进行修正。
环形链表限制：

环形链表是一种特殊的链表结构，其中链表的尾节点指向了链表中的某个节点，形成了一个环。在处理环形链表时，需要注意检测是否有环，并防止陷入无限循环。
可以使用快慢指针的方法来检测链表是否有环，并在插入新节点时保证链表不会形成环。
单向/双向链表限制：

单向链表只能从头到尾遍历，而双向链表可以从头到尾或从尾到头遍历。
如果问题需要从尾部向头部遍历链表，但是只有单向链表，可以考虑反转链表或者使用栈等数据结构来辅助遍历。
自定义节点类型的限制：

可以根据具体需求自定义链表节点类型，并在插入、删除等操作时进行合适的处理，确保节点类型满足设定的限制。
总的来说，解决链表的限制设定问题需要根据具体情况选择合适的数据结构、算法和操作，以满足问题的要求和约束。使用合适的技术和策略可以帮助有效解决链表限制设定问题。
*/
class Node{
public:
    int value;
    Node* next;
    Node(int value){
        this->value=value;
        this->next=nullptr;//初始化必须这么做，不然的话产生它的next的指针指向未定义区域的报错，指向nullptr也是指向一个区域
    }
    ~Node(){
        //对于简单的链表结构，其中的节点只是指向其他节点的引用，并不负责分配内存，
        //因此在默认情况下不需要在析构函数中释放 Node* next。
    }
};
//返回中上起始点在开始的位置
//奇数返回中点，偶数返回上中点
Node* midOrUpMidNode(Node* head){
    if(head==nullptr||head->next==nullptr||head->next->next==nullptr){
        return head;
    }
    Node* slow=head->next;
    Node* fast=head->next->next;
    while(fast->next!=nullptr&&fast->next->next!=nullptr){
        slow=slow->next;
        fast=fast->next->next;
    }
    return slow;
}
//返回中下起始点快指针先走一格
//奇数返回中点，偶数返回下中点
Node* midOrDownMidNode(Node* head){
    if(head==nullptr||head->next==nullptr){
        return head;
    }
    if(head->next->next==nullptr){
        return head->next;
    }
    Node* slow=head;
    Node* fast=head->next;
    while(fast->next!=nullptr&&fast->next->next!=nullptr){
        slow=slow->next;
        fast=fast->next->next;
    }
    return slow;
}
