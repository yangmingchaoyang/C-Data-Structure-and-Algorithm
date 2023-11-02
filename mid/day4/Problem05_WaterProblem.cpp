/*
给定一个数组arr，已知其中所有的值都是非负的，将这个数组看作一个容器，
请返回容器能装多少水
比如，arr = {3，1，2，5，2，4}，根据值画出的直方图就是容器形状，该容
器可以装下5格水
再比如，arr = {4，5，1，3，2}，该容器可以装下2格水
*/
#include <iostream>
#include <vector>

using namespace std;
int getWater1(vector<int> arr){
    if(arr.empty()||arr.size()<3){
        return 0;
    }
    int value=0;
    for(int i=0;i<arr.size()-1;i++){
        int leftMax=0;
        int rightMax=0;
        for(int l=0;l<i;i++){
            leftMax=max(arr[l],leftMax);
        }
        for(int r=i+1;r<arr.size();r++){
            rightMax=max(arr[r],rightMax);
        }
        value+=max(0,min(leftMax,rightMax)-arr[i]);
    }
    return value;
}


int getWater2(vector<int>arr){
    if(arr.empty()||arr.size()<3){
        return 0;
    }
    int n=arr.size()-2;
    vector<int>leftMaxs(n);
    leftMaxs[0]==arr[0];
    for(int i=1;i<n;i++){
        leftMaxs[i]=max(leftMaxs[i-1],arr[i]);
    }
    vector<int>rightMaxs(n);
    rightMaxs[n-1]=arr[n-1];
    for(int i=n-2;i>=0;i--){
        rightMaxs[i]=max(rightMaxs[i+1],rightMaxs[i]);
    }
    int value=0;
    for(int i=1;i<=n;i++){
        value+=max(0,min(leftMaxs[i-1],rightMaxs[i-1])-arr[i]);
    }

}





int getWater4(vector<int>arr){
    if(arr.empty()||arr.size()<3){
        return 0;
    }
    int value=0;
    int leftMax=arr[0];
    int rightMax=arr[arr.size()-1];
    int l=1;
    int r=arr.size()-2;
    while(l<=r){
        if(leftMax<=rightMax){
            value+=max(0,leftMax-arr[l]);
            leftMax=max(leftMax,arr[l++]);
        }else{
            value=max(0,rightMax-arr[r]);
            rightMax=max(rightMax,arr[r--]);
        }
    }
    return value;
}