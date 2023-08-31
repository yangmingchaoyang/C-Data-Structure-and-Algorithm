#include <iostream>
#include <vector>

using namespace std;

int getnum(vector<int>arr){
    int two=0;
    for(int i:arr){
        two=two^arr[i];
    }
    int rightone=two&(~two+1);
    int three=0;
    for(int i:arr){
        if(arr[i]&rightone!=0){
            three=two^arr[i];
        }
    }
    int one=two^three;
}