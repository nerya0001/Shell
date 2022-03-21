#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/wait.h>
#include "util.h"


void listDirCont() {

    DIR *dir;
    struct dirent *sd;
    dir = opendir(".");

    if (dir == NULL) {

        printf("%sError! Unable to open directory.\n", RED);
        printf("\033[0m"); // return to normal color
        exit(1);
    }

    while ((sd = readdir(dir)) != NULL) {

        char *extantion = strrchr(sd->d_name, '.');
        if (!extantion) {
            printf("%s%s  ", RED, sd->d_name);
            printf("%s", NORMAL);       
        } else if (strcmp(extantion, ".o")) {
            printf("%s%s  ", CYAN, sd->d_name);
            printf("%s", NORMAL);
        } else if (strcmp(extantion, ".c")) {
            printf("%s%s  ", GREEN, sd->d_name);
            printf("%s", NORMAL);
        } else if (strcmp(extantion, ".h")) {
            printf("%s%s  ", CYAN, sd->d_name);
            printf("%s", NORMAL);
        } else if (strcmp(extantion, ".a")) {
            printf("%s%s  ", WHITE, sd->d_name);
            printf("%s", NORMAL);
        } else {
            printf("%s  ", sd->d_name);
        }
    }
    
    closedir(dir);
    return;
}

void getCurPath() {

    char cwd[PATH_MAX];
    
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%suser@User: %s%s%s$ ", GREEN, BLUE, cwd, MAGENTA);
        printf("\033[0m"); // return to normal color
    } else {
        perror("getcwd() error");
        exit(1);
    }
}

void echo(char* buffer) {

    for (int i = 5; i < BUF_SIZE; i++) {
                printf("%c", buffer[i]);
            }
}

void changeDir(char* buffer) {

    char path[BUF_SIZE];
    bzero(path, BUF_SIZE);
    int j = 0;

    for (int i = 3; i < strlen(buffer); i++, j++){

        path[j] = buffer[i];
    }

    chdir(path);
}

void copySrcToDst(char* buffer) {

    // getting the src and dst
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

    char ch;
    FILE *fileSrc = fopen(srcFile, "r");
    FILE *fileDst = fopen(dstFile, "a");
    if (fileSrc == NULL || fileDst == NULL) {
        printf("%sError ocured while copying the files\n", RED);
        printf("\033[0m"); // return to normal color
        exit(1);
    }

    while ((ch = fgetc(fileSrc)) != EOF) {
        fputc(ch, fileDst);
    }

    printf("%sThe file was successfully copied.\n", GREEN);
    printf("\033[0m"); // return to normal color
    fclose(fileSrc);
    fclose(fileDst);
}

void del(char* buffer) {

    char path[BUF_SIZE];
    bzero(path, BUF_SIZE);
    int j = 0;
    for (int i = 7; i < strlen(buffer); i++, j++) {

        path[j] = buffer[i];
    }

    unlink(path);

}

int sysReplacement(char* buffer) {
    
    // parse the input by " "
    parse(buffer);
 
    // fork a child process
    int pid = fork();
    
    if (pid < 0) {

        // error  
        return 1;
        
    } else if (pid == 0) {

        execvp(parbuff[0], parbuff); 

    } else {

        /* parent process */
        /* parent will wait for the child to complete */
        wait(NULL);
    }
    return 0;
}

void parse(char* buffer) {

    char* pbuff;
    int i = 0;
    pbuff = strtok(buffer, " ");
    while (pbuff != NULL) {
        parbuff[i++] = pbuff;
        pbuff = strtok(NULL, " ");
    }

}