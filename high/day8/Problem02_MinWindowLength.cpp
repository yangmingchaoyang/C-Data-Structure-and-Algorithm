/*
给定字符串str1和str2，求str1的子串中含有str2所有字符的最小子串长度
【举例】
str1="abcde"，str2="ac" 因为"abc"包含 str2 所有的字符，并且在满足这一条件的str1的所有子串中，"abc"是
最短的，返回3。
str1="12345"，str2="344" 最小包含子串不存在，返回0。
*/
#include<iostream>
#include<vector>
using namespace std;

int minLength(string str1,string str2){
    if(str1.empty()||str2.empty()||str1.size()<str2.size()){
        return 0;
    }
    vector<int>map(256);
    for(int i=0;i!=str2.size();i++){
        map[str2[i]]++;
    }
    int left=0;
    int right=0;
    int match=str2.size();
    int minLen=INT_MAX;
    while(right!=str1.size()){
        map[str1[right]]--;//可能为负数，可能为0,可能为正数。
        if(map[str1[right]]>=0){
            match--;
        }
        if(match==0){
            while(map[str1[left]]<0){
                map[str1[left++]]++;
            }
            minLen=min(minLen,right-left+1);
            match++;
            map[str1[left++]]++;
        }
        right++;
    }
    return minLen==INT_MAX?0:minLen;


}