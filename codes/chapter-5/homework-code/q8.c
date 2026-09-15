/*
    Write a program that creates two children, and connects the stan-
    dard output of one to the standard input of the other, using the
    pipe() system call.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(void)
{
    const int str_size = 20;

    int fds[2];
    if (pipe(fds) == -1)
    {
        fprintf(stderr, "pipe failed!\n");
        exit (1);
    }

    printf("fds[0] = %d, fds[1] = %d\n", fds[0], fds[1]);

    int rc = fork();
    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit (1);
    }
    else if (rc == 0) // First child processes
    {
        close(fds[0]); // Read end closed.

        printf("(1) child pid: %d\n",(int) getpid());

        dup2(fds[1], STDOUT_FILENO);
        char* str = "(1)-hello!";
        printf("%s", str);

        close(fds[1]);
    }
    else
    {
        int rc2 = fork();
        if (rc2 < 0)
        {
            fprintf(stderr, "second fork failed!\n");
        }
        else if (rc2 == 0) // Second child process
        {
            close(fds[1]); // Write end closed.

            printf("(2) child pid: %d\n",(int) getpid());

            dup2(fds[0], STDIN_FILENO);

            char str[100] = " ";
            scanf(" %s", str);
            printf("(2) pipe come with '%s' via scanf \n", str);

            close(fds[0]);
        }
        else // Parent process
        {
                close(fds[0]);
                close(fds[1]);

                int stat1, stat2;

                pid_t ch1 = waitpid(rc, &stat1, 0);
                pid_t ch2 = waitpid(rc2, &stat2, 0);

                printf("first child (pid = %d) ended with %d\n", rc, stat1);
                printf("second child (pid = %d) ended with %d\n", rc2, stat2);
        }
    }

    return 0;
}

/*
int main(void)
{

    int fds[2];
    if (pipe(fds) == -1)
    {
        fprintf(stderr, "pipe failed!\n");
        exit (1);
    }

    printf("fds[0] = %d, fds[1] = %d\n", fds[0], fds[1]);

    int rc = fork();
    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit (1);
    }
    else if (rc == 0) // First child processes
    {
        close(fds[0]); // Read end closed.

        printf("(1) child pid: %d\n",(int) getpid());
        close(STDOUT_FILENO); // Now stdout looks for fds[1] > '4'

        char* str = "(1) hello!";
        printf("%s", str);
        write(fds[1], str, strlen(str) + 1);
        close(fds[1]);
    }
    else
    {
        int rc2 = fork();
// FPRİNTF çalışabilir!
        if (rc2 < 0)
        {
            fprintf(stderr, "second fork failed!\n");
        }
        else if (rc2 == 0) // Second child process
        {
            close(fds[1]); // Write end closed.

            printf("(2) child pid: %d\n",(int) getpid());

            char* str;
            read(fds[0], str, 100);
            printf("(2) pipe come with '%s' via read \n", str);

            scanf("%s", str);
            printf("(2) pipe come with '%s' via scanf \n", str);

            //close(STDIN_FILENO);
        }
        else
        {
            int rc_wait = wait(NULL);
            if (rc_wait > 0)
                printf("child finished their task properly!\n");
            else
                printf("child couldn't finished their task properly!\n");
        }
    }

    return 0;
}
*/

/*
    int main(void)
    {

        int fds[2];
        if (pipe(fds) == -1)
        {
            fprintf(stderr, "pipe failed!\n");
            exit (1);
        }

        printf("fds[0] = %d, fds[1] = %d\n", fds[0], fds[1]);

        int rc = fork();
        if (rc < 0)
        {
            fprintf(stderr, "fork failed\n");
            exit (1);
        }
        else if (rc == 0) // First child processes
        {
            close(fds[0]); // Read end closed.

            printf("(1) child pid: %d\n",(int) getpid());
            close(STDOUT_FILENO); // Now stdout looks for fds[1] > '4'

            char* str = "(1) hello!";
            write(fds[1], str, strlen(str) + 1);

            close(fds[1]);
        }
        else
        {
            int rc2 = fork();
    // FPRİNTF çalışabilir!
            if (rc2 < 0)
            {
                fprintf(stderr, "second fork failed!\n");
            }
            else if (rc2 == 0) // Second child process
            {
                close(fds[1]); // Write end closed.

                printf("(2) child pid: %d\n",(int) getpid());

                char* str;
                read(fds[0], str, 100);
                printf("(2) pipe come with '%s'\n", str);
                //close(STDIN_FILENO);
            }
            else
            {
                int rc_wait = wait(NULL);
                if (rc_wait > 0)
                    printf("child finished their task properly!\n");
                else
                    printf("child couldn't finished their task properly!\n");
            }
        }

        return 0;
    }
 */
