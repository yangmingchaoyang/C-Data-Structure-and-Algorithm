/*
随机快速排序（改进的快速排序）
1）在数组范围中，等概率随机选一个数作为划分值，然后把数组通过荷兰国旗问题分
成三个部分：
左侧<划分值、中间==划分值、右侧>划分值
2）对左侧范围和右侧范围，递归执行
3）时间复杂度为O(N*logN)
*/
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;




void swap(vector<int>& arr, int i, int j) {
    // if (i < 0 || i >= arr.size() || j < 0 || j >= arr.size()) {
    //     // 索引超出数组范围，可以选择抛出异常或采取其他错误处理措施
    //     return; // 或抛出异常 throw std::out_of_range("Index out of range");
    // }
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

vector<int> netherlandsFlag(vector<int>& arr, int l, int r) {
    vector<int> res = {-1, -1};
    if (l > r) {
        return res;
    }
    if (l == r) {
        res[0] = l;
        res[1] = r;
        return res;
    }
    int lessEqual = l - 1;
    int mess = r;
    int index = l;
    while (index < mess) {
        if (arr[index] < arr[r]) {
            swap(arr, index++, ++lessEqual);
        }
        else if (arr[index] > arr[r]) {
            swap(arr, index, --mess);
        }
        else {
            index++;
        }
    }
    swap(arr, mess, r);
    res[0] = lessEqual + 1;
    res[1] = mess;
    return res;
}

void process(vector<int>& arr, int l, int r) {
    if (l >= r) {
        return;
    }
    int randomIndex = l + rand() % (r - l + 1);
    swap(arr, randomIndex, r);
    vector<int> res = netherlandsFlag(arr, l, r);
    process(arr, l, res[0] - 1);
    process(arr, res[1] + 1, r);
}

void quickSort3(vector<int>& arr) {
    if (arr.empty() || arr.size() < 2) {
        return;
    }
    process(arr, 0, arr.size() - 1);
}

int main() {
    srand(time(0)); // 初始化随机数生成器
    vector<int> arr = {5, 3, 8, 2, 1, 9};
    quickSort3(arr);
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}