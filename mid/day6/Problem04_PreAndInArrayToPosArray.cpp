/*
已知一棵二叉树中没有重复节点，并且给定了这棵树的中序遍历数组和先序遍历
数组，返回后序遍历数组。
比如给定：
int[] pre = { 1, 2, 4, 5, 3, 6, 7 };
int[] in = { 4, 2, 5, 1, 6, 3, 7 };
返回：
{4,5,2,6,7,3,1}
*/
#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;


int setPos(vector<int>p,int pi,int pj,vector<int>n,int ni,int nj,vector<int>s,int si,unordered_map<int,int>map){
    if(pi>pj){
        return si;
    }
    s[si--]=p[pi];
    int i=map[p[pi]];
    si = setPos(p, pj - nj + i + 1, pj, n, i + 1, nj, s, si, map);
	return setPos(p, pi + 1, pi + i - ni, n, ni, i - 1, s, si, map);
}

vector<int>getPosArray(vector<int>pre,vector<int>in){
    if(pre.empty()||in.empty()){
        return {};
    }
    int len=pre.size();
    vector<int>pos(len);
    unordered_map<int,int>map;
    for(int i=0;i<len;i++){
        map[in[i]]=i;
    }
    setPos(pre,0,len-1,in,0,len-1,pos,len-1,map);
    return pos;
}

