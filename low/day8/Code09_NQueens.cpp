/*
N皇后问题是指在N*N的棋盘上要摆N个皇后，要求任何两个皇后不同行、不同列，
也不在同一条斜线上。
给定一个整数n，返回n皇后的摆法有多少种。
n=1，返回1。
n=2或3，2皇后和3皇后问题无论怎么摆都不行，返回0。
n=8，返回92。
*/
#include <iostream>
#include <vector>

bool isValid(std::vector<int>& record,int i,int j){
    for(int k=0;k<i;k++){
        if(j==record[k]||std::abs(record[k]-j)==std::abs(i-k)){
            return false;
        }
    }
    return true;
}


int process1(int i,std::vector<int>& record,int n){
    if(i==n){
        return 1;
    }
    int res=0;
    for(int j=0;j<n;j++){
        if(isValid(record,i,j)){
            record[i]=j;//对于这个vector来说，数据会自动覆盖
            res+=process1(i+1,record,n);
        }
    }
    return res;
}

int queue1(int n){
    if(n<1){
        return 0;
    }
    std::vector<int>record(n);
    return process1(0,record,n);
}


int process2(int limit,int colLim,int leftDiaLim,int rightDiaLim){
    if(colLim==limit){
        return 1;
    }
    int pos=limit&(~(colLim|leftDiaLim|rightDiaLim));
    int mostRightone=0;
    int res=0;
    while(pos!=0){
        mostRightone=pos&(~pos+1);
        pos=pos-mostRightone;
        res+=process2(limit,colLim|mostRightone,(leftDiaLim|mostRightone)<<1,(rightDiaLim|mostRightone)>>1);
    }
}

//colLim 列限制
//leftDiaLim左斜线限制
//rightDiaLim右斜线限制

int num2(int n){
    if(n<1||n>32){
        return 0;
    }
    //位运算
    int limit=n==32?-1:(1<<n)-1;
    return process2(limit,0,0,0);
}




int main() {
    int n = 8; // Change this to the desired value of n
    int result = queue1(n);
    std::cout << "Total solutions for " << n << "-Queens problem: " << result << std::endl;
    return 0;
}