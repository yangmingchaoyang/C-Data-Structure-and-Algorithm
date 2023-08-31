/*
【题目】
给定数组 arr，arr 中所有的值都为正数且不重复。每个值代表一种面值的货币，每种面值
的货币可以使用任意张，再给定一个整数 aim，代表要找的钱数，求组成 aim 的最少货币
数。
【举例】
arr=[5,2,3]，aim=20。
4 张 5 元可以组成 20 元，其他的找钱方案都要使用更多张的货币，所以返回 4。
arr=[5,2,3]，aim=0。
不用任何货币就可以组成 0 元，返回 0。
arr=[3,5]，aim=2。
根本无法组成 2 元，钱不能找开的情况下默认返回-1。
*/
#include <iostream>
#include <vector>
using namespace std;

int ff(vector<int> arr,int index,int aim){
    if(aim<0){
        return -1;
    }
    if(aim==0){
        return 0;
    }
    if(index==arr.size()){
        return -1;
    }

    int p1=ff(arr,index+1,aim);
    int p2Next=ff(arr,index+1,aim-arr[index]);
    if(p1==-1&&p2Next==-1){
        return -1;
    }else{
        if(p1==-1){
            return p2Next+1;
        }
        if(p2Next==-1){
            return p1;
        }
        return min(p1,p2Next+1);
    }

}

int min1(vector<int>arr,int aim){
    return ff(arr,0,aim);
}


int min2(vector<int>arr,int aim){
    int N=arr.size();
    vector<vector<int>>dp(N+1,vector<int>(aim+1));
    for(int i=0;i<N;i++){
        dp[i][0]=0;
    }
    for(int i=1;i<aim+1;i++){
        dp[N][i]=-1;
    }
    for(int row=N-1;row>=0;row--){
        for(int col=1;col<=aim;col++){
            int p1=dp[row+1][col];
            int p2Next=-1;
            if(col-arr[row]>=0){
                p2Next=dp[row+1][col-arr[row]];
            }
            if(p1==-1&&p2Next==-1){
                dp[row][col]=-1;
            }else if(p2Next=-1){
                dp[row][col]=p1;
            }else if(p1=-1){
                dp[row][col]=p2Next+1;
            }else{
                dp[row][col]=min(p1,p2Next);
            }

        }
    }
    return dp[0][aim];

}