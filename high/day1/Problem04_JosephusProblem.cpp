/*
某公司招聘，有n个人入围，HR在黑板上依次写下m个正整数A1、A2、……、Am，然后让这n个人围成一个
圈，并按照顺时针顺序为他们编号0、1、2、……、n-1。录取规则是：
第一轮从0号的人开始，取用黑板上的第1个数字，也就是A1
黑板上的数字按次序循环取用，即如果某轮用了第m个，则下一轮需要用第1个；如果某轮用到第k个，则
下轮需要用第k+1个（k<m）
每一轮按照黑板上的次序取用到一个数字Ax，淘汰掉从当前轮到的人开始按照顺时针顺序数到的第Ax个
人，下一轮开始时轮到的人即为被淘汰掉的人的顺时针顺序下一个人
被淘汰的人直接回家，所以不会被后续轮次计数时数到
经过n-1轮后，剩下的最后1人被录取
所以最后被录取的人的编号与（n，m，A1，A2，……，Am）相关。
输入描述：
第一行是一个正整数N，表示有N组参数
从第二行开始，每行有若干个正整数，依次存放n、m、A1、……、Am，一共有N行，也就是上面的N组参
数。
输出描述：
输出有N行，每行对应相应的那组参数确定的录取之人的编号示例1:
输入
1
4 2 3 1
输出
1
*/
#include<iostream>
#include<vector>
using namespace std;

class Node{
public:
    int value;
    Node* next;
    Node(int data){
        this->value=data;
        this->next=nullptr;
    }
};

/*函数 getLive 接受两个参数：i 表示总共有 i 个人，m 表示每隔 m 个人报数。*/
int getLive(int i,int m){
    if(i==1){
        return 1;
    }
    /*对上一轮的结果加上 m-1，表示在上一轮的基础上，再往后报 m-1 个数（因为从上一轮的起始位置开始报数，而不是从1开始）。*/
	/*对总人数 i 取模（%i），确保计算结果在 1 到 i 之间。
	最后再加上1，将结果转换为以1为起始的人数编号。 */
    return (getLive(i-1,m)+m-1)%i+1;
}

Node* josephusKill1(Node* head, int m) {
    if (head == nullptr || head->next == head || m < 1) {
        return head;
    }
    
    Node* last = head;
    while (last->next != head) {//找最后一个数
        last = last->next;
    }
    
    int count = 0;
    while (head != last) {
        if (++count == m) {
            last->next = head->next;
            count = 0;
        } else {
            last = last->next;
        }
        head = last->next;
    }   
    return head;
}

Node* josephusKill2(Node* head,int m){
    if(head==nullptr||head->next==head||m<1){
        return head;
    }
    Node* cur=head->next;
    int tmp=1;//tmp->list size
    while(cur!=head){
        tmp++;
        cur=cur->next;
    }
    tmp=getLive(tmp,m);
    while(--tmp!=0){
        head=head->next;
    }
    head->next=head;
    return head;
}