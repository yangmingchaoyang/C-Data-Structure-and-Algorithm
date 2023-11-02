/*给定一个字符串str，求最长的回文子序列。注意区分子序列和子串的不同。*/
#include<iostream>
#include<string>
#include<vector>
using namespace std;

int maxlen1(string str1){
    if(str1.empty()){
        return 0;
    }
    string str2;
    str2=reverse(str1);
    return lcse(str1,str2);
}

string reverse(string str){
    string res;
    for(int i=0;i<str.size();i++){
        res+=str[str.size()-1-i];
    }
    return res;
}

int lcse(string str1,string str2){
    vector<vector<int>>dp(str1.size(),vector<int>(str2.size()));
    dp[0][0]=str1[0]==str2[0]?1:0;
    for(int i=1;i<str1.size();i++){
        dp[i][0]=max(dp[i-1][0],str1[i]==str2[0]?1:0);
    }
    for(int j=1;j<str2.size();j++){
        dp[0][j]=max(dp[0][j-1],str1[0]==str2[j]?1:0);
    }
    for(int i=1;i<str1.size();i++){
        for (int j = 1; j < str2.size(); j++) {
			dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
			if (str1[i] == str2[j]) {
					dp[i][j] =max(dp[i][j], dp[i - 1][j - 1] + 1);
			}
		}
    }
    return dp[str1.size()-1][str2.size()-1];
}

int maxLen2(string str){
    if(str.empty()){
        return 0;
    }
    vector<vector<int>>dp(str.size(),vector<int>(str.size()));
    for(int i=0;i<str.size();i++){
        dp[i][i]=1;
    }
    for (int i = 0; i < str.size() - 1; i++) {
		dp[i][i + 1] = str[i] == str[i + 1] ? 2 : 1;
	}
    for(int i=str.size()-2;i>=0;i--){
        for(int j=i+2;j<str.size();j++){
            dp[i][j]=max(dp[i][j-1],dp[i+1][j]);//dp中装的是回文子串的数量。
            if(str[i]==str[j]){
                dp[i][j]=max(dp[i+1][j-1]+2,dp[i][j]);
            }
        }
    }
    return dp[0][str.size()-1];
}