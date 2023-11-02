/*
给定一个正数1，裂开的方法有一种，(1)
给定一个正数2，裂开的方法有两种，(1和1)、(2)
给定一个正数3，裂开的方法有三种，(1、1、1)、(1、2)、(3)
给定一个正数4，裂开的方法有五种，(1、1、1、1)、(1、1、2)、(1、3)、（2、2）、
（4）
给定一个正数n，求裂开的方法数。
动态规划优化状态依赖的技巧
*/
#include<iostream>
#include<vector>
using namespace std;

int process(int pre,int rest){
    if(rest==0){
        return 1;
    }
    if(pre>rest){
        return 0;
    }
    int ways=0;
    for(int i=pre;i<=rest;i++){
        ways+=process(i,rest-i);//第一个数为1
    }
    return ways;
}

int way1(int n){
    if(n<1){
        return 0;
    }
    return process(1,n);
}

int way2(int n){
    if(n<1){
        return 0;
    }
    vector<vector<int>>dp(n+1,vector<int>(n+1));
    //dp[i][j] 表示将整数 j 分解成不同整数之和的方式数，其中最小的整数大于等于i。
    for (int pre = 1; pre < dp.size(); pre++) {
		dp[pre][0] = 1;//将它们都设置为1，因为将任何整数分解成0的方式只有一种，就是不分解，即为自身。
	}
    for (int pre = n; pre > 0; pre--) {
		for (int rest = pre; rest <= n; rest++) {
			for (int i = pre; i <= rest; i++) {
            	dp[pre][rest] += dp[i][rest - i];
			}
		}
	}
	return dp[1][n];
}

int way2(int n) {
    if (n < 1) {
        return 0;
    }
    vector<vector<int>> dp(n + 1, vector<int>(n + 1));
    for (int pre = 1; pre < dp.size(); pre++) {
        dp[pre][0] = 1;
    }
    for (int pre = n; pre > 0; pre--) {
        for (int rest = pre; rest <= n; rest++) {
            for (int i = pre; i <= rest; i++) {
                dp[pre][rest] += dp[i][rest - i];
            }
        }
    }
    return dp[1][n];
}
/*
对于这段代码，dp[i][j] 代表将整数 i 拆分为连加数列，其中每个加数都不大于 j 的方式数。更具体地说，dp[i][j] 存储了将整数 i 拆分成 j 或更小的加数的方式数。

例如，如果 i 代表 5，j 代表 3，那么 dp[5][3] 就代表将整数 5 拆分为连加数列，其中每个加数都不大于 3 的方式数。这可能包括以下几种拆分方式：

5 = 3 + 2，其中最大的加数是 3，所以这是一种方式。
5 = 3 + 1 + 1，同样，最大的加数是 3，所以这也是一种方式。
5 = 2 + 2 + 1，这是另一种方式。
所以，dp[5][3] 的值将表示这种拆分的方式数，通常是一个整数。这个二维动态规划表中的值记录了各种整数拆分方式的数量，它们可以通过逐步填充表格来计算。
*/
int way3(int n){
    if(n<1){
        return 0;
    }
    vector<vector<int>>dp(n+1,vector<int>(n+1));
    for(int pre=1;pre<dp.size();pre++){
        dp[pre][0]=1;//
    }
    for(int pre=1;pre<dp.size();pre++){
        dp[pre][pre]=1;
    }
    for(int pre=n-1;pre>0;pre--){
        for(int rest=pre+1;rest<=n;rest++){//f(1,4)依赖于f(1,3),f(2,2),f(1,3),f(0,4)
            dp[pre][rest]=dp[pre+1][rest]+dp[pre][rest-pre];
        }
    }
    return dp[1][n];
}
