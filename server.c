#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "util.h"

void initServer()
{
    char *ip = "127.0.0.1";
    int port = 12345;

    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[1024];
    int x;

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("Socket error");
        exit(1);
    }

    if (setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0) {
        
        perror("setsockopt(SO_REUSEADDR) failed");
    }

    printf("%sTCP socket created.\n", RED);
    printf("\033[0m"); // return to normal color

    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    x = bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));

    if (x < 0) {
        perror("Bind error");
        exit(1);
    }

    // printf("%sBind\n", RED);
    // printf("\033[0m"); // return to normal color

    listen(server_sock, 10);

    printf("%sListening for incoming connections...\n", GREEN);
    printf("\033[0m"); // return to normal color
    int flag = 1;

    while (1) {

        if (flag) {
            addr_size = sizeof(client_addr);
            client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addr_size);
            printf("%sClient connected.\n", CYAN);
            printf("\033[0m"); // return to normal color
            flag = 0;
        }

        bzero(buffer, 1024);
        
        if (recv(client_sock, buffer, sizeof(buffer), 0) == 0) {
            printf("%sClient disconnected.\n\n", RED);
            printf("\033[0m"); // return to normal color
            close(client_sock);
            flag = 1;
        }else {
            for (int i = 0; i < 1024; i++) {
                printf("%c",buffer[i]);
            }
            printf("\n");
        }
    }
}


int main(int argc, char const *argv[]) {
    initServer();
    return 0;
}
