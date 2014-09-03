#include "TriSingleton.h"

TriThreading::TrackerList* pTrackerList=0;


void TriThreading::Private::AtExitFn()
{
    assert(pTrackerList!=0 && !pTrackerList->empty());
    
    // Pick the element at the top of the stack
    LifetimeTracker* pTop = pTrackerList->back();
    
    // Remove that object off the stack _before_ deleting pTop
    pTrackerList->pop_back();
    
    // Destroy the element
    delete pTop;
    
    // Destroy stack when it's empty _after_ deleting pTop
    if(pTrackerList->empty())
    {
        delete pTrackerList;
        pTrackerList = 0;
    }
}

