#ifndef TIMER_H
#define TIMER_H

#include <time.h>

/*
 * One snapshot of the three clocks used in the laboratory:
 *   wall       - time(NULL), whole seconds, used with difftime()
 *   cpu        - clock(), process CPU time in clock ticks
 *   highres    - gettimeofday()/QueryPerformanceCounter(), sub-second wall time
 */
typedef struct {
    time_t wall;
    clock_t cpu;
    double highres;
} TimerSnapshot;

void timer_start(TimerSnapshot *snapshot);
void timer_stop(const TimerSnapshot *start);

#endif /* TIMER_H */
