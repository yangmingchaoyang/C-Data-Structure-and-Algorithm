/*
给定一个数组 arr，该数组无序，但每个值均为正数，再给定一个正数 k。求 arr 的
所有子数组中所有元素相加和为 k 的最长子数组长度。
例如，arr=[1,2,1,1,1]，k=3。
累加和为 3 的最长子数组为[1,1,1]，所以结果返回 3。
要求：时间复杂度O(N)，额外空间复杂度O(1)
*/
#include<iostream>
#include<vector>
using namespace std;
//滑动窗口
int getMaxLength(vector<int>arr,int k){
    if(arr.empty()||k<0){
        return 0;
    }
    int left=0;
    int right=0;
    int sum=arr[0];
    int len=0;
    while(right<arr.size()){
        if(sum==k){
            len=max(len,right-left+1);
            sum-=arr[left++];
        }else if(sum<k){
            right++;
            if(right==arr.size()){
                break;
            }
            sum+=arr[right];
        }else{
            sum-=arr[left++];
        }
    }
    return len;
}
