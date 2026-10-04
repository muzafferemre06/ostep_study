#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

const int TRUE = 1;
const int ARG_LIM = 10;
const int PATH_LENGHT = 100;

char** pathList;
int pathNumber = 0;
/* Step by step plan:
 * 1-) Implement basic parser & command executor
 * without concerning edge cases.
 * 2-)
 */

/* use execv / path for desired command */
// refer to lines after 93 in README.md for
// detailed implementation
// applyCommand() = an interface for applying commands coming from user

    // Check for command if built-in or not! exit, cd (chdir), path

    // TODO: where to define path='/bin' (initial) variable? Or how to use path (lines 153)
    // for executing commands use access('path', XOK) -> if fails error

    // implement '>' redirection as well! by closing stdout, and opening other file!
    // should overwrite if opened - else open
    // multiple redirection sign or files are error

    // also apply parallel commands = use waitpid with loop

    // read errors: line 206 [Look later - not now!]

int applyCommand(char* command, char* arguments[], int argNum) {

    if (command == NULL){
        fprintf(stderr, "No command given properly!\n");
        return (1);
    }
    else {

        // // Defines path that will be executed.
        // char path[PATH_LENGHT];
        // strcpy(path, "/bin/")
        // strcat(path, command); //fprintf(stdout, "path: %s\n", path);

        // // This part implement the main functionality
        // int result = access(path, X_OK);
        // if (result == -1) {
        //     fprintf(stderr, "Couldn't access the path %s!\n", path);
        //     return (2);
        // }

    // This part implement the main functionality

        // Defines path that will be executed.
        char path[PATH_LENGHT];
        int pathFound = 0; // Flag for checking any suitable path.

        // Finds first path having the desired command
        // TODO: I have to test this somehow, but don't know how.
        for (int i = 0; i < pathNumber; i++) {
            strcpy(path, pathList[i]);
            strcat(path, command);

            int result = access(path, X_OK);
            if (result == 0) {
                pathFound = 1;
                break;
            }
            else {
                fprintf(stderr, "Couldn't access the path %s!\n", path);
            }
        }
        if (!pathFound) {
            fprintf(stderr, "Couldn't find a path for command in current pathList!\n");
            return (2);
        }

        int childPID = fork();
        if (childPID < 0) {
            fprintf(stderr, "Fork failed!\n");
            return (3);
        }
        else if (childPID == 0) {
            // first argument is path
            // second argument is the arguments of desired command
            execv(path, arguments);
            fprintf(stderr, "There was a problem while execv given command!\n");
            return (4);
        }
        else {
            int rc_wait = wait(NULL);
            //fprintf(stdout, "Child process finished it job!\n");
            return (0);
        }
    }
}
char* getInput(void) {
    char* buffer;
    size_t bufferSize = 256;
    size_t charsRead;

    buffer = (char*)malloc(bufferSize*sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Unable to allocate buffer for input!\n");
        return NULL;
    }

    charsRead = getline(&buffer, &bufferSize, stdin);
    buffer[strcspn(buffer,"\n")] = '\0'; // Delete the \n char & end this string.

    // fprintf(stdout, "User input, lenght of %zu, is: %s\n",
    //     charsRead, buffer);

    return buffer;
}
int parseInput(char* input, char* command[], char* arguments[], int* argNum) {
    // TODO: Add some checks for error catching!
    // TODO: delete trailing spaces -> look for if an argument only contains by space.
    int i;
    for(i = 0; i < ARG_LIM &&
        (arguments[i] = strsep(&input, " ")) != NULL; i++);

    *argNum = i;
    *command = arguments[0];
    arguments[*argNum] = NULL; // for execv function

    // for (i = 0; i < *argNum; i++)
    //     fprintf(stdout, "%d. arg is %s\n", i, arguments[i]);
    return (0);
}
int main(int argc, char *argv[]) {
// if argc > 2 and argv contains file
    // if batch file is given just do what writes over there

    //close stdin and open given file
    //close(stdin);
    //open(argv[3]);

    // while reading if encountered EOF -> exit(0);

// if no batch file is given
    char* input;
    char* command;

    // Initial path to look for commands is '/bin/'
    pathNumber = 1;
    pathList = (char**)malloc(sizeof(char*)*pathNumber);
    pathList[0] = (char*)malloc(sizeof(char)*PATH_LENGHT);
    // There might be a problem with last '/'
    // Change the way you handle.
    strcpy(pathList[0], "/bin/");

    // if in interactive mode.
    while (TRUE) {
        fprintf(stdout, "wish> ");
        input = getInput();
        if (input == NULL){
            fprintf(stderr, "Error when getting input!\n");
            exit (1);
        }

        int argNum;
        char* arguments[ARG_LIM + 1];

        // Gets command into variable 'command'
        if (parseInput(input, &command, arguments, &argNum) > 0) {
            fprintf(stderr, "Error when parsing input!\n");
            exit (1);
        }
        // Apply if built-in commands are given.
        // TODO: You can handle built-in functions in different function rather than main.
        if (strcmp(command, "exit") == 0) {
            if (argNum > 1) {
                fprintf(stderr, "Arguments cannot be given for exit!\n");
                exit (1);
            }

            fprintf(stdout, "Exit is given as command!\n");
            exit(0);
        }
        else if (strcmp(command, "cd") == 0) {
            if (argNum != 2) {
                fprintf(stderr, "Less or more arguments given for cd!\n");
                exit (1);
            }

            char cwd[PATH_LENGHT];
            if (chdir(arguments[1]) == -1) {
                fprintf(stderr, "There was an error when applying cd!\n");
                exit (1);
            }
            else {
                fprintf(stdout, "Directory changed to: %s\n", getcwd(cwd, PATH_LENGHT));
            }
        }
        else if (strcmp(command, "path") == 0) {
            // TODO: Implement the logic for chaning pathList & pathNumber
            // Override and free the current path
            for (int i = 0; i < pathNumber; i++)
                free(pathList[i]);
            free(pathList);

            pathNumber = argNum - 1;
            pathList = (char**)malloc(sizeof(char*)* (argNum- 1));
            for (int j = 0; j < argNum - 1; j++) {
                pathList[j] = (char*)malloc(sizeof(char)*PATH_LENGHT);
                strcpy(pathList[j], arguments[j + 1]); // There might be a problem with indices
            }

            for (int k = 0; k < pathNumber; k++)
                fprintf(stdout, "pathList[%d]: %s\n", k, pathList[k]);
        }
        else {
            if (applyCommand(command, arguments, argNum) > 0) {
                fprintf(stderr, "Problem occured when applying command, exiting!\n");
                exit(1);
            }
        }
    }
}
