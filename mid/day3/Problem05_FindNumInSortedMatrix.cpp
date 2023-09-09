/*
给定一个元素为非负整数的二维数组matrix，每行和每列都是从小到大有序的。
再给定一个非负整数aim，请判断aim是否在matrix中。
*/
#include <iostream>
#include <vector>
using namespace std;
bool isContains(vector<vector<int>>matrix,int K){
    int row=0;
    int col=matrix[0].size()-1;
    while(row<matrix.size()&&col>-1){
        if(matrix[row][col]==K){
            return true;
        }else if(matrix[row][col]>K){
            col--;
        }else{
            row++;
        }
    }
    return false;
}