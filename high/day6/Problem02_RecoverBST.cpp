/*
一棵二叉树原本是搜索二叉树，但是其中有两个节点调换了位置，使得这棵二叉树不再
是搜索二叉树，请找到这两个错误节点并返回。
已知二叉树中所有节点的值都不一样，给定二叉树的头节点 head，返回一个长度为2的
二叉树节点类型的数组errs，errs[0]表示一个错误节点， errs[1]表示另一个错误节
点。
进阶:
如果 在原问题中得到了这两个错误节点，我们当然可以通过交换两个节点的节点值的方
式让整棵二叉树重新成为搜索二叉树。
但现在要求你不能这么做，而是在结构上完全交换两个节点的位置，请实现调整的函数。
*/
#include<iostream>
#include<vector>
#include<stack>
using namespace std;

class Node{
public:
    int value;
    Node* left;
    Node* right;

    Node(){};
    Node(int data){
        value=data;
        left=nullptr;
        right=nullptr;
    }
};

vector<Node*>getTwoErrNodes(Node* head){
    vector<Node*>errs(2,nullptr);
    if(head==nullptr){
        return errs;
    }
    stack<Node*>stack;
    Node* pre=nullptr;
    while(!stack.empty()||head!=nullptr){
        if(head!=nullptr){
            stack.push(head);
            head=head->left;
        }else{
            head=stack.top();
            stack.pop();
            if(pre!=nullptr&&pre->value>head->value){
                errs[0]=errs[0]==nullptr?pre:errs[0];
                errs[1]=pre;
            }
            pre=head;
            head=head->right;
        }
    }
    return errs;
}

std::vector<Node*> getTwoErrParents(Node* head, Node* e1, Node* e2) {
    std::vector<Node*> parents(2, nullptr);
    if (head == nullptr) {
        return parents;
    }
    std::stack<Node*> stack;
    while (!stack.empty() || head != nullptr) {
        if (head != nullptr) {
            stack.push(head);
            head = head->left;
        } else {
            head = stack.top();
            stack.pop();
            if (head->left == e1 || head->right == e1) {
                parents[0] = head;
            }
            if (head->left == e2 || head->right == e2) {
                parents[1] = head;
            }
            head = head->right;
        }
    }
    return parents;
}



Node* recoverTree(Node* head) {
    std::vector<Node*> errs = getTwoErrNodes(head);
    std::vector<Node*> parents=getTwoErrParents(head,errs[0],errs[1]);
    Node* e1 = errs[0];
    Node* e1P = parents[0];
    Node* e1L = e1->left;
    Node* e1R = e1->right;
    Node* e2 = errs[1];
    Node* e2P = parents[1];
    Node* e2L = e2->left;
    Node* e2R = e2->right;
    if (e1 == head) {
        if (e1 == e2P) { // 在左子树中
            e1->left = e2L;
            e1->right = e2R;
            e2->right = e1;
            e2->left = e1L;
        } else if (e2P->left == e2) { // 在右子树中
            e2P->left = e1;
            e2->left = e1L;
            e2->right = e1R;
            e1->left = e2L;
            e1->right = e2R;
        } else { // 在右子树中
            e2P->right = e1;
            e2->left = e1L;
            e2->right = e1R;
            e1->left = e2L;
            e1->right = e2R;
        }
        head = e2;
    } else if (e2 == head) {
        if (e2 == e1P) { // 在左子树中
            e2->left = e1L;
            e2->right = e1R;
            e1->left = e2;
            e1->right = e2R;
        } else if (e1P->left == e1) { // 在右子树中
            e1P->left = e2;
            e1->left = e2L;
            e1->right = e2R;
            e2->left = e1L;
            e2->right = e1R;
        } else { // 在右子树中
            e1P->right = e2;
            e1->left = e2L;
            e1->right = e2R;
            e2->left = e1L;
            e2->right = e1R;
        }
        head = e1;
    } else {
        if (e1 == e2P) {
            if (e1P->left == e1) { // 在左子树中
                e1P->left = e2;
                e1->left = e2L;
                e1->right = e2R;
                e2->left = e1L;
                e2->right = e1;
            } else { // 在右子树中
                e1P->right = e2;
                e1->left = e2L;
                e1->right = e2R;
                e2->left = e1L;
                e2->right = e1;
            }
        } else if (e2 == e1P) {
            if (e2P->left == e2) { // 在左子树中
                e2P->left = e1;
                e2->left = e1L;
                e2->right = e1R;
                e1->left = e2;
                e1->right = e2R;
            } else { // 在右子树中
                e2P->right = e1;
                e2->left = e1L;
                e2->right = e1R;
                e1->left = e2;
                e1->right = e2R;
            }
        } else {
            if (e1P->left == e1) {
                if (e2P->left == e2) { // 位于左子树的左子树中
                    e1->left = e2L;
                    e1->right = e2R;
                    e2->left = e1L;
                    e2->right = e1R;
                    e1P->left = e2;
                    e2P->left = e1;
                } else { // 位于左子树的右子树中
                    e1->left = e2L;
                    e1->right = e2R;
                    e2->left = e1L;
                    e2->right = e1R;
                    e1P->left = e2;
                    e2P->right = e1;
                }
            } else {
                if (e2P->left == e2) { // 位于右子树的左子树中
                    e1->left = e2L;
                    e1->right = e2R;
                    e2->left = e1L;
                    e2->right = e1R;
                    e1P->right = e2;
                    e2P->left = e1;
                } else { // 位于右子树的右子树中
                    e1->left = e2L;
                    e1->right = e2R;
                    e2->left = e1L;
                    e2->right = e1R;
                    e1P->right = e2;
                    e2P->right = e1;
                }
            }
        }
    }
    return head;
}
