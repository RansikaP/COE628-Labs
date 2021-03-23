/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: mratnaya
 *
 * Created on February 22, 2021, 8:24 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <stdbool.h>

char removeSpaces(char string[100], char ** argv);

int main(int argc, char** argv)
{
    char input[100];
    char b_pipe[100];
    char a_pipe[100];
    int fd[2];
    int i = 0;
    int j = 0;
    bool flag = false;
    
    fgets(input, 100, stdin);
    
    for (i = 0; i < strlen(input) - 1; i++) {
        if (!flag) {
            if (input[i] == '|') {
                flag = true;
                j = 0;
            } else {
                b_pipe[j] = input[i];
                j++;
            }
        } else {
            a_pipe[j] = input[i];
            j++;
        }
    }
    
    pipe(fd);    
    pid_t id = fork();
    
    if (id == 0) {
        close(fd[0]);
        removeSpaces(b_pipe, argv);
        dup2(fd[1], 1);
        execvp(argv[0], argv);        
    } else {
        close(fd[1]);
        removeSpaces(a_pipe, argv);
        dup2(fd[0], 0);
        execvp(argv[0], argv);
    }
    
    return(EXIT_SUCCESS);
}

char removeSpaces(char string[100], char ** argv) {
    argv[0] = strtok(string, " "); //get text before first space        
    int i = 0;        
    while (argv[i] != NULL) { //loop until null
        argv[++i] = strtok(NULL, " "); //setting spaces to null
    }
}