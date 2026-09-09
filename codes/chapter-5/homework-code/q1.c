/*
Write a program that calls fork(). Before calling fork(), have the
main process access a variable (e.g., x) and set its value to some-
thing (e.g., 100). What value is the variable in the child process?
What happens to the variable when both the child and parent change
the value of x?

Answer: 
""""""
    hello (pid:53122)
    the value of x: 120 in (pid:53122)
    parent of 53123 (pid:53122)
    the value of x in parent: 115
    child (pid:53123)
    the value of x in child: 125
""""""

They initially have the same value, but after the fork and applied operations,
they have different values.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    printf("hello (pid:%d)\n", (int) getpid());

    int x = 120;
    printf("the value of x: %d in (pid:%d)\n", x, (int) getpid());

    int rc = fork();
    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("child (pid:%d)\n", (int) getpid());

        x += 5;
        printf("the value of x in child: %d\n", x);
    } else {
        // parent goes down this path (main)
        printf("parent of %d (pid:%d)\n", rc, (int) getpid());

        x-= 5;
        printf("the value of x in parent: %d\n", x);
    }
    return 0;
    }   