/*
如果一个字符串为str，把字符串str前面任意的部分挪到后面形成的字符串叫
作str的旋转词。比如str="12345"，str的旋转词有"12345"、"23451"、
"34512"、"45123"和"51234"。给定两个字符串a和b，请判断a和b是否互为旋转
词。
比如：
a="cdab"，b="abcd"，返回true。
a="1ab2"，b="ab12"，返回false。
a="2ab1"，b="ab12"，返回true。
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> getNextArray(string ms){
    if(ms.length()==1){
        return {-1};
    }
    vector<int>next(ms.length());
    next[0]=-1;
    next[1]=0;
    int pos=2;
    int cn=0;
    while(pos<next.size()){
        if(ms[pos-1]==ms[cn]){
            next[pos++]=++cn;
        }else if(cn>0){
            cn=next[cn];
        }else{
            next[pos++]=0;
        }
    }
    return next;

}


int getIndexof(string s,string m){
    if(s.length()<m.length()){
        return -1;
    }
    int si=0;
    int mi=0;
    vector<int>next=getNextArray(m);
    while(si<s.size()&&mi<m.length()){
        if(s[si]==m[mi]){
            si++;
            mi++;
        }else if(next[mi]==-1){
            si++;
        }else{
            mi=next[mi];
        }
    }
    return mi==m.length()?si-mi:-1;
}
bool isRotation(string a,string b){
    if(a.empty()||b.empty()||a.length()!=b.length()){
        return false;
    }
    string b2=b+b;
    return getIndexof(b2,a)!=-1;
}