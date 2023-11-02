/*
给定一个无序数组 arr，其中元素可正、可负、可 0，给定一个整数 k。求 arr 所
有的子数组 中累加和小于或等于 k 的最长子数组长度。
例如:arr=[3,-2,-4,0,6]，k=-2，相加和小于或等于-2 的最长子数组为{3,-2,-
4,0}，所以结果返回4。
*/
#include<iostream>
#include<vector>
using namespace std;

int maxLengthAwesome(vector<int>arr,int k){
    if(arr.empty()){
        return 0;
    }
    vector<int>minSums(arr.size());
    vector<int>minSumEnds(arr.size());
    minSums[arr.size()-1]=arr[arr.size()-1];
    minSumEnds[arr.size()-1]=arr.size()-1;
    for(int i=arr.size()-2;i>=0;i--){
        if(minSums[i+1]<0){
            minSums[i]=arr[i]+minSums[i+1];
            minSumEnds[i]=minSumEnds[i+1];
        }else{
            minSums[i]=arr[i];
            minSumEnds[i]=i;
        }
    }
    int end=0;
    int sum=0;
    int res=0;
    //i是窗口的最左的位置，end是窗口最右位置的下一个位置
    for(int i=0;i<arr.size();i++){
		// while循环结束之后：
		// 1) 如果以i开头的情况下，累加和<=k的最长子数组是arr[i..end-1]，看看这个子数组长度能不能更新res；
		// 2) 如果以i开头的情况下，累加和<=k的最长子数组比arr[i..end-1]短，更新还是不更新res都不会影响最终结果；
        while(end<arr.size()&&sum+minSums[end]<=k){
            sum+=minSums[end];
            end=minSumEnds[end]+1;
        }
        res=max(res,end-i);
        if(end>i){//窗口内还有数
            sum-=arr[i];
        }else{// 窗口内已经没有数了，说明从i开头的所有子数组累加和都不可能<=k
            end=i+1;
        }        
    }
}