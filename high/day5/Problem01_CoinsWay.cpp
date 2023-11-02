/*
给定一个正数数组arr，arr[i]表示第i种货币的面值，可以使用任意张。给定一个正
数aim，返回组成aim的方法数有多少种？
动态规划优化状态依赖的技巧
*/
#include<iostream>
#include<vector>
using namespace std;

int coin4(vector<int>arr,int aim){
    if(arr.empty()){
        return 0;
    }
    vector<vector<int>>dp(arr.size(),vector<int>(aim+1));
    for (int i = 0; i < arr.size(); i++) {
			dp[i][0] = 1;
	}
	for (int j = 1; arr[0] * j <= aim; j++) {
		dp[0][arr[0] * j] = 1;
	}
    for (int i = 1; i < arr.size(); i++) {
		for (int j = 1; j <= aim; j++) {
			dp[i][j] = dp[i - 1][j];
			dp[i][j] += j - arr[i] >= 0 ? dp[i][j - arr[i]] : 0;
		}
	}
	return dp[arr.size() - 1][aim];
}
