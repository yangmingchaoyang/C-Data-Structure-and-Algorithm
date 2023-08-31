#include <iostream>
#include <vector>
class Node{
public:
    int value;
    Node* left;
    Node* right;

    Node(int v){
        this->value=v;
        this->left=nullptr;
        this->right=nullptr;
    }
};

class Info{
public:
    bool issALLBST;
    int maxSubSTSize;
    int max;
    int min;

    Info(bool is,int size,int mi,int ni){
        this->issALLBST=is;
        this->maxSubSTSize=size;
        this->min=mi;
        this->max=ni;
    }
};

Info* process(Node* x){
    if(x==nullptr){
        return nullptr;
    }
    Info* leftInfo=process(x->left);
    Info* rightInfo=process(x->right);

    int min=x->value;
    int max=x->value;

    if(leftInfo!=nullptr){
        min=std::min(min,leftInfo->min);
        max=std::max(max,leftInfo->max);
    }
    if(rightInfo!=nullptr){
        min=std::min(min,rightInfo->min);
        max=std::max(max,rightInfo->max);
    }
    int maxSubBSTSize=0;
    if(leftInfo!=nullptr){
        maxSubBSTSize=leftInfo->maxSubSTSize;
    }
    if(rightInfo!=nullptr){
        maxSubBSTSize=std::max(maxSubBSTSize,rightInfo->maxSubSTSize);
    }
    bool isALLBST=false;
    if((leftInfo==nullptr?true:leftInfo->issALLBST)&&(rightInfo==nullptr?true:rightInfo->issALLBST)&&
    (leftInfo==nullptr?true:leftInfo->max<x->value)&&(rightInfo==nullptr?true:rightInfo->min>x->value)){
        maxSubBSTSize=(leftInfo==nullptr?0:leftInfo->maxSubSTSize)+(rightInfo==nullptr?0:rightInfo->maxSubSTSize)+1;
        isALLBST=true;
    }
    return new Info(isALLBST,maxSubBSTSize,min,max);

}