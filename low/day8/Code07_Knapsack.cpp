/*
给定两个长度都为N的数组weights和values，weights[i]和values[i]分别代表
i号物品的重量和价值。给定一个正数bag，表示一个载重bag的袋子，你装的物
品不能超过这个重量。返回你能装下最多的价值是多少？
*/
#include <iostream>
#include <vector>


int process(std::vector<int>& w,std::vector<int>& v,int index,int alreadyw,int bag){
    if(alreadyw>bag){
        return -1;
    }
    //重量没超
    if(index==w.size()){
        return 0;
    }
    int p1=process(w,v,index+1,alreadyw,bag);
    int p2next=process(w,v,index+1,alreadyw+w[index],bag);//之后的数据加上之前的数据
    int p2=-1;
    if(p2next!=-1){
        p2=v[index]+p2next;
    }
    return std::max(p1,p2);
}


int getMaxValue(std::vector<int>& w,std::vector<int>& v,int bag){
    return process(w,v,0,0,bag);
}


int process1(std::vector<int>& w,std::vector<int>& v,int index,int rest){
    if(rest<0){
        return -1;
    }
    if(index==w.size()){
        return 0;
    }
    int p1=process1(w,v,index+1,rest);
    int p2=-1;
    int p2next=process1(w,v,index+1,rest-w[index]);
    if(p2next!=-1){
        p2=v[index]+p2next;
    }
    return std::max(p1,p2);
}


int maxvalue(std::vector<int>w,std::vector<int>v,int bag){
    return process1(w,v,0,bag);
}



int dpway(std::vector<int> w,std::vector<int> v,int bag){
    int N=w.size();
    std::vector<std::vector<int>> dp(N + 1, std::vector<int>(bag + 1,0));
    for(int index=N-1;index>=0;index--){
        for(int rest=0;rest<=bag;rest++){
            int p1=dp[index+1][rest];
            int p2=-1;
            if(rest-w[index]>=0){
                p2=v[index]+dp[index+1][rest-w[index]];
            }
            dp[index][rest]=std::max(p1,p2);
        }
    }
    return dp[0][bag];
}



int main() {
    std::vector<int> weights = {2, 3, 4, 5};  // 物品重量
    std::vector<int> values = {3, 4, 5, 6};    // 物品价值
    int bagCapacity = 5;  // 背包容量

    int result = dpway(weights, values, bagCapacity);
    std::cout << "背包问题的最大价值: " << result << std::endl;

    return 0;
}