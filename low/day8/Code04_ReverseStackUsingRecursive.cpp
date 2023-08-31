/*
给你一个栈，请你逆序这个栈，不能申请额外的数据结构，只能使用递归函数。
如何实现?
*/
#include<iostream>
#include<stack>

int f(std::stack<int>& stack){
    int result=stack.top();
    stack.pop();
    if(stack.empty()){
        return result;
    }else{
        int last=f(stack);
        stack.push(result);
        return last;
    }
}

void resever(std::stack<int>& stack){
    if(stack.empty()){
        return;
    }
    int i=f(stack);//取出栈底元素，并让其他元素复原。
    resever(stack);
    stack.push(i);
}


int main() {
    std::stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);

    std::cout << "Original stack: ";
    while (!stack.empty()) {
        std::cout << stack.top() << " ";
        stack.pop();
    }

    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);

    resever(stack);

    std::cout << "\nReversed stack: ";
    while (!stack.empty()) {
        std::cout << stack.top() << " ";
        stack.pop();
    }

    return 0;
}