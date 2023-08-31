/*
给定一个有序数组arr，代表数轴上从左到右有n个点arr[0]、arr[1]...arr[n－1]，
给定一个正数L，代表一根长度为L的绳子，求绳子最多能覆盖其中的几个点。
*/
#include <iostream>
#include <vector>
using namespace std;


//在arr[0..R]范围上，找满足>=value的最左位置
int nearestIndex(vector<int>arr,int R,int value){
    int L=0;
    int index=R;
    while(L<R){
        int mid=L+((R-L)>>1);
        if(arr[mid]>=value){
            index=mid;
            R=mid-1;
        }else{
            L=mid+1;
        }
    }
    return index;
}

//长度为L的绳子最多覆盖几个点，请保证arr有序
int maxpoint(vector<int>arr,int L){
    int res=1;
    for(int i=0;i<arr.size();i++){
        int nearest=nearestIndex(arr,i,arr[i]-L);
        res=max(res,i-nearest+1);
    }
    return res;
}


int main() {
    vector<int> arr = {1, 3, 5, 7, 9, 11, 13};
    int L = 4;

    int result = maxpoint(arr, L);
    cout << "Maximum points covered by a rope of length " << L << ": " << result << endl;

    return 0;
}
