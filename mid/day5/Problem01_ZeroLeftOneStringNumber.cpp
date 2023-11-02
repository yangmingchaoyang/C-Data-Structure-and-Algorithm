/*
字符串只由'0'和'1'两种字符构成，
当字符串长度为1时，所有可能的字符串为"0"、"1"；
当字符串长度为2时，所有可能的字符串为"00"、"01"、"10"、"11"；
当字符串长度为3时，所有可能的字符串为"000"、"001"、"010"、"011"、"100"、
"101"、"110"、"111"
... 如果某一个字符串中，只要是出现'0'的位置，左边就靠着'1'，这样的字符串叫作达
标字符串。
给定一个正数N，返回所有长度为N的字符串中，达标字符串的数量。
比如，N=3，返回3，因为只有"101"、"110"、"111"达标。
*/
#include<iostream>
#include<vector>
using namespace std;

int getNum1(int n){
    if(n<1){
        return 0;
    }
    return process(1,n);
}
//对每个位置的数为0,为1做判断。
int process(int i,int n){
    if(i==n-1){//n-1时有两种情况，i为0或者i为1;
        return 2;
    }
    if(i==n){//n时只有一种为1的情况。
        return 1;
    }
    return process(i+1,n)+process(i+2,n);
}


int getNum2(int n){
    if(n<1){
        return 0;
    }
    if(n==1){
        return 1;
    }
    int pre=1;
    int cur=1;
    int tmp=0;
    for(int i=2;i<n+1;i++){
        tmp=cur;
        cur+=pre;
        pre=tmp;
    }
    return cur;
}
