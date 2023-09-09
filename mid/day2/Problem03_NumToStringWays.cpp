/*
将给定的数转换为字符串，原则如下：1对应 a，2对应b，…..26对应z，例如12258
可以转换为"abbeh", "aveh", "abyh", "lbeh" and "lyh"，个数为5，编写一个函
数，给出可以转换的不同字符串的个数。
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int process(string str,int index){
    if(index==str.size()){
        return 1;
    }
    if(str[index]=='0'){
        return 0;
    }
    int res=process(str,index+1);
    if(index==str.size()-1){
        return res;
    }//保证不越界
    if (((str[index] - '0') * 10 + str[index + 1] - '0') < 27) {
			res += process(str, index + 2);
	}
	return res;
}

int convertWay(int num){
    if(num<1){
        return 0;
    }
    return process(to_string(num),0);
}


int dpways(int num){
    if(num<1){
        return 0;
    }
    string str=to_string(num);
    vector<int>dp(str.size()+1);
    dp[str.size()]=1;
    dp[str.size()-1]=str[str.size()-1]=='0'?0:1;
    for(int i=str.size()-2;i>=0;i--){
        if(str[i]=='0'){
            dp[i]=0;
        }else{
            dp[i]=dp[i+1]+(((str[i]-'0')*10+(str[i+1]-'0'))<27)?dp[i+2]:0;
        }
    }
    return dp[0];
}