/*
Dijkstra算法
适用范围：没有权值为负数的边
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

Node* getMinDistanceAndUnselectedNode(std::unordered_map<Node*,int>ditanceMap,std::unordered_set<Node*>touchedNode){
    Node* minNode=nullptr;
    int minDistance=INT_MAX;
    for(const auto& entry:ditanceMap){
        Node* node=entry.first;
        int distance=entry.second;
        if(!touchedNode.count(node)&&distance<minDistance){
            minNode=node;
            minDistance=distance;
        }
    }
    return minNode;
}

std::unordered_map<Node*,int>dijkstral(Node* from){
        //从from出发到所有点的最小距离
        //key:从from出发到达key
        //value:从from出发到达key的最小距离
        //如果在表中，没有T的记录，含义是从head出发到T这个点的距离为正无穷
        std::unordered_map<Node*,int>distanceMap;
        distanceMap[from]=0;
        //已经求距离的节点，存在selectedNode中，以后再也不碰
        std::unordered_set<Node*>slecteNode;
        Node* minNode=getMinDistanceAndUnselectedNode(distanceMap,slecteNode);
        while(minNode!=nullptr){
            int distance=distanceMap[minNode];
            for(Edge* edge:minNode->edges){
                Node* toNode=edge->to;
                if(!distanceMap.count(toNode)){
                    distanceMap[toNode]=distance+edge->weight;
                }else{
                    distanceMap[toNode]=std::min(distanceMap[toNode],distance+edge->weight);
                }
            }
            slecteNode.insert(minNode);
            minNode=getMinDistanceAndUnselectedNode(distanceMap,slecteNode);
        }
    return distanceMap;
}

class NodeRecord{
public:
    Node* node;
    int distance;
    NodeRecord(Node* node,int distance):node(node),distance(distance){};
};


class NodeHeap{
private:
    std::vector<Node*>nodes;
    std::unordered_map<Node*,int>heapIndexMap;//key是某个node,value上面数组的位置
    std::unordered_map<Node*,int>distanceMap;//key是某个节点，value是从源头到该节点的最小距离
    int size;//堆上有多少点

public:
    NodeHeap(int length){
        nodes.resize(length);
        size=0;
    }

    bool isEmpty(){
        return size==0;
    }
    
    void swap(int index1,int index2){
        heapIndexMap[nodes[index1]]=index2;
        heapIndexMap[nodes[index2]]=index1;
        Node* tmp=nodes[index1];
        nodes[index1]=nodes[index2];
        nodes[index2]=tmp;
    }

    //点是否进来过
    bool isEntered(Node* node){
        return heapIndexMap.count(node);
    }

    //是否在堆上
    bool inHeap(Node* node){
        return isEntered(node)&&heapIndexMap[node]!=-1;
    }

    void insertHeapify(Node* node,int index){
        while(distanceMap[nodes[index]]<distanceMap[nodes[(index-1)/2]]){
            swap(index,(index-1)/2);
            index=(index-1)/2;
        }
    }

    void heapify(int index,int size){
        int left=index*2+1;
        while(left<size){
            int smallest=left+1<size&&distanceMap[nodes[left+1]]<distanceMap[nodes[left]]?left+1:left;
            smallest=distanceMap[nodes[smallest]]<distanceMap[nodes[index]]?smallest:index;
            if(smallest==index){
                break;
            }
            swap(smallest,index);
            index=smallest;
            left=index*2+1;
        }
    }




    //有一个点叫node,现在发现了一个从源节点出发到达node的距离为distance
    //判断要不要更新，如果需要就更新
    void addOrUpdateOrIgnore(Node* node,int distance){
        if(inHeap(node)){
            distanceMap[node]=std::min(distanceMap[node],distance);
            insertHeapify(node,heapIndexMap[node]);
        }
        if(!isEntered(node)){
            nodes[size]=node;
            heapIndexMap[node]=size;
            distanceMap[node]=distance;
            insertHeapify(node,size++);
        }
    }

    NodeRecord* pop(){
        NodeRecord* nodeRecord=new NodeRecord(nodes[0],distanceMap[nodes[0]]);
        swap(0,size-1);
        heapIndexMap[nodes[size-1]]=-1;
        //nodes[size-1]==nullptr;
        distanceMap.erase(nodes[size-1]);
        heapify(0,--size);
        return nodeRecord;
    }

    ~NodeHeap(){
        for(Node* node:nodes){
                if(node!=nullptr){
                    delete node;
                }
        }
    }
};

std::unordered_map<Node*,int>dijkstra2(Node* head,int size){
    NodeHeap* nodeHeap=new NodeHeap(size);
    nodeHeap->addOrUpdateOrIgnore(head,0);
    std::unordered_map<Node*,int>result;
    while(!nodeHeap->isEmpty()){
        NodeRecord* record=nodeHeap->pop();
        Node* cur=record->node;
        int distance=record->distance;
        for(Edge* edge:cur->edges){
            nodeHeap->addOrUpdateOrIgnore(edge->to,edge->weight+distance);
        }
        result[cur]=distance;
    }
    if(nodeHeap!=nullptr){
        delete nodeHeap;
        nodeHeap=nullptr;
    }
    return result;
}


int main() {
    // Create a graph
    Graph graph;

    // Create nodes
    Node* node1 = new Node(1);
    Node* node2 = new Node(2);
    Node* node3 = new Node(3);
    Node* node4 = new Node(4);

    // Add nodes to the graph
    graph.nodes[node1->value] = node1;
    graph.nodes[node2->value] = node2;
    graph.nodes[node3->value] = node3;
    graph.nodes[node4->value] = node4;

    // Create edges
    Edge* edge1 = new Edge(10, node1, node2);
    Edge* edge2 = new Edge(5, node2, node3);
    Edge* edge3 = new Edge(15, node1, node3);
    Edge* edge4 = new Edge(20, node2, node4);
    Edge* edge5 = new Edge(8, node3, node4);

    // Add edges to the graph
    graph.edges.insert(edge1);
    graph.edges.insert(edge2);
    graph.edges.insert(edge3);
    graph.edges.insert(edge4);
    graph.edges.insert(edge5);

    // Run Dijkstra's algorithm from node1
    Node* startNode = node1;
    std::unordered_map<Node*, int> result = dijkstra2(startNode, 4);

    // Display the shortest distances from startNode to other nodes
    for (const auto& entry : result) {
        Node* node = entry.first;
        int distance = entry.second;
        std::cout << "Shortest distance from Node " << startNode->value
                  << " to Node " << node->value << " is: " << distance << std::endl;
    }

    // Clean up dynamically allocated nodes and edges
    delete node1;
    delete node2;
    delete node3;
    delete node4;
    delete edge1;
    delete edge2;
    delete edge3;
    delete edge4;
    delete edge5;

    return 0;
}