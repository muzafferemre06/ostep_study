/*
    Write a program that creates two children, and connects the stan-
    dard output of one to the standard input of the other, using the
    pipe() system call.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    int rc = fork();

    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit (1);
    }
    else if (rc == 0) // First child processes
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
