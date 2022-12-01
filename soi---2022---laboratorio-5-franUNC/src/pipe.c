#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../include/pipe.h"
#include "../include/executecommands.h"

static void pipeLine(char* commands[], int numberOfProc);
static char** decod(char* command, int* numberOfProc);

int executePipe(char* command){
    
    if (strchr(command, '|')) {

        char **commands;
        int numberOfProc;

        commands = decod(command,&numberOfProc);

        pipeLine(commands,numberOfProc);
        return 0;
    }
    return 1;

}


static void pipeLine(char** commands, int numberOfProc){
    
    int fileDescriptors[2];
    pid_t pid;
    if(pipe(fileDescriptors) == -1){
        perror("Pipe error");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    switch(pid){
        case -1:
            perror("Could not create child");
            break;

        case 0:
            close(fileDescriptors[0]);
            dup2(fileDescriptors[1],STDOUT_FILENO);
            close(fileDescriptors[1]);
            if(numberOfProc>1)
                pipeLine(commands,numberOfProc-1);
            else
                executeCommand(commands[numberOfProc-1]);
            exit(0);
            break;

        default:
            wait(0);
            pid = fork();

            switch(pid){
                case -1:
                    perror("Could not create child");
                    break;

                case 0:
                    close(fileDescriptors[1]);
                    dup2(fileDescriptors[0],STDIN_FILENO);
                    close(fileDescriptors[0]);
                    executeCommand(commands[numberOfProc]);
                    exit(0);
                    break;

                default:
                    close(fileDescriptors[0]);
                    close(fileDescriptors[1]);
                    wait(0);
                    break;
            }
            break;
    }
}


static char** decod(char* command, int* numberOfProc){
    char **commands;
    commands = (char**)malloc(sizeof(char*)*10);
    *numberOfProc = 0;

    command = strtok(command,"|");
    while (command!=NULL)
    {
        commands[*numberOfProc] = command;

        command= strtok(NULL,"|");
        *numberOfProc = *numberOfProc+1;
    }

    *numberOfProc = *numberOfProc-1;

    return commands;
}
