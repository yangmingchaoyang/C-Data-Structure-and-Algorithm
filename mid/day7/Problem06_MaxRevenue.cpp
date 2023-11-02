/*
CC直播的运营部门组织了很多运营活动，每个活动需要花费一定的时间参与，主播每参
加完一个活动即可得到一定的奖励，参与活动可以从任意活动开始，但一旦开始，就需
要将后续活动参加完毕（注意：最后一个活动必须参与），活动之间存在一定的依赖关
系（不存在环的情况），现在给出所有的活动时间与依赖关系，以及给出有限的时间，
请帮主播计算在有限的时候内，能获得的最大奖励，以及需要的最少时长。

如上图数据所示，给定有限时间为10天。可以获取得最大奖励为：11700，需要的时长为：9天。参加的活动为BDFH
四个。
输入描述：
第一行输入数据N与D，表示有N项活动，D表示给予的时长。0＜N＜＝1000，0＜D＜＝10000。
从第二行开始到N+1行，每行描述一个活动的信息，其中第一项表示当前活动需要花费的时间t，第二项表示可以获
得的奖励a，之后有N项数据，表示当前活动与其他活动的依赖关系，1表示有依赖，0表示无依赖。每项数据用空格
分开。
输出描述：
输出两项数据A与T，用空格分割。A表示所获得的最大奖励，T表示所需要的时长。
输入
8 10
3 2000 0 1 1 0 0 0 0 0
3 4000 0 0 0 1 1 0 0 0
2 2500 0 0 0 1 0 0 0 0
1 1600 0 0 0 0 1 1 1 0
4 3800 0 0 0 0 0 0 0 1
2 2600 0 0 0 0 0 0 0 1
4 4000 0 0 0 0 0 0 0 1
3 3500 0 0 0 0 0 0 0 0
输出
11700 9
*/
#include<vector>
#include<iostream>
#include<unordered_map>
#include<map>
#include<queue>
using namespace std;
/*
使用 std::map 时的情况：

有序性要求：如果你需要在键值对之间维护有序性，即按键的升序或降序遍历，应该使用 std::map。std::map 会自动维护键的有序性。

键的自定义排序：如果你需要基于自定义的比较函数对键进行排序，应该使用 std::map。你可以提供一个比较器来定义键的排序规则。

稳定性要求：如果你希望容器的迭代顺序在元素插入或删除时保持稳定，即不会发生改变，应该使用 std::map。std::map 会保持稳定的迭代顺序。

对于小型数据集：在数据集较小的情况下，使用 std::map 通常不会造成太大的性能损失，并且它提供了有序性和稳定性。

使用 std::unordered_map 时的情况：

快速查找和插入：如果你需要快速的键值对查找、插入和删除操作，并且不关心键的顺序，应该使用 std::unordered_map。它提供了平均时间复杂度为 O(1) 的操作。

大型数据集：在处理大型数据集时，std::unordered_map 的性能通常比 std::map 更好，因为哈希表的查找操作效率更高。

不需要稳定性：如果你不关心容器的迭代顺序是否稳定，即迭代顺序可以随插入和删除操作而变化，可以使用 std::unordered_map。

不需要自定义排序：如果不需要基于自定义比较函数对键进行排序，std::unordered_map 是一个不错的选择。
*/
//保证只有唯一的最后节点
//mymap为空时，会返回mymap.end();
/*********************************************/
std::map<int, int>::const_iterator findLessThanOrEqual(const std::map<int, int>& myMap, int targetKey) {
    auto it = myMap.lower_bound(targetKey);
    if (it != myMap.begin()) {
        --it; // 移动迭代器到小于等于给定键的元素
        return it;
    } else {
        // 如果找不到匹配的键，返回 end() 迭代器
        return myMap.end();
    }
}

vector<int>maxRevenue(int allTime,vector<int>revenue,vector<int>times,vector<vector<int>>dependents){
    int size=revenue.size();
    unordered_map<int,vector<int>>parents;
    for(int i=0;i<size;i++){
        parents[i]=std::vector<int>();
    }
    int end=-1;
    for(int i=0;i<dependents.size();i++){
        bool allZero=true;
        for(int j=0;j<dependents[0].size();j++){
            if(dependents[i][j]!=0){
                parents[j].push_back(i);
                allZero=false;
            }
        }
        if(allZero){
            end=i;
        }
    }
    unordered_map<int,map<int,int>>nodeCostRevenueMap;
    for(int i=0;i<size;i++){
        nodeCostRevenueMap[i]=std::map<int,int>();
    }
    nodeCostRevenueMap[end][times[end]]=revenue[end];
    queue<int>que;
    que.push(end);
    while(!que.empty()){
        int cur=que.front();
        que.pop();
        for(int last:parents[cur]){
            for(auto entry:nodeCostRevenueMap[cur]){
                int lastCost=entry.first+times[last];
                int lastRevenue=entry.second+revenue[last];
                map<int,int>&lastmap=nodeCostRevenueMap[last];//这里不能是值传递，需要是引用传递
                if(findLessThanOrEqual(lastmap,lastCost)==lastmap.end()||findLessThanOrEqual(lastmap,lastCost)->second<lastRevenue){
                    lastmap[lastCost]=lastRevenue;
                }
            }
            que.push(last);
        }
    }
    map<int,int>allmap;
    for(int i=0;i<size;i++){
        for(auto entry:nodeCostRevenueMap[i]){
            int cost=entry.first;
            int reven=entry.second;
            if(findLessThanOrEqual(allmap,cost)==allmap.end()||findLessThanOrEqual(allmap,cost)->second<reven){
                allmap[cost]=reven;
            }
        }
    }
    if(findLessThanOrEqual(allmap,allTime)!=allmap.end()){
        return {findLessThanOrEqual(allmap,allTime)->first,findLessThanOrEqual(allmap,allTime)->second};
    }
    return {-1,-1};
}

int main() {
    // 测试数据
    int allTime = 10;
    std::vector<int> revenue = { 2000, 4000, 2500, 1600, 3800, 2600, 4000, 3500 };
    std::vector<int> times = { 3, 3, 2, 1, 4, 2, 4, 3 };
    std::vector<std::vector<int>> dependents = {
				{ 0, 1, 1, 0, 0, 0, 0, 0 }, 
				{ 0, 0, 0, 1, 1, 0, 0, 0 }, 
				{ 0, 0, 0, 1, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 1, 1, 1, 0 }, 
				{ 0, 0, 0, 0, 0, 0, 0, 1 }, 
				{ 0, 0, 0, 0, 0, 0, 0, 1 },
				{ 0, 0, 0, 0, 0, 0, 0, 1 },
				{ 0, 0, 0, 0, 0, 0, 0, 0 }
    };

    std::vector<int> result = maxRevenue(allTime, revenue, times, dependents);

    std::cout << "Max Revenue: " << result[0] << ", Time: " << result[1] << std::endl;

    return 0;
}