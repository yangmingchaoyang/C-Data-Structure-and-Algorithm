/*
把一个数字用中文表示出来。数字范围为 [0, 99999]。
为了方便输出，使用字母替换相应的中文，万W 千Q 百B 十S 零L。使用数字取代中
文数字注：对于 11 应该表示为 一十一(1S1)，而不是十一(S1)
输入描述：
数字 0（包含）到 99999（包含）。
输出描述：
用字母替换相应的中文，万W 千Q 百B 十S 零L
示例1:
输入
12001
输出
1W2QL1
*/
#include <iostream>
#include <cmath>
#include <string>
#include <vector>

std::string num1To9(int num) {
    if (num < 1 || num > 9) {
        return "";
    }
    std::vector<std::string> names = { "一", "二", "三", "四", "五", "六", "七", "八", "九" };
    return names[num - 1];
}

std::string num1To99(int num, bool hasBai) {
    if (num < 1 || num > 99) {
        return "";
    }
    if (num < 10) {
        return num1To9(num);
    }
    int shi = num / 10;
    if (shi == 1 && (!hasBai)) {
        return "十" + num1To9(num % 10);
    } else {
        return num1To9(shi) + "十" + num1To9(num % 10);
    }
}

std::string num1To999(int num) {
    if (num < 1 || num > 999) {
        return "";
    }
    if (num < 100) {
        return num1To99(num, false);
    }
    std::string res = num1To9(num / 100) + "百";
    int rest = num % 100;
    if (rest == 0) {
        return res;
    } else if (rest >= 10) {
        res += num1To99(rest, true);
    } else {
        res += "零" + num1To9(rest);
    }
    return res;
}

std::string num1To9999(int num) {
    if (num < 1 || num > 9999) {
        return "";
    }
    if (num < 1000) {
        return num1To999(num);
    }
    std::string res = num1To9(num / 1000) + "千";
    int rest = num % 1000;
    if (rest == 0) {
        return res;
    } else if (rest >= 100) {
        res += num1To999(rest);
    } else {
        res += "零" + num1To99(rest, false);
    }
    return res;
}

std::string num1To99999999(int num) {
    if (num < 1 || num > 99999999) {
        return "";
    }
    int wan = num / 10000;
    int rest = num % 10000;
    if (wan == 0) {
        return num1To9999(rest);
    }
    std::string res = num1To9999(wan) + "万";
    if (rest == 0) {
        return res;
    } else {
        if (rest < 1000) {
            return res + "零" + num1To999(rest);
        } else {
            return res + num1To9999(rest);
        }
    }
}

std::string getNumChiExp(int num) {
    if (num == 0) {
        return "零";
    }
    std::string res = num < 0 ? "负" : "";
    int yi = std::abs(num / 100000000);
    int rest = std::abs(num % 100000000);
    if (yi == 0) {
        return res + num1To99999999(rest);
    }
    res += num1To9999(yi) + "亿";
    if (rest == 0) {
        return res;
    } else {
        if (rest < 10000000) {
            return res + "零" + num1To99999999(rest);
        } else {
            return res + num1To99999999(rest);
        }
    }
}

// for test
int generateRandomNum() {
    bool isNeg = (rand() % 2) == 0;
    int value = rand();
    return isNeg ? -value : value;
}

int main() {
    srand(time(NULL)); // Seed the random number generator
    std::cout << getNumChiExp(0) << std::endl;
    std::cout << getNumChiExp(INT_MAX) << std::endl;
    std::cout << getNumChiExp(INT_MIN) << std::endl;
    int num = generateRandomNum();
    std::cout << num << std::endl;
    std::cout << getNumChiExp(num) << std::endl;
    num = generateRandomNum();
    std::cout << num << std::endl;
    std::cout << getNumChiExp(num) << std::endl;
    num = generateRandomNum();
    std::cout << num << std::endl;
    std::cout << getNumChiExp(num) << std::endl;
    num = generateRandomNum();
    std::cout << num << std::endl;
    std::cout << getNumChiExp(num) << std::endl;
    std::cout << getNumChiExp(10) << std::endl;
    std::cout << getNumChiExp(110) << std::endl;
    std::cout << getNumChiExp(1010) << std::endl;
    std::cout << getNumChiExp(10010) << std::endl;
    std::cout << getNumChiExp(1900000000) << std::endl;
    std::cout << getNumChiExp(1000000010) << std::endl;
    std::cout << getNumChiExp(1010100010) << std::endl;
    return 0;
}

