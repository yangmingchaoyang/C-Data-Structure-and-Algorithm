/*
设计并实现TopKRecord结构，可以不断地向其中加入字符串，并且可以根据字
符串出现的情况随时打印加入次数最多的前k个字符串。具体为:
1）k在TopKRecord实例生成时指定，并且不再变化(k是构造TopKRecord的参数)。
2）含有 add(String str)方法，即向TopKRecord中加入字符串。
3）含有 printTopK()方法，即打印加入次数最多的前k个字符串，打印有哪些
字符串和对应的次数即可，不要求严格按排名顺序打印。
4）如果在出现次数最多的前k个字符串中，最后一名的字符串有多个，比如出
现次数最多的前3个字符串具体排名为：
A 100次 B 90次 C 80次 D 80次 E 80次，其他任何字符串出现次数都
不超过80次
那么只需要打印3个，打印ABC、ABD、ABE都可以。也就是说可以随意抛弃最
后一名，只要求打印k个
要求：
1）在任何时候，add 方法的时间复杂度不超过 O(logk)
2）在任何时候，printTopK方法的时间复杂度不超过O(k)。
*/
//需要使用指针的原因：因为所使用的类，没有一些指定好的>,=,<等的操作，防止了虚传递。
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

    void add(const string& str) {//因为这一步可能会改变中间部分的内容，所以必须使用手写堆结构
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
