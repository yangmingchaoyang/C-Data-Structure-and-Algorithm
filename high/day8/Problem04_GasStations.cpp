/*
N个加油站组成一个环形，给定两个长度都是N的非负数组 oil和dis(N>1)，oil[i]代表
第i个加油站存的油可以跑多少千米，dis[i]代表第i个加油站到环中下一个加油站相隔
多少千米。
假设你有一辆油箱足够大的车，初始时车里没有油。如果车从第i个加油站出发，最终
可以回到这个加油站，那么第i个加油站就算良好出发点，否则就不算。
请返回长度为N的boolean型数组res，res[i]代表第 i 个加油站是不是良好出发点。
*/

#include<vector>
#include<iostream>

using namespace std;
// 已知start的next方向上有一个良好出发点
// start如果可以达到这个良好出发点，那么从start出发一定可以转一圈
void connectGood(vector<int>dis,int start,int init,vector<bool>res){
    int need=0;
    while(start!=init){
        if(dis[start]<need){
            need-=dis[start];//如果距离小于need，则减去这段距离并将need更新为差值，表示仍然需要更多的距离才能连接到init。
            break;
        }else{
            res[start]=true;//表示从start到init的连接已经成功，同时将need设置为0，表示不再需要额外距离。
            need=0;
        }
        start=lastIndex(start,dis.size());
    }
}

int lastIndex(int& index,int size){
    return index==0?(size-1):index-1;
}

int nextIndex(int& index,int size){
    return index==size-1?0:(index+1);
}

vector<bool>enlargeArea(vector<int>dis,int init){
    vector<bool>res(dis.size());
    int start=init;
    int end=nextIndex(init,dis.size());
    int need=0;
    int rest=0;
    do{
       // 当前来到的start已经在连通区域中，可以确定后续的开始点一定无法转完一圈
       if(start!=init&&start==lastIndex(end,dis.size())){
            break;
       } 
       // 当前来到的start不在连通区域中，就扩充连通区域
       if(dis[start]<need){//从当前start出发，无法到达initial点
            need-=dis[start];
       }else{//如start可以到达initial,扩充连通区域的结束点
            rest+=dis[start]-need;
            need=0;
            while(rest>=0&&end!=start){
                rest+=dis[end];
                end=nextIndex(end,dis.size());
            }
            // 如果连通区域已经覆盖整个环，当前的start是良好出发点，进入2阶段
            if(rest>=0){
                res[start]=true;
                connectGood(dis,lastIndex(start,dis.size()),init,res);//最后，将 start 更新为上一个加油站，继续循环，直到连接完成。
                break;
            }
       }
        start=lastIndex(start,dis.size());
    }while(start!=init);
    return res;
}

int changeDisArrayGetInit(vector<int>&dis,vector<int>&oil){
    int init=-1;
    for(int i=0;i<dis.size();i++){
        dis[i]=oil[i]-dis[i];
        if(dis[i]>=0){
            init=i;
        }
    }
    return init;
}

vector<bool> stations(vector<int>dis,vector<int>oil){
    if(dis.empty()||oil.empty()||dis.size()<2||oil.size()<2){
        return vector<bool>();
    }
    int init=changeDisArrayGetInit(dis,oil);
    return init==-1?vector<bool>(dis.size(),false):enlargeArea(dis,init);
}