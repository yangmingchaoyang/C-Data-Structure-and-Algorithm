#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
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

            Node* query(Node* o1,Node* o2){
                Node* cur1=o1;
                Node* cur2=o2;
                unordered_set<Node*>path;
                while(map.count(cur1)){
                    path.insert(cur1);
                    cur1=map[cur1];
                }
                while(!path.count(cur2)){
                    cur2=map[cur2];
                }
                return cur2;
            }


};