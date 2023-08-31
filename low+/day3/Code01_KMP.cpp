/*
KMP算法解决的问题
字符串str1和str2，str1是否包含str2，如果包含返回str2在str1中开始的位置。
如何做到时间复杂度O(N)完成？
*/
#include <iostream>
#include <vector>

using namespace std;
/*
KMP（Knuth-Morris-Pratt）算法是一种用于字符串匹配的高效算法，用于在一个主字符串（文本）中查找一个模式字符串（模式）的出现位置。相较于朴素的字符串匹配算法，KMP 算法具有更高的效率，特别是在处理大文本和长模式时。它的核心思想是避免在匹配失败时重复比较已经比较过的部分。

KMP 算法的主要步骤包括：

构建部分匹配表（Partial Match Table，PMT）： PMT 是一个与模式字符串相关的数据结构，它记录了模式中每个位置的前缀和后缀的最长公共部分的长度。这个表的构建是 KMP 算法的关键步骤。

使用 PMT 进行匹配： 在匹配的过程中，算法会根据 PMT 的信息来移动模式字符串，以尽可能减少主字符串和模式字符串的比较次数。

KMP 算法的优势在于它避免了在匹配失败时对已比较过的字符重新比较。具体来说，它会根据 PMT 表来判断在匹配失败后，模式字符串应该向右移动多少步，而无需将模式字符串回退到之前已经比较过的位置。

这种方式使得 KMP 算法的时间复杂度保持在 O(N+M)，其中 N 是主字符串的长度，M 是模式字符串的长度。相比朴素的字符串匹配算法的 O(N*M)，KMP 算法在某些情况下可以显著提高匹配效率。

总结而言，KMP 算法通过构建部分匹配表，利用已经比较过的信息，避免了不必要的字符比较，从而实现了高效的字符串匹配。它在处理大规模文本搜索、字符串匹配等问题中有着广泛的应用。

*/
vector<int> getnextarr(const string& str){
    vector<int>res(str.length());
    res[0]=-1;
    if(str.length()<2){
        return res;
    }
    res[1]=0;//1只能跳到0,不然一直在1的位置
    int i=2;
    int cn=0;
    while(i<str.length()){
        if(str[i-1]==str[cn]){
            res[i++]=++cn;
        }else if(cn>0){
            cn=res[cn];
        }else{
            res[i++]=0;
        }
    }
    return res;
}

int getstrindex(string str1,string str2){
    if(str1.empty()||str2.empty()||str1.size()<str2.size()){
        return -1;
    }
    int M=str1.length();
    int N=str2.length();
    int i1=0,i2=0;
    vector<int>next=getnextarr(str2);
    while(i1<M&&i2<N){
        if(str1[i1]==str2[i2]){
            i1++;
            i2++;
        }else if(next[i2]==-1){
            i1++;
        }else{
            i2=next[i2];
        }
    }
    return i2==str2.length()?i1-i2:-1;
}


int main() {
    string s = "abcababcababcabc";
    string m = "ababcabc";
    int result = getstrindex(s, m);
    cout << "Pattern found at index: " << result << endl;
    return 0;
}