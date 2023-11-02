/*
项目有四个信息：
1）哪个项目经理提的
2）被项目经理润色出来的时间点
3）项目优先级
4）项目花费的时间
项目经理们可以提交项目给程序员们，程序员可以做这些项目。
比如长度为4的数组[1, 3, 2, 2]，表示1号项目经理提的，被项目经理润色出来的时间点是3，优先级2，花
费程序员2个时间。
所以给一个N*4的矩阵，就可以代表N个项目。
给定一个正数pm，表示项目经理的数量，每个项目经理只负责自己的那些项目，并且一次只能提交一个项目
给程序员们，这个提交的项目做完了，才能再次提交。
经理对项目越喜欢，就会越早提交。一个项目优先级越高越被喜欢；如果优先级一样，花费时间越少越喜欢；
如果还一样，被项目经理润色出来的时间点越早越喜欢。
给定一个正数sde，表示程序员的数量，所有经理提交了的项目，程序员会选自己喜欢的项目做，每个人做
完了一个项目，然后才会再来挑选。
当程序员在挑选项目时，有自己的喜欢标准。一个项目花费时间越少越被喜欢；如果花费时间一样，该项目
的负责人编号越小越被喜欢。
返回一个长度为N的数组，表示N个项目的结束时间。

比如：
int pms = 2;
int sde = 2;
int[][] programs = { { 1, 1, 1, 2 }, { 1, 2, 1, 1 }, { 1, 3, 2, 2 }, { 2, 1, 1, 2 },
{ 2, 3, 5, 5 } };
返回：{3, 4, 5, 3, 9}
*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
class Program {
public:
    int index;//任务索引
    int pm;//任务负责人
    int start;//时间点，项目开始时间。
    int rank;//优先级
    int cost;//花费
    Program(){};
    Program(int idx, int pmNum, int begin, int r, int c) : index(idx), pm(pmNum), start(begin), rank(r), cost(c) {}
};

class PmLoveRule {
public:
    bool operator()(const Program& o1, const Program& o2) {
        if (o1.rank != o2.rank) {
            return o1.rank - o2.rank;
        } else if (o1.cost != o2.cost) {
            return o1.cost - o2.cost;
        } else {
            return o1.start - o2.start;
        }
    }
};

class BigQueues {
private:
    std::vector<std::priority_queue<Program, std::vector<Program>, PmLoveRule>> pmQueues;
    std::vector<Program> sdeHeap;
    std::vector<int> indexes;
    int heapsize;

public:
    BigQueues(int size) : heapsize(0), sdeHeap(size), indexes(size + 1, -1), pmQueues(size) {
        // for (int i = 0; i < size; i++) {
        //     pmQueues[i] = std::priority_queue<Program, std::vector<Program>, PmLoveRule>();
        // }
    }

    bool isEmpty() {
        return heapsize == 0;
    }

    void add(Program program) {
        std::priority_queue<Program, std::vector<Program>, PmLoveRule>& queue = pmQueues[program.pm];
        queue.push(program);
        Program head = queue.top();
        int heapindex = indexes[head.pm];
        if (heapindex == -1) {
            sdeHeap[heapsize] = head;
            indexes[head.pm] = heapsize;
            heapInsert(heapsize++);
        } else {
            sdeHeap[heapindex] = head;
            heapInsert(heapindex);
            heapify(heapindex);
        }
    }

    Program pop() {
        Program head = sdeHeap[0];
        std::priority_queue<Program, std::vector<Program>, PmLoveRule>& queue = pmQueues[head.pm];
        queue.pop();
        if (queue.empty()) {
            /*如果队列为空，首先通过 swap 函数将 sdeHeap 中的位于索引 0 和位于索引 heapsize - 1 处的对象进行交换，
            然后将 sdeHeap 中的最后一个对象（在 heapsize - 1 处）设置为默认值，通常是 Program(0, 0, 0, 0, 0)。
            还需要更新 indexes 数组，将 head.pm 对应的索引设置为 -1，以表示该 pm 编号的程序队列不再在 sdeHeap 中存在。*/
            swap(0, heapsize - 1);
            sdeHeap[--heapsize] = Program(0, 0, 0, 0, 0); // Initialize to default values
            indexes[head.pm] = -1;
        } else {
            sdeHeap[0] = queue.top();
        }
        heapify(0);
        return head;
    }

