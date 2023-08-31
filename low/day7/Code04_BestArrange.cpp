/*
一些项目要占用一个会议室宣讲，会议室不能同时容纳两个项目的宣讲。
给你每一个项目开始的时间和结束的时间(给你一个数 组，里面是一个个具体
的项目)，你来安排宣讲的日程，要求会议室进行的宣讲的场次最多。
返回这个最多的宣讲场次。
*/
#include <iostream>
#include <vector>
#include <algorithm>

struct Program {
    int start;
    int end;

    Program(int start, int end) : start(start), end(end) {}
};

int bestArrange1(std::vector<Program*> programs);

// Helper function to recursively find the maximum number of arranged programs
int process(std::vector<Program*> programs, int done, int timeLine);

// Helper function to copy all elements from a vector except the element at the given index
std::vector<Program*> copyButExcept(std::vector<Program*> programs, int index);

int bestArrange1(std::vector<Program*> programs) {
    if (programs.empty()) {
        return 0;
    }
    return process(programs, 0, 0);
}

int process(std::vector<Program*> programs, int done, int timeLine) {
    if (programs.empty()) {
        return done;
    }
    int max = done;
    for (int i = 0; i < programs.size(); i++) {
        if (programs[i]->start >= timeLine) {
            std::vector<Program*> next = copyButExcept(programs, i);
            int curResult = process(next, done + 1, programs[i]->end);
            max = std::max(max, curResult);

            // Free the memory of the 'next' vector after the recursive call
            for (Program* program : next) {
                delete program;
            }
        }
    }
    return max;
}

std::vector<Program*> copyButExcept(std::vector<Program*> programs, int index) {
    std::vector<Program*> ans;
    for (int k = 0; k < programs.size(); k++) {
        if (k != index) {
            ans.push_back(new Program(programs[k]->start, programs[k]->end));//指针内容的复制，需要new 出一个新的指针。 
        }
    }
    return ans;
}

bool comparePrograms(const Program& p1, const Program& p2) {
    return p1.end < p2.end;
}


int bestArrange2(std::vector<Program>& programs) {
    std::sort(programs.begin(), programs.end(), comparePrograms);

    int timeline = 0;
    int result = 0;
    for (int i = 0; i < programs.size(); i++) {
        if (timeline <= programs[i].start) {
            result++;
            timeline = programs[i].end;
        }
    }
    return result;
}


int main() {
    // Example usage
    std::vector<Program> programs;
    programs.push_back(Program(1, 3));
    programs.push_back(Program(2, 4));
    programs.push_back(Program(3, 5));

    int maxArrange = bestArrange2(programs);

    std::cout << "Maximum number of arranged programs: " << maxArrange << std::endl;

    return 0;
}
