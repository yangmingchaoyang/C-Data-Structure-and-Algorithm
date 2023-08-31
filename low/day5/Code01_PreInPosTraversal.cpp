/*
用递归和非递归两种方式实现二叉树的先序、中序、后序遍历
*/
#include <iostream>
#include <stack>
#include <string>
class Node{
public:
    int value;
    Node* left;
    Node* right;

    Node(int v){
        this->value=v;
        left = nullptr;
        right = nullptr;
    }
};


void f(Node* head){
    if(head==nullptr){
        return;
    }
    f(head->left);
    f(head->right);
}


//先序遍历
void pre(Node* head){
    if(head==nullptr){
        return;
    }
    std::cout<<head->value<<" "<<std::endl;
    pre(head->left);
    pre(head->right);
}

void in(Node* head){
    if(head==nullptr){
        return;
    }
    in(head->left);
    std::cout<<head->value<<" "<<std::endl;
    in(head->right);   
}


void pos(Node* head){
    if(head==nullptr){
        return;
    }
    pos(head->left);
    pos(head->right);
    std::cout<<head->value<<" "<<std::endl;   
}

void pre(Node* head){
    if(head!=nullptr){
        std::stack<Node*>stack;
        stack.push(head);
        while(!stack.empty()){
            Node* cur=stack.top();
            stack.pop();
            std::cout<<cur->value<<" ";
            if(cur->right!=nullptr){
                stack.push(cur->right);
            }
            if(cur->left!=nullptr){
                stack.push(cur->left);
            }
        }
        std::cout<<std::endl;
    }
}


void in(Node* head){
    if(head!=nullptr){
        std::stack<Node*>stack;
        Node* cur=head;
        while(!stack.empty()||cur!=nullptr){
            if(cur!=nullptr){
                stack.push(cur);
                cur=cur->left;
            }
            else{
                cur=stack.top();
                stack.pop();
                std::cout<<cur->value<<" ";
                cur=cur->right;
            }
        }
        std::cout<<std::endl;
    }
}


void pos(Node* head){
    std::stack<Node*>s1;
    std::stack<Node*>s2;
    Node* cur=head;
    s1.push(cur);
    while(!s1.empty()){
        cur=s1.top();
        s1.pop();
        s2.push(cur);
        if(cur->left!=nullptr){
            s1.push(cur->left);
        }
        if(cur->right!=nullptr){
            s1.push(cur->right);
        }
    }
    while(!s2.empty()){
        std::cout<<s2.top()<<" ";
        s2.pop();
    }
    std::cout<<std::endl;
}