#include<iostream>
using namespace std;

int f(int x,int y){
    if(x==0){
        return y+2;
    }
    if(y==0){
        return f(x-1,1);
    }
    return f(x-1,f(x,y-1));
}

int main(){
    cout<<f(2,3)<<endl;
}