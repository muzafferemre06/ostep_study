#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/* use execv / path for desired command */
// refer to lines after 93 in README.md for
// detailed implementation
// applyCommand() = an interface for applying commands coming from user

    // TODO: where to define path?
    // for executing commands use access('path', XOK) -> if fails error
    //


/*
Get the user input
Apply the user input
If user input is exit -> then exit!
*/
int main(int argc, char *argv[]) {
// if argc > 2 and argv contains file
    // if batch file is given just do what writes over there

    //close stdin and open given file
    //close(stdin);
    //open(argv[3]);

    // while reading if encountered EOF -> exit(0);

    // if no batch file is given
    const int TRUE = 1;
    char* buffer;
    size_t bufferSize = 128;
    size_t charsRead;
    buffer = (char*)malloc(bufferSize*sizeof(char));
    if (buffer == NULL)
        fprintf(stderr, "Unable to allocate buffer for input!\n");
    else {
        while (TRUE) {
            fprintf(stdout, "wish> ");
            /*
            * // get the command from user, then ->
                if (command != "exit")
                    applyCommand(command);
                else
                exit(0);
            */

            charsRead = getline(&buffer, &bufferSize, stdin);
            // Parse input
            // strsep(buffer, ...);

            fprintf(stdout, "User input, lenght of %zu, is: %s\n",
                charsRead, buffer);
            exit(0);
        }
    }
}
