/*
给出n个数字 a_1,...,a_n，问最多有多少不重叠的非空区间，使得每个区间内数字的
xor都等于0。
*/
#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;
int mostEOR(vector<int>arr){
    int ans=0;
    int xor=0;
    vector<int>mosts(arr.size());
    unordered_map<int,int>map;
    map[0]=-1;
    for(int i=0;i<arr.size();i++){
        xor^=arr[i];
        if(map.count(xor)){
            int pre=map[xor];
            mosts[i]=pre==-1?1:(mosts[pre]+1);
        }
        if(i>0){
            mosts[i]=max(mosts[i-1],mosts[i]);
        }
        map[xor]=i;
        ans=max(ans,mosts[i]);
    }
    return ans;
}