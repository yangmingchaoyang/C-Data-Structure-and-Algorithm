/*
归并排序的扩展
小和问题和逆序对问题
小和问题
在一个数组中，每一个数左边比当前数小的数累加起来，叫做这个数组
的小和。求一个数组 的小和。
例子:[1,3,4,2,5] 1左边比1小的数，没有; 3左边比3小的数，1; 4左
边比4小的数，1、3; 2左边比2小的数，1; 5左边比5小的数，1、3、4、
2; 所以小和为1+1+3+1+1+3+4+2=16
*/
#include <iostream>
#include <vector>

using namespace std;

int merge(vector<int>& arr,int l,int m,int r){
    vector<int> help(r - l + 1); 
    int i=0;
    int p1=l;
    int p2=m+1;
    int res=0;
    while(p1<=m&&p2<=r){
        res+=arr[p1]<arr[p2]?(r-p2+1)*arr[p1]:0;//除自己的数组外，右数组比他大的数有多少个，（因为它已经保证了相互比较的数组是有序的
        help[i++]=arr[p1]<arr[p2]?arr[p1++]:arr[p2++];
    }
    while(p1<=m){
        help[i++]=arr[p1++];
    }
    while(p2<=r){
        help[i++]=arr[p2++];
    }
    for(i=0;i<help.size();i++){
        arr[l+i]=help[i];
    }
    return res;
}



//递归可以使用值传递
int process(vector<int> arr,int l,int r){
    if(l==r){
        return 0;
    }
    int mid=l+((r-l)>>1);
    return process(arr,l,mid)+process(arr,mid+1,r)+merge(arr,l,mid,r);//最后一次合并产生的小和和前几次左右全部的小和。
}


int smallSum(vector<int>& arr){
    if(arr.empty()||arr.size()<2){
        return 0;
    }
    return process(arr,0,arr.size()-1);
}


int main() {
    vector<int> arr = {5, 3, 8, 2, 1, 9};
    cout<<smallSum(arr)<<endl;
    return 0;
}