/*
二叉树的序列化和反序列化
就是内存里的一棵树如何变成字符串形式，又如何从字符串形式变成内存里的树
如何判断一颗二叉树是不是另一棵二叉树的子树？
*/
#include <iostream>
#include <queue>
#include <string>
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

void pres(Node* head,std::queue<std::string>ans){
    if(head==nullptr){
        ans.push(nullptr);
    }else{
        ans.push(std::to_string(head->value));
        pres(head->left,ans);
        pres(head->right,ans);
    }

}

std::queue<std::string>preSerial(Node* head){
    std::queue<std::string>ans;
    pres(head,ans);
    return ans;
}


Node* preb(std::queue<std::string>prelist){
    std::string value=prelist.front();
    if(value.empty()){
        return nullptr;
    }
    Node* head = new Node(std::stoi(value));
    head->left = preb(prelist);
    head->right = preb(prelist);
    
    return head;
}

Node* buildByPreQueue(std::queue<std::string>& prelist) {
    if (prelist.empty()) {
        return nullptr;
    }
    return preb(prelist);
}

void printPreOrder(Node* head) {
    if (head == nullptr) {
        return;
    }
    std::cout << head->value << " ";
    printPreOrder(head->left);
    printPreOrder(head->right);
}

Node* generateNode(std::string val){
    if(!val.empty()){
        return nullptr;
    }
    return new Node(std::stoi(val));
}


std::queue<std::string>levelSerial(Node* head){
    std::queue<std::string>ans;
    if(head==nullptr){
        ans.push(nullptr);
    }else{
        ans.push(std::to_string(head->value));
        std::queue<Node*>queue;
        queue.push(head);
        while(!queue.empty()){
            head=queue.front();
            if(head->left!=nullptr){
                ans.push(std::to_string(head->left->value));
                queue.push(head->left);
            }else{
                ans.push(nullptr);
            }
            if(head->right!=nullptr){
                ans.push(std::to_string(head->right->value));
                queue.push(head->right);
            }else{
                ans.push(nullptr);
            }
        }
    }
    return ans;
}



int main() {
    // 构建二叉树
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);

    // 将二叉树进行序列化
    std::queue<std::string> serialized = preSerial(root);

    // 输出序列化结果
    std::cout << "Serialized tree: ";
    while (!serialized.empty()) {
        std::cout << serialized.front() << " ";
        serialized.pop();
    }
    std::cout << std::endl;

    // 从序列化结果中恢复二叉树
    Node* restored = buildByPreQueue(serialized);

    // 打印恢复的二叉树的前序遍历结果
    std::cout << "Restored tree (Preorder): ";
    printPreOrder(restored);
    std::cout << std::endl;

    // 释放二叉树的内存
    // ...

    return 0;
}
