/*
给一个包含n个整数元素的集合a，一个包含m个整数元素的集合b。
定义magic操作为，从一个集合中取出一个元素，放到另一个集合里，且操作过
后每个集合的平均值都大大于于操作前。
注意以下两点：
1）不可以把一个集合的元素取空，这样就没有平均值了
2）值为x的元素从集合b取出放入集合a，但集合a中已经有值为x的元素，则a的
平均值不变（因为集合元素不会重复），b的平均值可能会改变（因为x被取出
了）
问最多可以进行多少次magic操作？
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

double avg(double sum,int size){
    return sum/(double)(size);
}

int maxOps(vector<int>arr1,vector<int>arr2){
    double sum1=0;
    for(int i=0;i<arr1.size();i++){
        sum1+=(double)arr1[i];
    }
    double sum2=0;
    for(int i=0;i<arr2.size();i++){
        sum2+=(double)arr2[i];
    }
    if(avg(sum1,arr1.size())==avg(sum2,arr2.size())){
        return 0;
    }
    vector<int> arrMore;
    vector<int> arrLess;
    double sumMore=0;
    double sumLess=0;
    if (avg(sum1, arr1.size()) > avg(sum2, arr2.size())) {
			arrMore = arr1;
			sumMore = sum1;
			arrLess = arr2;
			sumLess = sum2;
	} else {
			arrMore = arr2;
			sumMore = sum2;
			arrLess = arr1;
			sumLess = sum1;
	}
    sort(arrMore.begin(),arrMore.end());
    unordered_set<int>setLess;
    for(int num:arrLess){
        setLess.insert(num);
    }
    int moreSize=arrMore.size();
    int lessSize=arrLess.size();
    int ops=0;
    for(int i=0;i<arrMore.size();i++){
        double cur=(double)arrMore[i];
        //在这个运算中不会发生小的平均值大于大的的平均值的情况。
        if (cur < avg(sumMore, moreSize) && cur > avg(sumLess, lessSize)
					&& !setLess.count(arrMore[i])) {
				sumMore -= cur;
				moreSize--;
				sumLess += cur;
				lessSize++;
				setLess.insert(arrMore[i]);
				ops++;
			}
    }
    return ops;




}