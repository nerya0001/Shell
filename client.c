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

    int sock;
    struct sockaddr_in addr;
    // socklen_t addr_size;
    char buffer[1024];
    // int n;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket error");
        exit(1);
    }

    printf("%sTCP server socket created.\n", RED);
    printf("\033[0m"); // return to normal color

    memset(&addr, '\0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = port;
    addr.sin_addr.s_addr = inet_addr(ip);

    connect(sock, (struct sockaddr *)&addr, sizeof(addr));
    printf("%sConnected to the server.\n", RED);
    printf("\033[0m"); // return to normal color
    
    char input[50];
    bzero(input, 50);
    scanf("%[^\n]%*c", input);
    // int len = strlen(input);

    while (strncmp(input, "LOCAL", 5) != 0) {

        bzero(buffer, 1024);
        for (int i = 0; i < 50; i++) {
            buffer[i] = input[i];
        }

        send(sock, buffer, strlen(buffer), 0);
        bzero(input, 50);
        scanf("%[^\n]%*c", input);
    }

    bzero(buffer, 1024);
    for (int i = 0; i < 50; i++) {
        buffer[i] = input[i];
    }

    send(sock, buffer, strlen(buffer), 0);
    getCurPath();
}