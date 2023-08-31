/*
给定一个整型数组arr，代表数值不同的纸牌排成一条线。玩家A和玩家B依次拿走每张纸
牌，规定玩家A先拿，玩家B后拿，但是每个玩家每次只能拿走最左或最右的纸牌，玩家A
和玩家B都绝顶聪明。请返回最后获胜者的分数。
【举例】
arr=[1,2,100,4]。
开始时，玩家A只能拿走1或4。如果开始时玩家A拿走1，则排列变为[2,100,4]，接下来
玩家 B可以拿走2或4，然后继续轮到玩家A... 如果开始时玩家A拿走4，则排列变为[1,2,100]，接下来玩家B可以拿走1或100，然后继
续轮到玩家A... 玩家A作为绝顶聪明的人不会先拿4，因为拿4之后，玩家B将拿走100。所以玩家A会先拿1，
让排列变为[2,100,4]，接下来玩家B不管怎么选，100都会被玩家 A拿走。玩家A会获胜，
分数为101。所以返回101。
arr=[1,100,2]。
开始时，玩家A不管拿1还是2，玩家B作为绝顶聪明的人，都会把100拿走。玩家B会获胜，
分数为100。所以返回100。
*/
#include <iostream>
#include <vector>
//返回先手玩家得到的数量
int s(std::vector<int>& arr,int l,int r);

int f(std::vector<int>& arr,int l,int r){
    if(l==r){
        return arr[l];
    }
    return std::max(arr[l]+s(arr,l+1,r),arr[r]+s(arr,l,r-1));
}

int s(std::vector<int>& arr,int l,int r){
    if(l==r){
        return 0;
    }
    return std::min(f(arr,l+1,r),f(arr,l,r-1));//这是因为先手做过选择，会使后手得到的数更小，所以要求最小值
}


int win(std::vector<int> arr){
    if(arr.size()==0){
        return 0;
    }
    return std::max(f(arr,0,arr.size()-1),s(arr,0,arr.size()-1));//求的是在这种情况下，先手和后手所能得到的最大值
}


int win2(std::vector<int>& arr){
    if(arr.size()==0){
        return 0;
    }
    int N=arr.size();
    std::vector<std::vector<int>>f(N,std::vector<int>(N,0));
    std::vector<std::vector<int>>s(N,std::vector<int>(N,0));
    for(int i=0;i<N;i++){
        f[i][i]=arr[i];
    }
    for(int i=1;i<N;i++){//这是一种斜着写的策略，
        int L=0;
        int R=i;
        while(L<N&&R<N){
            f[L][R]=std::max(arr[L]+s[L+1][R],arr[R]+s[L][R-1]);
            s[L][R]=std::min(f[L+1][R],f[L][R-1]);
            L++;
            R++;
        }
    }
    return std::max(f[0][N-1],s[0][N-1]);


}
