/*
给定一个正方形矩阵，只用有限几个变量，实现矩阵中每个位置的数顺时针转动
90度，比如如下的矩阵
0 1 2 3
4 5 6 7
8 9 10 11
12 13 14 15
矩阵应该被调整为：
12 8 4 0
13 9 5 1
14 10 6 2
15 11 7 3
*/
#include <iostream>
#include <vector>

void printEdge(std::vector<std::vector<int>>matrix,int tR,int tC,int dR,int dC){
    if(tR==dR){
        for(int i=tC;i<=dC;i++){
            std::cout<<matrix[tR][i]<<" ";
        }
    }else if(tC==dC){
        for(int i=tR;i<=dR;i++){
            for(int i=tR;i<=dR;i++){
                std::cout<<matrix[i][tC]<<" ";
            }
        }
    }else{
        int curC=tC;
        int curR=tR;
        while(curC!=dC){
            std::cout<<matrix[tR][curC]<<" ";
            curC++;
        }
        while(curR!=dR){
            std::cout<<matrix[curR][dC]<<" ";
            curR++;
        }
        while(curC!=tC){
            std::cout<<matrix[dR][curC]<<" ";
            curC--;
        }
        while(curR!=tR){
            std::cout<<matrix[curR][tC]<<" ";
            curR--;
        }
    }
}




void spirealOrderPrint(std::vector<std::vector<int>>matrix){
    int tR=0;
    int tC=0;
    int dR=matrix.size()-1;
    int dC=matrix[0].size()-1;

    while(tR<=dR&&tC<=dC){
        printEdge(matrix,tR++,tC++,dR--,dC--);
    }
}


void printMatrix(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int value : row) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    std::vector<std::vector<int>> matrix = {
        {1, 2, 3,4},
        {5, 6,7,8},
        {9,10,11,12},
        {13,14,15,16}
    };

    std::cout << "原始矩阵：" << std::endl;
    printMatrix(matrix);

    std::cout << "螺旋顺序打印：" << std::endl;
    spirealOrderPrint(matrix);

    return 0;
}