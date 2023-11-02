/*
小Q正在给一条长度为n的道路设计路灯安置方案。
为了让问题更简单,小Q把道路视为n个方格,需要照亮的地方用'.'表示, 不需要
照亮的障碍物格子用'X'表示。小Q现在要在道路上设置一些路灯, 对于安置在
pos位置的路灯, 这盏路灯可以照亮pos - 1, pos, pos + 1这三个位置。
小Q希望能安置尽量少的路灯照亮所有'.'区域, 希望你能帮他计算一下最少需
要多少盏路灯。
输入描述：
输入的第一行包含一个正整数t(1 <= t <= 1000), 表示测试用例数
接下来每两行一个测试数据, 第一行一个正整数n(1 <= n <= 1000),表示道路
的长度。第二行一个字符串s表示道路的构造,只包含'.'和'X'。
输出描述：
对于每个测试用例, 输出一个正整数表示最少需要多少盏路灯。
*/
#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

// 当前来到了i位置
// 函数潜台词：help[0..i-2]上都已经点亮了
// pre表示i-1位置是否点亮
// 返回如果把所有位置都点亮，help[i..最后]需要几盏灯
// process(help, i, true)：表示help[0..i-2]上都已经点亮了，i-1位置也点亮的情况下，help[i..最后]需要几盏灯
// process(help, i, false)：表示help[0..i-2]上都已经点亮了，但是i-1位置没亮的情况下，help[i..最后]需要几盏灯
int process(string help,int i,bool pre){
    if(i=help.size()){
        return 0;
    }
    if(i==help.size()-1){//前一个路的情况，最后一个必须被照亮，不照亮返回最大值。
        return pre?0:INT_MAX;
    }
    int ans=INT_MAX;
    int resLight=0;
    if(pre){
        if(help[i]=='X'){
            resLight=process(help,i+1,true);
            if(resLight!=INT_MAX){
                ans=min(ans,resLight);
            }
        }else{
            resLight=process(help,i+1,false);
            if(resLight!=INT_MAX){
                ans=min(ans,resLight);
            }
            resLight=process(help,i+2,true);
            if(resLight!=INT_MAX){
                ans=min(ans,resLight+1);
            }
        }
    }else{
        resLight=process(help,i+2,true);
        if(resLight!=INT_MAX){
            ans=min(ans,resLight+1);
        }
    }
    return ans;
}

int minLight1(string s){
    if(s.empty()){
        return 0;
    }
    //数组的大小必须是常量表达式
    int len=s.size();
    string help; // 使用动态内存分配
    help[0]='.';
    help[s.size()+1]='.';
    for(int i=0;i<s.size();i++){
        help[i+1]=s[i];
    }
    return process(help,1,true);
}

int minLight2(string s){
    if(s.empty()){
        return 0;
    }
    string help=".";
    help=help+s;
    help=help+".";
    vector<vector<int>>dp(help.length()+1,vector<int>(2));
    dp[help.length()][0]=0;
    dp[help.length()][1]=0;
    dp[help.length()-1][0]=INT_MAX;
    dp[help.length()-1][1]=0;
    for(int i=help.length()-2;i>=1;i--){
        dp[i][0]=INT_MAX;
        dp[i][1]=INT_MAX;
        int restLight=0;
        if(help[i]=='X'){
            restLight=dp[i+1][1];
            if(restLight!=INT_MAX){
                dp[i][1]=min(dp[i][1],restLight);
            }
        }else{
            restLight=dp[i+1][0];
            if(restLight!=INT_MAX){
               dp[i][1]=min(dp[i][1],restLight);
            }
            restLight=dp[i+2][1];
            if (restLight != INT_MAX) {
				dp[i][1] = min(dp[i][1], restLight + 1);
			}
        }
        restLight=dp[i+2][1];
        if(restLight!=INT_MAX){
            dp[i][0]=min(dp[i][0],restLight+1);
        }
    }
    return dp[1][1];
}



