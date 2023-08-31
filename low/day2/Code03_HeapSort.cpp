/*
堆
1，堆结构就是用数组实现的完全二叉树结构
2，完全二叉树中如果每棵子树的最大值都在顶部就是大根堆
3，完全二叉树中如果每棵子树的最小值都在顶部就是小根堆
4，堆结构的heapInsert与heapify操作
5，堆结构的增大和减少
6，优先级队列结构，就是堆结构
*/
#include <iostream>
using namespace std;
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


    void heapSort(int* arr,int len){
        if(arr==nullptr||len<2){
            return;
        }
        for(int i=len-1;i>=0;i--){
            heapify(arr,i,len);
        }
        int heapsize=len;
        swap(arr,0,--heapsize);
        while(heapsize>0){
            heapify(arr,0,heapsize);
            swap(arr,0,--heapsize);
        }
    }


int main() {
    int arr[] = {5, 3, 8, 2, 1, 9};
    int size = sizeof(arr) / sizeof(arr[0]);
    heapSort(arr, size);
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}
