class Solution {
public:
    bool search(vector<int>& nums, int target) {
        if(nums.size() == 0)
            return false;
        int l = 0, r = nums.size() - 1;
        while (l < r) {
            int mid = (r - l) / 2 + l;
            if (target == nums[mid]) {
                return true;
            } 
            else if (nums[l] <= nums[mid]) {
                if (nums[l] == nums[mid]) ++l;
                else if (target >= nums[l] && target < nums[mid]) {
                    r = mid - 1;
                } else l = mid + 1;
            } 
            else if (nums[mid] <= nums[r]) {
                if (nums[mid] == nums[r]) --r;
                else if (target > nums[mid] && target <= nums[r]) {
                    l = mid + 1;
                } else r = mid - 1;
            } 
        }
        return nums[l] == target;

    }
};