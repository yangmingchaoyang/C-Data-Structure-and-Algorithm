/*
广度优先遍历
1，利用栈实现
2，从源节点开始把节点按照深度放入栈，然后弹出
3，每弹出一个点，把该节点下一个没有进过栈的邻接点放入栈
4，直到栈变空
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


void dfs(Node* node){
    if(node==nullptr){
        return;
    }
    std::stack<Node*>stack;
    std::unordered_set<Node*>set;
    stack.push(node);
    set.insert(node);
    std::cout<<node->value<<" ";
    while(!stack.empty()){
        Node* cur=stack.top();
        stack.pop();
        for(Node* next:cur->nexts){
            if(!set.count(next)){
                stack.push(cur);
                stack.push(next);
                set.insert(next);
                std::cout<<next->value<<" ";
                break;//break退出了for循环
            }
        }
    }
}


int main() {
    // Test code for createGraph function
    // Build the graph, add nodes and connections

    Node* node1 = new Node(1);
    Node* node2 = new Node(2);
    Node* node3 = new Node(3);
    Node* node4 = new Node(4);

    node1->nexts.push_back(node2);
    node1->nexts.push_back(node3);

    node2->nexts.push_back(node4);

    node3->nexts.push_back(node4);

    Graph graph;
    graph.nodes[1] = node1;
    graph.nodes[2] = node2;
    graph.nodes[3] = node3;
    graph.nodes[4] = node4;

    dfs(node1); // Start DFS from node1

    // Clean up memory by deleting dynamically allocated nodes
    graph.nodes.clear();
    graph.edges.clear();

    return 0;
}