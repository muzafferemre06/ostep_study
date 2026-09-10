/*
    Write a slight modification of the previous program, this time us-
    ing waitpid() instead of wait(). When would waitpid() be
    useful?

    A: When we create more than one child in parent proc. this will be
    useful for looking out for every child proc.
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
        printf("child pid: %d\n",(int) getpid());
    }
    else
    {
        pid_t child_pid = waitpid(rc, &stat, 0);
        printf("(parent pid: %d) child (pid: %d) ended with = %d\n",
            (int) getpid(), child_pid, stat);
    }

    return 0;
}
