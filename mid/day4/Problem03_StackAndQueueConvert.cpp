/*
如何仅用队列结构实现栈结构?
如何仅用栈结构实现队列结构?
*/
#include <iostream>
#include <stack>

class TwoStackQueue{
private:
    std::stack<int>stackPush;
    std::stack<int>stackpop;

public:
    TwoStackQueue(){};
    void pushToppop(){
        if(stackpop.empty()){
            while(!stackPush.empty()){
                stackpop.push(stackPush.top());
                stackPush.pop();
            }
        }
    }
    void add(int pushInt){
        stackPush.push(pushInt);
        pushToppop();
    }
    void poll(){
        if(stackpop.empty()&&stackPush.empty()){
            throw std::runtime_error("Queue id empty");
        }
        pushToppop();
        return stackpop.pop();
    }
    int peek(){
        if(stackpop.empty()&&stackPush.empty()){
            throw std::runtime_error("Queue id empty");
        }
        pushToppop();
        return stackpop.top();
    }
};
