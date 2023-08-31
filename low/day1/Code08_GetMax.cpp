/*
    用递归方法找一个数组中的最大值，
*/
#include<iostream>
#include <vector>

using namespace std;

int process(vector<int>arr,int L,int R){
    if(L==R){
        return arr[L];
    }
    int mid=L+((R-L)>>1);
    int leftMax=process(arr,L,mid);
    int rightMax=process(arr,mid+1,R);

    return max(leftMax,rightMax);
}

int getMax(vector<int> arr){
    return process(arr,0,arr.size()-1);
}


int main() {
    vector<int> test1 = {3, 8, 2, 10, 5};  // Max = 10
    vector<int> test2 = {1, 1, 1, 1};     // Max = 1
    vector<int> test3 = {5};              // Max = 5

    cout << "Max of test1: " << getMax(test1) << endl;
    cout << "Max of test2: " << getMax(test2) << endl;
    cout << "Max of test3: " << getMax(test3) << endl;

    return 0;
}