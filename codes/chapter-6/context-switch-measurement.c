/* Measure cost of context switch*/

/*

 */

#define _GNU_SOURCE
#include <sched.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

// How to do:
// set_affinity for 1 cpu core usage
// Create a pipe
// Create 2 processes and make them first write - and then read
// Break the cycle at some point.
// Calculate the time somehow
// Print the time in parent process.

int main(void)
{
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(0, &mask);

    if (sched_setaffinity(0, sizeof(cpu_set_t), &mask) == -1)
    {
        fprintf(stderr, "error: sched_setaffinity\n");
        return 1;
    }
    else
    {
        const int RW_LOOP = 500000;
        int cnt = 0;
        int buffer;
        int num_to_write = 5;

        int fds1[2];
        if (pipe(fds1) == -1)
        {
            fprintf(stderr, "pipe1 give error!\n");
            exit (1);
        }

        int fds2[2];
        if (pipe(fds2) == -1)
        {
            fprintf(stderr, "pipe2 give error!\n");
            exit (1);
        }


        struct timespec begin, end;
        clock_gettime(CLOCK_REALTIME, &begin);

        pid_t p1 = fork();
        if (p1 < 0)
        {
            fprintf(stderr, "error when first fork occurs!\n");
            exit(1);
        }
        else if (p1 == 0) // First child
        {
            close(fds1[0]);
            close(fds2[1]);

            while (cnt < RW_LOOP)
            {
                write(fds1[1], &num_to_write, sizeof(int));
                read(fds2[0], &buffer, sizeof(int));
                cnt++;
            }

            close(fds1[1]);
            close(fds2[0]);
        }
        else
        {
            pid_t p2 = fork();
            if (p2 < 0)
            {
                fprintf(stderr, "error when second fork occurs!\n");
                exit(1);
            }
            else if (p2 == 0) // Second child
            {
                close(fds1[1]);
                close(fds2[0]);

                while (cnt < RW_LOOP)
                {
                    read(fds1[0], &buffer, sizeof(int));
                    write(fds2[1], &num_to_write, sizeof(int));
                    cnt++;
                }

                close(fds1[0]);
                close(fds2[1]);
            }
            else // Parent process
            {
                close(fds1[0]);
                close(fds1[1]);

                close(fds2[0]);
                close(fds2[1]);

                int stat1, stat2;

                pid_t ch1 = waitpid(p1, &stat1, 0);
                pid_t ch2 = waitpid(p2, &stat2, 0);

                printf("first child (pid = %d) ended with %d\n", p1, stat1);
                printf("second child (pid = %d) ended with %d\n", p2, stat2);

                clock_gettime(CLOCK_REALTIME, &end);
                long seconds = end.tv_sec - begin.tv_sec;
                long nanoseconds = end.tv_nsec - begin.tv_nsec;
                double elapsed = seconds + nanoseconds * 1e-9;

                printf("%d times loop has taken %.12f seconds to run\n", RW_LOOP, elapsed);
                printf("average cost of context switch is: %.12f\n", elapsed / RW_LOOP);
            }
        }
    }
    return 0;
}
