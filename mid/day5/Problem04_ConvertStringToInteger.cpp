/*
给定一个字符串，如果该字符串符合人们日常书写一个整数的形式，返回int类
型的这个数；如果不符合或者越界返回-1或者报错。
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;
bool isValid(string chas){
    if(chas[0]!='-'&&(chas[0]<'0'||chas[0]>'9')){
        return false;
    }
    if(chas[0]=='-'&&(chas.length()==1||chas[1]=='0')){
        return false;
    }
    if(chas[0]=='0'&&chas.length()>1){
        return false;
    }
    for(int i=1;i<chas.length();i++){
        if(chas[i]<'0'||chas[i]>'9'){
            return false;
        }
        return true;
    }
}

int convert(string chas){
    if(chas.empty()){
        return 0;
    }
    if(!isValid(chas)){
        return 0;
    }
    bool posi=chas[0]=='-'?false:true;
    int minq=INT_MIN/10;
    int minr=INT_MIN%10;
    int res=0;
    int cur=0;
    for(int i=posi?0:1;i<chas.size();i++){
        cur='0'-chas[i];//这是个负数
        if((res<minq)||(res==minq&&cur<minr)){
            return 0;
        }
        res=res*10+cur;
    }
    //如果整数是正数并且 res 等于 INT_MIN，则也会发生整数溢出，
    if(posi&&res==INT_MIN){
        return 0;
    }
    return posi?-res:res;
    
}