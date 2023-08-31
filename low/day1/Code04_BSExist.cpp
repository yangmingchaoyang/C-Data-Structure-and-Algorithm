/*
    在一个有序数组中，找某个数是否存在
*/

#include <iostream>
#include <vector>

bool exist(std::vector<int>& sortedArr, int num) {
    if (sortedArr.empty()) {
        return false;
    }
    int L = 0;
    int R = sortedArr.size() - 1;
    int mid = 0;

    while (L <= R) {//L到达过了最后一个数。
        mid = L + ((R - L) >> 1); // mid=(L+R)/2
        if (sortedArr[mid] == num) {
            return true;
        } else if (sortedArr[mid] > num) {
            R = mid - 1;
        } else {
            L = mid + 1;
        }
    }
    return false;
}

int main() {
    // Example usage
    std::vector<int> sortedArr = {1, 3, 5, 7, 9, 11};
    int num = 5;
    bool result = exist(sortedArr, num);
    std::cout << "Result: " << (result ? "true" : "false") << std::endl;
    return 0;
}