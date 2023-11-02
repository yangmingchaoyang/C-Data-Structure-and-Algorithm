/*
给定一个数组arr长度为N，你可以把任意长度大于0且小于N的前缀作为左部分，剩下的
作为右部分。但是每种划分下都有左部分的最大值和右部分的最大值，请返回最大的，
左部分最大值减去右部分最大值的绝对值。
*/
#include<iostream>
#include<vector>

using namespace std;
int maxABS1(vector<int>arr){
    int res=INT_MIN;
    int maxLeft=0;
    int maxRight=0;
    for(int i=0;i!=arr.size();i++){
        maxLeft=INT_MIN;
        for(int j=0;j!=i+1;j++){
            maxLeft=max(arr[j],maxLeft);
        }
        maxRight=INT_MIN;
        for(int j=i+1;j!=arr.size();j++){
            maxRight=max(arr[j],maxRight);
        }
        res=max(abs(maxLeft-maxRight),res);
    }
    return res;
}

int maxABS2(vector<int>arr){
    vector<int>lArr(arr.size());
    vector<int>rArr(arr.size());
    lArr[0]=arr[0];
    rArr[arr.size()-1]=arr[arr.size()-1];
    for (int i = 1; i < arr.size(); i++) {
			lArr[i] = max(lArr[i - 1], arr[i]);
	}
	for (int i = arr.size() - 2; i > -1; i--) {
			rArr[i] = max(rArr[i + 1], arr[i]);
	}
    int nummax=0;
    for(int i=0;i<arr.size();i++){
        nummax=max(nummax,abs(lArr[i]-rArr[i+1]));
    }
    return nummax;
}


