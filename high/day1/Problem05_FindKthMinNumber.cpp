/*
给定两个一维int数组A和B. 其中：A是长度为m、元素从小到大排好序的有序数组。B是长度为n、元素从小
到大排好序的有序数组。希望从A和B数组中，找出最大的k个数字，要求：使用
尽量少的比较次数。
*/
#include<iostream>
#include<vector>
using namespace std;

int getUpMedian(vector<int>a1,int s1,int e1,vector<int>a2,int s2,int e2){
    int mid1=0;
    int mid2=0;
    int offset=0;
    while(s1<e1){
        mid1=(s1+e1)/2;
        mid2=(s2+e2)/2;
        /*(e1 - s1 + 1) 计算了范围的长度。
        & 1 将范围的长度与二进制位模式为00000001的数进行按位与操作，目的是获取范围的长度的最低位（最右边的位）。
        如果范围的长度是奇数，则结果为1；如果范围的长度是偶数，则结果为0。
        ^ 1 对上一步的结果进行按位异或操作，将1翻转为0，将0翻转为1。
        因此，如果范围的长度是奇数，offset 的计算结果为0；如果范围的长度是偶数，offset 的计算结果为1。*/
        offset=((e1-s1+1)&1)^1;
        if(a1[mid1]>a2[mid2]){//要保证加的数等于减的数
            e1=mid1;
            s2=mid2+offset;
        }else if(a1[mid1]<a2[mid2]){
            s1=mid1+offset;
            e2=mid2;
        }else{
            return a1[mid1];
        }
    }
    return min(a1[s1],a2[s2]);
}

int findKthNum(vector<int>arr1,vector<int>arr2,int kth){
    if(arr1.empty()||arr2.empty()){
        throw runtime_error("Your arr is invalid!");
    }
    if(kth<1||kth>arr1.size()+arr2.size()){
        throw runtime_error("K is invalid");
    }
    vector<int>longs=arr1.size()>=arr2.size()?arr1:arr2;
    vector<int>shorts=arr1.size()<arr2.size()?arr1:arr2;
    int l=longs.size();
    int s=shorts.size();
    //放入函数内的数都是不确定能否可行的数。
    if(kth<=s){
        return getUpMedian(shorts,0,kth-1,longs,0,kth-1);
    }
    if(kth>l){
        if(shorts[kth-l-1]>=longs[l-1]){
            return shorts[kth-l-1];
        }
        if(longs[kth-s-1]>=shorts[s-1]){
            return longs[kth-s-1];
        }
        return getUpMedian(shorts,kth-l,s-1,longs,kth-s,l-1);
    }
    if(longs[kth-s-1]>=shorts[s-1]){
        return longs[kth - s - 1];
    }
    return getUpMedian(shorts,0,s-1,longs,kth-s,kth-1);
}