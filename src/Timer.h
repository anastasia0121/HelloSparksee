#ifndef __CLASS_TIMER__H
#define __CLASS_TIMER__H

#include <unistd.h>

namespace timer
{
    inline uint64_t rdtsc() 
    {
        uint64_t lo, hi;
        asm volatile ( "rdtsc\n" : "=a" (lo), "=d" (hi) );
        return ((uint64_t)hi << 32) | lo;
    }

    uint64_t init_rate()
    {
        uint64_t tsc = rdtsc();
        sleep(1);
        uint64_t rate = rdtsc() - tsc;

        return rate;
    }

    double to_msec(uint64_t tsc, uint64_t rate)
    {
        return static_cast<double>(tsc) / (rate / 1000);
    }
}
#endif // __CLASS_TIMER__H
