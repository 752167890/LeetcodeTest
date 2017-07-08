/*
	题目介绍：Given a non-negative integer num, repeatedly add all its digits until the result has only one digit. 
	For example: 
	Given num = 38, the process is like: 3 + 8 = 11, 1 + 1 = 2. Since 2 has only one digit, return it. 
	Follow up:
	Could you do it without any loop/recursion in O(1) runtime? 

	解题思路：
	这是一个找规律的问题。。。ps：完全没有想到，我以为会用到位运算

	模拟这个规律:
	给定
		10 -> 1+0 =1  
		11 —> 1+1 =2
        12 -> 1+2 =3
        13 -> 1+3 =4
        14 -> 1+4 =5
        15 -> 1+5 =6
        16 -> 1+6 =7
        17 -> 1+7 =8
        18 -> 1+8 =9
        19 -> 1+9 =1
   故规律为(i-1)%9+1
*/
class Solution {
public:
    int addDigits(int num) {
    	return (num-1)%9+1;
    }
};