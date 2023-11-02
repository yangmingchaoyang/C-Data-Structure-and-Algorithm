#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Node {
public:
    string str;
    int times;

    Node(const string& s, int t) : str(s), times(t) {}
};

class TopKRecord {
private:
    vector<Node*> heap;
    int index;
    unordered_map<string, Node*> strNodeMap;
    unordered_map<Node*, int> nodeIndexMap;

    void swap(int index1, int index2) {
        nodeIndexMap[heap[index1]] = index2;
        nodeIndexMap[heap[index2]] = index1;
        Node* tmp = heap[index1];
        heap[index1] = heap[index2];
        heap[index2] = tmp;
    }

    void heapInsert(int index) {
        while (index != 0) {
            int parent = (index - 1) / 2;
            if (heap[index]->times < heap[parent]->times) {
                swap(parent, index);
                index = parent;
            } else {
                break;
            }
        }
    }

    void heapify(int index, int heapSize) {
        int left = index * 2 + 1;
        int right = index * 2 + 2;
        int smallest = index;
        while (left < heapSize) {
            if (heap[left]->times < heap[index]->times) {
                smallest = left;
            }
            if (right < heapSize && heap[right]->times < heap[smallest]->times) {
                smallest = right;
            }
            if (smallest != index) {
                swap(smallest, index);
            } else {
                break;
            }
            index = smallest;
            left = index * 2 + 1;
            right = index * 2 + 2;
        }
    }

public:
    TopKRecord(int size) : index(0) {
        heap.resize(size);
    }

    void add(const string& str) {
        Node* curNode = nullptr;
        int preIndex = -1;
        if (strNodeMap.find(str) == strNodeMap.end()) {
            curNode = new Node(str, 1);
            strNodeMap[str] = curNode;
            nodeIndexMap[curNode] = -1;
        } else {
            curNode = strNodeMap[str];
            curNode->times++;
            preIndex = nodeIndexMap[curNode];
        }

        if (preIndex == -1) {
            if (index == heap.size()) {
                if (heap[0]->times < curNode->times) {
                    nodeIndexMap[heap[0]] = -1;
                    nodeIndexMap[curNode] = 0;
                    heap[0] = curNode;
                    heapify(0, index);
                }
            } else {
                nodeIndexMap[curNode] = index;
                heap[index] = curNode;
                heapInsert(index++);
            }
        } else {
            heapify(preIndex, index);
        }
    }

    void printTopK() {
        cout << "TOP: " << endl;
        for (int i = 0; i != heap.size(); i++) {
            if (heap[i] == nullptr) {
                break;
            }
            cout << "Str: " << heap[i]->str;
            cout << " Times: " << heap[i]->times << endl;
        }
    }


    ~TopKRecord(){
        for(auto& entry:strNodeMap){
            if(entry.second!=nullptr){
                delete entry.second;
                entry.second=nullptr;
            }
        }
    }
};

int main() {
    TopKRecord topK(1);  // 创建一个 TopKRecord 对象，保留前3个元素

    topK.add("apple");
    topK.add("banana");
    topK.add("apple");
    topK.add("cherry");
    topK.add("banana");
    topK.add("banana");
    topK.add("banana");
    topK.add("banana");
    topK.add("banana");
    topK.add("banana");
    topK.add("banana");

    topK.printTopK();  // 打印前3个出现次数最多的元素

    return 0;
}
