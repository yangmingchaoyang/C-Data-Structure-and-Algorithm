/*
岛问题
【题目】
一个矩阵中只有0和1两种值，每个位置都可以和自己的上、下、左、右 四个位置相连，如
果有一片1连在一起，这个部分叫做一个岛，求一个矩阵中有多少个岛?
【举例】
001010
111010
100100
000000
这个矩阵中有三个岛
【进阶】
如何设计一个并行算法解决这个问题
*/

#include <iostream>
#include <vector>
using namespace std;

//数组无法输出的问题，一般都是因为越界了。
void infect(vector<vector<int>>& m ,int i,int j,int N,int M){
    if(i<0||i>=N||j<0||j>=M||m[i][j]!=1){
        return;
    }
    m[i][j]=2;//将1变为2，这样的话下次再到这个位置，就知道来过了。
    infect(m,i+1,j,N,M);
    infect(m,i-1,j,N,M);
    infect(m,i,j+1,N,M);
    infect(m,i,j-1,N,M);
}



int countIslands(vector<vector<int>>m){
    if(m.empty()||m[0].empty()){
        return 0;
    }
    int N=m.size();
    int M=m[0].size();
    int res=0;
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            if(m[i][j]==1){
                res++;
                infect(m,i,j,N,M);
            }
        }
    }
    return res;
}


int main() {
    vector<vector<int>> map = {
        {1, 1, 0, 0, 0},
        {1, 1, 0, 1, 1},
        {0, 0, 0, 1, 1},
        {0, 0, 0, 0, 0},
        {1, 1, 0, 1, 1}
    };

    int islands = countIslands(map);
    cout << "Number of islands: " << islands << endl;

    return 0;
}