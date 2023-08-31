#include <iostream>
using namespace std;


class MyMaxHeap{
private:
    int* heap;
    const int limit;
    int heapSize;

    void swap(int* arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
    }

    void heapInsort(int* arr,int index){
        while(arr[index]>arr[(index-1)/2]){
            swap(arr,index,(index-1)/2);
            index=(index-1)/2;
        }
    }

    void heapify(int* arr,int index,int heapSize){
        int left=index*2+1;
        while(left<heapSize){
            int largest=left+1<heapSize&&arr[left+1]>arr[left]?(left+1):left;
            largest=arr[largest]>arr[index]?largest:index;
            if(largest==index){
                break;
            }
            swap(arr,largest,index);
            index=largest;
            left=index*2+1;
        }
    }

    
public:
    MyMaxHeap(int num):limit(num){
        heap=new int[limit];
        heapSize=0;
    }

    bool isEmpty(){
        return heapSize==0;
    }

    bool isFull(){
        return heapSize==limit;
    }
    void push(int value){
        if(heapSize==limit){
            throw std::runtime_error("Heap is full");
        }
        heap[heapSize]=value;
        heapInsort(heap,heapSize++);
    }

    int pop(){
        int ans=heap[0];
        swap(heap,0,--heapSize);
        heapify(heap,0,heapSize);
        return ans;
    }

    ~MyMaxHeap(){
        delete[] heap;
        heap=nullptr;
    }

};



int main() {
    try {
        MyMaxHeap maxHeap(5);
        std::cout << "Is heap empty? " << (maxHeap.isEmpty() ? "Yes" : "No") << std::endl;
        std::cout << "Is heap full? " << (maxHeap.isFull() ? "Yes" : "No") << std::endl;

        maxHeap.push(5);
        maxHeap.push(10);
        maxHeap.push(7);
        maxHeap.push(15);
        maxHeap.push(3);

        std::cout << "Popped element: " << maxHeap.pop() << std::endl;
        std::cout << "Popped element: " << maxHeap.pop() << std::endl;

        std::cout << "Is heap empty? " << (maxHeap.isEmpty() ? "Yes" : "No") << std::endl;
        std::cout << "Is heap full? " << (maxHeap.isFull() ? "Yes" : "No") << std::endl;

        maxHeap.push(12);
        maxHeap.push(8);

        std::cout << "Popped element: " << maxHeap.pop() << std::endl;
        std::cout << "Popped element: " << maxHeap.pop() << std::endl;
        std::cout << "Popped element: " << maxHeap.pop() << std::endl;
        std::cout << "Popped element: " << maxHeap.pop() << std::endl;
        std::cout << "Popped element: " << maxHeap.pop() << std::endl;

        std::cout << "Is heap empty? " << (maxHeap.isEmpty() ? "Yes" : "No") << std::endl;
        std::cout << "Is heap full? " << (maxHeap.isFull() ? "Yes" : "No") << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << "Exception occurred: " << e.what() << std::endl;
    }

    return 0;
}