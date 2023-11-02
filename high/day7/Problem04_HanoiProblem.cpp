/*
汉诺塔游戏的要求把所有的圆盘从左边都移到右边的柱子上，给定一个整型数组arr，
其中只含有1、2和3，代表所有圆盘目前的状态，1代表左柱，2代表中柱，3代表右柱，
arr[i]的值代表第i+1个圆盘的位置。
比如，arr=[3,3,2,1]，代表第1个圆盘在右柱上、第2个圆盘在右柱上、第3个圆盘在中
柱上、第4个圆盘在左柱上
如果arr代表的状态是最优移动轨迹过程中出现的状态，返回arr这种状态是最优移动轨
迹中的第几个状态；如果arr代表的状态不是最优移动轨迹过程中出现的状态，则返回-
1。
*/
#include<iostream>
#include<vector>
using namespace std;

int process(vector<int>arr,int i,int from,int mid,int to){
    if(i==-1){
        return 0;
    }
    if(arr[i]!=from&&arr[i]!=to){
        return -1;
    }
    if(arr[i]==from){
        return process(arr,i-1,from,to,mid);
    }else{
        int rest=process(arr,i-1,mid,from,to);
        if(rest==-1){
            return -1;
        }
        return (1<<i)+rest;
    }
}

int step1(vector<int>arr){
    if(arr.empty()){
        return -1;
    }
    return process(arr,arr.size()-1,1,2,3);
}


int step2(vector<int>arr){
    if(arr.empty()){
        return -1;
    }
    int from=1;
    int mid=2;
    int to=3;
    int i=arr.size()-1;
    int res=0;
    int tmp=0;
    while(i>=0){
        if(arr[i]!=from&&arr[i]!=to){
            return -1;
        }
        if(arr[i]==to){
            res+=1<<i;
            tmp=from;from=mid;
        }else{
            tmp=to;
            to=mid;
        }
        mid=tmp;
        i--;
    }
    return res;
}