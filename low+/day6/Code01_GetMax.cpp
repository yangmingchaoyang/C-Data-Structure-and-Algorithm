/*
位运算的题目
之前介绍过一些，下面继续
给定两个有符号32位整数a和b，返回a和b中较大的。
【要求】
不用做任何比较判断。
*/
#include <iostream>

//如果传入的整数是 0，函数会返回 1，如果传入的整数是 1，函数会返回 0
//1->0
//0->1
int filp(int n){
    return n^1;
}

//n为非负数，返回1
//n为负数，返回0
int sign(int n){
    return filp((n>>31)&1);//判断符号位
}

int getMax1(int a,int b){
    int c=a-b;
    int scA=sign(c);
    int scB=filp(scA);
    return a*scA+b*scB;
}