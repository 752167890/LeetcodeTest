/*题目17：Letter Combinations of a Phone Number 
这个题是抄袭的网上的答案。希望能给以后再遇到这种全排列的问题开辟道路
思路很容易。但是不会用代码实现这种全排列的问题。

编程的时候，回溯法非常重要。
*/
//递归解法
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> res;
        //如果数据为空返回空结果
        if (digits.empty()) return res;
        //数据的字典
        string dict[] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        //递归
        letterCombinationsDFS(digits, dict, 0, "", res);
        return res;
    }
    void letterCombinationsDFS(string digits, string dict[], int level, string out, vector<string> &res) {
        //如果递归到最后，那么将结果放入res。
        if (level == digits.size()) res.push_back(out);
        else {
        	//获取当前数字在字典中的字母
            string str = dict[digits[level] - '2'];
            //
            for (int i = 0; i < str.size(); ++i) {
                out.push_back(str[i]);
                letterCombinationsDFS(digits, dict, level + 1, out, res);
                //这一步是回溯（很关键）
                /*
                比如给定的数字是“2,3”
                1.out中存了一个a
				2.进入DFS函数，因为此时leverl为1，没有到digits.size()，所以进入else中
				将out变为“ad”
				3.再次进入DFS函数，此时因为level=2已经与digits.size()相等，将out放入结果res中
				4.递归结束，此时开始回溯（很关键），回溯到1的状态，也就是out存入了一个a
				5.再次重复2,3得到"ae","af"。然后再次结束递归，此时两次回溯（因为1进入一次，2进入一次）
				6.此时的out为空，存入b，然后重复。
                */
                out.pop_back();
            }
        }
    }
};
//迭代解法
/*
迭代解法可读性比较好，但是编写难度感觉比较大。
整体思路解读：以2,3为例子
	1.在res中存入“”,如果数字没有，立马返回
	2.存入第一个数字的字典，也就是res={'a','b','c'}
	3.开始改写，将a擦除，改写为ad,ae,af。每次改写的时候的迭代次数由n控制
	4.同理，改写b,c得到结果
*/
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> res;
        if (digits.empty()) return res;
        string dict[] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        res.push_back("");
        for (int i = 0; i < digits.size(); ++i) {
        	//这一步用来实现，迭代次数的控制
            int n = res.size();
            string str = dict[digits[i] - '2'];
            for (int j = 0; j < n; ++j) {
                string tmp = res.front();
                //这一步实现，不停的替换改写。
                res.erase(res.begin());
                for (int k = 0; k < str.size(); ++k) {
                    res.push_back(tmp + str[k]);
                }
            }
        }
        return res;
    }
};