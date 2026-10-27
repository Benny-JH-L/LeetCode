
#include<cmath>
#include<climits>
#include<string>

class Solution 
{
public:
    int countDaysTogether(string arriveAlice, string leaveAlice, string arriveBob, string leaveBob) 
    {
        auto getMonth = [](string& str) -> int
        {
            return atoi(str.substr(0, 2).c_str());
        };

        auto getDay = [](string& str) -> int
        {
            return atoi(str.substr(3, 2).c_str());
        };

        // find who arrived late
        int aliceM = getMonth(arriveAlice);
        int bobM = getMonth(arriveBob);
        int latestArriveM = aliceM, latestArriveD = getDay(arriveAlice);    // set to alice for now

        if (bobM > aliceM)
        {
            latestArriveM = bobM;
            latestArriveD = getDay(arriveBob);
        }
        // tie breaker, by day
        else if (bobM == aliceM)
        {
            int bobD = getDay(arriveBob);
            if (bobD > latestArriveD)
            {
                latestArriveM = bobM;
                latestArriveD = bobD;
            }
        }
        
        // find who left early
        aliceM = getMonth(leaveAlice);
        bobM = getMonth(leaveBob);
        int earlyLeaveM = aliceM, earlyLeaveD = getDay(leaveAlice); // set to alice for now

        if (bobM < aliceM)
        {
            earlyLeaveM = bobM;
            earlyLeaveD = getDay(leaveBob);
        }
        // tie breaker, by day
        else if (bobM == aliceM)
        {
            int bobD = getDay(leaveBob);
            if (bobD < earlyLeaveD)
            {
                earlyLeaveM = bobM;
                earlyLeaveD = bobD;
            }
        }

        // cout << "latestArriveMonth: " << latestArriveM << endl;
        // cout << "latestArriveDay: " << latestArriveD << endl;
        // cout << "earlyLeaveM: " << earlyLeaveM << endl;
        // cout << "earlyLeaveD: " << earlyLeaveD << endl;

        // get days from months
        int totalDays {};
        vector<int> daysInMonth = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};  // off set array by 1; so it is 1-indexed for getting months
        for (int startM = latestArriveM + 1; startM < earlyLeaveM; ++startM)
        {
            // cout << "added month<"<<startM<<">: "<<daysInMonth[startM]<<"days"<< endl;
            totalDays += daysInMonth[startM];
        }
        
        // cout << "total days so far: " << totalDays << endl;
        if (latestArriveM == earlyLeaveM && latestArriveD <= earlyLeaveD)
        {
            totalDays += (abs(latestArriveD - earlyLeaveD) + 1);
        }
        // account for days for periphery months
        else if (latestArriveM < earlyLeaveM)
        {
            // cout << "adding days: " << (daysInMonth[latestArriveM] - latestArriveD + 1) << endl;
            totalDays += daysInMonth[latestArriveM] - latestArriveD + 1;

            // cout << "adding days: " <<earlyLeaveD << endl;
            totalDays += earlyLeaveD;
        }
        
        return totalDays;
    }
};
