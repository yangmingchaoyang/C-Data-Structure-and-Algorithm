/*
    选择排序
*/
#include <iostream>
using namespace std;

void swap(int* arr,int i,int j){
    int temp=arr[i];
    arr[i]=arr[j];
    arr[j]=temp;
}

//找到最大值索引，放在最前面。
void selectionsort(int* arr,int len){
    if(arr==nullptr||len<2){
        return;
    }
    for(int i=0;i<len;i++){
        int minindex=i;
        for(int j=i+1;j<len;j++){//找到最大的索引值然后交换
            minindex=arr[minindex]<arr[j]?minindex:j;
        }
        if(minindex!=i){
            swap(arr,minindex,i);
        }
    }
}

int main(){
    int arr[10]={1,2,10,24,20,18,67,56,70,10};
    cout<<sizeof(arr)/sizeof(arr[0])<<endl;
    selectionsort(arr,sizeof(arr)/sizeof(arr[0]));
    for(int i=0;i<10;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    return 0;
}