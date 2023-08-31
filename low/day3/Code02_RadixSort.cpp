/*
    2）基数排序
*/

#include <iostream>
#include <cmath>
#include <vector>

// 求最大值有多少位
int maxbits(const std::vector<int>& arr) {
    int max = INT_MIN;
    for (int i = 0; i < arr.size(); i++) {
        max = std::max(max, arr[i]);
    }
    int res = 0;

    while (max != 0) {
        res++;
        max /= 10;
    }
    return res;
}
// 获取数字 x 在第 d 位上的数字
int getDigit(int x, int d) {
    return ((x / static_cast<int>(std::pow(10, d - 1))) % 10);
}




void radixSortarr(std::vector<int>& arr, int l, int r, int digit) {
    const int radix = 10;
    int i = 0, j = 0;
    std::vector<int> help(r - l + 1);
    for (int d = 1; d <= digit; d++) {
        std::vector<int> count(radix, 0); // count[0...9]
        for (i = l; i <= r; i++) {
            j = getDigit(arr[i], d);
            count[j]++;
        }
        // for (i = 1; i < radix; i++) {//从小到大排
        //     count[i] += count[i - 1];
        // }
        for (i = radix - 2; i >= 0; i--) {//从大到小排
            count[i] += count[i + 1];
        }
        for (i = r; i >= l; i--) {
            j = getDigit(arr[i], d);
            help[count[j] - 1] = arr[i];
            count[j]--;
        }
        for (i = l, j = 0; i <= r; i++, j++) {
            arr[i] = help[j];
        }
    }
}



// 基数排序
void radixSort(std::vector<int>& arr) {
    if (arr.empty() || arr.size() < 2) {
        return;
    }
    int max_bit = maxbits(arr);
    radixSortarr(arr, 0, arr.size() - 1, max_bit);
}





int main() {
    std::vector<int> arr = {170, 45, 75, 90, 802, 24, 2, 66};
    radixSort(arr);

    std::cout << "Sorted array: ";
    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}