//并查集结构的详解和实现
#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>

/*
在 C++ 的 std::unordered_map 中，nodes[value] = node; 和 nodes.insert(std::make_pair(value, node)); 是实现上等价的，它们都可以用来将一个键值对插入到哈希表中或更新已存在的键的值。这两种方式在大多数情况下都会得到相同的结果，但是它们有一些微妙的区别。

nodes[value] = node;: 如果键 value 不存在于哈希表中，则此方法会在哈希表中插入一个新的键值对 (value, node)。如果键 value 已经存在，则会将其对应的值更新为 node。

nodes.insert(std::make_pair(value, node));: 使用 insert 方法插入键值对 (value, node)。如果键 value 已经存在于哈希表中，则 insert 方法不会对哈希表做任何修改。

虽然这两种方法在大多数情况下都可以得到相同的结果，但有几个需要考虑的因素：

如果您希望在插入时确保键 value 尚未存在，可以使用 insert 方法，因为它不会更新已存在的键的值。

如果您希望在更新值时忽略键是否存在，可以使用 nodes[value] = node;。

如果您需要检查插入是否成功，可以使用 insert 方法，并检查返回值。

所以，选择使用哪种方法取决于您的需求和偏好。在本例中，您可以选择 nodes[value] = node; 或 nodes.insert(std::make_pair(value, node));，它们都可以实现相同的功能。
*/


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

   
};


int main() {
    // Testing the UnionSet class
    std::vector<int> values = {1, 2, 3, 4, 5};
    UnionSet<int> unionSet(values);

    unionSet.unionSets(1, 2);
    unionSet.unionSets(2, 3);

    std::cout << "Representative of 1: " << unionSet.findFather(unionSet.nodes[1])->value << std::endl;
    std::cout << "Representative of 2: " << unionSet.findFather(unionSet.nodes[2])->value << std::endl;
    std::cout << "Representative of 3: " << unionSet.findFather(unionSet.nodes[3])->value << std::endl;
    std::cout << "Representative of 4: " << unionSet.findFather(unionSet.nodes[4])->value << std::endl;
    std::cout << "Representative of 5: " << unionSet.findFather(unionSet.nodes[5])->value << std::endl;

    return 0;
}