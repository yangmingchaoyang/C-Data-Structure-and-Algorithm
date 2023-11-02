/*
一个数组的异或和是指数组中所有的数异或在一起的结果。给定一个数组arr，求最大子数组异或和。
"最大子数组异或和" 指的是在给定整数数组中找到一个连续子数组（子序列），使得该子数组中的元素经过异或运算后得到的值最大。
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int mostEOR(vector<int>& arr) {
    int ans = 0;
    int xor_val = 0;
    vector<int> mosts(arr.size(), 0);//一个与输入数组 arr 同样大小的数组，用于存储每个位置的最大异或和子序列长度。
    unordered_map<int, int> map;
    map[0] = -1;
    for (int i = 0; i < arr.size(); i++) {
        xor_val ^= arr[i];
        if (map.find(xor_val) != map.end()) {
            int pre = map[xor_val];
            mosts[i] = (pre == -1) ? 1 : (mosts[pre] + 1);
        }
        if (i > 0) {
            mosts[i] = max(mosts[i - 1], mosts[i]);
        }
        map[xor_val]=i;
        ans=max(ans, mosts[i]);
    }
    return ans;
}

int comparator(vector<int>& arr) {
    if (arr.empty()) {
        return 0;
    }

    int n = arr.size();
    vector<int> eors(n);
    int eor = 0;
    for (int i = 0; i < n; i++) {
        eor ^= arr[i];
        eors[i] = eor;
    }

    vector<int> mosts(n);
    mosts[0] = (arr[0] == 0) ? 1 : 0;
    for (int i = 1; i < n; i++) {
        mosts[i] = (eors[i] == 0) ? 1 : 0;
        for (int j = 0; j < i; j++) {
            if ((eors[i] ^ eors[j]) == 0) {
                mosts[i] = max(mosts[i], mosts[j] + 1);
            }
        }
        mosts[i] = max(mosts[i], mosts[i - 1]);
    }

    return mosts[n - 1];
}


struct TrieNode {
    TrieNode* next[2];
    TrieNode() {
        next[0] = nullptr;
        next[1] = nullptr;
    }
};

class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
        int maxXOR = 0;
        TrieNode* root = new TrieNode();

        for (int num : nums) {
            TrieNode* curr = root;
            TrieNode* XORNode = root;
            int currXOR = 0;

            for (int i = 31; i >= 0; i--) {
                int bit = (num >> i) & 1;
                if (!curr->next[bit]) {
                    curr->next[bit] = new TrieNode();
                }
                curr = curr->next[bit];

                int oppositeBit = 1 - bit;
                if (XORNode->next[oppositeBit]) {
                    currXOR = (currXOR << 1) | 1;
                    XORNode = XORNode->next[oppositeBit];
                } else {
                    currXOR = currXOR << 1;
                    XORNode = XORNode->next[bit];
                }
            }

            maxXOR = max(maxXOR, currXOR);
        }

        return maxXOR;
    }
};






int main() {
    vector<int> arr = {3, 2, 1, 0, 3, 2, 1};
    int result = mostEOR(arr);
    cout << "Maximum EOR: " << result << endl;
    return 0;
}