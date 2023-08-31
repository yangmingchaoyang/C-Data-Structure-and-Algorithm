/*
荷兰国旗问题
问题一
给定一个数组arr，和一个数num，请把小于等于num的数放在数 组的左边，大于num的
数放在数组的右边。要求额外空间复杂度O(1)，时间复杂度O(N)
问题二(荷兰国旗问题)
给定一个数组arr，和一个数num，请把小于num的数放在数组的 左边，等于num的数放
在数组的中间，大于num的数放在数组的 右边。要求额外空间复杂度O(1)，时间复杂度
O(N)

不改进的快速排序
1）把数组范围中的最后一个数作为划分值，然后把数组通过荷兰国旗问题分成三个部
分：
左侧<划分值、中间==划分值、右侧>划分值
2）对左侧范围和右侧范围，递归执行
分析
1）划分值越靠近两侧，复杂度越高；划分值越靠近中间，复杂度越低
2）可以轻而易举的举出最差的例子，所以不改进的快速排序时间复杂度为O(N^2)
*/
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void swap(int arr[], int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int* netherlandsFlag(int arr[], int l, int r) {
    int* res = new int[2];
    res[0] = -1;
    res[1] = -1;
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

void process(int arr[], int l, int r) {
    if (l >= r) {
        return;
    }
    int randomIndex = l + rand() % (r - l + 1);
    swap(arr, randomIndex, r);
    int* res = netherlandsFlag(arr, l, r);
    process(arr, l, res[0] - 1);
    process(arr, res[1] + 1, r);
    delete[] res; // 释放动态分配的数组内存
}

void quickSort(int arr[], int size) {
    if (arr == nullptr || size < 2) {
        return;
    }
    srand(time(0)); // 初始化随机数生成器
    process(arr, 0, size - 1);
}

int main() {
    int arr[] = {5, 3, 8, 2, 1, 9};
    int size = sizeof(arr) / sizeof(arr[0]);
    quickSort(arr, size);
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}