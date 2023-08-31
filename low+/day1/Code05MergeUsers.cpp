#include <iostream>
#include <unordered_map>
#include <stack>
#include <vector>

class User{
public:
    std::string a;
    std::string b;
    std::string c;

    User(std::string a,std::string b,std::string c){
        this->a=a;
        this->b=b;
        this->c=c;
    }
};

template <typename V>
class Node {
public:
    V value;
    Node(V v) : value(v) {}
};

template <typename V>
class UnionSet {
public:
    std::unordered_map<V, Node<V>*> nodes;
    std::unordered_map<Node<V>*, Node<V>*> parents;
    std::unordered_map<Node<V>*, int> sizeMap;

public:
    UnionSet(const std::vector<V>& values) {
        for (const V& value : values) {
            Node<V>* node = new Node<V>(value);
            nodes[value] = node;
            parents[node] = node;
            sizeMap[node] = 1;
        }
    }

    Node<V>* findFather(Node<V>* cur) {
        std::stack<Node<V>*> path;
        while (cur != parents[cur]) {
            path.push(cur);
            cur = parents[cur];
        }
        while (!path.empty()) {
            parents[path.top()] = cur;
            path.pop();
        }
        return cur;
    }

    bool isSameSet(V a,V b){
        if(nodes.find(a)==nodes.end()||nodes.find(b)==nodes.end()){
            return false;
        }
        return findFather(nodes[a])==findFather(nodes[b]);
    }
    void unionSets(V a, V b) {
        if (nodes.find(a) == nodes.end() || nodes.find(b) == nodes.end()) {
            return;
        }
        Node<V>* aHead = findFather(nodes[a]);
        Node<V>* bHead = findFather(nodes[b]);
        if (aHead != bHead) {
            int aSetSize = sizeMap[aHead];
            int bSetSize = sizeMap[bHead];
            Node<V>* big = aSetSize >= bSetSize ? aHead : bHead;
            Node<V>* small = big == aHead ? bHead : aHead;
            parents[small] = big;
            sizeMap[big] = aSetSize + bSetSize;
            sizeMap.erase(small);
        }
    }

    int getSetNum(){
        return sizeMap.size();
    }
};

int mergeUsers(std::vector<User*>users){
    UnionSet<User*>unionfind(users);
    std::unordered_map<std::string,User*>mapa;
    std::unordered_map<std::string,User*>mapb;
    std::unordered_map<std::string,User*>mapc;

    for(User* user:users){
        if(mapa.find(user->a)!=mapa.end()){    
            unionfind.unionSets(user,mapa[user->a]);
        }else{
            mapa[user->a]=user;
        }
        if(mapb.find(user->b)!=mapb.end()){    
            unionfind.unionSets(user,mapb[user->b]);
        }else{
            mapb[user->b]=user;
        }
        if(mapc.find(user->c)!=mapc.end()){    
            unionfind.unionSets(user,mapc[user->c]);
        }else{
            mapc[user->c]=user;
        }
    }
    return unionfind.getSetNum();
}