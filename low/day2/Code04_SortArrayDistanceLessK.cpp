/*
堆排序扩展题目
已知一个几乎有序的数组，几乎有序是指，如果把数组排好顺序的话，每个元
素移动的距离可以不超过k，并且k相对于数组来说比较小。请选择一个合适的
排序算法针对这个数据进行排序。
*/

#include <iostream>
#include <vector>
#include <queue>
#include <functional>


struct CompareGreater {//大根堆
    bool operator()(int a, int b) {
        return a > b;
    }
};

struct CompareLess {//小根堆
    bool operator()(int a, int b) {
        return a < b;
    }
    
};


void sortedArrDistanceLessK(std::vector<int>& arr,int k){
    std::priority_queue<int, std::vector<int>, CompareGreater> maxHeap;
    int index=0;
    for (; index <= std::min(static_cast<int>(arr.size()) - 1, k - 1); index++) {
        maxHeap.push(arr[index]);
    }
    int i=0;
    for(;index<arr.size();i++,index++){
        maxHeap.push(arr[index]);
        arr[i]=maxHeap.top();
        maxHeap.pop();
    }
    while(!maxHeap.empty()){
        arr[i++]=maxHeap.top();
        maxHeap.pop();
    }
}


// Validation code
void printArray(const std::vector<int>& arr) {
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> arr = {5, 3, 8, 2, 1, 9};
    int k = 3;

    std::cout << "Original array: ";
    printArray(arr);

    sortedArrDistanceLessK(arr, k);

    std::cout << "Sorted array: ";
    printArray(arr);

    return 0;
}