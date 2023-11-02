/*
牛牛准备参加学校组织的春游, 出发前牛牛准备往背包里装入一些零食, 牛牛的背包容
量为w。
牛牛家里一共有n袋零食, 第i袋零食体积为v[i]。
牛牛想知道在总体积不超过背包容量的情况下，他一共有多少种零食放法(总体积为0也
算一种放法)。
*/

#include <iostream>
#include <vector>
using namespace std;

int process(vector<int>arr,int w,int index){
    if(w<0){
        return 0;
    }
    if(w==0){
        return 1;
    }
    return process(arr,w,index++)+process(arr,w-arr[index],index++);
}

int way1(vector<int>arr,int w){
    if(arr.empty()||w<0){
        return 0;
    }
    return process(arr,w,0);
}

int ways(vector<int>arr,int w){
    if(arr.empty()||w<0){
        return 0;
    }
    int n=arr.size();
    vector<vector<int>>dp(n,vector<int>(w+1));
    for(int i=0;i<arr.size();i++){
        dp[i][0]=1;
    }
    for(int j=1;j<=w;j++){
        dp[0][j]=j>=arr[0]?2:1;
    }
    for(int i=1;i<arr.size();i++){
        for(int j=1;j<=w;j++){
            dp[i][j]=dp[i-1][j];//不加这包零食
            if(j-arr[i]>=0){
                dp[i][j]+=dp[i-1][j-arr[i]];//加这包零食
            }
        }
    }
    return dp[arr.size()-1][w];
}