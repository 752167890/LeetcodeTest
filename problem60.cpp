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
	个人思路：
		本题实际上是求1-9位自然数，所组成的全排列中，按照从小到大的规律的第k个数。
		求全排列的方法，采用了递归回溯的思想（琢磨了好久，自己的功力还是不行）。
		方法：1.纯暴力解法，直接算出所有的全排列，然后返回第k个数。这种方法会超时。
			  2.优化过的暴力算法，算出前k个数，然后返回最后一个数，并且优化了内存分配。仍然会超时，不过已经很接近AC。
			  3.进一步优化的暴力算法，不再需要求出全部的全排列，首先根据推导的公式：
			  		te=(k-1)/(n-1)!   (n>1)   此处的te为flag数组的下表，实际表示的数字为te+'1'。
			  		te=0              (n=1)
			  	可以直接得到所求的第一位的数据，然后对剩下的n-1个数字求全排列。
			  	知道求到第k个，所需要的次数为k-te*(n-1)!。通过这样优化可以AC，但是效率不高。
			  4.最佳方法，通过对k进行运算，可以直接得到每一位的数据（还没有推出公式，暂时没有实现）。 
*/
//优化过的暴力算法，算出前k位所有的全排列。不能AC
class Solution {
public:
    string getPermutation(int n, int k) {
        vector<int> flag(n,0);//创建一个n个元素的数组
        //用于存放最终结果
		vector<string> sol;
		//优化内存分配，预先开辟k个空间
		sol=*(new vector<string>(k,""));
		//计数器，用于跳出
		int number=0;
		string out;
		for(int i=0;i<n;i++)
		{
			//如果某一位使用了，那么置1
			flag[i]=1;
			//从第一位为i开始，求全排列
			getPermutationDFS(i,n,k,flag,out,sol,number);
			//算完了，跳出
			if(number==k)
			{
				break;
			}
			//算完一次以i为首位的以后，要进行重置，以进行下一次。这也就是回溯的过程
			flag.assign(n,0);
			out.clear();
		}
		//最终返回第k个元素
		return sol[k-1];
    }
	void getPermutationDFS(int i,int n,int k,vector<int> &flag,string &out,vector<string> &sol,int &number)
	{
		//结束标志
		int endflag=1;
		for(int m=0;m<n;m++)
		{
			//如果有元素没有访问，那么不结束
			if(flag[m]==0)
			{
				endflag=0;
			}
		}
		if(endflag)
		{
			//如果只剩最后一个元素，那么直接插入
			out.push_back(i+'1');
			sol[number]=out;
			if(number==k)
			{
				return;
			}
			number++;
		}
		//如果不是最后一位
		else
		{
			out.push_back(i+'1');
			//找到下一个没访问的元素
			for(int j=0;j<n;j++)
			{
				if(flag[j]==0)
				{
					flag[j]=1;
					//递归
					getPermutationDFS(j,n,k,flag,out,sol,number);
					if(number==k)
					{
						return;
					}
					//回溯，特别重要，一层层的还原
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