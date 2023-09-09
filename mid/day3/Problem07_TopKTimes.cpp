/*给定一个字符串类型的数组arr，求其中出现次数最多的前K个*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <functional>

using namespace std;

// 定义 Node 结构体
struct Node {
    string str;
    int times;

    Node(const string& s, int t) : str(s), times(t) {}
};

// 定义 NodeComparator 结构体，用于比较 Node 对象
//小的放在前面
struct NodeComparator {
    bool operator()(const Node& o1, const Node& o2) const {
        return o1.times > o2.times;
    }
};

// 定义函数，找到并打印前K个频率最高的字符串
void printTopKAndRank(const vector<string>& arr, int topK) {
    if (arr.empty() || topK < 1) {
        return;
    }

    unordered_map<string, int> map;
    for (const string& str : arr) {
        map[str]++;
    }

    topK = min(static_cast<int>(arr.size()), topK);
    priority_queue<Node, vector<Node>, NodeComparator> heap;

    for (const auto& entry : map) {
        Node cur(entry.first, entry.second);
        if (heap.size() < topK) {
            heap.push(cur);
        } else {
            if (heap.top().times < cur.times) {
                heap.pop();
                heap.push(cur);
            }
        }
    }

    while (!heap.empty()) {
        cout << heap.top().str << endl;
        heap.pop();
    }
}

int main() {
    vector<string> arr = {"apple", "banana", "apple", "cherry", "banana", "apple"};
    int topK = 2;
    printTopKAndRank(arr, topK);
    return 0;
}
