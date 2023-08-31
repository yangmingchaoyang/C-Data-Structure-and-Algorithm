/*
    在一个有序数组中，找>=某个数最左侧的位置    
*/
#include <iostream>
#include <vector>

int nearestLeftIndex(std::vector<int>& arr, int value) {
    int L = 0;
    int R = arr.size() - 1;
    int index = -1; // 记录最左的对号
    while (L <= R) {
        int mid = L + ((R - L) >> 1);
        if (arr[mid] >= value) {
            index = mid;
            R = mid - 1;
        } else {
            L = mid + 1;
        }
    }
    return index;
}



int nearestRightIndex(std::vector<int>& arr, int value) {
    int L = 0;
    int R = arr.size() - 1;
    int index = -1; // 记录最右的对号
    while (L <= R) {
        int mid = L + ((R - L) >> 1);
        if (arr[mid] > value) {
            R = mid - 1;
        } else {
            index = mid;
            L = mid + 1;
        }
    }
    return index;
}
int main() {
    // Example usage
    std::vector<int> arr = {1, 3, 5, 7, 9, 11};
    int value = 6;
    int result = nearestLeftIndex(arr, value);
    std::cout << "Result: " << result << std::endl;
    return 0;
}