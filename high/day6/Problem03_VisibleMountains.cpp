/*
一个不含有负数的数组可以代表一圈环形山，每个位置的值代表山的高度。比如，
{3,1,2,4,5}、{4,5,3,1,2}或{1,2,4,5,3}都代表同样结构的环形山。
山峰A和山峰B能够相互看见的条件为:
1.如果A和B是同一座山，认为不能相互看见。
2.如果A和B是不同的山，并且在环中相邻，认为可以相互看见。
3.如果A和B是不同的山，并且在环中不相邻，假设两座山高度的最小值为min。
1）如果A通过顺时针方向到B的途中没有高度比min大的山峰，认为A和B可以相互
看见
2）如果A通过逆时针方向到B的途中没有高度比min大的山峰，认为A和B可以相互
看见
3）两个方向只要有一个能看见，就算A和B可以相互看见
给定一个不含有负数且没有重复值的数组 arr，请返回有多少对山峰能够相互看见。
进阶：
给定一个不含有负数但可能含有重复值的数组arr，返回有多少对山峰能够相互看见。
*/
#include<iostream>
#include<vector>
#include<stack>
using namespace std;

class Record{
public:
    int value;
    int times;
    
    Record(){};
    Record(int value){
        this->value=value;
        this->times=1;
    }
};

// 环形数组中当前位置为i，数组长度为size，返回i的下一个位置
int nextIndex(int i,int size){
    return i<(size-1)?(i+1):0;
}
// 如果k==1返回0，如果k>1返回C(2,k)
int getInternalSum(int k){
    return k==1?0:(k*(k-1)/2);
}


int getVisibleNum(vector<int>arr){
    if(arr.empty()||arr.size()<2){
        return 0;
    }
    int size=arr.size();
    int maxIndex=0;
    //先在环中找到其中一个最大值的位置，那一个都行
    for(int i=0;i<size;i++){
        maxIndex=arr[maxIndex]<arr[i]?i:maxIndex;
    }
    stack<Record>sta;
    // 先把(最大值,1)这个记录放入stack中
    sta.push(Record(arr[maxIndex]));
    // 从最大值位置的下一个位置开始沿next方向遍历
    int index=nextIndex(maxIndex,size);
    // 用“小找大”的方式统计所有可见山峰对
    int res=0;
    // 遍历阶段开始，当index再次回到maxIndex的时候，说明转了一圈，遍历阶段就结束
    while(index!=maxIndex){//单调栈（单调递减）
		// 当前数要进入栈，判断会不会破坏第一维的数字从顶到底依次变大
		// 如果破坏了，就依次弹出栈顶记录，并计算山峰对数量
        while(sta.top().value<arr[index]){
            int k=sta.top().times;
            sta.pop();
            // 弹出记录为(X,K)，如果K==1，产生2对; 如果K>1，产生2*K + C(2,K)对。
            res+=getInternalSum(k)+2*k;
        }
        // 当前数字arr[index]要进入栈了，如果和当前栈顶数字一样就合并
		// 不一样就把记录(arr[index],1)放入栈中  
        if(sta.top().value==arr[index]){
            sta.top().times++;
        }else{
            sta.push(Record(arr[index]));
        }      
        index=nextIndex(index,size);
    }
    // 清算阶段开始了
	// 清算阶段的第1小阶段
    while(sta.size()>2){
        int times=sta.top().times;
        sta.pop();
        res+=getInternalSum(times)+2*times;
    }
    // 清算阶段的第2小阶段
    if(sta.size()==2){
        int times=sta.top().times;
        sta.pop();
        res+=getInternalSum(times)+(sta.top().times==1?times:2*times);//看最后一个数有一个只能是times，大于1就能到2*times;
    }
    // 清算阶段的第3小阶段
	res += getInternalSum(sta.top().times);//自己重复的部分
    sta.pop();
	return res;
}