/*
现有n1+n2种面值的硬币，其中前n1种为普通币，可以取任意枚，后n2种为纪念币，
每种最多只能取一枚，每种硬币有一个面值，问能用多少种方法拼出m的面值？
*/
#include<iostream>
#include<vector>
using namespace std;

vector<vector<int>>getDpArb(vector<int>arr,int money){
    if(arr.empty()){
        return std::vector<std::vector<int>>();
    }
    vector<vector<int>>dp(arr.size(),vector<int>(money+1));
    for(int i=0;i<arr.size();i++){
        dp[i][0]=1;
    }
    for(int j=1;arr[0]*j<=money;j++){
        dp[0][arr[0]*j]=1;
    }
    for(int i=1;i<arr.size();i++){
        for(int j=1;j<=money;j++){
            dp[i][j]=dp[i-1][j];
            dp[i][j]+=j-arr[i]>=0?dp[i][j-arr[i]]:0;
        }
    }
    return dp;
}

vector<vector<int>>getDpOne(vector<int>arr,int money){
    if(arr.empty()){
        return vector<vector<int>>();
    }
    vector<vector<int>>dp(arr.size(),vector<int>(money+1));
    for (int i = 0; i < arr.size(); i++) {
			dp[i][0] = 1;
	}
	if (arr[0] <= money) {
		dp[0][arr[0]] = 1;
	}
    for(int i=1;i<arr.size();i++){
        for(int j=1;j<=money;j++){
            dp[i][j]=dp[i-1][j];
            dp[i][j]+=j-arr[i]>=0?dp[i-j][j-arr[i]]:0;
        }
    }
}

int moneyWays(vector<int>arbitrary,vector<int>onlyone,int money){
    if(money<0){
        return 0;
    }
    if(arbitrary.empty()&&onlyone.empty()){
        return money==0?1:0;
    }
    vector<vector<int>>dparb=getDpArb(arbitrary,money);
    vector<vector<int>>dpone=getDpOne(onlyone,money);
    if(dparb.empty()){
        return dpone[dpone.size()-1][money];
    }
    if(dpone.empty()){
        return dparb[dparb.size()-1][money];
    }
    int res=0;
    for(int i=0;i<=money;i++){
        res+=dparb[dparb.size() - 1][i]*dpone[dpone.size() - 1][money - i];
    }
    return res;
}