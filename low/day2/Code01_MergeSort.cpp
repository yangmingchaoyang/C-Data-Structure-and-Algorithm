/*
归并排序
1）整体就是一个简单递归，左边排好序、右边排好序、让其整体有序
2）让其整体有序的过程里用了排外序方法
3）利用master公式来求解时间复杂度
4）归并排序的实质
时间复杂度O(N*logN)，额外空间复杂度O(N)
*/
#include <iostream>
#include <vector>
using namespace std;
//归并排序(稳定性)
//必须使用引用不然就是值传递
void merge(vector<int>& arr,int l,int m,int r){
    vector<int>help;
    int i=0;
    int p1=l;
    int p2=m+1;
    while(p1<=m&&p2<=r){
        help.push_back(arr[p1]<arr[p2]?arr[p1++]:arr[p2++]);
    }
    while(p1<=m){
        help.push_back(arr[p1++]);
    }
    while(p2<=r){
        help.push_back(arr[p2++]);
    }
    for(i=0;i<help.size();i++){
        arr[l+i]=help[i];
    }
}

void process(vector<int>& arr,int l,int r){
    if(l==r){
        return;
    }
    int mid=l+((r-l)>>1);
    process(arr,l,mid);//递归是按顺序走的，但是也需要设置出正确的边界条件
    process(arr,mid+1,r);
    merge(arr,l,mid,r);
}
void mergesort2(vector<int>& arr){
    if(arr.empty()||arr.size()<2){
        return;
    }
    int N=arr.size();
    int mergeSize=1;
    while(mergeSize<N){
        int L=0;
        while(L<N){
            int M=L+mergeSize-1;
            if(M>=N){
                break;
            }
            int R=min(M+mergeSize,N-1);
            merge(arr,L,M,R);
            L=R+1;
        }
        if(mergeSize>N/2){
            break;
        }
        mergeSize<<=1;
    }
}

void mergesort(vector<int>& arr){
    if(arr.empty()||arr.size()<2){
        return;
    }
    process(arr,0,arr.size()-1);
}

int main() {
    vector<int> arr = {5, 3, 8, 2, 1, 9};
    mergesort2(arr);
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}