#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

const int TRUE = 1;
const int ARG_LIM = 10;

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

        // For debug purpose
        if (arguments == NULL) {
            fprintf(stdout, "No arguments are given for function!\n");
            fprintf(stdout, "Command given: %s\n", command);
        }
        else {
            fprintf(stdout, "Arguments are given for function!\n");
            fprintf(stdout, "Command given: %s with arguments:", command);
            for (int i = 0; i < argNum; i++)
                fprintf(stdout, " %s", arguments[i]);
            fprintf(stdout, "\n");
        }

        // This part will implement the main functionality
        // TODO: implement execv logic.
    }

    return (0);
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

    fprintf(stdout, "User input, lenght of %zu, is: %s\n",
        charsRead, buffer);

    return buffer;
}
int parseInput(char* input, char* command[], char* arguments[], int* argNum) {
    // TODO: Add some checks for error catching!
    // Parses the string to get arguments.
    *command = strsep(&input, " ");
    if (*command == NULL){
        fprintf(stderr, "Command wasn't extracted!\n");
        return 1;
    }

    // TODO: delete trailing spaces -> look for if an argument only contains by space.
    int i;
    for(i = 0; i < ARG_LIM &&
        (arguments[i] = strsep(&input, " ")) != NULL; i++);
    *argNum = i;

    for (i = 0; i < *argNum; i++)
        fprintf(stdout, "%d. arg is %s\n", i, arguments[i]);

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

    // if in interactive mode.
    while (TRUE) {
        fprintf(stdout, "wish> ");
        input = getInput();
        if (input == NULL){
            fprintf(stderr, "Error when getting input!\n");
            exit (1);
        }

        int argNum;
        char* arguments[ARG_LIM];

        // Gets command into variable 'command'
        if (parseInput(input, &command, arguments, &argNum) > 0) {
            fprintf(stderr, "Error when parsing input!\n");
            exit (1);
        }
        if (strcmp(command, "exit") == 0) {
            fprintf(stdout, "Exit is given as command!\n");
            exit(0);
        }
        else {
            if (applyCommand(command, arguments, argNum) > 0) {
                fprintf(stderr, "Problem occured when applying command, exiting!\n");
                exit(1);
            }
        }
    }
}
