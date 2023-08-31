/*
    冒泡排序
*/
#include <iostream>
using namespace std;

void swap(int* arr,int i,int j){
    int temp=arr[i];
    arr[i]=arr[j];
    arr[j]=temp;
}
//一直交换，找到最大值交换到最后面。


void bubblesort(int* arr, int len){
    if(arr==nullptr||len<2){
        return;
    }
    for(int i=len-1;i>0;i--){
        for(int j=0;j<i;j++){
            if(arr[j]>arr[j+1]){
                swap(arr,j,j+1);
            }
        }
    }
}


int main(){
    int arr[10]={1,2,10,24,20,18,67,56,70,10};//数组元素是指针，需要手动释放指针所指向的内存。
    //而使用标准库的容器类可以自动管理数组元素的析构和内存释放。
    cout<<sizeof(arr)/sizeof(arr[0])<<endl;
    bubblesort(arr,sizeof(arr)/sizeof(arr[0]));
    for(int i=0;i<10;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    return 0;
}