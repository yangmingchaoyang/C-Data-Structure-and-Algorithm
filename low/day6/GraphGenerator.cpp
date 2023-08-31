/*
图的存储方式
1)邻接表
2)邻接矩阵
如何表达图?生成图?
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
/*
在 Edge 类的析构函数中，我们需要释放指向 Node 对象的指针，但要注意的是，这里的 Edge 类只是简单地持有指向 Node 对象的指针，并不拥有这些对象的所有权。
因此，在析构函数中，我们只需要释放 Edge 对象自己所拥有的资源（如果有），而不需要释放指向其他对象的指针。
*/
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
    std::unordered_map<int, Node*> nodes;
    std::unordered_set<Edge*> edges;

    Graph() {}

    // Destructor to release any dynamically allocated memory
    ~Graph() {
        // Clean up dynamically allocated nodes and edges
        //虽然这两种方式在功能上是等效的，但在循环中访问容器元素时，使用引用方式更加高效和直接
        for (const auto& entry : nodes) {
            delete entry.second;
        }
        for (Edge* edge : edges) {
            delete edge;
        }
    }
};


Graph* creatGraph(std::vector<std::vector<int>>matrix){
    Graph* graph;
    for(int i=0;i<matrix.size();i++){
        int weight=matrix[i][0];
        int from=matrix[i][1];
        int to=matrix[i][2];
        if(!graph->nodes.count(from)){
            graph->nodes[from]=new Node(from);
        }
        if(!graph->nodes.count(to)){
            graph->nodes[to]=new Node(to);
        }

        Node* fromNode=graph->nodes[from];
        Node* toNode=graph->nodes[to];

        Edge* newEdge=new Edge(weight,fromNode,toNode);
        fromNode->nexts.push_back(toNode);
        fromNode->out++;
        toNode->in++;
        fromNode->edges.push_back(newEdge);
        graph->edges.insert(newEdge);
    }
    return graph;
}