/*
    Write a program that calls fork() and then calls some form of
    exec() to run the program /bin/ls. See if you can try all of the
    variants of exec(), including (on Linux) execl(), execle(),
    execlp(), execv(), execvp(), and execvpe(). Why do
    you think there are so many variants of the same basic call?

    4-) execv() = this uses vector
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
    else if (rc == 0) // Child processes
    {
        char* myargs[2];
        myargs[0] = "/bin/ls";
        myargs[1] = NULL;

        execv(myargs[0], myargs); // This takes absolute path, and then arguments.

        // Only works if execl returned with an error! Otherwise it is wiped out.
        printf("There was an error when calling execl!\n");
    }
    else
    {
        int rc_wait = wait(NULL);
        printf("rc_wait = %d\n", rc_wait);

        if (rc_wait > 0)
            printf("child finished its task properly!\n");
        else
            printf("child couldn't finished its task properly!\n");
    }

    return 0;
}
