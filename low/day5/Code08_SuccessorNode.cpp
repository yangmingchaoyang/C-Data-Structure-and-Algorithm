/*
在二叉树中找到一个节点的后继节点
【题目】 现在有一种新的二叉树节点类型如下:
public class Node {
public int value;
public Node left;
public Node right;
public Node parent;
public Node(int val) {
value = val;
}
}
该结构比普通二叉树节点结构多了一个指向父节点的parent指针。
假设有一棵Node类型的节点组成的二叉树，树中每个节点的parent指针都正确地指向自己的父节点，头节
点的parent指向null。
只给一个在二叉树中的某个节点node，请实现返回node的后继节点的函数。
在二叉树的中序遍历的序列中， node的下一个节点叫作node的后继节点。
*/

#include<iostream>
#include <vector>
using namespace std;

class Node{
public:
    int value;
    Node* left;
    Node* right;
    Node* parent;

    Node(int v){
        value=v;
        left=nullptr;
        right=nullptr;
        parent=nullptr;
    }
};


Node* getLeftMost(Node* node){
    if(node==nullptr){
        return node;
    }
    while(node->left!=nullptr){
        node=node->left;
    }
    return node;
}

Node* getSuccessorNode(Node* node){
    if(node==nullptr){
        return node;
    }
    if(node->right!=nullptr){
        return getLeftMost(node->right);
    }else{
        Node* parent=node->parent;
        while(parent!=nullptr&&parent->right==node){
            node=parent;
            parent=node->parent;
        }
        return parent;
    }
}