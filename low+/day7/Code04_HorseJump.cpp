/*
象棋中马的跳法
【题目】
请同学们自行搜索或者想象一个象棋的棋盘，然后把整个棋盘放入第一象限，棋盘的最左下
角是(0,0)位置。那么整个棋盘就是横坐标上9条线、纵坐标上10条线的一个区域。给你三个
参数，x，y，k，返回如果“马”从(0,0)位置出发，必须走k步，最后落在(x,y)上的方法数
有多少种？
*/
#include <iostream>
#include <vector>
using namespace std;

int process(int x,int y,int step){
    if(x<0||x>8||y<0||y>8){
        return 0;
    }
    if(step==0){
        return (x==0&&y==0)?1:0;
    }
    return process(x-1,y+2,step-1)
                +process(x+1,y+2,step-1)
                +process(x+2,y+1,step-1)
                +process(x+2,y-1,step-1)
                +process(x+1,y-2,step-1)
                +process(x-1,y-2,step-1)
                +process(x-2,y-1,step-1)
                +process(x-2,y+1,step-1);
}

int dpWay2(int x,int y,int step){
    vector<vector<vector<int>>>dp(9,vector<vector<int>>(10,vector<int>(step+1)));
}