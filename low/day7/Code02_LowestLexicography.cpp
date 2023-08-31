/*
贪心算法
在某一个标准下，优先考虑最满足标准的样本，最后考虑最不满足标准的样本，最终得到
一个答案的算法，叫作贪心算法。
也就是说，不从整体最优上加以考虑，所做出的是在某种意义上的局部最优解。
局部最优 -?-> 整体最优

贪心算法的在笔试时的解题套路
1，实现一个不依靠贪心策略的解法X，可以用最暴力的尝试
2，脑补出贪心策略A、贪心策略B、贪心策略C...
3，用解法X和对数器，去验证每一个贪心策略，用实验的方式得知哪个贪心策略正确
4，不要去纠结贪心策略的证明
*/
/*
从头到尾展示最正统的贪心策略求解过程
例子：
给定一个字符串类型的数组strs，找到一种拼接方式，使得把所有字符串拼起来之后形成的
字符串具有最小的字典序。
证明贪心策略可能是件非常腌心的事情。平时当然推荐你搞清楚所有的来龙去脉，但是笔试
时用对数器的方式！
*/
#include <iostream>
#include <vector>
#include <algorithm>

struct MyComparator {
    bool operator()(const std::string& a, const std::string& b) const {
        return (a + b) < (b + a);
    }
};

std::string lowestString(std::vector<std::string>& strs) {
    if (strs.empty()) {
        return "";
    }
    std::sort(strs.begin(), strs.end(), MyComparator());
    std::string res = "";
    for (const std::string& str : strs) {
        res += str;
    }
    return res;
}

int main() {
    std::vector<std::string> strs1 = { "jibw", "ji", "jp", "bw", "jibw" };
    std::cout << lowestString(strs1) << std::endl;

    std::vector<std::string> strs2 = { "ba", "b" };
    std::cout << lowestString(strs2) << std::endl;

    return 0;
}


