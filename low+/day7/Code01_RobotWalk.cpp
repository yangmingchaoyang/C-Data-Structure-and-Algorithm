/*
机器人达到指定位置方法数
【题目】
假设有排成一行的 N 个位置，记为 1~N，N 一定大于或等于 2。开始时机器人在其中的 M 位
置上(M 一定是 1~N 中的一个)，机器人可以往左走或者往右走，如果机器人来到 1 位置， 那
么下一步只能往右来到 2 位置;如果机器人来到 N 位置，那么下一步只能往左来到 N-1 位置。
规定机器人必须走 K 步，最终能来到 P 位置(P 也一定是 1~N 中的一个)的方法有多少种。给
定四个参数 N、M、K、P，返回方法数。
【举例】
N=5,M=2,K=3,P=3
上面的参数代表所有位置为 1 2 3 4 5。机器人最开始在 2 位置上，必须经过 3 步，最后到
达 3 位置。走的方法只有如下 3 种: 1)从2到1，从1到2，从2到3 2)从2到3，从3到2，从2到3
3)从2到3，从3到4，从4到3
所以返回方法数 3。 N=3,M=1,K=3,P=3
上面的参数代表所有位置为 1 2 3。机器人最开始在 1 位置上，必须经过 3 步，最后到达 3
位置。怎么走也不可能，所以返回方法数 0。

*/