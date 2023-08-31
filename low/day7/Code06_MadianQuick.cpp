/*
一个数据流中，随时可以取得中位数
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

class MedianHolder {
private:
    std::priority_queue<int, std::vector<int>, MaxHeapComparator> maxHeap;
    std::priority_queue<int, std::vector<int>, MinHeapComparator> minHeap;

    void modifyTwoHeapsSize() {
        if (maxHeap.size() == minHeap.size() + 2) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        }
        if (minHeap.size() == maxHeap.size() + 2) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }

public:
    void addNumber(int num) {
        if (maxHeap.empty() || num <= maxHeap.top()) {
            maxHeap.push(num);
        } else {
            minHeap.push(num);
        }
        modifyTwoHeapsSize();
    }

    int getMedian() {
        int maxHeapSize = maxHeap.size();
        int minHeapSize = minHeap.size();
        if (maxHeapSize + minHeapSize == 0) {
            return -1; // Return a sentinel value or handle differently
        }
        int maxHeapHead = maxHeap.top();
        int minHeapHead = minHeap.top();
        if (((maxHeapSize + minHeapSize) & 1) == 0) {
            return (maxHeapHead + minHeapHead) / 2;
        }
        return maxHeapSize > minHeapSize ? maxHeapHead : minHeapHead;
    }
};

struct MaxHeapComparator {
    bool operator()(int o1, int o2) const {
        return o1 < o2;
    }
};

struct MinHeapComparator {
    bool operator()(int o1, int o2) const {
        return o1 > o2;
    }
};

int main() {
    bool err = false;
    int testTimes = 200000;
    for (int i = 0; i != testTimes; i++) {
        int len = 30;
        int maxValue = 1000;
        std::vector<int> arr(len);
        for (int j = 0; j != len; j++) {
            arr[j] = std::rand() % (maxValue + 1);
        }
        MedianHolder medianHold;
        for (int j = 0; j != len; j++) {
            medianHold.addNumber(arr[j]);
        }
        int medianHoldResult = medianHold.getMedian();
        std::sort(arr.begin(), arr.end());
        int getMedianOfArrayResult = arr[(len - 1) / 2];
        if (len % 2 == 0) {
            getMedianOfArrayResult = (arr[len / 2 - 1] + arr[len / 2]) / 2;
        }
        if (medianHoldResult != getMedianOfArrayResult) {
            err = true;
            // Print relevant information or handle the error
            break;
        }
    }
    if (err) {
        std::cout << "Oops..what a problem!" << std::endl;
    } else {
        std::cout << "Today is a beautiful day^_^" << std::endl;
    }

    return 0;
}
