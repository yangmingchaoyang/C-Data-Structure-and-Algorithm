/*
打印一个字符串的全部排列
打印一个字符串的全部排列，要求不要出现重复的排列
*/
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

void process(char* str, int index, vector<string>& res) {
    if (str[index] == '\0') {
        res.push_back(string(str));
        return;
    }

    for (int i = index; str[i] != '\0'; i++) {
        swap(str[index], str[i]);
        process(str, index + 1, res);
        swap(str[index], str[i]);
    }
}

void process2(char* str, int i, vector<string>& res) {
    if (str[i] == '\0') {
        res.push_back(string(str));
        return;
    }
/*
str.c_str() 返回一个指向 std::string 对象内部字符数组的指针（const char* 类型）。
这允许你在 C++ 中使用标准字符串类的同时，将其内容传递给需要接受 C 风格字符串的 C 函数或其他需要 C 风格字符串的场景。
*/

/*
#include <iostream>
#include <string>

// 示例：接受 C 风格字符串的函数
void printCString(const char* cStr) {
    std::cout << "C-style string: " << cStr << std::endl;
}

int main() {
    std::string myString = "Hello, world!";
    
    // 将 std::string 转换为 C 风格字符串并传递给函数
    printCString(myString.c_str());

    return 0;
}


*/
    unordered_set<char> visited;
    for (int j = i; str[j] != '\0'; j++) {
        if (visited.find(str[j]) == visited.end()) {
            visited.insert(str[j]);
            swap(str[i], str[j]);
            process2(str, i + 1, res);
            swap(str[i], str[j]);
        }
    }
}

vector<string> permutation(string str) {
    vector<string> res;
    if (str.empty()) {
        return res;
    }

    char* cha = new char[str.length() + 1];
    strcpy(cha, str.c_str());

    // Uncomment one of the following lines based on which version you want to use.
    // process(cha, 0, res);
    // process2(cha, 0, res);

    delete[] cha;
    return res;
}