/*
给定一个非负整数n，代表二叉树的节点个数。返回能形成多少种不同的二叉树结构
*/

#include <iostream>
#include <vector>
using namespace std;

class Node{
public:
    int value;
    Node* left;
    Node* right;

    Node(int val){
        this->value=val;
        this->left=nullptr;
        this->right=nullptr;
    }
};
/*
这段代码是一个动态规划算法，用于计算给定节点数量 n 的二叉搜索树（BST）的数量。以下是代码的功能和操作步骤的解释：

输入参数：

n：要构建二叉搜索树的节点数量。
基本情况处理：

如果节点数量 n 小于 2，即 n 为 0 或 1，那么只有一种情况，即空树或只有一个节点的树。因此，函数返回 1。
动态规划步骤：

创建一个向量 num，长度为 n + 1，用于存储以节点数量为索引的不同二叉搜索树的数量。
将 num[0] 初始化为 1，表示空树的情况。
嵌套循环计算：

使用两个嵌套循环，外层循环变量 i 从 1 到 n，表示当前正在计算节点数量为 i 的二叉搜索树数量。
内层循环变量 j 从 1 到 i+1，用于计算以 j 为根节点时左子树和右子树的组合情况，进而得到 i 个节点的二叉搜索树数量。
在每次循环中，更新 num[i]，将其累加计算所有可能的左子树和右子树组合的情况。
返回结果：

最终，num[n] 存储了以 n 个节点构建的二叉搜索树的数量，函数返回这个值作为结果。
*/
int numTrees(int n){
    if(n<2){
        return 1;
    }
    vector<int>num(n+1);
    num[0]=1;
    for(int i=1;i<n+1;i++){
        for(int j=1;j<i+1;j++){
            num[i]+=num[j-1]*num[i-j];//加和各个节点作主节点,余下的节点排列
        }
    }
    return num[n];
}
Node* cloneTree(Node* head){
    if(head==nullptr){
        return nullptr;
    }
    Node* res=new Node(head->value);
    res->left=cloneTree(head->left);
    res->right=cloneTree(head->right);
    return res;
}


vector<Node*>generate(int start,int end){
    vector<Node*>res;
    if(start>end){
        res.push_back(nullptr);
    }
    Node* head=nullptr;
    for(int i=start;i<end+1;i++){
        head=new Node(i);
        vector<Node*>lSubs=generate(start,i-1);
        vector<Node*>rSubs=generate(i+1,end);
        for(Node* l:lSubs){
            for(Node* r:rSubs){
                head->left=l;
                head->right=r;
                res.push_back(cloneTree(head));
            }
        }
    }
}

vector<Node*>geneateTree(int n){
    return generate(1,n);
}

