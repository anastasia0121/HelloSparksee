#include <iostream> 
#include <unistd.h>

bool unit_test();
void perf_test(const int it);

int main(int argc, char *argv[]) 
{
//    if (!unit_test()) return -1;   
    perf_test(10000);

    return 0;
}
