/*
CC里面有一个土豪很喜欢一位女直播Kiki唱歌，平时就经常给她点赞、送礼、私聊。最近CC直播平台在举行
中秋之星主播唱歌比赛，假设一开始该女主播的初始人气值为start， 能够晋升下一轮人气需要刚好达到end，
土豪给主播增加人气的可以采取的方法有：
a. 点赞 花费x C币，人气 + 2
b. 送礼 花费y C币，人气 * 2
c. 私聊 花费z C币，人气 - 2
其中 end 远大于start且end为偶数， 请写一个程序帮助土豪计算一下，最少花费多少C币就能帮助该主播
Kiki将人气刚好达到end，从而能够晋级下一轮？
输入描述：
第一行输入5个数据，分别为：x y z start end，每项数据以空格分开。
其中：0＜x, y, z＜＝10000， 0＜start, end＜＝1000000
输出描述：
需要花费的最少C币。
示例1:
输入
3 100 1 2 6
输出
6
*/
#include<iostream>
#include<vector>
using namespace std;
/*
pre：表示当前已经花费的代币数量，即已经进行的操作的总花费。

aim：表示当前问题的目标值，即需要通过操作达到的目标值。

add：表示一次操作增加的代币数量。

times：表示一次操作乘法运算的倍数。

del：表示一次操作减少的代币数量。

finish：表示问题的终点值，即达到这个值就停止操作。

limitAim：表示问题中目标值的上限，即目标值不能大于这个值。

limitCoin：表示问题中花费代币数量的上限，即花费代币不能超过这个值。
*/
/*
设置上限（limitAim 和 limitCoin）的目的是为了避免递归进入无限循环或导致递归层数过深，从而造成栈溢出或计算时间过长的情况。这种限制可以防止程序无限地尝试各种组合，确保递归算法在合理的时间内终止。
*/
int process(int pre, int aim, int add, int times, int del, int finish, int limitAim, int limitCoin){
    if(pre>limitCoin){
        return INT_MAX;
    }
    if(aim<0){
        return INT_MAX;
    }
    if(aim>limitAim){
        return INT_MAX;
    }
    if(aim>limitAim){
        return INT_MAX;
    }
    if(aim==finish){
        return pre;
    }
    int minnum=INT_MAX;
    int p1=process(pre+add,aim-2,add,times,del,finish,limitAim,limitCoin);
    if(p1!=INT_MAX){
        minnum=p1;
    }
    int p2=process(pre+del,aim+2,add,times,del,finish,limitAim,limitCoin);
    if(p2!=INT_MAX){
        minnum=min(minnum,p2);
    }
    //这个表达式检测的是 aim 是否为偶数。
    if((aim&1)==0){
        int p3=process(pre+times,aim/2,add,times,del,finish,limitAim,limitCoin);
        if(p3!=INT_MAX){
            minnum=min(minnum,p3);
        }
    }
    return minnum;
}


int minCcoins1(int add,int times,int del,int start,int end){
    if(start>end){
        return -1;
    }
    return process(0,end,add,times,del,start,end * 2, ((end - start) / 2) * add);
}


int minCcoins2(int add,int times,int del,int start,int end){
    if(start>end){
        return -1;
    }
    int limitCoin=((end-start)/2)*add;
    int limitAim=end*2;
    vector<vector<int>>dp(limitCoin+1,vector<int>(limitAim+1));
    for(int pre=0;pre<=limitCoin;pre++){
        for(int aim=0;aim<=limitAim;aim++){
            if(aim==start){
                dp[pre][aim]=pre;
            }else{
                dp[pre][aim]=INT_MAX;
            }
        }
    }
    for(int pre=limitCoin;pre>=0;pre--){
        for(int aim=0;aim<=limitAim;aim++){
                if (aim - 2 >= 0 && pre + add <= limitCoin) {
					dp[pre][aim] =min(dp[pre][aim], dp[pre + add][aim - 2]);
				}
				if (aim + 2 <= limitAim && pre + del <= limitCoin) {
					dp[pre][aim] =min(dp[pre][aim], dp[pre + del][aim + 2]);
				}
				if ((aim & 1) == 0) {
					if (aim / 2 >= 0 && pre + times <= limitCoin) {
						dp[pre][aim] =min(dp[pre][aim], dp[pre + times][aim / 2]);
				}
			}
        }
    }
    return dp[0][end];
}
