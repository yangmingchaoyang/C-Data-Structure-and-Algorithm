/*
给定一个函数f，可以1～5的数字等概率返回一个。请加工出1～7的数字等概率
返回一个的函数g。
给定一个函数f，可以a～b的数字等概率返回一个。请加工出c～d的数字等概率
返回一个的函数g。
给定一个函数f，以p概率返回0，以1-p概率返回1。请加工出等概率返回0和1的
函数g
*/

#include <iostream>
#include <vector>
using namespace std;
int rand1To5(){
    return static_cast<int>(rand()%5)+1;
}

int rand1To7(){
    int num=0;
    do{
        num=(rand1To5()-1)*5+rand1To5()-1;
    }while(num>20);
    return num%7+1;
}


int rand1ToM(int m){
    return static_cast<int>(rand()%m)+1;
}

//它的作用是将一个十进制整数转换为任意进制（m 进制）表示，并将每一位的数字存储在一个向量（vector）中。
vector<int> getMSysNum(int value,int m){//value是目标值
    vector<int>res(32);
    int index=res.size()-1;
    while(value!=0){
        res[index--]=value%m;
        value=value/m;
    }
    return res;
}

vector<int> getRanMSysNumLessN(vector<int>nMsys,int m){
    vector<int>res(nMsys.size());
    int start=0;
    while(nMsys[start]==0){
        start++;
    }
    int index=start;
    bool lastEqual=true;
    while(index!=nMsys.size()){
        res[index]=rand1ToM(m)-1;
        if(lastEqual){
            if(res[index]>nMsys[index]){
                index=start;
                lastEqual=true;
                continue;
            }else{
                lastEqual=res[index]==nMsys[index];
            }
        }
        index++;
    }
    return res;
}

int getNumFromMSysNum(vector<int>mSysNum,int m){
		int res = 0;
		for (int i = 0; i != mSysNum.size(); i++) {
			res = res * m + mSysNum[i];
		}
		return res;
}

int rand1ToN(int n,int m){
    vector<int>nMSys=getMSysNum(n-1,m);
    vector<int>randNum=getRanMSysNumLessN(nMSys,m);
    return getNumFromMSysNum(randNum,m)+1;
}
