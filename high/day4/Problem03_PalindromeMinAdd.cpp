/*
给定一个字符串str，如果可以在str的任意位置添加字符，请返回在添加字符最少
的情况下，让str整体都是回文字符串的一种结果。
【举例】
str="ABA"。str本身就是回文串，不需要添加字符，所以返回"ABA"。
str="AB"。可以在'A'之前添加'B'，使str整体都是回文串，故可以返回"BAB"。也
可以在'B'之后添加'A'，使str整体都是回文串，故也可以返回"ABA"。总之，只要
添加的字符数最少，返回其中一种结果即可。
*/
#include<iostream>
#include<vector>
#include<string>
using namespace std;

/*
在循环中，首先检查 str[i] 和 str[j] 是否相等。如果相等，将 dp[i][j] 设置为0，表示它们之间的子串已经是回文（或者具有0的距离）。

如果 str[i] 和 str[j] 不相等，那么需要计算它们之间的距离。动态规划距离的计算规则是：

如果 str[i] 和 str[j] 不相等，dp[i][j] 被设置为 dp[i+1][j] 和 dp[i][j-1] 中的较小值，
然后加上1。这表示通过将 str[i] 添加到子串的结尾或将 str[j] 添加到子串的开头，可以使距离最小化。
*/
//需要多少能变成回文。
vector<vector<int>> getDP(string str){
    vector<vector<int>>dp(str.size(),vector<int>(str.size()));
    for(int j=1;j<str.size();j++){
        dp[j-1][j]=str[j-1]==str[j]?0:1;
        for(int i=j-2;i>-1;i--){
            if(str[i]==str[j]){
                dp[i][j]=dp[i+1][j-1];
            }else{
                dp[i][j]=min(dp[i+1][j],dp[i][j-1])+1;
            }
        }
    }
    return dp;
}

string getPalindrome1(string chas) {
    if (chas.empty()) {
        return chas;
    }
    vector<vector<int>> dp = getDP(chas);
    string res(chas.size(), ' '); // Initialize 'res' with the same length as 'chas'
    int i = 0;
    int j = chas.size() - 1;
    int resl = 0;
    int resr = res.size() - 1;
    while (i <= j) {
        if (chas[i] == chas[j]) {
            res[resl++] = chas[i++];
            res[resr--] = chas[j--];
        } else if (dp[i][j - 1] < dp[i + 1][j]) {//比较缺少左边或者右边的字符后，其需要多少能形成回文子串，选少的。
            res[resl++] = chas[j];
            res[resr--] = chas[j--];
        } else {
            res[resl++] = chas[i];
            res[resr--] = chas[i++];
        }
    }
    return res;
}

int main() {
    string input = "babad";  // Replace with your input string
    string result = getPalindrome1(input);

    cout << "Input String: " << input << endl;
    cout << "Longest Palindromic Subsequence: " << result << endl;

    return 0;
}