private:
    void heapInsert(int index) {
        while (index != 0) {
            int parent = (index - 1) / 2;
            if (sdeLoveRule(sdeHeap[parent], sdeHeap[index]) > 0) {
                swap(parent, index);
                index = parent;
            } else {
                break;
            }
        }
    }

    void heapify(int index) {
        int left = index * 2 + 1;
        int right = index * 2 + 2;
        int best = index;
        while (left < heapsize) {
            if (sdeLoveRule(sdeHeap[left], sdeHeap[index]) < 0) {
                best = left;
            }
            if (right < heapsize && sdeLoveRule(sdeHeap[right], sdeHeap[best]) < 0) {
                best = right;
            }
            if (best == index) {
                break;
            }
            swap(best, index);
            index = best;
            left = index * 2 + 1;
            right = index * 2 + 2;
        }
    }

    void swap(int index1, int index2) {
        Program p1 = sdeHeap[index1];
        Program p2 = sdeHeap[index2];
        sdeHeap[index1] = p2;
        sdeHeap[index2] = p1;
        indexes[p1.pm] = index2;
        indexes[p2.pm] = index1;
    }

    int sdeLoveRule(const Program& p1, const Program& p2) {
        if (p1.cost != p2.cost) {
            return p1.cost - p2.cost;
        } else {
            return p1.pm - p2.pm;
        }
    }
};

class StartRule {
public:
    bool operator()(const Program& o1, const Program& o2) {
        return o1.start - o2.start;
    }
};

std::vector<int> workFinish(int pms, int sdes, std::vector<std::vector<int>>& programs) {
    std::priority_queue<Program, std::vector<Program>, StartRule> programsQueue;
    for (int i = 0; i < programs.size(); i++) {
        Program program(i, programs[i][0], programs[i][1], programs[i][2], programs[i][3]);
        programsQueue.push(program);
    }
    std::priority_queue<int, std::vector<int>, std::greater<int>> sdeWakeQueue;//它会使堆成为一个最小堆，即顶部元素是最小的元素。
    for (int i = 0; i < sdes; i++) {
        sdeWakeQueue.push(1);//给每个程序员设置初始时间
    }
    BigQueues bigQueues(pms);
    int finish = 0;
    std::vector<int> ans(programs.size());
    while (finish != ans.size()) {
        int sdeWakeTime = sdeWakeQueue.top();
        sdeWakeQueue.pop();
        while (!programsQueue.empty()) {
            //这个条件是为了找到在当前系统唤醒时间之前就可以开始执行的任务
            if (programsQueue.top().start > sdeWakeTime) {//找到所有符合这一条件的任务加入队列进行排序。程序员开始任务的时间必须在任务开始时间之后。
                break;
            }
            bigQueues.add(programsQueue.top());
            programsQueue.pop();
        }
        if (bigQueues.isEmpty()) {
            sdeWakeQueue.push(programsQueue.top().start);//将队列中最早开始的程序的开始时间添加到 sdeWakeQueue 中，以等待下一个系统的空闲时间。
        } else {
            Program program = bigQueues.pop();
            ans[program.index] = sdeWakeTime + program.cost;
            sdeWakeQueue.push(ans[program.index]);
            finish++;
        }
    }
    return ans;
}

int main() {
    int pms = 3;
    int sdes = 2;
    std::vector<std::vector<int>> programs = {
        {1, 2, 0, 4},
        {1, 2, 3, 1},
        {0, 1, 2, 3},
        {2, 0, 3, 2}
    };

    std::vector<int> result = workFinish(pms, sdes, programs);

    for (int time : result) {
        std::cout << time << " ";
    }

    return 0;
}

