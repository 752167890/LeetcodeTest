/*
	题目介绍：Divide Two Integers 
	Divide two integers without using multiplication, division and mod operator. 
	If it is overflow, return MAX_INT. 
	大意：不使用乘法、除法、取余操作的情况下，使2个数做除法，并返回结果
	如果溢出则返回MAX_INT。
	其中 dividend 为被除数  divisor为除数。
    抄袭的网上的答案，附上个人的注释。

*/
class Solution {
public:
    int divide(int dividend, int divisor) {
    	//如果除数为0，或者被除数为INT_MIN，除数为-1的时候都会造成溢出
        if (divisor == 0 || (dividend == INT_MIN && divisor == -1)) 
        	return INT_MAX;
        //采用8字节来存储，将负数转化为正数，也避免了溢出的问题
        long long m = abs((long long)dividend), n = abs((long long)divisor), res = 0;
        //判断输出序列的符号
        int sign = ((dividend < 0) ^ (divisor < 0)) ? -1 : 1;
        //如果除数为1直接输出。
        if (n == 1) 
        	return sign == 1 ? m : -m;
        /*模拟过程：
        87/5=17
        87=0101 0111
        5 =0000 0101
        每次将t<<1，并且与m比较，若m>=t，则可以将t=t<<1，也就是将t的值更新
        t=n,t<<1 =>  t=0000 1010 
        满足m>=t 此时 t<<1 => 0001 0100 p=0000 0010
        循环这个过程，直到：
        t=0101 0000 p=0001 0000
        这个while循环结束
        也就是模拟这个过程：
                                1   
                             —————————
                        0101|0101 0111
                             0101 0000
        下一步也就是m-t，然后将res=p+res。
        这里问题的关键是，将t更新到恰好m>=t的时候，所以一开始不更新t的值，先比较，如果满足再更新
        */
        //当被除数大于除数的时候
        while (m >= n) {
        	//定义t作为中间变量
            long long t = n, p = 1;
            //每次将左移1位以后与m进行比较，若m大于它则
            //这一步while里面先试探性的比较
            while (m >= (t << 1)) {
            	//将t左移1位并赋值给t，满足才更新
                t <<= 1;
                //将p左移1位
                p <<= 1;
            }
            //求p的和
            res += p;
            //将m减去t
            m -= t;
        }
        //当被除数小于除数的时候，直接输出RES=0了
        return sign == 1 ? res : -res;
    }
};