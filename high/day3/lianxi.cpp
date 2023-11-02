#include <iostream>
#include <unordered_map>

class LFUCache {
public:
    LFUCache(int K) : capacity(K), size(0), headList(nullptr) { }

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
                modifyHeadList(headList);
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

private:
    class Node {
    public:
        int key;
        int value;
        int times;
        Node* up;
        Node* down;

        Node(int k, int v, int t) : key(k), value(v), times(t), up(nullptr), down(nullptr) { }
    };

    class NodeList {
    public:
        Node* head;
        Node* tail;
        NodeList* last;
        NodeList* next;

        NodeList(Node* node) : head(node), tail(node), last(nullptr), next(nullptr) { }

        void addNodeFromHead(Node* newHead) {
            newHead->down = head;
            head->up = newHead;
            head = newHead;
        }

        bool isEmpty() {
            return head == nullptr;
        }

        void deleteNode(Node* node) {
            if (head == tail) {
                head = nullptr;
                tail = nullptr;
            } else {
                if (node == head) {
                    head = node->down;
                    head->up = nullptr;
                } else if (node == tail) {
                    tail = node->up;
                    tail->down = nullptr;
                } else {
                    node->up->down = node->down;
                    node->down->up = node->up;
                }
            }
            node->up = nullptr;
            node->down = nullptr;
            delete node;
        }
    };

    int capacity;
    int size;
    NodeList* headList;
    std::unordered_map<int, Node*> records;
    std::unordered_map<Node*, NodeList*> heads;

    void move(Node* node, NodeList* oldNodeList) {
        oldNodeList->deleteNode(node);
        NodeList* preList = modifyHeadList(oldNodeList) ? oldNodeList->last : oldNodeList;
        NodeList* nextList = oldNodeList->next;
        if (!nextList) {
            NodeList* newList = new NodeList(node);
            if (preList) {
                preList->next = newList;
            }
            newList->last = preList;
            if (!headList) {
                headList = newList;
            }
            heads[node] = newList;
        } else {
            if (nextList->head->times == node->times) {
                nextList->addNodeFromHead(node);
                heads[node] = nextList;
            } else {
                NodeList* newList = new NodeList(node);
                if (preList) {
                    preList->next = newList;
                }
                newList->last = preList;
                newList->next = nextList;
                nextList->last = newList;
                if (headList == nextList) {
                    headList = newList;
                }
                heads[node] = newList;
            }
        }
    }

    bool modifyHeadList(NodeList* removeNodeList) {
        if (removeNodeList->isEmpty()) {
            if (headList == removeNodeList) {
                headList = removeNodeList->next;
                if (headList) {
                    headList->last = nullptr;
                }
            } else {
                removeNodeList->last->next = removeNodeList->next;
                if (removeNodeList->next) {
                    removeNodeList->next->last = removeNodeList->last;
                }
            }
            return true;
        }
        return false;
    }
};

int main() {
    LFUCache cache(2);
    cache.set(1, 1);
    cache.set(2, 2);
    std::cout << cache.get(1) << std::endl; // Output: 1
    cache.set(3, 3);
    std::cout << cache.get(2) << std::endl; // Output: -1 (not found)
    std::cout << cache.get(3) << std::endl; // Output: 3
    return 0;
}



