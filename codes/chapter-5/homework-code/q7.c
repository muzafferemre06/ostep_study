/*
    Write a program that creates a child process, and then in the child
    closes standard output (STDOUT_FILENO). What happens if the child
    calls printf() to print some output after closing the descriptor?

    A: It won't be able print anything because there is no way to direct the output.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    pid_t rc = fork();
    int stat;

    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit (1);
    }
    else if (rc == 0) // Child processes
    {
        close(STDOUT_FILENO);
        printf("(1) child pid: %d",(int) getpid());
    }
    else
    {
        int rc_wait = wait(NULL);
        if (rc_wait > 0)
            printf("child finished its task properly! it won't print anything\n");
        else
            printf("child couldn't finished its task properly!\n");
    }

    return 0;
}
