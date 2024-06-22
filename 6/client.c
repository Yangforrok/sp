#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080

int main(int argc, char *argv[]) {
    int sockfd;
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr(argc > 1 ? argv[1] : "127.0.0.1");

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
        printf("Connection to the server failed.\n");
        exit(0);
    }

    printf("Connected to the server successfully.\n");

    char cmd[1024];
    while (fgets(cmd, sizeof(cmd), stdin) != NULL) {
        write(sockfd, cmd, strlen(cmd)); // 發送命令給 server
        int n = read(sockfd, cmd, sizeof(cmd) - 1);
        if (n > 0) {
            cmd[n] = '\0
