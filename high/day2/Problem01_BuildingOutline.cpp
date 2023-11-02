/*
给定一个 N×3 的矩阵 matrix，对于每一个长度为 3 的小数组 arr，都表示一个大楼的三个数
据。arr[0]表示大楼的左边界，arr[1]表示大楼的右边界，arr[2]表示大楼的高度(一定大于 0)。
每座大楼的地基都在 X 轴上，大楼之间可能会有重叠，请返回整体的轮廓线数组。
【举例】
matrix = {
{2,5,6},
{1,7,4},
{4,6,7},
{3,6,5},
{10,13,2},
{9,11,3},
{12,14,4},
{10,12,5}
}
返回：
{{1,2,4},
{2,4,6},
{4,6,7},
{6,7,4},
{9,10,3},
{10,12,5},
{12,14,4}}
*/
// 排序的比较策略
// 1，第一个维度的x值从小到大。
// 2，如果第一个维度的值相等，看第二个维度的值，“加入”排在前，“删除”排在后
// 3，如果两个对象第一维度和第二个维度的值都相等，则认为两个对象相等，谁在前都行。
#include<iostream>
#include<vector>
#include<list>
#include<map>
#include <algorithm>
using namespace std;
struct Node {
    int x;
    bool isAdd;
    int h;
    Node() : x(0), isAdd(false), h(0) {} // 默认构造函数
    Node(int x, bool isAdd, int h) : x(x), isAdd(isAdd), h(h) {}
};

struct NodeComparator {
    /*首先按 x 进行升序排序。
    如果 x 相等，将按 isAdd 进行排序，"加入"（isAdd 为 true) 的节点排在前面。
    如果 x 和 isAdd 都相等，它们被视为相等，谁在前都可以。*/
    bool operator()(const Node& o1, const Node& o2) const {
        if (o1.x != o2.x) {
            return o1.x < o2.x;
        }
        if (o1.isAdd != o2.isAdd) {
            return o1.isAdd;
        }
        return false;
    }
};

list<list<int>>buildingOutline(vector<vector<int>>matrix){
    vector<Node>nodes(matrix.size()*2);
    //每一个大楼轮廓数组，产生两个描述高度变化的对象
    for(int i=0;i<matrix.size();i++){
        nodes[i*2]=Node(matrix[i][0],true,matrix[i][2]);
        nodes[i*2+1]=Node(matrix[i][1],false,matrix[i][2]);
    }
    //把描述高度变化的对象数组，按照规定的排序策略排序
    //因为数组排序是一个入和一个出，所以不用担心中间的空白的问题。
    std::sort(nodes.begin(), nodes.end(), NodeComparator());
    //TreeMap就是java中的红黑树结构，直接当作有序表使用
    map<int,int>mapHeighTimes;
    map<int,int>mapXvalueHeight;
    for(int i=0;i<nodes.size();i++){
        if(nodes[i].isAdd){//如果当前操作是加入
            if(!mapHeighTimes.count(nodes[i].h)){//没有出现的高度直接新加记录
                mapHeighTimes[nodes[i].h]=1;
            }else{
                mapHeighTimes[nodes[i].h]++;
            }
        }else{
            if(mapHeighTimes[nodes[i].h]==1){// 如果当前的高度出现次数为1，直接删除记录
                mapHeighTimes.erase(nodes[i].h);
            }else{//如果当前的高度出现次数大于1，次数减1即可
                 mapHeighTimes[nodes[i].h]--;
            }
        }
        //根据mapHeightTimes中的最大高度，设置mapXvalueHeight表
        if (mapHeighTimes.empty()) {//找到列表中x所对应的最大高度。
            mapXvalueHeight[nodes[i].x] = 0;
        } else {
            //这行代码的作用是将 mapHeightTimes 中的最大键值对的键（即最大高度的 x 坐标）赋值给 mapXvalueHeight 中指定键（nodes[i].x）的值。
            //mapHeightTimes.begin()->first 返回最小的键。
            mapXvalueHeight[nodes[i].x]=mapHeighTimes.rbegin()->first;
        }
    }
    // res为结果数组，每一个List<Integer>代表一个轮廓线，有开始位置，结束位置，高度，一共三个信息
    list<list<int>>res;
    // 一个新轮廓线的开始位置
	int start = 0;
	// 之前的最大高度
	int preHeight = 0;
    // 根据mapXvalueHeight生成res数组
    for(auto entry:mapXvalueHeight){
        //当前位置
        int curX=entry.first;
        //当前最大高度
        int curMaxheight=entry.second;
        if(preHeight!=curMaxheight){// 之前最大高度和当前最大高度不一样时
            if(preHeight!=0){
                res.push_back({start,curX,preHeight});
            }
            start=curX;
            preHeight=curMaxheight;
        }
    }
    return res;
}

int main() {
    std::vector<std::vector<int>> matrix = {
        {2, 9, 10},
        {3, 7, 15},
        {5, 12, 12},
        {15, 20, 10},
        {19, 24, 8}
    };

    std::list<std::list<int>> result = buildingOutline(matrix);

    // 打印结果
    for (const auto& outline : result) {
        std::cout << "Outline: ";
        for (const auto& item : outline) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}