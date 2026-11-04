#include "timer.h"

#include <stdio.h>

#ifdef _WIN32
#include <windows.h>

static double highres_seconds(void)
{
    LARGE_INTEGER counter;
    LARGE_INTEGER frequency;

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&counter);
    return (double)counter.QuadPart / (double)frequency.QuadPart;
}
#else
#include <sys/time.h>

static double highres_seconds(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;
}
#endif

void timer_start(TimerSnapshot *snapshot)
{
    snapshot->wall = time(NULL);
    snapshot->cpu = clock();
    snapshot->highres = highres_seconds();
}

void timer_stop(const TimerSnapshot *start)
{
    TimerSnapshot end;

    end.wall = time(NULL);
    end.cpu = clock();
    end.highres = highres_seconds();

    printf("time/difftime:        %.0f s\n",
           difftime(end.wall, start->wall));
    printf("clock/CLOCKS_PER_SEC: %.6f s\n",
           (double)(end.cpu - start->cpu) / (double)CLOCKS_PER_SEC);
    printf("high-resolution:      %.6f s\n",
           end.highres - start->highres);
}
