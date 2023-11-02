#include <iostream>
#include <string>

std::string num1To19(int num) {
    if (num < 1 || num > 19) {
        return "";
    }
    std::string names[] = { "One ", "Two ", "Three ", "Four ", "Five ", "Six ",
                            "Seven ", "Eight ", "Nine ", "Ten ", "Eleven ", "Twelve ",
                            "Thirteen ", "Fourteen ", "Fifteen ", "Sixteen ", "Seventeen ",
                            "Eighteen ", "Nineteen " };
    return names[num - 1];
}

std::string num1To99(int num) {
    if (num < 1 || num > 99) {
        return "";
    }
    if (num < 20) {
        return num1To19(num);
    }
    int high = num / 10;
    std::string tyNames[] = { "Twenty ", "Thirty ", "Forty ", "Fifty ",
                             "Sixty ", "Seventy ", "Eighty ", "Ninety " };
    return tyNames[high - 2] + num1To19(num % 10);
}

std::string num1To999(int num) {
    if (num < 1 || num > 999) {
        return "";
    }
    if (num < 100) {
        return num1To99(num);
    }
    int high = num / 100;
    return num1To19(high) + "Hundred " + num1To99(num % 100);
}

std::string getNumEngExp(int num) {
    if (num == 0) {
        return "Zero";
    }
    std::string res = "";
    if (num < 0) {
        res = "Negative, ";
    }
    if (num == INT_MIN) {
        res += "Two Billion, ";
        num %= -2000000000;
    }
    num = abs(num);
    int high = 1000000000;
    int highIndex = 0;
    std::string names[] = { "Billion", "Million", "Thousand", "" };
    while (num != 0) {
        int cur = num / high;
        num %= high;
        if (cur != 0) {
            res += num1To999(cur);
            res += names[highIndex] + (num == 0 ? " " : ", ");
        }
        high /= 1000;
        highIndex++;
    }
    return res;
}

int generateRandomNum() {
    bool isNeg = (rand() % 2) == 0;
    int value = rand();
    return isNeg ? -value : value;
}

int main() {
    srand(time(NULL)); // Seed the random number generator
    std::cout << getNumEngExp(0) << std::endl;
    std::cout << getNumEngExp(INT_MAX) << std::endl;
    std::cout << getNumEngExp(INT_MIN) << std::endl;
    int num = generateRandomNum();
    std::cout << num << std::endl;
    std::cout << getNumEngExp(num) << std::endl;
    return 0;
}
