class Solution 
{
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) 
    {
        /*
        Idea:
        Start with an empty subarray.
        Add one element to it and increase the count by 1 (single element subarrays are always non-decreasing).
        Adding the next element, (again increase count by 1).
            now we check the subarray of size 2, 
                - if it is not non-decrasing, compute if it is possible to make it non-decreasing. 
                    - If it is not possible we can skip making the subarrays with this prefix and start with the next ones.
                    - If it is possible, we can continue with this subarray but also keep the changes so we do not repeat work.
                - otherwise keep checking.
        Addint additional element
            check subarray of size 3, 
                - we know size 2 subarray is valid, so we need to check this element with the previous element. (we have a guarantee that elements from 0-n-1 in the subarray are non-decreasing but adding `n`th element we need to check with n-1 element)
        
        Ex.
        nums = [6,3,1,2,4,4], k = 7
        
        sub = [6]   // was empty but we'll start with 2.
        subStart = 0    // index in nums that this sub array is starting from
        subEnd = 0      // index in nums that this sub array is ending at
        count = 1       // count of subarrays that are non-decreasing that we've found

        sub = [6,3] 
        subStart = 0
        subEnd = 1
            | converted to sub = [6,6] k = 4 (used 3 operations) to make it non-decreasing
        count = 2

        sub = [6,6,1]   | [6,3,1] (original)
        subStart = 0
        subEnd = 2
            | with 4 k left we cannot make this into a non-decreasing so check next sub arrays
        count = 2

        // reset sub to [] and ++subStart, and set subEnd to subStart
        sub = [3]
        subStart = 1
        subEnd = 1
        count = 3

        sub = [3,1]
        subStart = 1
        subEnd = 2
            | converted sub = [3,3] k = 5
        count = 4

        sub = [3,1,2] | [3,3,2]
        subStart = 1
        subEnd = 3
            | converted sub = [3,3,3], k = 4
        count = 5

        (only if sub.size() - 1 > 2) Now that we've found a case where we can't make a non-decreasing, we extrapolate from subStart to subEnd - 1, other sub arrays that are non-decreasing

        once we get to the end, or case where we cannot get a non-decreasing, the subarray from subStart to subEnd is non-decreasing. Based on the size and the start and end
        we can also compute other subarrays inside of it that are also valid (so we don't have to recompute work)


        Idea 2:
        start iterating in `nums` from the front. We will be building subarrays from the front.
        
        Once we build some subarray and we can't get it to be a non-decreasing, we count the number of subarrays that are non-decreasing (leaving out the newest inserted elem).
        Then we can "slide" the window over to the right by 1 and repeat; we can do this because we've enountered a case where we can't build a non-decreasing array anymore. 
            - We can slide because of the guarantee that everything to the left of the newly added elem will be 
            non-decreasing and we can build a new subarray from our old work (eliminates repeated work). (see example below). 
        reset our operations `k` and reset the elements just before the newly added element (see example below). 
            - Note if the new `anchor` (ie left most element in the subarray) is the same as the old one, we can skip this step.
        Reallocate operations to the resetted elements to get the `k` we can operate with in this sub array. (see example below). 
        
        - ex. if we have the subarray that tracks our operations, [10,10,10,1] k = 2 (no operations included looks like [10,5,2,1]), where element `1` was newly added,
            we compute the number of non-decreasing sub arrays from [10,5,2], which will be 6 sub arrays that are non-decreasing.
            Shift the window over to the right by 1: [10,10,1] ([5,2,1]), and get the non-decreasing sub array count is 2, -> we get [10] and [10,10] we don't include the right most [10] or else we will count it twice due to us shifting right.
            then reset the elements at index 0 and 1 in [10,10,1] with it's `nums` equivalent (`nums[0]`, `nums[1]`), 
            resulting in [5,2,1] k = 10.
            Reallocate operations to the resetted elements `2` with `5` as our new `anchor`, [5,5,1] k = 7 (used 3 operations to increase 2 to 5)

            Then we can repeat the algorithm with [5,5,1] k = 7.
        
        ex. nums = [6,3,1,2,4,4], k = 7 | output 17
        
        sub = []
        1) add, sub = [6] k = 7
        2) add, sub = [6,3] k = 7
            increment 3 to 6,
            sub = [6,6] k = 4
        3) add, sub = [6,6,1] k = 4
            sub = [6,6,5] k = 0, not non-decreasing. non-decreasing count = 2 (based on [6,6] we get [6] and [6,6] again we don't include the right most [6] or we will count it twice bc the shift will count it for us)
            shift right and reset elements and k, reallocate based on new anchor
            sub = [3,1] k = 7 | anchor is 3 but when we shifted we got only size 2 array, so we don't reallocate.
        4) add, sub = [3,1] k = 7
            sub = [3,3] k = 5
        5) add, sub = [3,3,2] k = 5
            sub = [3,3,3] k = 4
        6) add, sub = [3,3,3,4] k = 4
        7) add, sub = [3,3,3,4,4] k = 4
        8) reached the end of the array, compute non-decreasing count from sub = [3,3,3,4,4], we get 15 here, but note that we double counted one of the elements
        non-decreasing count = 17
        */


    }
};
