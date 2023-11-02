/*
在一个字符串中找到没有重复字符子串中最长的长度。
例如：
abcabcbb没有重复字符的最长子串是abc，长度为3
bbbbb，答案是b，长度为1
pwwkew，答案是wke，长度是3
要求：答案必须是子串，"pwke" 是一个子字符序列但不是一个子字符串。
*/
#include<iostream>
#include<string>
#include<vector>
using namespace std;
int maxUnique(string chas){
    if(chas.empty()){
        return 0;
    }
    vector<int>map(26,-1);//整数数组 map，用于记录每个字符最后一次出现的位置
    int len=0;
    int pre=-1;
    int cur=0;
    for(int i=0;i!=chas.size();i++){
        pre=max(pre,map[chas[i]]);//更新 pre 为 pre 和 map[chas[i]] 中的较大值，以确保 pre 始终指向当前字符之前最后一次出现的位置。
        cur=i-pre;
        len=max(len,cur);
        map[chas[i]]=i;
    }
    return len;
}