/*
请注意区分子串和子序列的不同，给定两个字符串str1和str2，求两个字符串的最长公
共子串。
动态规划空间压缩的技巧讲解
*/
#include<iostream>
#include<string>
#include<vector>
using namespace std;

vector<vector<int>>getdp(string str1,string str2){
    vector<vector<int>>dp(str1.size(),vector<int>(str2.size()));
    for(int i=0;i<str1.size();i++){
        if(str1[i]==str2[0]){
            dp[i][0]=1;
        }
    }
    for(int j=1;j<str2.size();j++){
        if(str1[0]==str2[j]){
            dp[0][j]=1;
        }
    }
    for(int i=1;i<str1.size();i++){
        for(int j=1;j<str2.size();j++){
            if(str1[i]==str2[j]){//前面有1，说明前面的值是相同的
                dp[i][j]=dp[i-1][j-1]+1;
            }
        }
    }
    return dp;
}

string lcst1(string chs1,string chs2){
    if(chs1.empty()||chs2.empty()){
        return "";
    }
    vector<vector<int>>dp=getdp(chs1,chs2);
    int end=0;
    int max=0;
    for (int i = 0; i < chs1.size(); i++) {
		for (int j = 0; j < chs2.size(); j++) {
				if (dp[i][j] > max) {
					end = i;
					max = dp[i][j];
				}
			}
	}
    return chs1.substr(end-max+1,end+1);
}