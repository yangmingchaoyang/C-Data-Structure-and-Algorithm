/*
给定一个字符串str，返回把str全部切成回文子串的最小分割数。
【举例】
str="ABA"。
不需要切割，str本身就是回文串，所以返回0。
str="ACDCDCDAD"。
最少需要切2次变成3个回文子串，比如"A"、"CDCDC"和"DAD"，所以返回2。
*/
#include<iostream>
#include<vector>
#include<string>
using namespace std;
int minCut(string chas){
    if(chas.empty()){
        return 0;
    }
    int len=chas.size();
    vector<int>dp(len+1);
    dp[len]=-1;
    vector<vector<bool>>p(len,vector<bool>(len));
    for(int i=len-1;i>=0;i--){
        dp[i]=INT_MAX;
        for(int j=i;j<len;j++){
            if(chas[i]==chas[j]&&(j-i<2||p[i+1][j-1])){
                p[i][j]=true;
                dp[i]=min(dp[i],dp[j+1]+1);
            }
        }
    }
    return dp[0];
}
   

