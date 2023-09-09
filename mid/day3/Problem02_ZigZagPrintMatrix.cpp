/*
用zigzag的方式打印矩阵，比如如下的矩阵
0 1 2 3
4 5 6 7
8 9 10 11
打印顺序为：0 1 4 8 5 2 3 6 9 10 7 11
*/
#include <iostream>
#include <vector>
using namespace std;

void printLevel(std::vector<std::vector<int>>matrix,int ar,int ac,int br,int bc,bool fromUp){
    if(fromUp){//以及一个布尔值fromUp来表示是从右上往左下打印（true）还是从左下往右上打印（false）。
        while(ar!=br+1){
            std::cout<<matrix[ar++][ac--]<<" ";
        }
    }else{
        while(ar!=br+1){
            std::cout<<matrix[br--][bc++]<<" ";
        }
    }
}



void printMatrixZigZag(std::vector<std::vector<int>>matrix){
    int Ar=0;
    int Ac=0;
    int Br=0;
    int Bc=0;
    int Endr=matrix.size()-1;
    int Endc=matrix[0].size()-1;
    bool fromUp=false;//是不是从右上往左下打印
    while(Ar!=Endr+1){
        //我告诉你，斜线的两端，A和B，方向可以告诉你，去打印
        printLevel(matrix,Ar,Ac,Br,Bc,fromUp);
            Ar=Ac==Endc?Ar+1:Ar;
            Ac=Ac==Endc?Ac:Ac+1;
            Bc=Br==Endr?Bc+1:Bc;
            Br=Br==Endr?Br:Br+1;
            fromUp=!fromUp;
    }
    std::cout<<std::endl;
}

int main() {
    // Create a sample matrix
    std::vector<std::vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    // Call the function to print the matrix in zigzag pattern
    printMatrixZigZag(matrix);

    return 0;
}