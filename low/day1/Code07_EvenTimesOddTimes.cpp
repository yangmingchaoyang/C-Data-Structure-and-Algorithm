/*
异或运算的性质与扩展
1）0^N == N N^N == 0
2）异或运算满足交换律和结合率
3）不用额外变量交换两个数
4）一个数组中有一种数出现了奇数次，其他数都出现了偶数次，怎么找到这一个数
5）一个数组中有两种数出现了奇数次，其他数都出现了偶数次，怎么找到这两个数
*/

#include <iostream>
#include <vector>

//eor&(~eor+1)
//0^N=N,N^N=0;满足交换律和结合律

void printOddTimenum1(std::vector<int>& arr) {
    int eor = 0;
    for (int i : arr) {
        eor ^= i;
    }
    std::cout << eor << std::endl;
}

void printOddTimenum2(std::vector<int>& arr) {
    int eor = 0;
    for (int i : arr) {
        eor ^= i;
    }
    //eor&(~eor+1)//提出最右端的
    int rightOne = eor & (~eor + 1);//提出最右端的1;
    int onlyOne = 0;
    for (int i = 0; i < arr.size() - 1; i++) {
        if ((arr[i] & rightOne) != 0) {
            onlyOne ^= arr[i];
        }
    }
    std::cout << onlyOne << " " << (eor ^ onlyOne) << std::endl;
}




// 查该数的二进制有多少位为1
int bitcounts(int num) {
    int count = 0;
    while (num != 0) {
        int one = num & (~num + 1);
        count++;
        // 只能异或，因为有负数
        num = num ^ one;
    }
    return count;
}

int main() {
    // Example usage
    std::vector<int> arr = {1, 2, 2, 3, 3, 4, 4, 5, 5};
    printOddTimenum1(arr);
    printOddTimenum2(arr);
    int num = 6;
    int count = bitcounts(num);
    std::cout << "Number of 1 bits in " << num << ": " << count << std::endl;
    return 0;
}
