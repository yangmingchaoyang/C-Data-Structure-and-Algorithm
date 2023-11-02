/*
KMP算法扩展题目二 给定一个数组 arr，代表一排有分数的气球。每打爆一个气球都能获得分数，假设打爆气
球 的分数为 X，获得分数的规则如下:
1)如果被打爆气球的左边有没被打爆的气球，找到离被打爆气球最近的气球，假设分数为
L;如果被打爆气球的右边有没被打爆的气球，找到离被打爆气球最近的气球，假设分数为
R。 获得分数为 L*X*R。
2)如果被打爆气球的左边有没被打爆的气球，找到离被打爆气球最近的气球，假设分数为
L;如果被打爆气球的右边所有气球都已经被打爆。获得分数为 L*X。
3)如果被打爆气球的左边所有的气球都已经被打爆;如果被打爆气球的右边有没被打爆的
气球，找到离被打爆气球最近的气球，假设分数为 R;如果被打爆气球的右边所有气球都
已经 被打爆。获得分数为 X*R。
4)如果被打爆气球的左边和右边所有的气球都已经被打爆。获得分数为 X。
目标是打爆所有气球，获得每次打爆的分数。通过选择打爆气球的顺序，可以得到不同
的
总分，请返回能获得的最大分数。
2
M
0
P
4算法扩展题目二
【举例】
arr = {3,2,5}
如果先打爆3，获得3*2；再打爆2，获得2*5；最后打爆5，获得5；最后总分21
如果先打爆3，获得3*2;再打爆5，获得2*5；最后打爆2，获得2；最后总分18
如果先打爆2，获得3*2*5；再打爆3，获得3*5；最后打爆5，获得5；最后总分50
如果先打爆2，获得3*2*5；再打爆5，获得3*5；最后打爆3，获得3；最后总分48
如果先打爆5，获得2*5；再打爆3，获得3*2；最后打爆2，获得2；最后总分18
如果先打爆5，获得2*5;再打爆2，获得3*2；最后打爆3，获得3；最后总分19
返回能获得的最大分数为50
*/
#include<iostream>
#include<vector>
using namespace std;

// 打爆arr[L..R]范围上的所有气球，返回最大的分数
// 假设arr[L-1]和arr[R+1]一定没有被打爆
int process(vector<int>arr,int L,int R){
    if(L==R){//如果arr[L..R]范围上只有一个气球，直接打爆即可
        return arr[L-1]*arr[L]*arr[R+1];
    }
    // 最后打爆arr[L]的方案，和最后打爆arr[R]的方案，先比较一下
    int maxnum=max(arr[L-1]*arr[L]*arr[R+1]+process(arr,L+1,R),
                    arr[L-1]*arr[R]*arr[R+1]+process(arr,L,R-1));
    // 尝试中间位置的气球最后被打爆的每一种方案
    for(int i=L+1;i<R;i++){
        maxnum=max(maxnum,arr[L-1]*arr[i]*arr[R+1]+process(arr,L,i-1)+process(arr,i+1,R));
    }
    return maxnum;
}

int maxCoins1(vector<int>arr){
    if(arr.empty()){
        return 0;
    }
    if(arr.size()==1){
        return arr[0];
    }
    int N=arr.size();
    vector<int>help(N+2);
    help[0]=1;
    help[N+1]=1;
    for(int i=0;i<N;i++){
        help[i+1]=arr[i];
    }
    return process(help,1,N);//为了防止越界。
}


int maxCoins2(vector<int>arr){
    if(arr.empty()){
        return 0;
    }
    if(arr.size()==1){
        return arr[0];
    }
    int N=arr.size();
    vector<int>help(N+2);
    help[0]=1;
    help[N+1]=1;
    for(int i=0;i<N;i++){
        help[i+1]=arr[i];
    }
    vector<vector<int>>dp(N+2,vector<int>(N+2));
    for(int i=1;i<=N;i++){
        dp[i][i]=help[i-1]*help[i]*help[i+1];
    }
    for(int L=N;L>=1;L--){
        for(int R=L+1;R<=N;R++){
            // 求解dp[L][R]，表示help[L..R]上打爆所有气球的最大分数
			// 最后打爆help[L]的方案
            int finalL=help[L-1]*help[L]*help[R+1]+dp[L+1][R];
            // 最后打爆help[R]的方案
            int finalR=help[L-1]*help[R]*help[R+1]+dp[L][R-1];
            // 最后打爆help[L]的方案，和最后打爆help[R]的方案，先比较一下
            dp[L][R]=max(finalL,finalR);
            // 尝试中间位置的气球最后被打爆的每一种方案
			for (int i = L + 1; i < R; i++) {
				dp[L][R] = max(dp[L][R], help[L - 1] * help[i]
							* help[R + 1] + dp[L][i - 1] + dp[i + 1][R]);
			}
        }
    }
    return dp[1][N];
}


