/*题目介绍：567. Permutation in String 
	Given two strings s1 and s2, write a function to return true if s2 contains the permutation of s1. In other words, one of the first string's permutations is the substring of the second string. 
	Example 1:
	Input:s1 = "ab" s2 = "eidbaooo"
	Output:True
	Explanation: s2 contains one permutation of s1 ("ba").

	Example 2:
	Input:s1= "ab" s2 = "eidboaoo"
	Output: False

	Note:
	The input strings only contain lower case letters.
	The length of both given strings is in range [1, 10,000].
	个人思路：
		这个题目表面上是一个全排列的问题，一开始我也是这么认为的，因此想用stl的算法库中的next_permutation和prev_permutaion生成全排列然后再进行查找。
	但是这样效率明显太低了，因为排列的复杂度是o(n!)，查找的子串的效率又是o(m*n)。当子串长度变大时根本不行。
		因此，转化了一下思路，2个排列相同的字符串只是字母的排序不同，但是每个字母出现的次数是一样的。因此，我不需要再求S1的排列了。我只需要求S2中的
	与S1的字母出现次数相同的substr就可以了。因此这个问题变成了一个字符串匹配的问题（只不过比较的不再是单个字母，而是每个字母出现的次数是否相等）。
	最好的办法肯定是采用KMP，但是我不会写，因此只好写了简单匹配。
		一开始陷入了一个坑，想当然的采用了与逻辑上最为匹配的map结构来记录字母出现的次数，这样尽管直观，但是因为涉及到排序。时间复杂度为o(nlogn)。
	因此极大的增加了时间复杂度，最后改成数组以后，复杂度变成了O(n)然后就可以AC了。	
*/
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
		//s1串比s2串长，直接false
		if(s1.size()>s2.size())
		{
			return false;
		}
		//两个串相等的情况下，直接看排序以后是否相等。因为字母出现频率一样，故排序以后一样
        else if(s1.size()==s2.size())
		{
			sort(s1.begin(),s1.end());
            sort(s2.begin(),s2.end());
            if(s1==s2)
            {
                return true;
            }
        }
		//如果s1太长了，就无法暴力搜索了。
		else
		{
			//建立一个map。
			vector<int> s1map(26,INT_MIN);
			//记录S1的字母出现的次数
			for(int i=0;i<s1.size();i++)
			{
				if(s1map[s1[i]-'a']==INT_MIN)
				{
					s1map[s1[i]-'a']=1;
				}
				else
				{
					s1map[s1[i]-'a']++;
				}
			}
			//采用简单匹配的方式，去S2中匹配每一个子串
			for(int i=0;i<(s2.size()-s1.size()+1);i++)
			{
				//建一个temp
				vector<int> temp(s1map);
				for(int j=0;j<s1.size();j++)
				{
					if(temp[s2[i+j]-'a']!=INT_MIN)
					{
						temp[s2[i+j]-'a']--;
					}
				}
				int endflag=1;
				auto it=temp.begin();
				while(it!=temp.end())
				{
					//如果S1比较短，可能26个字母没有出现全，此时要跳过
					if(*it==INT_MIN)
					{
						it++;
						continue;
					}
					//如果不为0，则有字母次数不一样，那么这一段一定不是S1的某个排序，所以跳出
					else if(*it!=0)
					{
						endflag=0;
						break;
					}
					else
						it++;
				}
				//如果全一样，那么找到了，返回true
				if(endflag)
				{
					return true;
				}
			}
		}
		//如果最后还是没找到
		return false;
    }
};