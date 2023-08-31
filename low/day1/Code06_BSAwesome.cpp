/*
    局部最小值问题
*/
#include <iostream>
#include <vector>

using namespace std;


int getLessIndex(vector<int>arr){
    if(arr.empty()){
        return -1;
    }
    if(arr.size()==1||arr[0]<arr[1]){
        return 0;
    }
    if(arr[arr.size()-1]<arr[arr.size()-2]){
        return arr.size()-1;
    }
    int left=1;
    int right=arr.size()-2;
    int mid=0;
    while(left<right){
        mid=(left+right)/2;
        if(arr[mid]>arr[mid-1]){
            right=mid-1;
        }else if(arr[mid]>arr[mid+1]){
            left=mid+1;
        }else{
            return mid;
        }
    }
    return left;
}

