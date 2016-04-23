#include <iostream> 
#include <array>
#include <unistd.h>
#include <iomanip> 
#include <algorithm>

void switch_keyboard_layout(const std::wstring &src, std::wstring &dst);
void switch_keyboard_layout1(const std::wstring &src, std::wstring &dst);

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

uint64_t to_usec(uint64_t tsc, uint64_t rate)
{
    return tsc / (rate / 1000000);
}

template <typename T, size_t N>
void print_statistics(std::array<T,N> & percentile_map, std::array<T,N> & percentile_switch)
{
    int count = N;

    std::sort(percentile_map.begin(), percentile_map.end(), std::less<uint64_t>());
    std::sort(percentile_switch.begin(), percentile_switch.end(), std::less<uint64_t>());

    std::cout << std::setw(16) << "|" 
              << std::setw(20) << " 50% |"
              << std::setw(21) << " 70% |"
              << std::setw(20) << " 90% |"
              << std::setw(20) << " 95% |"
              << std::setw(20) << " 99% |" 
              << std::endl
              << "switch-case:   |" 
              << std::setw(15) << percentile_switch[50*100/count - 1]  <<  " us |" 
              << std::setw(16) << percentile_switch[70*100/count - 1]  <<  " us |" 
              << std::setw(15) << percentile_switch[90*100/count - 1]  <<  " us |" 
              << std::setw(15) << percentile_switch[95*100/count - 1]  <<  " us |" 
              << std::setw(15) << percentile_switch[100*100/count - 1]  <<  " us |" 
              << std::endl
              << "unordered_map: |" 
              << std::setw(15) << percentile_map[50*100/count - 1]  <<  " us |" 
              << std::setw(16) << percentile_map[70*100/count - 1]  <<  " us |" 
              << std::setw(15) << percentile_map[90*100/count - 1]  <<  " us |" 
              << std::setw(15) << percentile_map[95*100/count - 1]  <<  " us |" 
              << std::setw(15) << percentile_map[100*100/count - 1]  <<  " us |" << std::endl;
}

void perf_test()
{
    const int count = 100;
    std::array<uint64_t, count> percentile_map;
    std::array<uint64_t, count> percentile_switch;

    std::wstring src, dst;
    src = L"qertyuiop[]asdfghjkl;'zxcvbnm,.1234567890йцукенгшщзхъфывапролджэячсмитьбю.";

    uint64_t rate = init_rate(); 

    for (int i = 0; i < count; ++i)
    {
        volatile uint64_t t3 = rdtsc();
        for (int i = 0; i < 1000; ++i)
            switch_keyboard_layout1(src, dst);
        volatile uint64_t t4 = rdtsc();
        percentile_map[i] = t4 - t3;

        volatile uint64_t t1 = rdtsc();
        for (int i = 0; i < 1000; ++i)
            switch_keyboard_layout(src, dst);
        volatile uint64_t t2 = rdtsc();
        percentile_switch[i] = t2 - t1;
    }


    print_statistics(percentile_map, percentile_switch);
}
