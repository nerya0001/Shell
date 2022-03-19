#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/wait.h>
#include "util.h"


void listDirCont()
{
    DIR *dir;
    struct dirent *sd;
    dir = opendir(".");
    if (dir == NULL)
    {
        printf("%sError! Unable to open directory.\n", RED);
        printf("\033[0m"); // return to normal color
        exit(1);
    }
    while ((sd = readdir(dir)) != NULL)
    {
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

void getCurPath()
{
    char cwd[PATH_MAX];
    
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%suser@User: %s%s%s$ ", GREEN, BLUE, cwd, MAGENTA);
        printf("\033[0m"); // return to normal color
    }
    else
    {
        perror("getcwd() error");
        exit(1);
    }
}

void copySrcToDst(char *src, char *dst)
{
    char ch;
    FILE *fpSrc = fopen(src, "r");
    FILE *fpDst = fopen(dst, "a");
    if (fpSrc == NULL || fpDst == NULL)
    {
        printf("%sError in copy files\n", RED);
        printf("\033[0m"); // return to normal color
        exit(1);
    }
    while ((ch = fgetc(fpSrc)) != EOF)
    {
        fputc(ch, fpDst);
    }
    printf("%sFile copied successfully.\n", GREEN);
    printf("\033[0m"); // return to normal color
    fclose(fpSrc);
    fclose(fpDst);
}