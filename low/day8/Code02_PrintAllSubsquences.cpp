/*
打印一个字符串的全部子序列，包括空字符串
*/
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
//使用unorderset可以保证没有重复
void process1(const std::string& str,int index,std::vector<std::string>& ans,std::string path){
    if(index==str.length()){
        ans.push_back(path);
        return;
    }
    std::string no=path;
    process1(str,index+1,ans,no);
    std::string yes=path+str[index];
    process1(str,index+1,ans,yes);

}



std::vector<std::string>subs(const std::string& s){
    std::string path="";

    std::vector<std::string> ans;

    process1(s,0,ans,path);

    return ans;
}
