/*
给定一个数组arr，长度为N且每个值都是正数，代表N个人的体重。再给定一个正数
limit，代表一艘船的载重。以下是坐船规则，1）每艘船最多只能做两人；2）乘客
的体重和不能超过limit。返回如果同时让这N个人过河最少需要几条船。
*/
#include<iostream>
#include<vector>
using namespace std;

//请保证arr有序
int minBoat(vector<int>arr,int weight){
    if(arr.empty()){
        return 0;
    }
    int lessR=-1;
    for(int i=arr.size()-1;i>=0;i--){
        if(arr[i]<=(weight/2)){
            lessR=i;
            break;
        }
    }
    if(lessR==-1){//如果 lessR 仍然为 -1，表示没有小于等于重量一半的物品，那么直接返回数组中所有物品的数量，因为每个物品都需要单独一艘船。
        return arr.size();
    }
    int lessIndex=lessR;
    int moreIndex=lessR+1;
    int lessUnused=0;
    while(lessIndex>=0){//直到所有的小的都循环了一变。
        int solved=0;
        while(moreIndex<arr.size()&&arr[lessIndex]+arr[moreIndex]<=weight){
            moreIndex++;
            solved++;
        }
        if(solved==0){
            lessUnused++;//将 lessUnused 增加 1，表示当前的小于等于 weight/2 的物品未被使用。
            lessIndex--;
        }else{
            lessIndex=max(-1,lessIndex-solved);
        }
    }
    /*
    计算已使用的小于等于 weight/2 的物品数量 lessUsed，未使用的数量 lessUnused，以及剩余物品中无法被分配的数量 moreUnsolved。
    */
    int lessAll = lessR + 1;
	int lessUsed = lessAll - lessUnused;
	int moreUnsolved = arr.size() - lessR - 1 - lessUsed;
	return (lessUsed + ((lessUnused + 1) >> 1)) + moreUnsolved;
    //通过(lessUnused+1)来保证奇数和偶数输出的结果相同。
}