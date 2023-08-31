/*
Bob的生存概率
【题目】
给定五个参数n,m,i,j,k。表示在一个N*M的区域，Bob处在(i,j)点，每次Bob等概率的向上、
下、左、右四个方向移动一步，Bob必须走K步。如果走完之后，Bob还停留在这个区域上，
就算Bob存活，否则就算Bob死亡。请求解Bob的生存概率，返回字符串表示分数的方式。
*/
#include <iostream>
#include <vector>
#include <string>

using namespace std;

//求最大公约数
long gcd(long a, long b) {
    return b == 0 ? a : gcd(b, a % b);
}

long process(int N, int M, int i, int j, int K) {
    // TODO: Implement the logic of the process function
    // Replace this with your actual implementation
    return 0;
}

std::string bob1(int N, int M, int i, int j, int K) {
    long all = static_cast<long>(std::pow(4, K));//总可能的数量k^4
    long live = process(N, M, i, j, K);
    long gcd_value = gcd(all, live);
    return std::to_string(live / gcd_value) + "/" + std::to_string(all / gcd_value);
}