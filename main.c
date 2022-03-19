#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/wait.h>
#include "util.h"

#define BUF_SIZE 20

int main()
{
    char buffer[BUF_SIZE] = {0};
    int check;

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

        else if (strncmp(buffer, "ECHO", 4) == 0) {

            for (int i = 5; i < BUF_SIZE; i++) {
                printf("%c", buffer[i]);
            }

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

            char path[BUF_SIZE];
            bzero(path, BUF_SIZE);
            int j = 0;

            for (int i = 3; i < strlen(buffer); i++, j++){

                path[j] = buffer[i];
            }

            chdir(path);
            getCurPath();
        }

        
        // fopen, fread, fwrite is libary function.
        else if (strncmp(buffer, "COPY", 4) == 0) {

            char srcFile[BUF_SIZE];
            char dstFile[BUF_SIZE];
            bzero(srcFile, BUF_SIZE);
            bzero(dstFile, BUF_SIZE);
            int j = 5;
            int i = 0;
            // int flag1 = 1;
            while (buffer[j] != ' ') {

                srcFile[i] = buffer[j];
                i++;
                j++;
            }

            j++;
            i = 0;

            while (buffer[j] != '\0') {

                dstFile[i] = buffer[j];
                i++;
                j++;
            }

            copySrcToDst(srcFile, dstFile);
        }

        // unlink of a file is a system function.
        else if (strncmp(buffer, "DELETE", 6) == 0) {

            char path[BUF_SIZE];
            bzero(path, BUF_SIZE);
            int j = 0;
            for (int i = 7; i < strlen(buffer); i++, j++) {

                path[j] = buffer[i];
            }

            unlink(path);
        }
        
        // The system() is library function that create a process and getting it to do the work
        // alternativly I implemented the state machine my self
        // to swich between the state machine and the system() you need to uncomment the machine and comment out the system()
        else if (strlen(buffer) > 0) {
            // fork a child process 
            // int pid = fork();
            // if (pid < 0)
            // {
            //     // error  
            //     return 1;
            // }
            // else if (pid == 0)
            // {
            //     // child process
            //     char p[50] = "/bin/";
            //     strcat(p,input);
            //     execlp(p, input, NULL); 
            // }
            // else
            // {
            //     /* parent process */
            //     /* parent will wait for the child to complete */
            //     wait(NULL);
            // }
            
            system(buffer);
            getCurPath();
            
        }
        
        bzero(buffer, BUF_SIZE);
        check = scanf("%[^\n]%*c", buffer);
        
    }

    return 0;
}
