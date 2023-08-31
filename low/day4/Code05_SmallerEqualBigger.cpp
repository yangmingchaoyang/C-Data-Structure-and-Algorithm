/*
将单向链表按某值划分成左边小、中间相等、右边大的形式
【题目】给定一个单链表的头节点head，节点的值类型是整型，再给定一个整
数pivot。实现一个调整链表的函数，将链表调整为左部分都是值小于pivot的
节点，中间部分都是值等于pivot的节点，右部分都是值大于pivot的节点。
【进阶】在实现原问题功能的基础上增加如下的要求
【要求】调整后所有小于pivot的节点之间的相对顺序和调整前一样
【要求】调整后所有等于pivot的节点之间的相对顺序和调整前一样
【要求】调整后所有大于pivot的节点之间的相对顺序和调整前一样
【要求】时间复杂度请达到O(N)，额外空间复杂度请达到O(1)。
*/
#include <iostream>
#include <vector>

class Node{
public:
    int value;
    Node* next;

    Node(int value){
        this->value=value;
        this->next=nullptr;
    }
};

void swap(std::vector<Node*>&arr,int i,int j){
    Node* temp;
    temp=arr[i];
    arr[i]=arr[j];
    arr[j]=temp;
}
//先用链表装起来
Node* listPartition(Node* head,int pivot){
    if(head==nullptr){
        return head;
    }
    Node* cur=head;
    int i=0;
    while(cur!=nullptr){
        i++;
        cur=cur->next;
    }
    std::vector<Node*>vector;
    while(head!=nullptr){
        vector.push_back(head);
        head=head->next;
    }
    int l=-1;
    int r=i;
    int index=0;
    while(index<r){
        if(vector[index]->value<pivot){
            swap(vector,++l,index++);
        }else if(vector[index]->value>pivot){
            swap(vector,--r,index);
        }else{
            index++;
        }
    }
    for(i=1;i<vector.size();i++){
        vector[i-1]->next=vector[i];//这句话来重组链表
    }
    vector[i-1]->next=nullptr;
    return vector[0];
}


void printLinkedList(Node* head) {
    Node* cur = head;
    while (cur != nullptr) {
        std::cout << cur->value << " ";
        cur = cur->next;
    }
    std::cout << std::endl;
}

Node* listPartition2(Node* head,int pivok){
 Node* ls = nullptr;
    Node* le = nullptr;
    Node* ms = nullptr;
    Node* me = nullptr;
    Node* rs = nullptr;
    Node* re = nullptr;
    Node* next = nullptr;
    while(head!=nullptr){
        next=head->next;
        head->next=nullptr;
        if(head->value<pivok){
            if(ls==nullptr){
                ls=head;
                le=head;
            }else{
                le->next=head;
                le=head;
            }
        }else if(head->value>pivok){
            if(rs==nullptr){
                rs=head;
                re=head;
            }else{
                re->next=head;
                re=head;
            }
            
        }else{
            if(ms==nullptr){
                ms=head;
                me=head;
            }else{
                me->next=head;
                me=head;
            } 
        }
        head=next;
    }
    if(le!=nullptr){
        le->next=ms;
        me=(me==nullptr)?le:me;
    }
    if(me!=nullptr){
        me->next=rs;
    }
    return (ls!=nullptr)?ls:(ms!=nullptr?ms:rs);
}



int main() {
    // 构建一个示例链表: 3 -> 5 -> 8 -> 5 -> 10 -> 2 -> 1
    Node* head = new Node(3);
    head->next = new Node(5);
    head->next->next = new Node(8);
    head->next->next->next = new Node(5);
    head->next->next->next->next = new Node(10);
    head->next->next->next->next->next = new Node(2);
    head->next->next->next->next->next->next = new Node(1);

    // 调用函数进行链表划分
    int pivot = 5;
    Node* newHead = listPartition2(head, pivot);

    // 打印划分后的链表
    std::cout << "Partitioned Linked List: ";
    printLinkedList(newHead);

    // 释放链表内存
    while (newHead != nullptr) {
        Node* temp = newHead;
        newHead = newHead->next;
        delete temp;
        temp=nullptr;
    }
    return 0;
}