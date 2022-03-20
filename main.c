#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/wait.h>
#include "util.h"



int main()
{
    char buffer[BUF_SIZE] = {0}; // buffer for the input
    int check; // var to check the there was actualy input

    getCurPath();
    check = scanf("%[^\n]%*c", buffer); 
    
    // if nothing was received we need to flush the stdin, so we don't enter an infinite loop
    if (check == 0) {
            while ( getchar() != '\n' );
            getCurPath();
        }
        
    while (strcmp(buffer, "EXIT")) {
        
        // if nothing was received we need to flush the stdin, so we don't enter an infinite loop
        if (check == 0) {
            while ( getchar() != '\n' );
            getCurPath();
        }

        else if (strncmp(buffer, "ECHO", 4) == 0 || strncmp(buffer, "echo", 4) == 0) {
            
            echo(buffer);

            printf("\n");
            getCurPath();
        }

        else if (strncmp(buffer, "DIR", 3) == 0) {

            listDirCont();

            printf("\n");
            getCurPath();
        }

        else if (strncmp(buffer, "TCP PORT", 8) == 0) {

            initClient();
        }

        // change directory to the asked one
        // the comand cddir is a system function  
        else if (strncmp(buffer, "CD", 2) == 0) {
        // else if (strncmp(buffer, "CD", 2) == 0 || strncmp(buffer, "cd", 2) == 0) {

            changeDir(buffer);
            
            getCurPath();
        }

        
        // fopen, fread, fwrite is libary function.
        else if (strncmp(buffer, "COPY", 4) == 0 || strncmp(buffer, "copy", 4) == 0) {

            copySrcToDst(buffer);

            getCurPath();
        }

        // unlink of a file is a system function.
        else if (strncmp(buffer, "DELETE", 6) == 0 || strncmp(buffer, "delete", 6) == 0) {

            del(buffer);

            getCurPath();
        }
        
        // The system() is library function that create a child process and getting it to do the work
        // alternativly I implemented the state machine my self
        // to swich between the state machine and the system() you need to leave the one you want uncommented.
        // else if (strlen(buffer) > 0) {
        else {
            
            sysReplacement(buffer);
            // system(buffer);

            getCurPath();
            
        }
        
        bzero(buffer, BUF_SIZE);
        check = scanf("%[^\n]%*c", buffer);  
    }

    return 0;
}
