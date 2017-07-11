/*题目介绍：Smallest Range 
	You have k lists of sorted integers in ascending order. Find the smallest range that includes at least one number from each of the k lists. 
	We define the range [a,b] is smaller than range [c,d] if b-a < d-c or a < c if b-a == d-c.
	Input:[[4,10,15,24,26], [0,9,12,20], [5,18,22,30]]
	Output: [20,24]
	Explanation: 
	List 1: [4, 10, 15, 24,26], 24 is in range [20,24].
	List 2: [0, 9, 12, 20], 20 is in range [20,24].
	List 3: [5, 18, 22, 30], 22 is in range [20,24].

	Note:
	The given list may contain duplicates, so ascending order means >= here.
	1 <= k <= 3500
	-10^5 <= value of elements <= 10^5.
	个人思路：
		1.要找到最小的range，那么我们要知道最大值，并且要知道最小值。
		还要满足限制条件：
			(1)须包含每个list中的元素。
			(2)当range相等时，数越小越好。
		对于(1)采用的办法是，我们建立一个数组ptr，大小为k，初始化的时候存入所有list的首元素。
		这样我们更新这个数组的时候，如果我们替换掉某个元素，那么我们必须要从被替换的元素所在的list中替换。这样使得ptr总
		保持包含每个list中的1个元素的条件。
		对于(2)我们要尽可能的寻找最小的数，故建立最小堆。
		2.那么如何寻找最小值和最大值呢？
		对于最小值：这里采用建立最小堆的过程来寻找每次的最小值，采用了优先级队列priority_queue来实现最小堆。
		这样每次堆的顶部元素都是当前的最小值。这样可以方便得到最小值。
		对于最大值：在建堆过程中，通过遍历得到一个最大值（所有堆中元素最大），这样每次更新的时候，只需要与插入元素相比
		就可以得到当前最大值。
		3.为了编写程序方便，我创建了2个新的结构体，用来保存一些辅助信息。
		4.每次更新元素时:插入被移除元素（当前最小值）的list中的下一位置的元素
		5.当插入时，list溢出，那么循环结束，此时的minrange保存了最终的结果。这是因为所有的list中都是升序，我们又是不停的追逐
		最小值，所以当list结束时，尽管其他的list可能还没有遍历完，但是那些数肯定大，没有意义，无序再去遍历了。
*/
class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
    	//定义一个节点的结构体，用来表示存放在堆中的数据类型
		struct Node{
			int val;//存储节点的值
			int node_index;//存储节点在List中的索引
			int list_index;//存储节点的List的序号
			//构造函数，进行节点初始化
			Node(int a=0,int b=0,int c=0)
			{
				val=a;
				node_index=b;
				list_index=c;
			}
			//重载<符号，使得priority_queue变成一个最小堆
			bool operator<(const Node b) const
			{
				return this->val>b.val;
			}
		};
		//定义最小range的结构体，存放当前的结果信息
		struct Minrange{
			int max;//当前最大值
			int min;//当前最小值
			int range;//当前的range
			Minrange()
			{
				max=0;
				min=0;
				range=INT_MAX;
			}
		};
		priority_queue<Node> ptr;//定义一个最小堆
		struct Node now_min(INT_MAX,0,0);//存放当前的最小值
		struct Node now_max(INT_MIN,0,0);//存放当前的最大值
		struct Minrange minrange;//用来存放当前所得到的最小range
		vector<int> sol;//存放答案
		int k;//list的个数
		k=nums.size();
		//如果为空,那么将每个List的首元素插入优先级队列ptr中
		do
		{
			//对最小堆进行初始化，插入元素
			if(ptr.empty())
			{
				for(int i=0;i<k;i++)
				{
					//建堆
					ptr.push(Node(nums[i][0],0,i));
					//在插入的过程中，得到当前的最大值（因为ptr为最小堆，每次只能得到最小值）
					if(nums[i][0]>now_max.val)
					{
						//记录最大值的一些信息
						now_max.val=nums[i][0];
						now_max.node_index=0;
						now_max.list_index=i;
					}
				}
			}
			//如果不为空
			else
			{
				int list_size;//用来存放每次循环得到的最小值所在的list的大小。
				//取出当前的最小值
				now_min=ptr.top();
				//对range进行判断，来决定是否更新minrange
				if((now_max.val-now_min.val)<minrange.range)
				{
					minrange.range=now_max.val-now_min.val;
					minrange.max=now_max.val;
					minrange.min=now_min.val;
				}
				list_size=nums[now_min.list_index].size();
				ptr.pop();//将最小的元素pop出去，下一步要插入新元素
				//如果某一个list到头了，那么循环结束，返回最终结果
				if(now_min.node_index==list_size-1)
				{
					break;
				}
				else
				{
					//添加新元素到最小堆
					ptr.push(Node(nums[now_min.list_index][now_min.node_index+1],now_min.node_index+1,now_min.list_index));
					//判断该元素是否比当前最大元素大，如果大则修改当前所记录的最大值
					if(nums[now_min.list_index][now_min.node_index+1]>now_max.val)
					{
						now_max.val=nums[now_min.list_index][now_min.node_index+1];
						now_max.list_index=now_min.list_index;
						now_max.node_index=now_min.node_index+1;
					}
				}
			}
		}while(1);
		sol.push_back(minrange.min);
		sol.push_back(minrange.max);
		return sol;
    }
};