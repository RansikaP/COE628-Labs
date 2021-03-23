/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Ransika Perera
 *
 * Created on February 8, 2021, 11:26 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/*
 * 
 */
int main(int argc, char** argv) {
    
    while(1) {
        char input[100];        
        printf("Your command> ");
        fgets(input, 100, stdin);  //get stdin input      
        char last = input[strlen(input) - 2]; //get last character 
        char cmp = '&';
        
        if (cmp == last) { //set clear non command inputs (&, \n)
            input[strlen(input) - 2] = NULL;
        } else {
            input[strlen(input) - 1] = NULL;
        }
             
        argv[0] = strtok(input, " "); //get text before first space        
        int i = 0;
        
        while (argv[i] != NULL) { //loop until null
            argv[++i] = strtok(NULL, " "); //setting spaces to null
        }
        
        pid_t id = fork();
        
        if (last != cmp && id != 0) { //wait if parent and no & in command
            wait(NULL);        
        }
        
        if (id == 0) { //if child execute command
            execvp(argv[0], argv); //executes command on terminal
            printf("command failed"); //prints if command failed
        }
        
        printf("\n");
        
    }
        
}