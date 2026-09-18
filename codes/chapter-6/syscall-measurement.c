/*
 * Average cost of one syscall:

 muzaffer@muzaffer-asus-tuf-gaming-a15-fa507nv-fa507nv:~/Desktop/OSTEP/codes/chapter-6$ ./sys
 5000 times loop has taken 0.002297 seconds to run
 Average time to run read sys call: 0.00000

 muzaffer@muzaffer-asus-tuf-gaming-a15-fa507nv-fa507nv:~/Desktop/OSTEP/codes/chapter-6$ gcc syscall-measurement.c -o sys
 muzaffer@muzaffer-asus-tuf-gaming-a15-fa507nv-fa507nv:~/Desktop/OSTEP/codes/chapter-6$ ./sys
 500000 times loop has taken 0.213856000000 seconds to run
 Average time to run read sys call: 0.000000427712

 muzaffer@muzaffer-asus-tuf-gaming-a15-fa507nv-fa507nv:~/Desktop/OSTEP/codes/chapter-6$ gcc syscall-measurement.c -o sys
 muzaffer@muzaffer-asus-tuf-gaming-a15-fa507nv-fa507nv:~/Desktop/OSTEP/codes/chapter-6$ ./sys
 5000000 times loop has taken 2.144221000000 seconds to run
 Average time to run read sys call: 0.000000428844

 ---------------------------------------------------------

 muzaffer@muzaffer-asus-tuf-gaming-a15-fa507nv-fa507nv:~/Desktop/OSTEP/codes/chapter-6$ ./sys
 [clock()]         5000000 times loop has taken 2.139420000000 seconds to run
 [clock_gettime()] 5000000 times loop has taken 2.139718298000 seconds to run
 [clock()]         Average time to run read sys call: 0.000000427884
 [clock_gettime()] Average time to run read sys call: 0.000000427944

 It is actually quite fast.
 */

#include <bits/time.h>
#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>

void syscall_read(void)
{
    char buffer;
    read(STDIN_FILENO, &buffer, 0);
}

int main (void)
{
    const int LOOP_COUNT = 5000000;
    int time = clock();
    struct timespec begin, end;
    clock_gettime(CLOCK_REALTIME, &begin);

    for (int i = 0; i < LOOP_COUNT; i++)
        syscall_read();

    time = clock() - time;
    double time_taken = ((double) time) / CLOCKS_PER_SEC;

    clock_gettime(CLOCK_REALTIME, &end);
    long seconds = end.tv_sec - begin.tv_sec;
    long nanoseconds = end.tv_nsec - begin.tv_nsec;
    double time_taken_v2 = seconds + nanoseconds * 1e-9;

    printf("[clock()]         %d times loop has taken %.12f seconds to run\n",
        LOOP_COUNT, time_taken);

    printf("[clock_gettime()] %d times loop has taken %.12f seconds to run\n",
        LOOP_COUNT, time_taken_v2);


    double avg1 = (double) time_taken / LOOP_COUNT;
    double avg2 = time_taken_v2 / LOOP_COUNT;

    printf("[clock()]         Average time to run read sys call: %.12f\n", avg1);
    printf("[clock_gettime()] Average time to run read sys call: %.12f\n", avg2);

    return 0;
}
