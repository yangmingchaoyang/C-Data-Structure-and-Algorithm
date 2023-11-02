/*
给定一个数组arr，如果通过调整可以做到arr中任意两个相邻的数字相乘是4的倍数，
返回true；如果不能返回false
*/
#include <iostream>
#include <vector>
using namespace std;
/*
给定一个数组arr，如果通过调整可以做到arr中任意两个相邻的数字相乘是4的倍数，
返回true；如果不能返回false
*/
bool nearMultiple4Times(vector<int>arr){
    int fourTimes=0;//是4的倍数的数有多少个
    int evenExpFourTimes=0;//是偶数但是不是4的倍数的数
    int odd=0;//奇数有多少个
    for(int i=0;i<arr.size();i++){
        if((arr[i]&1)!=0){
            odd++;
        }else{
            if(arr[i]%4==0){
                fourTimes++;
            }else{
                evenExpFourTimes++;
            }
        }
    }
    //如果存在是2的倍数不是4的倍数，则可以将2的倍数放在一起，则相当于开始的第一个数必须是4的倍数。
    return evenExpFourTimes==0?(fourTimes+1>=odd):(fourTimes>=odd);
} 