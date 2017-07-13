/*题目介绍：60. Permutation Sequence 
	The set [1,2,3,…,n] contains a total of n! unique permutations.
	By listing and labeling all of the permutations in order,
	We get the following sequence (ie, for n = 3): 
	"123"
	"132"
	"213"
	"231"
	"312"
	"321"

	Given n and k, return the kth permutation sequence.
	Note: Given n will be between 1 and 9 inclusive.
*/
//优化过的暴力算法，算出前k位所有的全排列。不能AC
class Solution {
public:
    string getPermutation(int n, int k) {
        vector<int> flag(n,0);//创建一个n个元素的数组
		vector<string> sol;
		sol= *( new vector<string>(k,"") );
		int number=0;
		string out;
		for(int i=0;i<n;i++)
		{
			flag[i]=1;
			getPermutationDFS(i,n,k,flag,out,sol,number);
			if(number==k)
			{
				break;
			}
			//回溯
			flag.assign(n,0);
			out.clear();
		}
		return sol[k-1];
    }
	void getPermutationDFS(int i,int n,int k,vector<int> &flag,string &out,vector<string> &sol,int &number)
	{
		int endflag=1;
		for(int m=0;m<n;m++)
		{
			if(flag[m]==0)
			{
				endflag=0;
			}
		}
		if(endflag)
		{
			out.push_back(i+'1');
			sol[number]=out;
			if(number==k)
			{
				return;
			}
			number++;
		}
		else
		{
			out.push_back(i+'1');
			for(int j=0;j<n;j++)
			{
				if(flag[j]==0)
				{
					flag[j]=1;
					getPermutationDFS(j,n,k,flag,out,sol,number);
					if(number==k)
					{
						return;
					}
					//回溯，特别重要
					flag[j]=0;
					out.pop_back();
				}
			}
		}
	}
};

//勉强AC的代码，先算出最后数字的第一位，之后的再用全排得到
class Solution {
public:
    string getPermutation(int n, int k) {
        vector<int> flag(n,0);//创建一个n个元素的数组
		vector<string> sol;
		int number;
		string out;
		int te;
		if(n>1)
		{
			te=(k-1)/fact(n-1);
		}
		else
		{
			te=0;
		}
		flag[te]=1;
		number=te*fact(n-1);
		getPermutationDFS(te,n,k,flag,out,sol,number);
		return sol.back();
    }
    int fact(int n)
    {
        if(n==1||n==0)
        {
            return 1; 
        }
        else
        {
            return n*fact(n-1);
        }
    }
	void getPermutationDFS(int i,int n,int k,vector<int> &flag,string &out,vector<string> &sol,int &number)
	{
		int endflag=1;
		for(int m=0;m<n;m++)
		{
			if(flag[m]==0)
			{
				endflag=0;
			}
		}
		if(endflag)
		{
			out.push_back(i+'1');
			sol.push_back(out);
			if(number==k)
			{
				return;
			}
			number++;
		}
		else
		{
			out.push_back(i+'1');
			for(int j=0;j<n;j++)
			{
				if(flag[j]==0)
				{
					flag[j]=1;
					getPermutationDFS(j,n,k,flag,out,sol,number);
					if(number==k)
					{
						return;
					}
					//回溯，特别重要
					flag[j]=0;
					out.pop_back();
				}
			}
		}
	}
};

//最优化的代码