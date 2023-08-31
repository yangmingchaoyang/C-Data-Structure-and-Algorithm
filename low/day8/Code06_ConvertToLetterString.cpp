/*
规定1和A对应、2和B对应、3和C对应... 那么一个数字字符串比如"111"，就可以转化为"AAA"、"KA"和"AK"。
给定一个只有数字字符组成的字符串str，返回有多少种转化结果。
*/
#include <iostream>
using namespace std;

int process(const std::string& str,int i){
    if(str[i]=='\0'){
        return 1;
    }
    if(str[i]=='0'){
        return 0;
    }
    if(str[i]=='1'){
        int res=process(str,i+1);
        if(i+1<str.length()){
            res+=process(str,i+2);
        }
        return res;
    }
    if(str[i]=='2'){
        int res=process(str,i+1);
        if(i+1<str.length()&&str[i+1]>='0'&&str[i+1]<='6'){
            res+=process(str,i+2);
        }
        return res;
    }
    return process(str,i+1);
}

int dpWay2(const std::string& str){
    if(str.empty()){
        return 0;
    }
    int N=str.length();
    int* dp=new int[N+1];
    dp[N]=1;

    for(int i=N-1;i>=0;i--){
        if(str[i]=='0'){
            dp[i]=0;
        }
        else if(str[i]=='1'){
            dp[i]=dp[i+1];
            if(i+1<str.length()){
                dp[i]+=dp[i+2];
            }
        }
        else if(str[i]=='2'){
            dp[i]=dp[i+1];
            if(i+1<str.length()&&(str[i+1]>='0'&&str[i+1]<='6')){
                dp[i]+=dp[i+2];
            }
        }else{
            dp[i]=dp[i+1];
        }
    }
    int result=dp[0];
    delete[] dp;
    return result;
}


int number(const std::string& str){
    if(str.empty()){
        return 0;
    }
    return process(str,0);
}


int main() {
    string input_str = "12"; // Replace with the input string of your choice
    cout << number(input_str) << endl;
    cout << dpWay2(input_str) << endl;
    return 0;
}