/*
图的宽度优先遍历
1，利用队列实现
2，从源节点开始依次按照宽度进队列，然后弹出
3，每弹出一个点，把该节点所有没有进过队列的邻接点放入队列
4，直到队列变空
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
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
        for (const auto& entry : nodes) {
            delete entry.second;
        }
        for (Edge* edge : edges) {
            delete edge;
        }
    }
};



//宽度优先遍历
void bfs(Node* node){
    if(node==nullptr){
        return;
    }
    std::queue<Node*> queue;
    std::unordered_set<Node*>set;
    queue.push(node);
    set.insert(node);
    while(!queue.empty()){
        Node* cur=queue.front();
        queue.pop();
        std::cout<<cur->value<<" ";
        for(Node* next:cur->nexts){
            if(!set.count(next)){
                set.insert(next);
                queue.push(next);
            }
        }
    }
}
/*
在图中，节点之间可以有多个连接（边），因此在进行遍历时，可能会遇到同一个节点被多次加入队列的情况。
如果不使用 set 来进行去重，那么同一个节点可能会被重复处理，导致遍历过程无限循环，无法正确结束。
*/