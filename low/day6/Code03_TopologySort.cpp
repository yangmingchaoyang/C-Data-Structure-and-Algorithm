/*
拓扑排序算法
适用范围：要求有向图，且有入度为0的节点，且没有环
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
/*
在 Edge 类的析构函数中，我们需要释放指向 Node 对象的指针，但要注意的是，这里的 Edge 类只是简单地持有指向 Node 对象的指针，并不拥有这些对象的所有权。
因此，在析构函数中，我们只需要释放 Edge 对象自己所拥有的资源（如果有），而不需要释放指向其他对象的指针。
*/
class Node;

class Edge{
public:
    int weight;
    Node* from;
    Node* to;

    Edge(int weight,Node* from,Node* to){
        this->weight=weight;
        this->from=from;
        this->to=to;
    }

};


class Node{
public:
    int value;
    //到这个点的边的数量
    int in;
    //这个边出去的数量
    int out;
    //直接邻居
    std::vector<Node*>nexts;
    //从这个点出发的边的集合
    std::vector<Edge*>edges;
    Node(int value){
        this->value=value;
        in=0;
        out=0;
    }

    ~Node() {
        //Clean up dynamically allocated edges
        for (Edge* edge : edges) {
            delete edge;
        }
    }
};


class Graph {
public:
//编号为几的点
    std::unordered_map<int, Node*> nodes;
    std::unordered_set<Edge*> edges;

    Graph() {}

    // Destructor to release any dynamically allocated memory
    ~Graph() {
        // Clean up dynamically allocated nodes and edges
        for (const auto& entry : nodes) {
            delete entry.second;
        }
        for (Edge* edge : edges) {
            delete edge;
        }
    }
};


std::vector<Node*>sortedTopology(Graph* graph){
    std::unordered_map<Node*,int>inMap;
    std::queue<Node*>zeroInQueue;
    for (const auto& entry : graph->nodes) {
        Node* node = entry.second;
        inMap[node] = node->in;
        if (node->in == 0) {
            zeroInQueue.push(node);
        }
    }
    std::vector<Node*>result;
    while(!zeroInQueue.empty()){
        Node* cur=zeroInQueue.front();
        zeroInQueue.pop();
        for(Node* next:cur->nexts){
            inMap[next]--;
            if(inMap[next]==0){
                zeroInQueue.push(next);
            }
        }
    }
    return result;
}