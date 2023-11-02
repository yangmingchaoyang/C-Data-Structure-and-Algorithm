/*
实现一个特殊的栈，在实现栈的基本功能的基础上，再实现返回栈中最小元素
的操作。
要求：1.pop、push、getMin操作的时间复杂度都是O(1)；2.设计的栈类型可以
使用现成的栈结构
*/

#include <iostream>
#include <stack>
using namespace std;


class Mystack1{
private:
    stack<int>stackData;
    stack<int>stackMin;

public:

    int getmin(){
        if(this->stackMin.empty()){
            throw std::runtime_error("stack is empty");
        }
        return this->stackMin.top();
    }

    void push(int newNum){
        if(this->stackMin.empty()){
            this->stackMin.push(newNum);
        }else if(newNum<=this->getmin()){
            this->stackMin.push(newNum);
        }
        this->stackData.push(newNum);
    }

    int pop(){
        if(this->stackData.empty()){
            throw std::runtime_error("Your stack isempty");
        }
        int value=this->stackData.top();
        this->stackData.pop();
        if(value==this->getmin()){
            this->stackMin.pop();
        }
        return value;
    }
};


class Mystack2{
private:
    stack<int>stackData;
    stack<int>stackMin;

public:

    int getmin(){
        if(this->stackMin.empty()){
            throw std::runtime_error("stack is empty");
        }
        return this->stackMin.top();
    }

    void push(int newNum){
        if(this->stackMin.empty()){
            this->stackMin.push(newNum);
        }else if(newNum<this->getmin()){
            this->stackMin.push(newNum);
        }else{
            int newMin=this->stackMin.top();
            this->stackMin.push(newMin);
        }
        this->stackData.push(newNum);
    }

    int pop(){
        if(this->stackData.empty()){
            throw std::runtime_error("Your stack isempty");
        }
        int value=this->stackData.top();
        this->stackData.pop();
        this->stackMin.pop();
        return value;
    }
};

