/*
用螺旋的方式打印矩阵，比如如下的矩阵
0 1 2 3
4 5 6 7
8 9 10 11
打印顺序为：0 1 2 3 7 11 10 9 8 4 5 6
*/
#include <iostream>
#include <vector>


void rotateEdge(std::vector<std::vector<int>>matrix,int a,int b,int c,int d){
    int tmp=0;

    for(int i=0;i<d-b;i++){
        tmp=matrix[a][b+i];
        matrix[a][b+i]=matrix[c-i][b];
        matrix[c][d+i]=matrix[a+i][d];
        matrix[a+i][d]=tmp;
    }
}

void rotate(std::vector<std::vector<int>>matrix){
    int a=0;
    int b=0;
    int c=matrix.size()-1;
    int d=matrix[0].size()-1;
    while(a<c){
        rotateEdge(matrix,a++,b++,c--,d--);
    }
}