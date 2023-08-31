//给定两个二叉树的节点node1和node2，找到他们的最低公共祖先节点
#include <iostream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

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

Node* lowestAncestor(Node* head,Node* o1,Node* o2){
    if(head==nullptr||head==o1||head==o2){
        return head;
    }
    Node* left=lowestAncestor(head->left,o1,o2);
    Node* right=lowestAncestor(head->right,o1,o2);
    if(left!=nullptr&&right!=nullptr){
        return head;
    }
    return left!=nullptr?left:right;
}


class Record1{
    private:
        unordered_map<Node*,Node*>map;

        void setMap(Node* head){
            if(head==nullptr){
                return;
            }
            if(head->left!=nullptr){
                map[head->left]=head;
            }
            if(head->right!=nullptr){
                map[head->right]=head;
            }
            setMap(head->left);
            setMap(head->right);
        }

    public:
        Record1(Node* head){
            if(head!=nullptr){
                map[head]=nullptr;
            }
            setMap(head);
        }

        Node* query(Node* o1,Node* o2){//找到两个节点的最低公共祖先。
            unordered_set<Node*>path;
            while(map.count(o1)){
                path.insert(o1);
                o1=map[o1];
            }
            while(!path.count(o2)){
                o2=map[o2];
            }
            return o2;
        }
};


class Record2 {
private:
    std::unordered_map<Node*, std::unordered_map<Node*, Node*>> map;

public:
    Record2(Node* head) {
        initMap(head);
        setMap(head);
    }

    void initMap(Node* head) {
        if (head == nullptr) {
            return;
        }
        map[head] = std::unordered_map<Node*, Node*>();
        initMap(head->left);
        initMap(head->right);
    }

    void setMap(Node* head) {
        if (head == nullptr) {
            return;
        }
        headRecord(head->left, head);
        headRecord(head->right, head);
        subRecord(head);
        setMap(head->left);
        setMap(head->right);
    }
    //传递的 h 不变
    void headRecord(Node* n, Node* h) {
        if (n == nullptr) {
            return;
        }
        map[n][h] = h;
        headRecord(n->left, h);
        headRecord(n->right, h);
    }

    void subRecord(Node* head) {
        if (head == nullptr) {
            return;
        }
        preLeft(head->left, head->right, head);
        subRecord(head->left);
        subRecord(head->right);
    }

    void preLeft(Node* l, Node* r, Node* h) {
        if (l == nullptr) {
            return;
        }
        preRight(l, r, h);
        preLeft(l->left, r, h);
        preLeft(l->right, r, h);
    }

    void preRight(Node* l, Node* r, Node* h) {
        if (r == nullptr) {
            return;
        }
        map[l][r] = h;
        preRight(l, r->left, h);
        preRight(l, r->right, h);
    }

    Node* query(Node* o1, Node* o2) {
        if (o1 == o2) {
            return o1;
        }
        if (map.count(o1)) {
            return map[o1][o2];
        }
        if (map.count(o2)) {
            return map[o2][o1];
        }
        return nullptr;
    }
};

int main() {
    Node* head = new Node(1);
    head->left = new Node(2);
    head->right = new Node(3);
    head->left->left = new Node(4);
    head->left->right = new Node(5);
    head->right->left = new Node(6);
    head->right->right = new Node(7);

    Record2 record(head);

    // Test query function
    Node* o1 = head->left->right;
    Node* o2 = head->right->left;

    Node* ancestor = record.query(o1, o2);
    if (ancestor != nullptr) {
        std::cout << "Lowest common ancestor: " << ancestor->value << std::endl;
    } else {
        std::cout << "No common ancestor found." << std::endl;
    }

    // Clean up memory (deallocate nodes)
    // ...

    return 0;
}