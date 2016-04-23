#include <iostream> 
#include <unistd.h>

bool unit_test();
void perf_test();

int main(int argc, char *argv[]) 
{
//    if (!unit_test()) return -1;   
    perf_test();

    return 0;
}
