/*
二实现如下功能
void set(int key, int value)：加入或修改key对应的value
int get(int key)：查询key对应的value值
但是缓存中最多放K条记录，如果新的第K+1条记录要加入，就需要根据策略删掉一条记录，
然后才能把新记录加入。
这个策略为：在缓存结构的K条记录中，哪一个key从进入缓存结构的时刻开始，被调用
set或者get的次数最少，就删掉这个key的记录；如果调用次数最少的key有多个，上次调
用发生最早的key被删除。
这就是LFU缓存替换算法。实现这个结构，K作为参数给出。
*/
#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

class Node{
public:
    int key;
    int value;
    int times;//这个节点发生get或者set的次数总和
    Node* up;//节点之是双向链表所以有上一个节点
    Node* down;//有下一个节点

    Node(){};

    Node(int key,int value,int times){
        this->key=key;
        this->value=value;
        this->times=times;
    }
};

//桶结构
class NodeList{
public:
    Node* head;//头节点
    Node* tail;//尾节点
    NodeList* last;//桶之间是双向链表所以有前一个桶
    NodeList* next;//桶之间是双向链表所以有后一个桶

    NodeList(){
        head==nullptr;
        tail==nullptr;
        last==nullptr;
        next==nullptr;
    };

    NodeList(Node* node){
        head=node;
        tail=node;
    }

    //把一个新的节点加入这个桶，新的节点都放在顶端变成新的头部
    void addNodeFromHead(Node* newHead){
        newHead->down=head;
        head->up=newHead;
        head=newHead;
    }

    //判断这个桶是不是空的
    bool isEmpty(){
        return head==nullptr;
    }

    //删除node节点并保证node的上下环境重新连接
    void deleteNode(Node* node){
        if(head==tail){
            head==nullptr;
            tail==nullptr;
        }else{
            if(node==head){
                head=node->down;
                head->up=nullptr;
            }else if(node==tail){
                tail=node->up;
                tail->down=nullptr;
            }else{
                node->up->down=node->down;
                node->down->up=node->up;
            }
        }
        node->up=nullptr;
        node->down=nullptr;
        delete node;
    }

     ~NodeList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->down;
            delete temp;
        }
    }

};

//总的缓存结构
class LFUCache{
private:
    int capacity;//缓存的大小限制，即K
    int size;//缓存目前有多少个节点
    unordered_map<int,Node*>records;//表示key（int)由那个节点（Node)代表
    unordered_map<Node*,NodeList*>heads;// 表示节点(Node)在哪个桶(NodeList)里
    NodeList* headList;// 整个结构中位于最左的桶

public:
    LFUCache(int K){
        this->capacity=K;
        this->size=0;
        this->records=unordered_map<int,Node*>();
        this->heads=unordered_map<Node*,NodeList*>();
        headList==nullptr;
    }

	// removeNodeList：刚刚减少了一个节点的桶
	// 这个函数的功能是，判断刚刚减少了一个节点的桶是不是已经空了。
	// 1）如果不空，什么也不做
	//
	// 2)如果空了，removeNodeList还是整个缓存结构最左的桶(headList)。
	// 删掉这个桶的同时也要让最左的桶变成removeNodeList的下一个。
	//
	// 3)如果空了，removeNodeList不是整个缓存结构最左的桶(headList)。
	// 把这个桶删除，并保证上一个的桶和下一个桶之间还是双向链表的连接方式
	//
	// 函数的返回值表示刚刚减少了一个节点的桶是不是已经空了，空了返回true；不空返回false
private:
    bool modifyHeadList(NodeList* removeNodeList){
        if(removeNodeList->isEmpty()){
            if(headList==removeNodeList){
                headList=removeNodeList->next;
                if(headList!=nullptr){
                    headList->last=nullptr;
                }
            }else{
                removeNodeList->last->next=removeNodeList->next;
                if(removeNodeList->next!=nullptr){
                    removeNodeList->next->last=removeNodeList->last;
                }
            }
            delete removeNodeList;
            removeNodeList=nullptr;
            return true;
        }
        return false;
    }


	// 函数的功能
	// node这个节点的次数+1了，这个节点原来在oldNodeList里。
	// 把node从oldNodeList删掉，然后放到次数+1的桶中
	// 整个过程既要保证桶之间仍然是双向链表，也要保证节点之间仍然是双向链表
    void move(Node* node,NodeList* oldNodeList){
        oldNodeList->deleteNode(node);
        // preList表示次数+1的桶的前一个桶是谁
		// 如果oldNodeList删掉node之后还有节点，oldNodeList就是次数+1的桶的前一个桶
		// 如果oldNodeList删掉node之后空了，oldNodeList是需要删除的，所以次数+1的桶的前一个桶，是oldNodeList的前一个
        NodeList* preList=modifyHeadList(oldNodeList)?oldNodeList->last:oldNodeList;
        // nextList表示次数+1的桶的后一个桶是谁
        NodeList* nextList=oldNodeList->next;
        if(nextList==nullptr){
            NodeList* newList=new NodeList(node);
            if(preList!=nullptr){
                preList->next=newList;
            }
            newList->last=preList;
            if(headList==nullptr){
                headList=newList;
            }
            heads[node]=newList;
        }else{//只有和nexlist->head相等或者比他大这两种可能。
            if(nextList->head->times==node->times){//只有time相等的点放在一起。
                nextList->addNodeFromHead(node);//说明可以加入nextList这个集合。
                heads[node]=nextList;
            }else{
                NodeList* newList=new NodeList(node);
                if(preList!=nullptr){
                    preList->next=newList;
                }
                newList->last=preList;
                newList->next=nextList;
                nextList->last=newList;
                if(headList==nextList){
                    headList=newList;
                }
                heads[node]=newList;
            }
        }
    }

    void set(int key, int value) {
        if (records.find(key) != records.end()) {
            Node* node = records[key];
            node->value = value;
            node->times++;
            NodeList* curNodeList = heads[node];
            move(node, curNodeList);
        } else {
            if (size == capacity) {
                Node* node = headList->tail;
                headList->deleteNode(node);
                modifyHeadList(headList);//判断是否删除该节点
                records.erase(node->key);
                heads.erase(node);
                size--;
            }
            Node* node = new Node(key, value, 1);
            if (!headList) {
                headList = new NodeList(node);
            } else {
                if (headList->head->times == node->times) {
                    headList->addNodeFromHead(node);
                } else {
                    NodeList* newList = new NodeList(node);
                    newList->next = headList;
                    headList->last = newList;
                    headList = newList;
                }
            }
            records[key] = node;
            heads[node] = headList;
            size++;
        }
    }

    int get(int key) {
        if (records.find(key) == records.end()) {
            return -1;
        }
        Node* node = records[key];
        node->times++;
        NodeList* curNodeList = heads[node];
        move(node, curNodeList);
        return node->value;
    }

};
