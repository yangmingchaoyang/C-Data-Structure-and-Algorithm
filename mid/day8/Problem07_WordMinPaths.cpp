/*
给定两个字符串，记为start和to，再给定一个字符串列表list，list中一定包含to
list中没有重复字符串，所有的字符串都是小写的。
规定：
start每次只能改变一个字符，最终的目标是彻底变成to，但是每次变成的新字符串必须在list
中存在。
请返回所有最短的变换路径。
【举例】
start="abc",end="cab",list={"cab","acc","cbc","ccc","cac","cbb","aab","abb"}
转换路径的方法有很多种，但所有最短的转换路径如下:
abc -> abb -> aab -> cab
abc -> abb -> cbb -> cab
abc -> cbc -> cac -> cab
abc -> cbc -> cbb -> cab
*/
#include<iostream>
#include<unordered_map>
#include<queue>
#include<vector>
#include<unordered_set>
#include<string>
#include<list>
using namespace std;
//std::vector 不支持在前面或中间插入或删除元素时的高效操作，而 std::list 更适合这种情况。
//深度优先遍历的set是重要的去重操作
unordered_map<string,int>getDistances(string start,unordered_map<string,vector<string>>nexts){
    unordered_map<string,int>distances;
    distances[start]=0;
    queue<string>que;
    que.push(start);
    unordered_set<string>set;
    set.insert(start);
    while(!que.empty()){
        string cur=que.front();
        que.pop();
        for(string str:nexts[cur]){
            if(!set.count(str)){
                distances[str]=distances[cur]+1;
                que.push(str);
                set.insert(str);
            }
        }
    }
    return distances;
}

//需要找到与给定单词相差一个字符的所有可能的单词，并检查它们是否包含在字典中。
vector<string>getNext(string chs,unordered_set<string>dict){
    vector<string>res;
    for(char cur='a';cur<='z';cur++){
        for(int i=0;i<chs.size();i++){
            if(chs[i]!=cur){
                char tmp=chs[i];
                chs[i]=cur;
                if(dict.count(chs)){
                    res.push_back(chs);
                }
                chs[i]=tmp;
            }
        }
    }
    return res;
}

unordered_map<string,vector<string>>getNexts(vector<string>words){
    unordered_set<string>dict;
    unordered_map<string,vector<string>>nexts;
    for(int i=0;i<words.size();i++){
        nexts[words[i]]=vector<string>();
    }
    for(int i=0;i<words.size();i++){
        nexts[words[i]]=getNext(words[i],dict);
    }
    return nexts;
}
//它是一个深度优先搜索（DFS）算法的应用，用于解决图中的路径问题。
/*
cur：当前正在考虑的节点（字符串类型）。
to：目标节点，我们希望找到从 cur 到 to 的最短路径。
nexts：一个包含节点与其邻接节点列表的映射，表示图中节点之间的连接关系。
distances：一个包含每个节点到起点 cur 的距离的映射。
solution：一个用于暂时存储当前路径的字符串向量，表示从起点到当前节点 cur 的路径。
res：一个二维字符串向量，用于存储所有找到的最短路径。
*/
void getShortestPaths(const std::string& cur, const std::string& to,
    const std::unordered_map<std::string, std::vector<std::string>>& nexts,
    const std::unordered_map<std::string, int>& distances,
    std::list<std::string>& solution, std::vector<std::vector<std::string>>& res) {
    
    solution.push_back(cur);//回溯方法这个是路径相加的方法。
    if (to == cur) {//所有操作中能得到结果的操作都是最小路径，因为在深度优先遍历中，已经确定了到达to的最小步骤是多少，因此只要确定其前一个步骤数是-1的，就是他的步骤。
        res.push_back(std::vector<std::string>(solution.begin(), solution.end()));
    } else {
        for (const std::string& next : nexts.at(cur)) {
            if (distances.at(next) == distances.at(cur) + 1) {//为了最短路径
                getShortestPaths(next, to, nexts, distances, solution, res);
            }
        }
    }
    solution.pop_back();
}

std::vector<std::vector<std::string>> findMinPaths(const std::string& start, const std::string& to,
    const std::vector<std::string>& list) {
    
    std::vector<std::vector<std::string>> res;
    std::vector<std::string> tempList(list.begin(), list.end());
    tempList.push_back(start);//加入了start
    unordered_map<string,vector<string>>nexts=getNexts(list);
    unordered_map<string,int>distances=getDistances(start,nexts);
    std::list<std::string> pathList;
    getShortestPaths(start, to, nexts, distances, pathList, res);
    return res;
}