/*
假设s和m初始化，s = "a"; m = s;
再定义两种操作，第一种操作：
m = s;
s = s + s;
第二种操作：
s = s + m;
求最小的操作步骤数，可以将s拼接到长度等于n
*/
#include <iostream>
#include <vector>
using namespace std;

//怎么判断一个数是不是质数
//质数（素数）是指大于1的正整数，除了1和它本身以外，没有其他正因子（除了1和它自己外，不能被任何其他整数整除）
bool isPrim(int n){
    if(n<2){
        return false;
    }
    int maxnum=(int)sqrt((double)n);//素数
    for(int i=2;i<=maxnum;i++){
        if(n%i==0){
            return false;
        }
    }
    return true;
}

//保证n不是质数
//返回：
//0)所有因子的和，但是因子不包括1
//1)所有因子的个数，但是因子不包括1
vector<int> divsSumAndCount(int n){
    int sum=0;
    int count=0;
    vector<int>res;
    for(int i=2;i<=n;i++){
        while(n%i==0){
            sum+=i;
            count++;
            n/=i;
        }
    }
    res.push_back(sum);
    res.push_back(count);
    return res;
}

int minOps(int n){
    if(n<2){
        return 0;
    }
    if(isPrim(n)){
        return n-1;
    }
    vector<int>arr=divsSumAndCount(n);
    return arr[0]-arr[1];
}