/*题目介绍：18. 4Sum 
	Given an array S of n integers, are there elements a, b, c, and d in S such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.
	Note: The solution set must not contain duplicate quadruplets. 
	For example, given array S = [1, 0, -1, 0, -2, 2], and target = 0.

	A solution set is:
	[
	  [-1,  0, 0, 1],
	  [-2, -1, 1, 2],
	  [-2,  0, 0, 2]
	]
	个人思路：
	这个题采用的暴力办法实现的，实现过程中采用了一些剪枝操作。但是根本还是暴力法，因此效果不是很好。
	方法就是求出A(4,n)的全排列，然后筛选出符合要求的4个数字，并去掉重复值。
	因为本题的实际是求出C(4,N),但是直接求出各种组合，因此最后只好先求排列，再筛选。
*/
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
    	//首先将原有数据进行排序，便于处理
		sort(nums.begin(),nums.end());
		vector<int> out;
		vector<vector<int>> res;
		//创建一个map，用于记录结果的前三位，以用来判断重复。
		multimap<int,vector<int>> flag;
		//用于实现全排列，记录轨迹
		vector<int> come(nums.size(),0);
		for(int i=0;i<nums.size();i++)
		{
			come[i]=1;
			//剪枝操作，这种情况，已经不可能得到target了
			if(target-nums[i]>3*nums.back()||target-nums[i]<3*nums.front())
			{
				continue;
			}
			for(int j=0;j<nums.size();j++)
			{
				//剪枝操作，这种情况，已经不可能得到target了
				if(come[j]||(target-(nums[i]+nums[j]))>2*nums.back()||(target-(nums[i]+nums[j]))<2*nums.front())
				{
					continue;
				}
				come[j]=1;
				for(int k=0;k<nums.size();k++)
				{
					//剪枝操作，这种情况，已经不可能得到target了
					if(come[k]||(target-(nums[i]+nums[j]+nums[k]))>nums.back()||(target-(nums[i]+nums[j]+nums[k]))<nums.front())
					{
						continue;
					}
					come[k]=1;
					for(int l=0;l<nums.size();l++)
					{
						if(come[l])
						{
							continue;
						}
						else
						{
							//如果符合条件
							if((nums[i]+nums[j]+nums[k]+nums[l])==target)
							{
								out.push_back(nums[i]);
								out.push_back(nums[j]);
								out.push_back(nums[k]);
								out.push_back(nums[l]);
								//将结果进行排序，从而使得排列的结果，得到一致，进而进行去重
								sort(out.begin(),out.end());
								//因为第一位会有重复，所以采用multimap来存储
								auto beg=flag.equal_range(out[0]).first;
								auto end=flag.equal_range(out[0]).second;
								//如果map中没有
								if(beg==flag.end())
								{
									vector<int> temp;
									temp.push_back(out[1]);
									temp.push_back(out[2]);
									//将前三位插入map，其中第一个数为key
									flag.insert(make_pair(out[0],temp));
									res.push_back(out);
									out.clear();
								}
								//如果第一位已经存在，判断二、三位是否重复
								else
								{
									int endflag=0;
									for(auto m=beg;m!=end;m++)
									{
										vector<int> temp;
										temp=m->second;
										//如果二三位相等，那么第四位必然相等，故直接结束这次循环
										if(temp[0]==out[1]&&temp[1]==out[2])
										{
											endflag=1;
											break;
										}
									}
									if(endflag)
									{
										out.clear();
										continue;
									}
									else
									{
										//如果二三位没有重复
										vector<int> temp;
										temp.push_back(out[1]);
										temp.push_back(out[2]);
										//插入到map中
										flag.insert(make_pair(out[0],temp));
										res.push_back(out);
										out.clear();
									}				
								}	
							}
							//剪枝操作，接下来没必要跑了，肯定没有结果了
							else if((nums[i]+nums[j]+nums[k]+nums[l])>target)
							{
								break;
							}
							//针对LeetCode的最后一个数据集专门优化，实在太难跑了，这个程序还是太渣了
							else if((l<nums.size()-5)&&(nums[i]+nums[j]+nums[k]+nums[l+5])<target)
							{
								l=l+5;
							}
						}
					}
					//下面这些都是回溯，用来实现全排列。
					come[k]=0;
				}
				come[j]=0;
			}
			come.assign(nums.size(),0);
		}
		return res;
    }
};