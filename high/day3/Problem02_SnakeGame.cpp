/*
给定一个二维数组matrix，每个单元都是一个整数，有正有负。最开始的时候小Q操纵
一条长度为0的蛇蛇从矩阵最左侧任选一个单元格进入地图，蛇每次只能够到达当前位
置的右上相邻，右侧相邻和右下相邻的单元格。蛇蛇到达一个单元格后，自身的长度会
瞬间加上该单元格的数值，任何情况下长度为负则游戏结束。小Q是个天才，他拥有一
个超能力，可以在游戏开始的时候把地图中的某一个节点的值变为其相反数（注：最多
只能改变一个节点）。问在小Q游戏过程中，他的蛇蛇最长长度可以到多少？
比如：
1 -4 10
3 -2 -1
2 -1 0
0 5 -2
最优路径为从最左侧的3开始，3 -> -4(利用能力变成4) -> 10。所以返回17。
*/
//行，列，min,能力是否使用,本身的值,返回值比较大小。
#include<iostream>
#include<vector>
using namespace std;

// 从(i,j)出发一直走到最右侧的旅程中
// 0) 在没有使用过能力的情况下，返回路径最大和
// 1) 在使用过能力的情况下，返回路径最大和
vector<int> process(vector<vector<int>>m,int i,int j){
    if(j==m[0].size()-1){
        return vector<int>{m[i][j],-m[i][j]};
    }
    vector<int>restAns=process(m,i,j+1);
    int restUnuse=restAns[0];
    int restUse=restAns[1];
    if(i-1>=0){
        restAns = process(m, i - 1, j + 1);
        restUnuse = max(restUnuse, restAns[0]);
		restUse = max(restUse, restAns[1]);
    }
    if (i + 1 < m.size()) {
			restAns = process(m, i + 1, j + 1);
			restUnuse =max(restUnuse, restAns[0]);
			restUse =max(restUse, restAns[1]);
	}
    int no=m[i][j]+restUnuse;
    int yes=max(m[i][j]+restUse,-m[i][j]+restUnuse);//这句代码很强啊。
    return vector<int>{no,yes};
}


int walk1(vector<vector<int>>matrix){
    if(matrix.empty()||matrix[0].empty()){
        return 0;
    }
    int res=INT_MIN;
    for(int i=0;i<matrix.size();i++){
        vector<int>ans=process(matrix,i,0);
        res=max(res,max(ans[0],ans[1]));
    }
    return res;
}

int walk2(vector<vector<int>>matrix){
    if(matrix.empty()||matrix[0].empty()){
        return 0;
    }
    vector<vector<vector<int>>>dp(matrix.size(),vector<vector<int>>(matrix[0].size(),vector<int>(2)));
    for(int i=0;i<dp.size();i++){
        dp[i][matrix[0].size()-1][0]=matrix[i][matrix[0].size()-1];
        dp[i][matrix[0].size()-1][1]=-matrix[i][matrix[0].size()-1];
    }
    for(int j=matrix[0].size()-2;j>=0;j--){
        for(int i=0;i<matrix.size();i++){
            int restUnuse=dp[i][j+1][0];
            int restUse=dp[i][j+1][1];
            if (i - 1 >= 0) {
				restUnuse = max(restUnuse, dp[i - 1][j + 1][0]);
				restUse = max(restUse, dp[i - 1][j + 1][1]);
			}
			if (i + 1 < matrix.size()) {
				restUnuse =max(restUnuse, dp[i + 1][j + 1][0]);
				restUse = max(restUse, dp[i + 1][j + 1][0]);
			}
            dp[i][j][0]=matrix[i][j]+restUnuse;
            dp[i][j][1]=max(matrix[i][j]+restUse,-matrix[i][j]+restUnuse);
        }
    }
    int res=INT_MAX;
    for(int i=0;i<matrix.size();i++){
        res=max(res,max(dp[i][0][0],dp[i][0][1]));
    }
    return res;
}