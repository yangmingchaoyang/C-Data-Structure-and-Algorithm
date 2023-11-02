/*
KMP算法扩展题目二
给定一棵二叉树的头节点head，已知所有节点的值都不一样，返回其中最大的且符
合搜索二叉树条件的最大拓扑结构的大小。
拓扑结构：不是子树，只要能连起来的结构都算。
包含二叉搜索树 (BST) 的节点，并且满足 BST 的性质（即左子树上的节点值小于当前节点，
右子树上的节点值大于当前节点）的树结构，其包含节点数目最多。
*/
#include<iostream>
#include<vector>
#include <map>
#include <algorithm>
using namespace std;

class Node{
public:
    int value;
    Node* left;
    Node* right;

    Node(int data){
        this->value=data;
        left=nullptr;
        right=nullptr;
    }
};

//这个函数主要用于帮助确定节点 n 是否属于二叉搜索树 h。
bool isBSTNode(Node* h,Node* n,int value){
    if(h==nullptr){
        return false;
    }
    if(h==n){
        return true;
    }
    return isBSTNode(h->value>value?h->left:h->right,n,value);
}

/*它计算在给定的二叉树 h 中，包含节点 n 的最大拓扑结构的大小。
拓扑结构是指包含节点 n 以及其子节点的子树。这个函数首先检查节点 n 是否属于 BST h，
如果是，则递归地计算左子树和右子树的最大拓扑结构大小，并将它们相加，最后加上 n 本身，返回总的大小。*/
int maxTopo(Node* h,Node* n){
    if(h!=nullptr&&n!=nullptr&&isBSTNode(h,n,n->value)){
        return maxTopo(h,n->left)+maxTopo(h,n->right)+1;
    }
    return 0;
}
/*
用于计算给定二叉树 head 的最大二叉搜索树拓扑结构的大小。
它首先检查根节点是否为 nullptr，如果是，返回拓扑结构大小为 0。
否则，它通过调用 maxTopo 函数来计算包含根节点的最大拓扑结构的大小，
然后递归地计算左子树和右子树的最大拓扑结构大小。最后，返回最大的拓扑结构大小。
*/
int bstTopSize1(Node* head){
    if(head==nullptr){
        return 0;
    }
    int maxnum=maxTopo(head,head);
    maxnum=max(bstTopSize1(head->left),maxnum);
    maxnum=max(bstTopSize1(head->right),maxnum);
    return maxnum;
}

class Record {
public:
    int l;
    int r;
    Record(){};
    Record(int left, int right) {
        l = left;
        r = right;
    }
};


int modifyMap(Node* n, int v, std::map<Node*, Record>& m, bool s) {
   if(n==nullptr||(!m.count(n))){
        return 0;
   }
   Record r=m[n];
   if((s&&n->value>v)||((!s)&&n->value<v)){
        m.erase(n);
        return r.l+r.r+1;
   }else{
        int minus=modifyMap(s?n->right:n->left,v,m,s);
        if(s){
            r.r=r.r-minus;
        }else{
            r.l=r.l-minus;
        }
        m[n]=r;
        return minus;
   }
}

int posOrder(Node* h, std::map<Node*, Record>& map) {
    if (h == nullptr) {
        return 0;
    }
    int ls = posOrder(h->left, map);
    int rs = posOrder(h->right, map);
    modifyMap(h->left, h->value, map, true);
    modifyMap(h->right, h->value, map, false);
    Record* lr = &map[h->left];
    Record* rr = &map[h->right];
    int lbst = lr == nullptr ? 0 : lr->l + lr->r + 1;
    int rbst = rr == nullptr ? 0 : rr->l + rr->r + 1;
    map[h] = Record(lbst, rbst);
    return std::max({lbst + rbst + 1, ls, rs});
}

int bstTopoSize2(Node* head) {
    std::map<Node*, Record> map;
    return posOrder(head, map);
}

int main() {
    // Create and test the tree
    Node* root = new Node(5);
    root->left = new Node(2);
    root->right = new Node(6);
    root->left->left = new Node(1);
    root->left->right = new Node(4);
    root->left->right->left = new Node(3);

    int result = bstTopoSize2(root);
    std::cout << "Maximum BST Topology Size: " << result << std::endl;

    return 0;
}