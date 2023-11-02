/*
任何一个str的二叉树结构中，如果两个节点有共同的父节点，那么这两个节点可以交换位
置，这两个节点叫作一个交换组。一个结构会有很多交换组，每个交换组都可以选择进行交
换或者不交换，最终形成一个新的结构，这个新结构所代表的字符串叫作 str的旋变字符串。
比如， 在上面的结构五中，交换组有a和b、ab和c、abc和d。如果让a和b的组交换；让ab和
c的组不交 换；让abc和d的组交换，形成的结构如图
____dbac____
/ \
d __bac__
/ \ __ba__ c
/ \
b a

这个新结构所代表的字符串为"dbac"，叫作"abcd"的旋变字符串。也就是说，一个字符串
str的旋变字符串是非常多的，str 可以形成很多种结构，每一种结构都有很多交换组，每
一个交换组都可以选择交换或者不交换，形成的每一个新的字符串都叫 str的旋变字符串。
给定两个字符串str1和str2，判断str2是不是str1的旋变字符串。
*/
#include<iostream>
#include<string>
#include<vector>
using namespace std;

bool sameTypeSameNumberr(string str1,string str2){
    if(str1.size()!=str2.size()){
        return false;
    }
    vector<int>map(256);
    for(int i=0;i<str1.size();i++){
        map[str1[i]]++;
    }
    for(int i=0;i<str2.size();i++){
        if(--map[str2[i]]<0){
            return false;
        }
    }
    return true;
}
// 返回str1[从L1开始往右长度为size的子串]和str2[从L2开始往右长度为size的子串]是否互为旋变字符串
// 在str1中的这一段和str2中的这一段一定是等长的，所以只用一个参数size
bool process(string str1,string str2,int L1,int L2,int size){
    if(size==1){
        return str1[L1]==str2[L2];
    }
    // 枚举每一种情况，有一个计算出互为旋变就返回true。都算不出来最后返回false
    for(int leftPart=1;leftPart<size;leftPart++){
        if((process(str1,str2,L1,L2,leftPart)&&process(str1,str2,L1+leftPart,L2+leftPart,size-leftPart))||
        (process(str1,str2,L1,L2+size-leftPart,leftPart)&&process(str1,str2,L1+leftPart,L2,size-leftPart))){
            return true;
        }
    }
    return false;
}


bool isScramble1(string str1,string str2){
    if(str1==str2){
        return true;
    }
    if(!sameTypeSameNumberr(str1,str2)){
        return false;
    }
    int N=str1.size();
    return process(str1,str2,0,0,N);
}

bool isScramble2(string str1,string str2){
    if(str1==str2){
        return true;
    }
    if(!sameTypeSameNumberr(str1,str2)){
        return false;
    }
    int N=str1.size();
    vector<vector<vector<bool>>>dp(N,vector<vector<bool>>(N,vector<bool>(N+1)));
    for(int L1=0;L1<N;L1++){
        for(int L2=0;L2<N;L2++){
            dp[L1][L2][1]=str1[L1]==str2[L2];
        }
    }
    // 第一层for循环含义是：依次填size=2层、size=3层..size=N层，每一层都是一个二维平面
	// 第二、三层for循环含义是：在具体的一层，整个面都要填写，所以用两个for循环去填一个二维面
	// L1的取值氛围是[0,N-size]，因为从L1出发往右长度为size的子串，L1是不能从N-size+1出发的，这样往右就不够size个字符了
	// L2的取值范围同理
	// 第4层for循环完全是递归函数怎么写，这里就怎么改的
    for(int size=2;size<=N;size++){
        for(int L1=0;L1<=N-size;L1++){
            for(int L2=0;L2<=N-size;L2++){
                for(int leftPart=1;leftPart<size;leftPart++){//leftPart到N,就是两个字符串完全相同，在前面已经考虑过了。
                    if((dp[L1][L2][leftPart] && dp[L1 + leftPart][L2
								+ leftPart][size - leftPart])
								|| (dp[L1][L2 + size - leftPart][leftPart] && dp[L1
										+ leftPart][L2][size - leftPart])){
                                            dp[L1][L2][size]=true;
                                            break;
                                        }
                }
            }
        }
    }
    return dp[0][0][N];
}