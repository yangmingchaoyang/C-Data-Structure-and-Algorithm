/*给定一个整型矩阵，返回子矩阵的最大累计和。*/
/****************************************/
#include<iostream>
#include<vector>
using namespace std;
int maxSum(vector<vector<int>>m){
    if(m.empty()||m[0].empty()){
        return 0;
    }
    int nummax=INT_MIN;
    int cur=0;
    vector<int>s;
    s.resize(m[0].size());
    for(int i=0;i!=m.size();i++){
        s.clear();
        for(int j=i;j!=m.size();j++){
            cur=0;
            for(int k=0;k!=s.size();k++){
                s[k]+=m[j][k];
                cur+=s[k];
                nummax=max(nummax,cur);
                cur=cur<0?0:cur;
            }
        }
    }
    return nummax;
}