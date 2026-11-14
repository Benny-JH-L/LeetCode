
#include<queue>
#include<cmath>

class Solution 
{
public:
    class SegmentTree
    {        
    private:
        SegmentTree *left = nullptr, *right = nullptr;
        bool seen = false;
        int lb {}, rb {};

        string getRangeStr()
        {
            string s = "[" + to_string(lb) + ", " + to_string(rb) +"] | " + "length: " + to_string(rb-lb+1);
            return s;
        }

    public:
        SegmentTree(int leftBound, int rightBound) : lb(leftBound), rb(rightBound)
        {
            cout << "["<<lb<<", " << rb <<"]" << endl;

            // create children if not a leaf node
            if (lb + 1 < rb) 
            {
                int mid = (lb + rb) / 2;
                left = new SegmentTree(lb, mid);
                right = new SegmentTree(mid, rb);
            }
        }

        ~SegmentTree()
        {
            delete left;
            delete right;
        }

        void Update(const int& leftB, const int& rightB)
        {
            // update range is outside of node range
            if (rightB < lb || leftB > rb)
                return;
            
            // node is entirely inside update range
            if (leftB <= lb && rb <= rightB)
            {
                seen = true;
                cout << "\tupdated " << getRangeStr() << endl;
                return; // return, we can compute how many children nodes are below this node when we count
            }

            // update range partially covers this node, check children
            if (left != nullptr)
            {
                left->Update(leftB, rightB);
                right->Update(leftB, rightB);
            }
        }

        void GetSeen(long long& result)
        {
            if (seen)
            {
                ++result;
                // cout << getRangeStr() << endl;
            }
            
            if (left != nullptr)
            {
                left->GetSeen(result);
                right->GetSeen(result);
            }
        }
    };

    long long countNonDecreasingSubarrays(vector<int>& nums, int k) 
    {
        /*
        Idea 2:
        start iterating in `nums` from the front. We will be building subarrays from the front.
        
        Once we build some subarray and we can't get it to be a non-decreasing, we count the number of subarrays that are non-decreasing (leaving out the newest inserted elem).
            - subtract by 1, as to not double count when we slide the window (see example below).
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

        NOTE: this method of counting the subarrays will result in double counting...
        - use a segment tree to record the range of elements seen, with that we can compute the number of subarrays that are in that range.
        */

        int myK = k, windowStart {};
        queue<int> subarray {};

        SegmentTree *segTreePtr = new SegmentTree(0, nums.size()-1);

        auto printSubarray = [&subarray]()
        {
            queue<int> copy = subarray;
            cout << "\nfront -> [";
            while (!copy.empty())
            {
                cout << copy.front() << ", ";
                copy.pop();
            }
            cout << "]" << endl;
        };

        for (int i = 0; i < nums.size(); ++i)
        {
            int newElem = nums[i];

            printSubarray();
            cout << "i: "<<i<<" | newElem: " << newElem << " | currK: " << myK << endl;

            // check non-decreasing (subarrays of size 1 are non-decreasing)
            if (subarray.size() > 0)
            {
                int& back = subarray.back();
                // cout << "\tback: " << back << endl;
                if (newElem < back) // need to increment new element to equal back
                {
                    myK -= (back - newElem);    // compute how many operations are left over
                    if (myK >= 0)
                        newElem = back;
                    // not able to make non-decreasing subarray with new element
                    else
                    {
                        cout << "update seg tree: ["<<windowStart<<", "<<(i-1)<<"]" << endl;
                        segTreePtr->Update(windowStart, i - 1);
                        
                        // // count number of non-decreasing subarrays
                        // addSubarrayCount(subarray, result);
                        // // when we shift by 1, we will double count a single subarray of size 1, re-adjust count
                        // if (subarray.size() > 1)
                        //     --result;

                        // cout << "result: " << result << endl;

                        // shift window over by 1
                        ++windowStart;
                        cout << "windowStart: " << windowStart << endl;
                        subarray.pop(); // remove front element

                        // if the windowStart is the same as `i`, we have a size 1 subarray and
                        // the element we are trying to add makes the subarray non non-decreasing, we can't shift the window on a size 1 subarray.
                        if (windowStart == i)
                        {
                            --i;
                            continue;
                        }

                        // remake the subarray, distribute operations
                        subarray = {};
                        subarray.push(nums[windowStart]);
                        myK = k;
                        
                        int subElem {};
                        bool shiftAgain = false;
                        for (int start = windowStart + 1; start < i; ++start)
                        {
                            printSubarray();

                            int& backElem = subarray.back(); // set new back element
                            subElem = nums[start];
                            cout << "subElem: " << subElem << endl;
                            if (subElem < backElem)
                            {
                                myK -= (backElem - subElem);
                                cout << "myK: " << myK << endl;
                                subElem = backElem;
                                shiftAgain = (myK < 0);
                                if (shiftAgain)     // shifting resulted in a non non-decreasing subarray, shfit again
                                {
                                    subarray = {};  // clear the subarray
                                    cout << "bruh what happen?\n";
                                    break;
                                }
                            }
                            subarray.push(subElem);
                        }
                        cout << "windowshift end" << endl;

                        if (i+1 == nums.size())
                        {
                            --i;
                            continue;
                        }
                    }
                }
            }
            subarray.push(newElem);    // add element
        }

        cout << "\n\n--end algo--";
        printSubarray();
        cout << "update seg tree: ["<<windowStart<<", "<<(nums.size()-1)<<"]" << endl;
        segTreePtr->Update(windowStart, nums.size()-1);

        long long result {};
        segTreePtr->GetSeen(result);
        return result;
    }
};
