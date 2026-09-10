/*
 Write another program using fork(). The child process should
 print “hello”; the parent process should print “goodbye”. You should
 try to ensure that the child process always prints first; can you do
 this without calling wait() in the parent?

 -> For now, it doesn't seem possible. I could have use some signal -such as opening a file in child proc. after print-
 for parent process to indicate hello is printed. But don't know whether this is the best approach.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

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
        printf("hello!\n");
        check = 1;
    }
    else
    {
        printf("goodbye!\n");
    }

    return 0;
}
