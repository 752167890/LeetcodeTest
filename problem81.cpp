/*
    题目介绍：Search in Rotated Sorted Array II 
    Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.
    (i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
    Write a function to determine if a given target is in the array.
    The array may contain duplicates.

    简而言之：在一个部分有序且有重复的数组中，怎么样最高效的寻找到一个数字是否存在。
    核心思想是采用二分查找的变形，通过这样将时间复杂度从O(n)降到O(log2(n))。
    个人一个小小的扩展猜想，不知道对不对：
    一个序列本来是有序的，只是有一些重复值在里面,任意找一个轴，分成的2段，内部各自肯定是有序的(包括重复)
    这2段任意组合在一起以后，无论从中间怎么切割，分成2个子序列，只要这个序列的长度大于等于2，肯定会有一个有序（包括重复）。
    切割的位置恰好是旋转的轴，那么2个部分就都是有序
    
*/
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        if(nums.size() == 0)//如果数组为空则返回False
            return false;
        int l = 0, r = nums.size() - 1;
        while (l <= r) {
            //获取数组的中间值，若为偶数则是中间轴靠后的一个
            int mid = (r - l) / 2 + l;
            //如果target恰好等于中间值，那么返回True
            if (target == nums[mid]) {
                return true;
            } 
            //根据猜想，中间数肯定能够划分出一个有序组出来
            //如果数组的中间值大于l所指的数，那么左边是一个有序组
            //原因如下：
            //如果左边不是有序组的话，那么矛盾的地方必然是原sorted序列旋转的轴
            //换句话说，该轴的左边有序，右边也有序
            //且某一边的数必然全部大于等于另一边，这样才能保证旋转回去还是有序的。
            //这样就产生了矛盾，因为(start,mid)不是有序，所以(mid,end)为有序。
            //设矛盾位置为a，且(start,a)和(a,end)为有序,nums[mid]>nums[start],nums[mid]<nums[a]
            //这样也就无法保证：某一边的数必然全部大于等于另一边这个定理。
            //故左边必然是个有序组。
            else if (nums[l]<nums[mid]) {
                //因为nums[l]<nums[mid]，且有序，故(l,mid)为递增
                //首先判断target与左边区间2端是否相等，右端已经判断过，故只需左端
                if (target == nums[l])
                {
                    return true;
                }
                //下一步判断target是否在左边区间中
                else if (target > nums[l] && target < nums[mid]) {
                    //那么在这个区间进一步搜索。
                    r = mid - 1;
                } 
                //target只能可能在右边或者不存在
                //然后进一步迭代，将右边的区间，分割为1个有序，1个无序。
                else 
                    l = mid + 1;
            }
            //根据上面的结论，同理可以得到，//如果数组的中间值小于r所指的数，那么右边是一个有序组
            else if(nums[r]>nums[mid])
            { 
                //故(mid,r)是递增的。
                //首先判断target与右边区间2端是否相等。
                if (target==nums[r])
                {
                    return true;
                }
                //判断是否在右边区间中，如果是则是二分查找
                else if (target > nums[mid] && target < nums[r]) {
                        l = mid + 1;
                    } 
                else
                    r= mid - 1;
              
            } 
            //当这俩相等，则无法划分
            else if (nums[l] == nums[mid])
            {
                l++;
            }
            else if (nums[r] == nums[mid])
            {
                r--;
            }
        }
        //都没找到
        return false;

    }
};