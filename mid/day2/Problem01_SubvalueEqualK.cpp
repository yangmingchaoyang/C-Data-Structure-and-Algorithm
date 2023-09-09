//给定一个数组arr，求差值为k的去重数字对。

#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>
using namespace std;

vector<vector<int>>  allPair(vector<int> arr,int k){
    if(arr.empty()||arr.size()<2){
        return {};
    }
    vector<vector<int>>res;
    int l=0;
    int r=arr.size()-1;
    sort(arr.begin(),arr.end());
    while(l<r){
        if(arr[r]-arr[l]>k){
            r--;
        }else if(arr[r]-arr[l]<k){
            l++;
        }else{
            res.push_back({arr[l],arr[r]});
            l++;
            r--;
        }
        while(l<r&&arr[l]==arr[l+1]){
            l++;
        }
        while(r>l&&arr[r]==arr[r-1]){
            r--;
        }
    }
    return res;
}


vector<vector<int>>allPair2(vector<int>arr,int k){
    unordered_set<int>set;
    for(int i=0;i<arr.size();i++){
        set.insert(arr[i]);
    }
    vector<vector<int>>res;
    for(int cur:set){
        if(set.count(cur+k)){
            res.push_back({cur,cur+k});
        }
    }
    return res;
}



