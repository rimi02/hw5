#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, size_t day, size_t shift, size_t worker, size_t shiftCount, size_t workerCount);




// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    return scheduleHelper(avail, dailyNeed, maxShifts, sched, 0, 0, 0, 0, 0);






}

bool scheduleHelper(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, size_t day, size_t shift, size_t worker, size_t shiftCount, size_t workerCount){
    if(day == avail.size()){
        return true;
    }
    if(shift == dailyNeed){
        return scheduleHelper(avail, dailyNeed, maxShifts, sched, day+1, 0, 0, 0, 0);
    }
    if(worker == avail[0].size()){
        return false;
    }
    if(avail[day][worker] == true){
        if(shiftCount < maxShifts){
            if(workerCount < dailyNeed){
                sched[day].push_back(worker);
                if(scheduleHelper(avail, dailyNeed, maxShifts, sched, day, shift+1, 0, shiftCount+1, workerCount+1)){
                    return true;
                }
                sched[day].pop_back();
            }
        }
    }
    return scheduleHelper(avail, dailyNeed, maxShifts, sched, day, shift, worker+1, shiftCount, workerCount);
}