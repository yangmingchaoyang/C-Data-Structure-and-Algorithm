/*
动态规划的空间压缩技巧
给你一个二维数组matrix，其中每个数都是正数，要求从左上角走到右下角。每
一步只能向右或者向下，沿途经过的数字要累加起来。最后请返回最小的路径和。
*/
#include<iostream>
#include<vector>

using namespace std;

int minPathSum1(vector<vector<int>>num){
    if(num.empty()||num[0].empty()){
        return 0;
    }
    int row=num.size();
    int col=num[0].size();
    vector<vector<int>>dp(row,vector<int>(col));
    dp[0][0]=num[0][0];
    for(int i=1;i<row;i++){
        dp[i][0]=dp[i-1][0]+num[i][0];
    }
    for(int j=1;j<col;j++){
        dp[0][j]=dp[0][j-1]+num[0][j];
    }
    for(int i=1;i<row;i++){
        for(int j=1;j<col;j++){
            dp[i][j]=min(dp[i-1][j],dp[i][j-1])+num[i][j];
        }
    }
    return dp[row-1][col-1];
}

int minPathSum2(vector<vector<int>>m){
    if(m.empty()||m[0].empty()){
        return 0;
    }
    int more=max(m.size(),m[0].size());
    int less=min(m.size(),m[0].size());
    bool rowmore=(more==m.size());
    vector<int>arr(less);
    arr[0]=m[0][0];
    for(int i=1;i<less;i++){
        arr[i]=arr[i-1]+(rowmore?m[0][i]:m[i][0]);
    }
    for(int i=1;i<more;i++){
        arr[0]=arr[0]+(rowmore?m[i][0]:m[0][i]);
        for(int j=1;j<less;j++){
            arr[j]=min(arr[j-1],arr[j])+(rowmore?m[i][j]:m[j][i]);
        }
    }
    return arr[less-1];
}
