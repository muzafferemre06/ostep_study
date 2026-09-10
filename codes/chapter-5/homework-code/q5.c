/*
    Now write a program that uses wait() to wait for the child process
    to finish in the parent. What does wait() return? What happens if
    you use wait() in the child?

    Answer 1: in parent, it returns PID of child proc.
    Answer 2: wait returned -1 when run in child. This means it gave error

*/

// Q2:

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
    else if (rc == 0) // Child processes
    {
        printf("child pid: %d\n",(int) getpid());

        int return_val = wait(NULL);
        printf("what happened = %d\n", return_val);
    }
    else
    {
        printf("parent pid: %d \n",(int) getpid());
    }

    return 0;
}

/* Q1:
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
        else if (rc == 0) // Child processes
        {
            printf("child pid: %d\n",(int) getpid());
        }
        else
        {
            int rc_wait = wait(NULL);
            printf("(parent pid: %d) child pid = %d\n",(int) getpid(), rc_wait);
        }

        return 0;
    }
 */
