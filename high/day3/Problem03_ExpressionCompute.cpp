/*
给定一个字符串str，str表示一个公式，公式里可能有整数、加减乘除符号和左右
括号，返回公式的计算结果。
【举例】
str="48*((70-65)-43)+8*1"，返回-1816。
str="3+1*4"，返回7。
str="3+(1*4)"，返回7。
【说明】
1．可以认为给定的字符串一定是正确的公式，即不需要对str做公式有效性检查。
2．如果是负数，就需要用括号括起来，比如"4*(-3)"。但如果负数作为公式的开头
或括号部分的开头，则可以没有括号，比如"-3*4"和"(-3*4)"都是合法的。
3．不用考虑计算过程中会发生溢出的情况。
*/
#include<iostream>
#include<vector>
#include<string>
#include<list>
#include<deque>
using namespace std;
/*
你可以选择使用 deque 或 list。如果需要在两端进行频繁的插入和删除操作，deque 通常更合适。
如果需要频繁在任意位置进行插入和删除操作，或者需要维护稳定的迭代器，list 可能更适合。
*/
void addNum(std::deque<std::string>& que, int num) {
    if (!que.empty()) {
        int cur = 0;
        std::string top = que.back();
        que.pop_back();
        if (top == "+" || top == "-") {
            que.push_back(top);
        } else {
            cur = std::stoi(que.back());//转为数字
            que.pop_back();
            num = (top == "*") ? (cur * num) : (cur / num);
        }
    }
    que.push_back(std::to_string(num));
}

int getNum(std::deque<std::string>& que) {
    int res = 0;
    bool add = true;
    std::string cur;
    int num = 0;
    while (!que.empty()) {
        cur = que.front();
        que.pop_front();
        if (cur == "+") {
            add = true;
        } else if (cur == "-") {
            add = false;
        } else {
            num = std::stoi(cur);
            res += add ? num : (-num);
        }
    }
    return res;
}

int getValue(std::string str) {
    char* charArray = new char[str.length() + 1];
    std::strcpy(charArray, str.c_str());
    int result = value(charArray, 0)[0];
    delete[] charArray;
    return result;
}

int* value(char* str, int i) {
    std::deque<std::string> que;
    int pre = 0;
    int* bra = nullptr;
    while (i < std::strlen(str) && str[i] != ')') {
        if (str[i] >= '0' && str[i] <= '9') {
            pre = pre * 10 + (str[i++] - '0');
        } else if (str[i] != '(') {
            std::string numStr(1, str[i]);
            addNum(que, pre);
            que.push_back(numStr);
            pre = 0;
            i++;
        } else {
            bra = value(str, i + 1);
            pre = bra[0];
            i = bra[1] + 1;
            delete[] bra;
        }
    }
    addNum(que, pre);
    int result = getNum(que);
    int* resArray = new int[2];
    resArray[0] = result;
    resArray[1] = i;
    return resArray;
}