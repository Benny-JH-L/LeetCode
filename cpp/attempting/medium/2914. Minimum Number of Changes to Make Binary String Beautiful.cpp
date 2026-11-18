class Solution 
{
public:
    int minChanges(string s) 
    {
        /*
        Idea:
        Divide and conquer.
        Convert `s` into a vector<bool>, where 0 is false and 1 is true.
        Split the array in half (ensure it's even), keep splitting the array until you get an array of size 2.
        Check if the subarray evaluates to 'true' if not, change it such that it is (make bits to 1). 
        If the children subarrays are `beautiful` then the parent must also be beautiful.
        
        Idea 2:
        Start at the begining of `s` and check two characters at a time and make them beautiful. 
        We can guarantee the characters we checked can make beautiful subarrays.
        */

        int result {};    

        for (auto it = s.begin(); it + 1 < s.end(); it += 2)
        {
            if (*it != *(it + 1))   // One char is a '1' and other is a '0'.
                ++result;           // need to change one number to make this substring beautiful.
        }
        
        return result;
    }
};
