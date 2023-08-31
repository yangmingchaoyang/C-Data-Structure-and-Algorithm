/*
kruskal算法
适用范围：要求无向图
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <algorithm>
/*
在 Edge 类的析构函数中，我们需要释放指向 Node 对象的指针，但要注意的是，这里的 Edge 类只是简单地持有指向 Node 对象的指针，并不拥有这些对象的所有权。
因此，在析构函数中，我们只需要释放 Edge 对象自己所拥有的资源（如果有），而不需要释放指向其他对象的指针。
*/
class Node;
class Edge;
class UnionFind;

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



class UnionFind{
private:
    std::unordered_map<Node*,Node*>fatherMap;
    std::unordered_map<Node*,int>sizeMap;
public:
    UnionFind(){
    };

    void makeSets(const std::vector<Node*>& nodes) {
        fatherMap.clear();
        sizeMap.clear();
        for (Node* node : nodes) {
            fatherMap[node] = node;
            sizeMap[node] = 1;
        }
    }

    Node* findFather(Node* n){
        std::stack<Node*>path;
        while(n!=fatherMap[n]){
            path.push(n);
            n=fatherMap[n];
        }
        while(!path.empty()){
            fatherMap[path.top()]=n;
            path.pop();
        }
        return n;
    }

    bool isSameSet(Node* a,Node* b){
        return  findFather(a)==findFather(b);
    }

    void unionset(Node* a,Node* b){
        if(a==nullptr||b==nullptr){
            return;
        }
        Node* aDai=findFather(a);
        Node* bDai=findFather(b);
        if(aDai!=bDai){
            int aSetSize=sizeMap[aDai];
            int bSetSize=sizeMap[bDai];
            Node* bigNode=aSetSize>bSetSize?aDai:bDai;
            Node* smallNode=bigNode==aDai?bDai:aDai;
            fatherMap[smallNode]=bigNode;
            sizeMap[bigNode]=aSetSize+bSetSize;
            sizeMap.erase(smallNode);
        }
    }
};


class EdgeComparator {
public:
    bool operator()(const Edge* o1, const Edge* o2) const {
        return o1->weight < o2->weight;
    }
};


std::unordered_set<Edge*> kruskalMST(Graph& graph) {
    UnionFind unionFind;
    std::vector<Node*> nodesVector;

    // Get all nodes from graph and put them into a vector
    for (const auto& entry : graph.nodes) {
        nodesVector.push_back(entry.second);
    }
    // Make sets for UnionFind
    unionFind.makeSets(nodesVector);
    // Use a min-heap (priority queue) to sort edges by weight in ascending order
    std::priority_queue<Edge*, std::vector<Edge*>, EdgeComparator> priorityQueue;
    for (Edge* edge : graph.edges) {
        priorityQueue.push(edge);
    }

    std::unordered_set<Edge*> result;
    while (!priorityQueue.empty()) {
        Edge* edge = priorityQueue.top();
        priorityQueue.pop();

        if (!unionFind.isSameSet(edge->from, edge->to)) {
            result.insert(edge);
            unionFind.unionset(edge->from, edge->to);
        }
    }

    return result;
}

int main() {
    // Create a graph and add nodes and edges
    Graph graph;

    // Create nodes
    Node* node1 = new Node(1);
    Node* node2 = new Node(2);
    // Add nodes to the graph
    graph.nodes[1] = node1;
    graph.nodes[2] = node2;

    // Create edges
    Edge* edge1 = new Edge(1, node1, node2);
    // Add edges to the graph
    graph.edges.insert(edge1);

    // Call Kruskal algorithm and get the result
    std::unordered_set<Edge*> mstEdges = kruskalMST(graph);

    // Print the Minimum Spanning Tree (MST) edges
    std::cout << "Minimum Spanning Tree (MST) Edges: ";
    for (const auto& edge : mstEdges) {
        std::cout << edge->from->value << "->" << edge->to->value << " ";
    }
    std::cout << std::endl;

    // Clean up dynamically allocated resources
    // for (const auto& entry : graph.nodes) {
    //     delete entry.second;
    // }
    // for (Edge* edge : graph.edges) {
    //     delete edge;
    // }

    return 0;
}