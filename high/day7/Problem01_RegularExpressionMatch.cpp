/*
判定一个由[a-z]字符构成的字符串和一个包含'?'和'*'通配符的字符串是否匹配。
' * ' 是一个特殊的字符，它表示前一个字符可以重复零次或多次
通配符'?'匹配任意单一字符,'*'匹配任意多个字符包括0个字符。
字符串长度不会超过100，字符串不为空。
输入描述：
字符串 str 和包含通配符的字符串 pattern。1 <= 字符串长度 <= 100输出描述：
true 表示匹配，false 表示不匹配
*/
#include<iostream>
#include<vector>
using namespace std;

bool isValid(string s,string e){
    for(int i=0;i<s.size();i++){
        if(s[i]=='*'||s[i]=='.'){
            return false;
        }
    }
    for(int i=0;i<e.size();i++){
        /*'' 出现在字符串的开头（i == 0），这是因为在正则表达式中 '' 
        通常用于表示零次或多次重复前一个字符，而开头不能有前一个字符。
        '' 直接跟在另一个 '' 的后面，这是因为连续的 '*' 是无效的。*/
        if(e[i]=='*'&&(i==0||e[i-1]=='*')){
            return false;
        }
    }
    return true;
}

bool process(string s,string e,int si,int ei){
    if(ei==e.size()){
        return si==s.size();
    }
    /*，表示下一个字符不是 ''，那么它会检查当前字符是否匹配，即 e[ei] 是否等于 s[si] 或者是 '.'。
    如果匹配成功，它递归调用 process 来比较下一个字符，即 process(s, e, si+1, ei+1)。*/
    if(ei+1==e.size()||e[ei+1]!='*'){
        return si!=s.size()&&(e[ei]==s[si]||e[ei]=='.')&&process(s,e,si+1,ei+1);
    }
    /*如果 ei+1 是 ''，表示下一个字符是 ''，那么它使用循环来尝试匹配 e[ei] 和 s[si]。
    它不断比较 e[ei] 和 s[si]，并递归调用 process 来检查是否可以匹配零次、一次或多次重复。这个过程在循环中进行，直到匹配成功或者不匹配。*/
    while(si!=s.size()&&e[ei]==s[si]||e[ei]=='.'){
        if(process(s,e,si,ei+2)){
            return true;
        }
        si++;
    }
    return process(s,e,si,ei+2);//只匹配0次
}


bool isMatch(string &s,string &e){
    if(s.empty()||e.empty()){
        return false;
    }
    return isValid(s,e)?process(s,e,0,0):false;
}

vector<vector<bool>>initMap(string s,string e){
    int slen=s.size();
    int elen=e.size();
    vector<vector<bool>>dp(slen+1,vector<bool>(elen+1));
    dp[slen][elen]=true;
    for(int j=elen-2;j>-1;j=j-2){
        if(e[j]!='*'&&e[j+1]=='*'){
            dp[slen][j]=true;
        }else{
            break;
        }
    }
    if(slen>0&&elen>0){
        if(e[elen-1]=='.'||s[slen-1]==e[elen-1]){
            dp[slen-1][elen-1]=true;
        }
    }
    return dp;
}

bool isMathchDP(string s,string e){
    if(s.empty()||e.empty()){
        return false;
    }
    if(!isValid(s,e)){
        return false;
    }
    vector<vector<bool>>dp=initMap(s,e);
    for(int i=s.size()-1;i>-1;i--){
        for(int j=e.size()-2;j>-1;j--){
            if(e[j+1]!='*'){
                dp[i][j]=(s[i]==e[j]||e[j]=='.')&&dp[i+1][j+1];
            }else{
                int si=i;
                while(si!=s.size()&&(s[i]==e[j]||e[j]=='.')){
                    if(dp[si][j+2]){
                        dp[i][j]=true;
                    }
                    si++;
                }
                if(dp[i][j]!=true){
                    dp[i][j]=dp[si][j+2];
                }
            }
        }
    }
    return dp[0][0];
}