/*输入：
正数数组costs
正数数组profits
正数k
正数m
含义：
costs[i]表示i号项目的花费
profits[i]表示i号项目在扣除花费之后还能挣到的钱(利润)
k表示你只能串行的最多做k个项目
m表示你初始的资金
说明：
你每做完一个项目，马上获得的收益，可以支持你去做下一个项目。
输出：
你最后获得的最大钱数。*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

struct Node {
    int p;
    int c;

    Node(int p, int c) : p(p), c(c) {}
};

struct MinCostComparator {
    bool operator()(const Node& o1, const Node& o2) const {
        return o1.c > o2.c;
    }
};

struct MaxProfitComparator {
    bool operator()(const Node& o1, const Node& o2) const {
        return o1.p < o2.p;
    }
};

int findMaximizedCapital(int k, int W, std::vector<int>& Profits, std::vector<int>& Capital) {
    std::vector<Node> nodes(Profits.size());
    for (int i = 0; i < Profits.size(); i++) {
        nodes[i] = Node(Profits[i], Capital[i]);
    }

    std::priority_queue<Node, std::vector<Node>, MinCostComparator> minCostQ;
    std::priority_queue<Node, std::vector<Node>, MaxProfitComparator> maxProfitQ;
    for (int i = 0; i < nodes.size(); i++) {
        minCostQ.push(nodes[i]);
    }
    for (int i = 0; i < k; i++) {
        while (!minCostQ.empty() && minCostQ.top().c <= W) {
            maxProfitQ.push(minCostQ.top());
            minCostQ.pop();
        }
        if (maxProfitQ.empty()) {
            return W;
        }
        W += maxProfitQ.top().p;
        maxProfitQ.pop();
    }
    return W;
}

int main() {
    // Example usage
    int k = 2;
    int W = 0;
    std::vector<int> Profits = {1, 2, 3};
    std::vector<int> Capital = {0, 1, 1};

    std::cout << findMaximizedCapital(k, W, Profits, Capital) << std::endl;

    return 0;
}
