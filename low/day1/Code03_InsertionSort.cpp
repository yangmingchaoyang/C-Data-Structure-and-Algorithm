/*
    插入排序
*/
#include <iostream>
using namespace std;

void swap(int* arr,int i,int j){
    int temp=arr[i];
    arr[i]=arr[j];
    arr[j]=temp;
}

//  1,2,10,24,3
//先保证1,2有序，在保证123有序;所以最外围从index=1开始

void insortionsort(int* arr,int len){
    if(arr==nullptr||len<2){
        return;
    }
    for(int i=1;i<len;i++){
        for(int j=i-1;j>=0&&arr[j+1]<arr[j];j--){//先让0~1有序，再让0~2有序，依次向后
            swap(arr,j+1,j);
        }
    }
}

int main(){
    int arr[10]={1,2,10,24,20,18,67,56,70,10};
    cout<<sizeof(arr)/sizeof(arr[0])<<endl;
    insortionsort(arr,sizeof(arr)/sizeof(arr[0]));
    for(int i=0;i<10;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    return 0;
}