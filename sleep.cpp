// sleep.cpp
#include <stdio.h>
#include <sys/timeb.h>
#include <sys/utime.h>


/// <summary>
/// count milisecond
/// </summary>
/// <returns></returns>
int getMilliCount() {
    timeb tb;
    ftime(&tb);
    int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
    return nCount;
}

/// <summary>
/// sleep the process in "sleeptime" (ms)
/// </summary>
/// <param name="sleeptime"></param>
void sleep(int sleeptime)
{
    int count = 0;
    int beginsleep = getMilliCount();
    while (getMilliCount() - beginsleep < sleeptime)
    {
        count++;
    }
}