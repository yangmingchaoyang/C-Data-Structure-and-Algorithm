/*
Manacher算法解决的问题
字符串str中，最长回文子串的长度如何求解？
如何做到时间复杂度O(N)完成？
*/
#include <iostream>
#include <vector>
using namespace std;

//为了解决偶数长度的回文子串问题
string manacherString(const string& str){
    string res="";
    int index=0;
    for(int i=0;i<(str.size()*2+1);i++){
        res+=(i&1)==0?'#':str[index++];
    }
    return res;
}

int maxLcpsLength(string str1){
    if(str1.empty()){
        return 0;
    }
    string str=manacherString(str1);
    vector<int>pArr(str.size());//回文半径数组
    int C=-1;//中心
    int R=-1;//回文右边界的再往右一个位置，最大的有效区是R-1位置
    int maxint=INT_MIN;
    for(int i=0;i<str.size();i++){
        pArr[i]=R>i?min(pArr[2*C-i],R-i):1;
        while(i+pArr[i]<str.size()&&i-pArr[i]>-1){
            if(str[i+pArr[i]]==str[i-pArr[i]]){
                pArr[i]++;
            }else{
                break;
            }
        }
        if(i+pArr[i]>R){
            R=i+pArr[i];
            C=i;
        }
        maxint=max(maxint,pArr[i]);
    }
    return maxint-1;
}


int main() {
    string str;
    cout << "Enter a string: ";
    cin >> str;
    
    int result = maxLcpsLength(str);
    cout << "Longest Palindromic Substring Length: " << result << endl;
    
    return 0;
}