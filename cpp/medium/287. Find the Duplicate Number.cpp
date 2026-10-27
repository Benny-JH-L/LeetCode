
class Solution 
{
public:
    int findDuplicate(vector<int>& nums) 
    {
        /*
        we can use two pointers; 1 fast, 1 slow, to traverse the array to find the duplicate value.
        */
        int size = nums.size();
        for (int slow = nums[0], fast = nums[1];true;) // there is a guarantee that there is a duplicate number; we can terminate in the body
        {
            cout << "slow: " << slow << endl;
            cout << "fast: " << fast << endl<<endl;
            if (fast != slow && nums[slow] == nums[fast])
                return nums[slow];
            
            slow = nums[slow];
            fast = nums[fast+1];
        }
    }
};
