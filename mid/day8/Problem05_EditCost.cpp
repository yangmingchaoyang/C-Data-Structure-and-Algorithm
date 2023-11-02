/*
给定两个字符串str1和str2，再给定三个整数ic、dc和rc，分别代表插入、删
除和替换一个字符的代价，返回将str1编辑成str2的最小代价。
【举例】
str1="abc"，str2="adc"，ic=5，dc=3，rc=2
从"abc"编辑成"adc"，把'b'替换成'd'是代价最小的，所以返回2
str1="abc"，str2="adc"，ic=5，dc=3，rc=100
从"abc"编辑成"adc"，先删除'b'，然后插入'd'是代价最小的，所以返回8
str1="abc"，str2="abc"，ic=5，dc=3，rc=2
不用编辑了，本来就是一样的字符串，所以返回0
*/
#include<iostream>
#include<string>
#include<vector>
using namespace std;

int minCost1(string chs1,string chs2,int ic,int dc,int rc){
    int row=chs1.size()+1;
    int col=chs2.size()+1;
    vector<vector<int>>dp(row,vector<int>(col));
    for(int i=1;i<row;i++){
        dp[i][0]=dc*i;
    }
    for(int j=1;j<col;j++){
        dp[0][j]=ic*j;
    }
    for(int i=1;i<row;i++){
        for(int j=1;j<col;j++){//替换和dp[i-1][j-1]有关
            if(chs1[i-1]==chs2[j-1]){
                dp[i][j]=dp[i-1][j-1];
            }else{
                dp[i][j]=dp[i-1][j-1]+rc;
            }
            dp[i][j]=min(dp[i][j],dp[i][j-1]+ic);//插入和dp[i][j-1]有关
            dp[i][j]=min(dp[i][j],dp[i-1][j]+dc);//删除和dp[i-1][j]有关
        }
    }
    return dp[row-1][col-1];


}

int minCost2(string str1, string str2, int ic, int dc, int rc) {
    if (str1.empty() || str2.empty()) {
        return 0;
    }
    vector<char> chs1(str1.begin(), str1.end());
    vector<char> chs2(str2.begin(), str2.end());
    vector<char> &longs = (chs1.size() >= chs2.size()) ? chs1 : chs2;
    vector<char> &shorts = (chs1.size() < chs2.size()) ? chs1 : chs2;
    if (chs1.size() < chs2.size()) {
        int tmp = ic;
        ic = dc;
        dc = tmp;
    }
    vector<int> dp(shorts.size() + 1, 0);
    for (int i = 1; i <= shorts.size(); i++) {
        dp[i] = ic * i;
    }
    for (int i = 1; i <= longs.size(); i++) {
        int pre = dp[0];
        dp[0] = dc * i;
        for (int j = 1; j <= shorts.size(); j++) {
            int tmp = dp[j];
            if (longs[i - 1] == shorts[j - 1]) {
                dp[j] = pre;
            } else {
                dp[j] = pre + rc;
            }
            dp[j] = min(dp[j], dp[j - 1] + ic);
            dp[j] = min(dp[j], tmp + dc);
            pre = tmp;
        }
    }
    return dp[shorts.size()];
}

int main() {
    string str1 = "abcdef";
    string str2 = "azced";
    int ic = 1; // 插入代价
    int dc = 2; // 删除代价
    int rc = 3; // 替换代价

    int result = minCost2(str1, str2, ic, dc, rc);

    cout << "Minimum edit cost: " << result << endl;

    return 0;
}