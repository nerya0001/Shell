#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "util.h"

void initClient()
{
    char *ip = "127.0.0.1";
    int port = 12345;

    struct sockaddr_in addr;

    // sock = socket(AF_INET, SOCK_STREAM, 0);
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        perror("Socket error");
        exit(1);
    }

    printf("%sTCP server socket created.\n", RED);
    printf("\033[0m"); // return to normal color

    memset(&addr, '\0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = port;
    addr.sin_addr.s_addr = inet_addr(ip);

    connect(clientSocket, (struct sockaddr *)&addr, sizeof(addr));
    printf("%sConnected to the server.\n", RED);
    printf("\033[0m"); // return to normal color
    
}