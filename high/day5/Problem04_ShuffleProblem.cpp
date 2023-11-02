// 给定一个长度为偶数的数组arr，长度记为2*N。前N个为左部分，后N个为右部分。
// arr就可以表示为{L1,L2,..,Ln,R1,R2,..,Rn}，
// 请将数组调整成{R1,L1,R2,L2,..,Rn,Ln}的样子。

/*这段代码的作用是实现 "Wiggle Sort" 算法。Wiggle Sort 是一种排序方法，
将一个整数数组重新排列，使得相邻的元素满足不同的关系。它的主要目标是让数组中的元素成为 "峰谷峰" 或 "谷峰谷" 的形式。*/
#include<iostream>
#include<vector>
using namespace std;

#include <vector>
#include <algorithm>

class Solution {
public:
    int modifyIndex1(int i, int len) {
        if (i <= len / 2) {
            return 2 * i;
        } else {
            return 2 * (i - (len / 2)) - 1;
        }
    }

    int modifyIndex2(int i, int len) {
        return (2 * i) % (len + 1);
    }

    void shuffle(std::vector<int>& arr) {
        if (!arr.empty() && arr.size() % 2 == 0) {
            shuffle(arr, 0, arr.size() - 1);
        }
    }

    void shuffle(std::vector<int>& arr, int L, int R) {
        while (R - L + 1 > 0) {
            int len = R - L + 1;
            int base = 3;
            int k = 1;
            while (base <= (len + 1) / 3) {
                base *= 3;
                k++;
            }
            int half = (base - 1) / 2;
            int mid = (L + R) / 2;
            rotate(arr, L + half, mid, mid + half);
            cycles(arr, L, base - 1, k);
            L = L + base - 1;
        }
    }

    void cycles(std::vector<int>& arr, int start, int len, int k) {
        for (int i = 0, trigger = 1; i < k; i++, trigger *= 3) {
            int preValue = arr[trigger + start - 1];
            int cur = modifyIndex2(trigger, len);
            while (cur != trigger) {
                int tmp = arr[cur + start - 1];
                arr[cur + start - 1] = preValue;
                preValue = tmp;
                cur = modifyIndex2(cur, len);
            }
            arr[cur + start - 1] = preValue;
        }
    }

    void rotate(std::vector<int>& arr, int L, int M, int R) {
        reverse(arr, L, M);
        reverse(arr, M + 1, R);
        reverse(arr, L, R);
    }

    void reverse(std::vector<int>& arr, int L, int R) {
        while (L < R) {
            std::swap(arr[L], arr[R]);
            L++;
            R--;
        }
    }

    void wiggleSort(std::vector<int>& arr) {
        if (arr.empty()) {
            return;
        }
        std::sort(arr.begin(), arr.end());
        if (arr.size() % 2 == 1) {
            shuffle(arr, 1, arr.size() - 1);
        } else {
            shuffle(arr, 0, arr.size() - 1);
            for (int i = 0; i < arr.size(); i += 2) {
                std::swap(arr[i], arr[i + 1]);
            }
        }
    }
};




