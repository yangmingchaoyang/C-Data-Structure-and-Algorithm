/*
一个合法的括号匹配序列有以下定义:
①空串""是一个合法的括号匹配序列
②如果"X"和"Y"都是合法的括号匹配序列,"XY"也是一个合法的括号匹配序列
③如果"X"是一个合法的括号匹配序列,那么"(X)"也是一个合法的括号匹配序列
④每个合法的括号序列都可以由以上规则生成。
例如: "","()","()()","((()))"都是合法的括号序列
对于一个合法的括号序列我们又有以下定义它的深度:
①空串""的深度是0
②如果字符串"X"的深度是x,字符串"Y"的深度是y,那么字符串"XY"的深度为
max(x,y) 3、如果"X"的深度是x,那么字符串"(X)"的深度是x+1
例如: "()()()"的深度是1,"((()))"的深度是3。牛牛现在给你一个合法的括号
序列,需要你计算出其深度。
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

bool isValid(const std::string& str) {
    if (str.empty()) {
        return false;
    }
    int status = 0;
    for (char c : str) {
        if (c != ')' && c != '(') {
            return false;
        }
        if (c == ')' && --status < 0) {
            return false;
        }
        if (c == '(') {
            status++;
        }
    }
    return status == 0;
}

int deep(const std::string& s) {
    if (!isValid(s)) {
        return 0;
    }
    int count = 0;
    int max = 0;
    for (char c : s) {
        if (c == '(') {
            max = std::max(max, ++count);
        } else {
            count--;
        }
    }
    return max;
}

//最长合法括号字串()()()
//这个最长有效合法字串是6.
int maxlength(string chas){
    if(chas.empty()){
        return 0;
    }
    vector<int>dp(chas.size());
    int pre=0;
    int res=0;
    for(int i=1;i<chas.size();i++){
        if(chas[i]==')'){
            pre=i-dp[i-1]-1;//示当前右括号的位置减去上一个有效括号子串的长度再减 1。这个值表示当前右括号可能与之匹配的左括号的位置。
            if(pre>=0&&chas[pre]=='('){
                dp[i]=dp[i-1]+2+(pre>0?dp[pre-1]:0);
            }
        }
        res=max(res,dp[i]);
    }
    return res;
}

int main() {
    std::string input = "((()))()";
    std::cout << "Is Valid: " << isValid(input) << std::endl;
    std::cout << "Max Depth: " << deep(input) << std::endl;
    return 0;
}
