/*
数组异或和的定义:把数组中所有的数异或起来得到的值
给定一个整型数组 arr，其中可能有正、有负、有零，求其中子数组的最大异或和
【举例】
arr = {3}
数组只有1个数，所以只有一个子数组，就是这个数组本身，最大异或和为3
arr = {3, -28, -29, 2}
子数组有很多，但是{-28, -29}这个子数组的异或和为7，是所有子数组中最大的
*/
#include <iostream>
#include <vector>

class NumTrie {
public:
    class Node {
    public:
        Node* nexts[2];
        Node() {
            nexts[0] = nullptr;
            nexts[1] = nullptr;
        }
    };

    Node* head;

    NumTrie() {
        head = new Node();
    }

    /*add(int num) 方法用于将整数 num 的二进制表示添加到 NumTrie 中。
    它按位遍历 num，从最高位到最低位，根据每一位的值（0 或 1），将节点添加到树中的相应分支。
    这样，NumTrie 将包含一系列整数的二进制表示。*/
    void add(int num) {
        Node* cur = head;
        for (int move = 31; move >= 0; move--) {
            int path = (num >> move) & 1;
            if (cur->nexts[path] == nullptr) {
                cur->nexts[path] = new Node();
            }
            cur = cur->nexts[path];
        }
    }
    /*
    maxXor(int num) 方法用于查找与给定整数 num 的二进制表示异或结果最大的整数。
    它通过从 NumTrie 的根节点开始，根据 num 的每一位来选择最优的路径，以最大程度地增加异或结果的值。该方法返回最大异或值。
    */
    int maxXor(int num) {
        Node* cur = head;
        int res = 0;
        for (int move = 31; move >= 0; move--) {
            int path = (num >> move) & 1;
            int best = (move == 31) ? path : (path ^ 1);
            best = (cur->nexts[best] != nullptr) ? best : (best ^ 1);
            res |= (path ^ best) << move;//最高位的异或值
            cur = cur->nexts[best];
        }
        return res;
    }
};

int maxXorSubarray(std::vector<int>& arr) {
    if (arr.empty()) {
        return 0;
    }

    int max = INT_MIN;
    int eor = 0;
    NumTrie numTrie;
    numTrie.add(0);

    for (int i = 0; i < arr.size(); i++) {
        eor ^= arr[i];////存的就是前i项的异或和数组。
        max = std::max(max, numTrie.maxXor(eor));
        numTrie.add(eor);
    }

    return max;
}

int main() {
    std::vector<int> arr = {3, 10, 5, 25, 2, 8};
    int result = maxXorSubarray(arr);
    std::cout << "Maximum XOR subarray: " << result << std::endl;
    return 0;
}

