/*
请编写一个程序，对一个栈里的整型数据，按升序进行排序（即排序前，栈里
的数据是无序的，排序后最大元素位于栈顶），要求最多只能使用一个额外的
栈存放临时数据，但不得将元素复制到别的数据结构中。
*/

#include <iostream>
#include <stack>

using namespace std;
void sortStackByStack(stack<int> sta){
    stack<int> help;
    while(!sta.empty()){
        int cur=sta.top();
        sta.pop();
        while(!help.empty()&&help.top()<cur){
            sta.push(help.top());
            help.pop();
        }
        help.push(cur);
    }
    while(!help.empty()){
        sta.push(help.top());
        help.pop();
    }

}