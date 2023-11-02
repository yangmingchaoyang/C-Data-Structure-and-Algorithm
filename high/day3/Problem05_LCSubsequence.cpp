/*
请注意区分子串和子序列的不同，给定两个字符串str1和str2，求两个字符串
的最长公共子序列
考虑字符串 "ABCD" 和 "ACDF"。它们之间的最长公共子序列是 "ACD"，这是因为 "A"、"C" 和 "D" 在两个字符串中都以相同的顺序出现，
即使它们之间的字符 "B" 和 "F" 不同，但它们不是公共子序列的一部分。
动态规划空间压缩的技巧讲解
*/
#include<iostream>
#include<vector>
#include<string>
using namespace std;

vector<vector<int>>getdp(string str1,string str2){
    vector<vector<int>>dp(str1.size(),vector<int>(str2.size()));
    dp[0][0]=str1[0]==str2[0]?1:0;
    for(int i=1;i<str1.size();i++){
        dp[i][0]=max(dp[i-1][0],str1[i]==str2[0]?1:0);
    }
    for(int j=1;j<str2.size();j++){
        dp[0][j]=max(dp[0][j-1],str1[0]==str2[j]?1:0);
    }
    for(int i=1;i<str1.size();i++){
        for(int j=1;j<str2.size();j++){
            dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
            if(str1[i]==str2[j]){
                dp[i][j]=max(dp[i][j],dp[i-1][j-1]+1);
            }
        }
    }
    return dp;
}

string lcse(string chs1,string chs2){
    if(chs1.empty()||chs2.empty()){
        return "";
    }
    vector<vector<int>>dp=getdp(chs1,chs2);
    int m=chs1.size()-1;
    int n=chs2.size()-1;
    string res;
    int index=dp[m][n]-1;
    while(index>0){
        if(n>0&&dp[m][n]==dp[m][n-1]){
            n--;
        }else if(m>0&&dp[m][n]==dp[m-1][n]){
            m--;
        }else{
            res[index--]=chs1[m];
            m--;
            n--;
        }
    }
    return res;
}