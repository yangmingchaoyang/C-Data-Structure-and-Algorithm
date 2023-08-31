#include <iostream>
#include <vector>

using namespace std;


void swap(vector<int>arr,int i,int j){
    int temp=arr[i];
    arr[i]=arr[j];
    arr[j]=temp;
}

vector<int> getvectornum(vector<int>arr,int l,int r){
    if(l>r){
        return {-1,-1};
    }
    if(l==r){
        return {l,r};
    }
    int lessEqual=l-1;
    int mess=r;
    int index=l;
    vector<int>res;
    while(index<mess){
        if(arr[index]<arr[r]){
            swap(arr,index++,++lessEqual);
        }else if(arr[index]>arr[r]){
            swap(arr,index,--mess);
        }else{
            index++;
        }
    }
    swap(arr,mess,r);
    res[0]=lessEqual+1;
    res[1]=mess;
    return res;
}

void process(vector<int>arr,int l,int r){
    if(l>=r){
        return; 
    }
    int randnum=rand()%(r-l+1);
    swap(arr,r,randnum);
    vector<int>res=getvectornum(arr,l,r);
    process(arr,l,res[0]-1);
    process(arr,res[1]+1,r);
}

void quicksort(vector<int>arr){
    if(arr.empty()||arr.size()<2){
        return;
    }
    process(arr,0,arr.size()-1);
}
