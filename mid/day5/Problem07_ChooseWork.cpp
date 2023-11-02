/*
为了找到自己满意的工作，牛牛收集了每种工作的难度和报酬。牛牛选工作的标准是在难度不超过自身能力
值的情况下，牛牛选择报酬最高的工作。在牛牛选定了自己的工作后，牛牛的小伙伴们来找牛牛帮忙选工作，
牛牛依然使用自己的标准来帮助小伙伴们。牛牛的小伙伴太多了，于是他只好把这个任务交给了你。
class Job {
public int money;// 该工作的报酬
public int hard; // 该工作的难度
public Job(int money, int hard) {
this.money = money;
this.hard = hard;
}
}
给定一个Job类型的数组jobarr，表示所有的工作。给定一个int类型的数组arr，表示所有小伙伴的能力。
返回int类型的数组，表示每一个小伙伴按照牛牛的标准选工作后所能获得的报酬。
*/

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

class Job {
public:
    int money;
    int hard;

    Job(int money, int hard) : money(money), hard(hard) {}
};

struct JobComparator {
    bool operator()(const Job& o1, const Job& o2) {
        return o1.hard != o2.hard ? (o1.hard < o2.hard) : (o1.money > o2.money);
    }
};

std::vector<int> getMoneys(std::vector<Job>& jobs, std::vector<int>& ability) {
    std::sort(jobs.begin(), jobs.end(), JobComparator());
    for(auto j:jobs){
        std::cout<<j.hard<<" "<<j.money<<std::endl;
    }
    std::map<int, int> map;
    map[jobs[0].hard] = jobs[0].money;
    Job pre = jobs[0];
    for (size_t i = 1; i < jobs.size(); i++) {
        if (jobs[i].hard != pre.hard && jobs[i].money > pre.money) {
            pre = jobs[i];
            map[jobs[i].hard] = jobs[i].money;
        }
    }
    std::vector<int> ans(ability.size(), 0);
    for (size_t i = 0; i < ability.size(); i++) {
        auto it = map.lower_bound(ability[i]);
        if(it->first!=ability[i]){
            if(it!=map.begin()){
                it--;
            }else{
                it=map.end();//这种操作用于初始化或重置迭代器。
            }
        }
        //auto it=map.upper_bound(ability[i]);
        if (it != map.end()) {
            ans[i] = it->second;
        }
    }
    return ans;
}

int main() {
    // 创建Job对象数组
    std::vector<Job> jobs;
    jobs.push_back(Job(100, 3));
    jobs.push_back(Job(200, 2));
    jobs.push_back(Job(300, 3));
    jobs.push_back(Job(400, 2));
    jobs.push_back(Job(500, 4));

    // 创建ability数组
    std::vector<int> ability;
    ability.push_back(1);
    ability.push_back(2);
    ability.push_back(3);
    ability.push_back(4);

    // 调用getMoneys函数
    std::vector<int> result = getMoneys(jobs, ability);

    // 打印结果
    std::cout << "Result: ";
    for (int money : result) {
        std::cout << money << " ";
    }
    std::cout << std::endl;

    return 0;
}


