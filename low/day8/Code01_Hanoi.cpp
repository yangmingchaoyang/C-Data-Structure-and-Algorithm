/*
汉诺塔问题
打印n层汉诺塔从最左边移动到最右边的全部过程
*/
#include <iostream>
//请把1~N层圆盘从左->右

void func(int n,std::string from,std::string to,std::string other){
    if(n==1){
        std::cout<<"Move 1 from"<<from<<"to"<<to<<std::endl;
    }else{
        func(n-1,from,other,to);
        std::cout<<"Move"<<n<<"from"<<from<<"to"<<to<<std::endl;
        func(n-1,other,to,from);
    }
}


void hanoi2(int n){
    if(n>0){
        func(n,"left","right","mid");
    }
}