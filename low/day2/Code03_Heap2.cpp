#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>

template <typename T>
class MyHeap {
private:
    std::vector<T> heap;
    std::unordered_map<T, int> indexMap;
    int heapSize;
    std::function<bool(const T&, const T&)> comparator;


public:
//这些 const 限定符的目的是为了确保函数中的操作不会意外修改传入的参数或被引用的对象，以保持函数的安全性和预期行为。它们可以帮助程序员编写更加健壮和可靠的代码，避免无意间修改数据导致的错误。
    MyHeap(const std::function<bool(const T&, const T&)>& com)
        : heapSize(0), comparator(com) {}

    bool isEmpty() const {
        return heapSize == 0;
    }
    //const 关键字的目的是指定该成员函数为常量成员函数，表示该函数不会修改类的成员变量。既不会修改heapSize的值。
    int size() const {
        return heapSize;
    }

    bool contains(const T& key) const {
        return indexMap.find(key) != indexMap.end();
    }

    void push(const T& value) {
        heap.push_back(value);
        indexMap[value] = heapSize;
        heapInsert(heapSize++);
    }

    T pop() {
        T ans = heap[0];
        int end = heapSize - 1;
        swap(0, end);
        heap.pop_back();
        indexMap.erase(ans);
        heapify(0, --heapSize);
        return ans;
    }

    void resign(const T& value) {//修改一个数的值
        int valueIndex = indexMap[value];
        heapInsert(valueIndex);
        heapify(valueIndex, heapSize);
    }

private:
    void heapify(int index, int heapSize) {
        int left = index * 2 + 1;
        while (left < heapSize) {
            int largest = left + 1 < heapSize && comparator(heap[left + 1], heap[left]) ? left + 1 : left;
            largest = comparator(heap[largest], heap[index]) ? largest : index;
            if (largest == index) {
                break;
            }
            swap(largest, index);
            index = largest;
            left = index * 2 + 1;
        }
    }

    void heapInsert(int index) {
        while (index > 0 && comparator(heap[index], heap[(index - 1) / 2])) {
            swap(index, (index - 1) / 2);
            index = (index - 1) / 2;
        }
    }

    void swap(int i, int j) {
        T o1 = heap[i];
        T o2 = heap[j];
        heap[i] = o2;
        heap[j] = o1;
        indexMap[o1] = j;
        indexMap[o2] = i;
    }
};

// Example usage
int main() {
    // Define a custom comparator for integers (min heap)
    std::function<bool(const int&, const int&)> comp = [](const int& a, const int& b) {
        return a > b;
    };
    MyHeap<int> heap(comp);
    heap.push(5);
    heap.push(3);
    heap.push(8);
    heap.push(2);
    heap.push(1);
    heap.push(9);

    while (!heap.isEmpty()) {
        int val = heap.pop();
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}