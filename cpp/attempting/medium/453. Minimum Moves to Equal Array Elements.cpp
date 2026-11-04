
#include<queue>
#include<numeric>
#include<algorithm>

class Solution 
{
public:
    int minMoves(vector<int>& nums) 
    {
        /*
        have one max heap, call it MH, and one var, called BIG, that trackts the biggest element so far. Let NUMBIG be the number of BIG elements existing. Lets call R the number of increments needed to make all array alements equal.

        initially:
        put all the elements into the MH, pop largest element out and set BIG.
        compare the difference between BIG and top of MH, this is how many time we can increment each element in the MH until the top of MH will equal BIG. Increment R by the difference.
        Remove the top of MH, and increment the count of NUMBIG.
        Compare the difference of the new top of MH with BIG, and increment all elements by the difference (use a global variable to add onto instead of having to individually increment by 1). At this stage we have 1 increment we didn't allocate, save this in 'CARRY'.
        */
        sort(nums.begin(), nums.end());

        // check if all elems are the same
        bool allSame = true;
        for (int i = 0; i < nums.size() - 1; ++i)
        {
            if (nums[i] != nums[i+1])
            {
                allSame = false;
                break;
            }
        }
        if (allSame)
            return 0;

        priority_queue<int*> maxHeap {};
        for (int& n : nums)
            maxHeap.push(new int(n));
        
        // while (maxHeap.size() > 0)
        // {
        //     cout << *maxHeap.top() << " - ";
        //     maxHeap.pop();
        // }

        int* big = maxHeap.top(), moves {}, missingAdds {}, bigOccurs = 1, diff {}, size = nums.size();
        int* currTop = nullptr;

        maxHeap.pop();

        while (maxHeap.size() > 0)
        {
            currTop = maxHeap.top();
            diff = *big - (*currTop + moves);
            moves += diff;

            cout << "\nbig: " << *big;
            cout << "\ntop: " << *currTop;
            cout << "\n\ttopAfterMoves: " << *currTop + moves;
            cout << "\ndiff: " << diff;
            cout << "\nmoves: " << moves;

            if (diff-1 == 0)  // currTop is equal to big
                ++bigOccurs;
            // missing adds
            if (maxHeap.size() < size - 1)
            {
                missingAdds += (size - maxHeap.size() - 1);
            }

            cout << "\nmissingAdds: " << missingAdds;
            cout << "\nbigOccurs: " << bigOccurs << endl;
            maxHeap.pop();
        }

        int additionalMoves {};
        if (missingAdds != size)
        {
            int sameElems = size - missingAdds;
            int nonSame = size - sameElems;

            int lowCM = lcm((sameElems * nonSame), size-1);
            int greatCD = gcd((sameElems * nonSame), size-1);
            additionalMoves = lowCM / (size-1);
            cout << "lcm: " << lowCM << endl;
            cout << "gcd: " << greatCD << endl;
            cout << "additional moves: " << additionalMoves << endl;
            cout << "additional moves2: " << (greatCD / (size-1)) << endl;
        }

        return moves + additionalMoves;
    }
};
