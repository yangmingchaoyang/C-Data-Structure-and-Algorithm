/*
一个 char 类型的数组 chs，其中所有的字符都不同。
例如，chs=['A', 'B', 'C', ... 'Z']，则字符串与整数的对应关系如下:
A, B... Z, AA,AB...AZ,BA,BB...ZZ,AAA... ZZZ, AAAA...
1, 2...26,27, 28... 52,53,54...702,703...18278, 18279... 例如，chs=['A', 'B', 'C']，则字符串与整数的对应关系如下:
A,B,C,AA,AB...CC,AAA...CCC,AAAA...
1, 2,3,4,5...12,13...39,40... 给定一个数组 chs，实现根据对应关系完成字符串与整数相互转换的两个函数。
*/
#include<iostream>
#include<vector>
using namespace std;

char getKthCharAtChs(vector<char>chs,int k){
    if(k<1||k>chs.size()){
        return 0;
    }
    return chs[k-1];
}

string getString(vector<char>chs,int n){
    if(chs.empty()||n<1){
        return "";
    }
    int cur=1;
    int base=chs.size();//base是它的进制
    int len=0;//所需要的位数
    while(n>=cur){
        len++;
        n-=cur;
        cur*=base;
    }
    vector<char>reschar(len);//每一位上放什么字符
    int index=0;
    int nCur=0;
    do{
        cur/=base;
        nCur=n/cur;
        reschar[index++]=getKthCharAtChs(chs,nCur+1);
        n%=cur;
    }while(index!=reschar.size());
    string res="";
    for(int i=0;i<reschar.size();i++){
        res+=reschar[i];
    }
    return res;
}

int getNthFromChar(string chs,char ch){
    int res=-1;
    for (int i = 0; i != chs.size(); i++) {
		if (chs[i] == ch) {
			res = i + 1;
			break;
		}
	}
	return res;
}


int getNum(string chs,string strc){
    if(chs.empty()){
        return 0;
    }
    int base=chs.size();//是进制
    int cur=1;
    int res=0;
    for(int i=strc.size()-1;i!=-1;i--){
        res+=getNthFromChar(chs,strc[i])*cur;//通过进制算值。
        cur*=base;
    }
    return res;
}