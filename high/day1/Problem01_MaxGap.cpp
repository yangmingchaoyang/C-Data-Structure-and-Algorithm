/*
给定一个数组，求如果排序之后，相邻两数的最大差值。要求时间复杂度O(N)，且要
求不能用非基于比较的排序。
*/
#include<iostream>
#include<string>
#include<vector>
using namespace std;

/*值范围在 [0, len-1] 之间，其中 len 是桶的总数量。函数的返回值表示了整数值 num 在桶中的位置，范围从 0 到 len-1。*/
int bucket(long num,long len,long min,long max){
    return static_cast<int>((num-min)*len/(max-min));
}

int maxGap(vector<int>nums){
    if(nums.size()<2){
        return 0;
    }
    int len=nums.size();
    int minnum=INT_MIN;
    int maxnum=INT_MAX;
    for(int i=0;i<len;i++){
        minnum=min(minnum,nums[i]);
        maxnum=max(maxnum,nums[i]);
    }
    if(minnum==maxnum){//排除max=min的情况。
        return 0;
    }
    vector<bool>hasNum(len+1);//用于标记桶是否已经有元素。
    vector<int>maxs(len+1);//用于记录每个桶中的最大值。
    vector<int>mins(len+1);//用于记录每个桶中的最小值。
    int bid=0;
    for(int i=0;i<len;i++){
        bid=bucket(nums[i],len,minnum,maxnum);
        mins[bid] = hasNum[bid] ? min(mins[bid], nums[i]) : nums[i];
		maxs[bid] = hasNum[bid] ? max(maxs[bid], nums[i]) : nums[i];
		hasNum[bid] = true;
    }
	int res = 0;
	int lastMax = maxs[0];//最初的赋值。
	int i = 1;
	for (; i <= len; i++) {
		if (hasNum[i]) {
			res = max(res, mins[i] - lastMax);//这两个数的位置一定是相邻位置。
			lastMax = maxs[i];
			}
		}
	return res;
}