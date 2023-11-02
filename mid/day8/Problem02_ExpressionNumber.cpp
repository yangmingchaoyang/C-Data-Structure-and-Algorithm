/*
给定一个只由 0(假)、1(真)、&(逻辑与)、|(逻辑或)和^(异或)五种字符组成
的字符串express，再给定一个布尔值 desired。返回express能有多少种组合
方式，可以达到desired的结果。
【举例】
express="1^0|0|1"，desired=false
只有 1^((0|0)|1)和 1^(0|(0|1))的组合可以得到 false，返回 2。
express="1"，desired=false
无组合则可以得到false，返回0
*/
#include<iostream>
#include<string>
#include<vector>
using namespace std;

bool isValid(string exp){
    if((exp.size()&1)==0){
        return false;
    }
    for(int i=0;i<exp.size();i=i+2){
        if((exp[i]!='1')||(exp[i]!=0)){
            return false;
        }
    }
    for(int i=1;i<exp.size();i=i+2){
        if((exp[i] != '&') && (exp[i] != '|') && (exp[i] != '^')){
            return false;
        }
    }
    return true;
}

int p(string exp,bool desired,int L,int R){
    if(L==R){
        if(exp[L]=='1'){
            return desired?1:0;
        }else{
            return desired?0:1;
        }
    }
    int res=0;
    if(desired){
        for(int i=L+1;i<R;i+=2){
            switch (exp[i])
            {
			case '&':
					res += p(exp, true, L, i - 1) * p(exp, true, i + 1, R);
					break;
				case '|':
					res += p(exp, true, L, i - 1) * p(exp, false, i + 1, R);
					res += p(exp, false, L, i - 1) * p(exp, true, i + 1, R);
					res += p(exp, true, L, i - 1) * p(exp, true, i + 1, R);
					break;
				case '^':
					res += p(exp, true, L, i - 1) * p(exp, false, i + 1, R);
					res += p(exp, false, L, i - 1) * p(exp, true, i + 1, R);
					break;
            }
        }
    }else {
			for (int i = L + 1; i < R; i += 2) {
				switch (exp[i]) {
				case '&':
					res += p(exp, false, L, i - 1) * p(exp, true, i + 1, R);
					res += p(exp, true, L, i - 1) * p(exp, false, i + 1, R);
					res += p(exp, false, L, i - 1) * p(exp, false, i + 1, R);
					break;
				case '|':
					res += p(exp, false, L, i - 1) * p(exp, false, i + 1, R);
					break;
				case '^':
					res += p(exp, true, L, i - 1) * p(exp, true, i + 1, R);
					res += p(exp, false, L, i - 1) * p(exp, false, i + 1, R);
					break;
				}
			}
		}
		return res;
}

int num1(string express,bool desired){
    if(express.empty()){
        return 0;
    }
    if(!isValid(express)){
        return 0;
    }
    return p(express,desired,0,express.size()-1);//返回所有能够成功得到desired的方法数
}


int num2(const string &express, bool desired) {
    if (express.empty()) {
        return 0;
    }

    if (!isValid(express)) {
        return 0;
    }

    int n = express.size();
    vector<vector<int>> t(n, vector<int>(n));
    vector<vector<int>> f(n, vector<int>(n));

    for (int i = 0; i < n; i += 2) {
        t[i][i] = (express[i] == '0') ? 0 : 1;
        f[i][i] = (express[i] == '1') ? 0 : 1;
    }

    for (int i = 2; i < n; i += 2) {
        for (int j = i - 2; j >= 0; j -= 2) {
            for (int k = j; k < i; k += 2) {
                if (express[k + 1] == '&') {
                    t[j][i] += t[j][k] * t[k + 2][i];
                    f[j][i] += (f[j][k] + t[j][k]) * f[k + 2][i] + f[j][k] * t[k + 2][i];
                } else if (express[k + 1] == '|') {
                    t[j][i] += (f[j][k] + t[j][k]) * t[k + 2][i] + t[j][k] * f[k + 2][i];
                    f[j][i] += f[j][k] * f[k + 2][i];
                } else {
                    t[j][i] += f[j][k] * t[k + 2][i] + t[j][k] * f[k + 2][i];
                    f[j][i] += f[j][k] * f[k + 2][i] + t[j][k] * t[k + 2][i];
                }
            }
        }
    }
    return desired ? t[0][n - 1] : f[0][n - 1];
}