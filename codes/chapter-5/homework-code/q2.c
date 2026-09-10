/*
 2. Write a program that opens a file (with the open() system call)
 and then calls fork() to create a new process. Can both the child
 and parent access the file descriptor returned by open()? What
 happens when they are writing to the file concurrently, i.e., at the
 same time?

 -> They both can access the file descriptor returned by open() sys call.
 -> I wasn't able to make them write to file  at the same time.
 However, when I make parent process sleep for 1, it non-deterministically changes who writes first to file.
 But mainly parent process writes first. -> Correction: it is kernel who picks to write first.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(void)
{
    printf("File will be opened, stdout will be overwritten\n");

    close(STDOUT_FILENO);
    int fd = open("./q2_common.txt", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);

    int rc = fork();
    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit (1);
    }
    else if (rc == 0) // Child processes
    {
        printf("fd = %d, child (pid:%d)\n", fd, (int) getpid());
    }
    else
    {
        sleep(1);
        printf("fd = %d, parent (pid:%d)\n", fd, (int) getpid());
    }
    return 0;
}
