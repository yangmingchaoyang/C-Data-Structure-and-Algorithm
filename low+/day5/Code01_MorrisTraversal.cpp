/*
Morris遍历
一种遍历二叉树的方式，并且时间复杂度O(N)，额外空间复杂度O(1)
通过利用原树中大量空闲指针的方式，达到节省空间的目的
*/
#include <iostream>
#include <vector>
using namespace std;


struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };
void morris(TreeNode* root){
    if(!root) return;
    TreeNode* cur=root;
    TreeNode* mostRight;
    while(cur){
        mostRight = cur->left;
        if(mostRight){
            // 有左子树
            while(mostRight->right&&mostRight->right!=cur){
                // 只要有右孩子并且右孩子不是当前结点
                mostRight = mostRight->right;
            }
            if(!mostRight->right){
                // mostRight的右孩子为空，说明是第一次访问cur
                mostRight->right = cur;
                cur = cur->left;
                continue;
            }else{
                // mostRight的右孩子为cur，说明是第二次来到cur
                mostRight->right = nullptr;
            }
        }
        // 没有左子树或者第二次来到cur结点
        cur = cur->right;
    }
}


vector<int> result;// 保存先序遍历
void morris(TreeNode* root){
    if(!root) return;
    TreeNode* cur=root;
    TreeNode* mostRight;
    while(cur){
        mostRight = cur->left;
        if(mostRight){
            // 有左子树
            while(mostRight->right&&mostRight->right!=cur){
                // 只要有右孩子并且右孩子不是当前结点
                mostRight = mostRight->right;
            }
            if(!mostRight->right){
                // mostRight的右孩子为空，说明是第一次访问cur
                result.push_back(cur->val);
                mostRight->right = cur;
                cur = cur->left;
                continue;
            }else{
                // mostRight的右孩子为cur，说明是第二次来到cur
                mostRight->right = nullptr;
            }
        }else{
            // 没有左子树，只会遍历一次，直接访问
            result.push_back(cur->val);
        }
        // 没有左子树或者第二次来到cur结点
        cur = cur->right;
    }
}


void morris(TreeNode* root){
    if(!root) return;
    TreeNode* cur=root;
    TreeNode* mostRight;
    while(cur){
        mostRight = cur->left;
        if(mostRight){
            // 有左子树
            while(mostRight->right&&mostRight->right!=cur){
                // 只要有右孩子并且右孩子不是当前结点
                mostRight = mostRight->right;
            }
            if(!mostRight->right){
                // mostRight的右孩子为空，说明是第一次访问cur
                mostRight->right = cur;
                cur = cur->left;
                continue;
            }else{
                // mostRight的右孩子为cur，说明是第二次来到cur
                mostRight->right = nullptr;
            }
        }
        // 没有左子树或者第二次来到cur结点
        result.push_back(cur->val);
        cur = cur->right;
    }
}

TreeNode* reverseEdge(TreeNode* root){
    TreeNode* pre = nullptr;
    TreeNode* next = nullptr;
    while(root){
        next = root->right;
        root->right = pre;
        pre = root;
        root = next;
    }
    return pre;
}

void printRightEdge(TreeNode* root){
    TreeNode* tail = reverseEdge(root);// 获得逆置后的尾结点
    TreeNode* cur = tail;//暂存尾结点作为工作节点，最后得重新逆置tail还原
    while(cur){
        result.push_back(cur->val);
        cur = cur->right;
    }
    reverseEdge(tail);
}

void morris(TreeNode* root){
    if(!root) return;
    TreeNode* cur = root;
    TreeNode* mostRight = nullptr;
    while(cur){
        mostRight = cur->left;
        if(mostRight){
            while(mostRight->right&&mostRight->right!=cur){
                mostRight = mostRight->right;
            }
            if(!mostRight->right){
                // 第一次遍历cur节点
                mostRight->right = cur;
                cur = cur->left;
                continue;
            }else{
                mostRight->right = nullptr;
                printRightEdge(cur->left);
            }
        }
        // 没有左孩子或者第二次遍历到cur节点
        cur = cur->right;
    }
    // 最后处理根节点的右边界
    printRightEdge(root);
}