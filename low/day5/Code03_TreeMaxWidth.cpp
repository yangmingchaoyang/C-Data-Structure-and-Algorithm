/*
如何完成二叉树的宽度优先遍历(常见题目：求一棵二叉树的宽度)
*/
#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

class Node {
public:
    int value;
    Node* left;
    Node* right;

    Node(int v) {
        value = v;
        left = nullptr;
        right = nullptr;
    }
};

int maxWidthUseMap(Node* head){
    if(head==nullptr){
        return 0;
    }
    std::queue<Node*>queue;
    queue.push(head);
    //key在那一层value;
    std::unordered_map<Node*,int>levelMap;
    levelMap[head]=1;
    int curLevel=1;//当前你正在统计的那一层的宽度
    int curLevelNodes=0;//当前层curLevel层，宽度目前是多少
    int max=0;
    while(!queue.empty()){
        Node* cur=queue.front();
        //得到当前的层数
        int curNodeLevel=levelMap[cur];
        if(cur->left!=nullptr){
            levelMap[cur->left]=curLevelNodes+1;
            queue.push(cur->left);
        }
        if(cur->right!=nullptr){
            levelMap[cur->right]=curLevelNodes+1;
            queue.push(cur->right);
        }
        if(curNodeLevel==curLevel){
            curLevelNodes++;
            //加的是当前层的最后一个
        }else{//到下一层第一个的时候没有给curlevelnode++;
            max=std::max(max,curLevelNodes);
            curLevel++;
            curLevelNodes=1;
        }
    }
}



int maxWidth2(Node* head){
    if(head==nullptr){
        return 0;
    }
    std::queue<Node*>queue;
    queue.push(head);
    Node* curEnd=head;//当前层，最右的节点
    Node* nextEnd=nullptr;//下一层最右的节点
    int max=0;
    int curlevelNodes=0;//当前层的节点数
    while(!queue.empty()){
        Node* cur=queue.front();
        if(cur->left!=nullptr){
            queue.push(cur->left);
            nextEnd=cur->left;
        }
        if(cur->right!=nullptr){
            queue.push(cur->right);
            nextEnd=cur->right;
        }
        curlevelNodes++;
        if(cur==curEnd){
            max=std::max(max,curlevelNodes);
            curlevelNodes=0;
            curEnd=nextEnd;
        }
    }
    return max;    
}