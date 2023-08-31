/*
一块金条切成两半，是需要花费和长度数值一样的铜板的。比如长度为20的金
条，不管切成长度多大的两半，都要花费20个铜板。
一群人想整分整块金条，怎么分最省铜板?
例如,给定数组{10,20,30}，代表一共三个人，整块金条长度为10+20+30=60。
金条要分成10,20,30三个部分。 如果先把长度60的金条分成10和50，花费60；
再把长度50的金条分成20和30，花费50；一共花费110铜板。
但是如果先把长度60的金条分成30和30，花费60；再把长度30金条分成10和20，
花费30；一共花费90铜板。
输入一个数组，返回分割的最小代价。
*/
#include <iostream>
#include <vector>
#include <queue>
#include <functional>

int lessMoney(std::vector<int>& arr) {
    std::priority_queue<int, std::vector<int>, std::greater<int>> pQ;
    for (int i = 0; i < arr.size(); i++) {
        pQ.push(arr[i]);
    }
    int sum = 0;
    int cur = 0;
    while (pQ.size() > 1) {
        cur = pQ.top();
        pQ.pop();
        cur += pQ.top();
        pQ.pop();
        sum += cur;
        pQ.push(cur);
    }
    return sum;
}

int main() {
    // solution
    std::vector<int> arr = { 6, 7, 8, 9 };
    std::cout << lessMoney(arr) << std::endl;

    std::vector<int> arrForHeap = { 3, 5, 2, 7, 0, 1, 6, 4 };

    // min heap
    std::priority_queue<int, std::vector<int>, std::greater<int>> minQ1;
    for (int i = 0; i < arrForHeap.size(); i++) {
        minQ1.push(arrForHeap[i]);
    }
    while (!minQ1.empty()) {
        std::cout << minQ1.top() << " ";
        minQ1.pop();
    }
    std::cout << std::endl;

    // min heap use Comparator
    std::priority_queue<int, std::vector<int>, std::greater<int>> minQ2;
    for (int i = 0; i < arrForHeap.size(); i++) {
        minQ2.push(arrForHeap[i]);
    }
    while (!minQ2.empty()) {
        std::cout << minQ2.top() << " ";
        minQ2.pop();
    }
    std::cout << std::endl;

    // max heap use Comparator
    std::priority_queue<int, std::vector<int>, std::less<int>> maxQ;
    for (int i = 0; i < arrForHeap.size(); i++) {
        maxQ.push(arrForHeap[i]);
    }
    while (!maxQ.empty()) {
        std::cout << maxQ.top() << " ";
        maxQ.pop();
    }
    std::cout << std::endl;

    return 0;
}
