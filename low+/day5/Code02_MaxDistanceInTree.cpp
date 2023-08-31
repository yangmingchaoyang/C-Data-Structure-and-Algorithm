/*
叉树节点间的最大距离问题
从二叉树的节点a出发，可以向上或者向下走，但沿途的节点只能经过一次，到达节点b时路
径上的节点个数叫作a到b的距离，那么二叉树任何两个节点之间都有距离，求整棵树上的最
大距离。
*/
#include <vector>
#include <iostream>

using namespace std;


class Node{
public:
    int value;
    Node* left;
    Node* right;

    Node(int data){
        this->value=data;
        this->left=nullptr;
        this->right=nullptr;
    }
};

class Info{
public:
    int maxDistance;
    int height;
    Info(int dis,int h){
        maxDistance=dis;
        height=h;
    }
};

/*
悬空指针或野指针： 当你使用一个指针，但它没有被初始化或者已经释放，导致指针指向的内存地址是不确定的时候，就会发生悬空指针或野指针问题。在你的情况下，错误消息中的 0xbaadf00dbaadf00d 似乎是一个特殊的标记，可能是由某些调试工具在释放内存后将指针设置为无效值的结果。这可能表明你在释放内存后，仍然在尝试访问已经释放的内存。

内存越界： 当你访问了数组或指针指向的内存范围之外的区域时，就会发生内存越界错误。这通常会触发操作系统的保护机制，导致出现 "Segmentation fault" 错误。

使用已被释放的内存： 如果你在释放内存后，仍然尝试使用已被释放的内存，就会发生 "Segmentation fault" 错误。
*/
Info process(Node* x){
    if(x==nullptr){//空指针也需要定义
        return Info(0,0);
    }
    Info leftInfo=process(x->left);
    Info rifgtInfo=process(x->right);
    int p1=leftInfo.maxDistance;
    int p2=rifgtInfo.maxDistance;
    int p3=leftInfo.height+rifgtInfo.height+1;
    int maxDistance=max(p3,max(p1,p2));
    int height=max(leftInfo.height,rifgtInfo.height)+1;


    return Info(maxDistance,height);
}

int maxDistance(Node* head){
    return process(head).maxDistance;
}


int main() {
    // 构造二叉树
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left=new Node(3);
    root->left->right=new Node(3);
    root->right->left=new Node(3);
    root->right->right=new Node(3);



    // 计算最远节点距离
    int result = maxDistance(root);
    cout << "Max Distance: " << result << endl;

    // 释放内存
    delete root->right->right;
    delete root->right->left;
    delete root->right;
    delete root->left->right;
    delete root->left->left;
    delete root->left;
    delete root;

    return 0;
}