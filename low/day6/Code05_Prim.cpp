/*
prim算法
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
        // for (Edge* edge : edges) {
        //     delete edge;
        // }
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

class EdgeComparator{
public:
    bool operator()(const Edge* o1,const Edge* o2){//谁越小越放在前面。
        return o1->weight<o2->weight;
    }
};


std::unordered_set<Edge*>primMST(Graph* graph){
    std::priority_queue<Edge*,std::vector<Edge*>,EdgeComparator>priorityQueue;
    //哪些点被解锁了
    std::unordered_set<Node*>nodeSet;
    //已经考虑过的边不要重复考虑
    std::unordered_set<Edge*>edgeSet;
    std::unordered_set<Edge*>result;
    for(const auto& entry:graph->nodes){
        Node* node=entry.second;
        if(!nodeSet.count(node)){
            nodeSet.insert(node);
            for(Edge* edge:node->edges){
                if(!edgeSet.count(edge)){
                    edgeSet.insert(edge);//考虑过的边不需要再加入队列中
                    priorityQueue.push(edge);
                }
            }
            while(!priorityQueue.empty()){
                Edge* edge=priorityQueue.top();
                priorityQueue.pop();
                Node* toNode=edge->to;
                if(!nodeSet.count(toNode)){
                    nodeSet.insert(toNode);//这样能够锁定一条边
                    result.insert(edge);//相当于找到了一个路径
                }
                for(Edge* nextEdge:toNode->edges){
                    if(!edgeSet.count(nextEdge)){
                        edgeSet.insert(nextEdge);
                        priorityQueue.push(nextEdge);
                    }
                }
            }
        }
    }
    return result;
}




int main() {
    // Create a graph
    Graph* graph=new Graph();

    // Create nodes and add them to the graph
    Node* node1 = new Node(1);
    Node* node2 = new Node(2);
    Node* node3 = new Node(3);
    graph->nodes[1] = node1;
    graph->nodes[2] = node2;
    graph->nodes[3] = node3;

    // Create edges and add them to the graph and nodes
    Edge* edge1 = new Edge(2, node1, node2);
    Edge* edge2 = new Edge(3, node1, node3);
    Edge* edge3 = new Edge(1, node2, node3);
    graph->edges.insert(edge1);
    graph->edges.insert(edge2);
    graph->edges.insert(edge3);
    node1->edges.push_back(edge1);
    node1->edges.push_back(edge2);
    node1->out = 2;
    node2->edges.push_back(edge3);
    node2->in = 1;
    node2->out = 1;
    node3->in = 2;

    // Find the minimum spanning tree using Prim's algorithm
    std::unordered_set<Edge*> mst = primMST(graph);

    // Output the edges in the minimum spanning tree
    std::cout << "Minimum Spanning Tree Edges:" << std::endl;
    if (!mst.empty()) {
        std::cout << "最小生成树的边:" << std::endl;
        for (Edge* edge : mst) {
            std::cout << "从节点 " << edge->from->value << " 到节点 " << edge->to->value << "，权重: " << edge->weight << std::endl;
        }
    } else {
        std::cout << "给定图中不存在最小生成树。" << std::endl;
    }

    // Clean up dynamically allocated memory
    delete graph;

    return 0;
}