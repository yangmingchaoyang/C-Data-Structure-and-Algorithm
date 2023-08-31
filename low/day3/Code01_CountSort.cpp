/*
桶排序思想下的排序
1）计数排序
分析：
1)桶排序思想下的排序都是不基于比较的排序
2)时间复杂度为O(N)，额外空间负载度O(M)
3)应用范围有限，需要样本的数据状况满足桶的划分
*/
#include <iostream>
#include <vector>
#include <algorithm>

void countSort(std::vector<int>& arr) {
    if (arr.empty() || arr.size() < 2) {
        return;
    }
    int max = INT_MIN;
    for (int i = 0; i < arr.size(); i++) {
        max = std::max(max, arr[i]);
    }

    std::vector<int> bucket(max + 1, 0);
    for (int i = 0; i < arr.size(); i++) {
        bucket[arr[i]]++;
    }

    int i = 0;
    for (int j = 0; j < bucket.size(); j++) {
        while (bucket[j]-- > 0) {
            arr[i++] = j;
        }
    }
}

int main() {
    std::vector<int> arr = {5, 2, 9, 1, 3};
    countSort(arr);

    std::cout << "Sorted array: ";
    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}