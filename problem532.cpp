/*题目介绍：532. K-diff Pairs in an Array 
Given an array of integers and an integer k, you need to find the number of unique k-diff pairs in the array. Here a k-diff pair is defined as an integer pair (i, j), where i and j are both numbers in the array and their absolute difference is k. 
Example 1:
Input: [3, 1, 4, 1, 5], k = 2
Output: 2
Explanation: There are two 2-diff pairs in the array, (1, 3) and (3, 5).
Although we have two 1s in the input, we should only return the number of unique pairs.

Example 2:
Input:[1, 2, 3, 4, 5], k = 1
Output: 4
Explanation: There are four 1-diff pairs in the array, (1, 2), (2, 3), (3, 4) and (4, 5).

Example 3:
Input: [1, 3, 1, 5, 4], k = 0
Output: 1
Explanation: There is one 0-diff pair in the array, (1, 1).

Note:
1.The pairs (i, j) and (j, i) count as the same pair.
2.The length of the array won't exceed 10,000.
3.All the integers in the given input belong to the range: [-1e7, 1e7].
个人思路：
	本题采用了暴力解法，效率不是很高。简单来说就是维护一个二元组data_map，然后进行暴力搜索，找到满足条件的
数据时，就去data_map里面找，如果找不到，那么插入二元组，如果找得到，那么什么都不做。最后返回二元组的大小。	
*/

class Solution {
public:
    int findPairs(vector<int>& nums, int k) {
        int i,j;
		map<int,int> data_map;
		//因为k为absolute difference,也就是说k=|x-y|，所以k>=0.当k<0时，k为无效数据，直接返回0
		if(k<0)
			return 0;
		//暴力搜索
		for(i=0;i<nums.size();i++)
		{
			for(j=0;j<nums.size();j++)
			{
				//当找到满足k的数据，且不重复时（也就是j!=i时）
				if(((nums[j]-nums[i])==k)&&j!=i)
				{
					//如果二元组里面没有就插入
					if(data_map.find(nums[j])==data_map.end())
					{
						data_map.insert(pair<int,int>(nums[j],nums[i]));
					}
				}
			}
		}
		return data_map.size();
    }
};