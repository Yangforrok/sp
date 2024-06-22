#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_CLIENTS 10

int client_sockets[MAX_CLIENTS];
int num_clients = 0;
pthread_mutex_t lock;

void *client_handler(void *arg) {
    int connfd = *(int *)arg;
    char cmd[1024];

    while (1) {
        int len = read(connfd, cmd, sizeof(cmd)); // 讀取 client 的指令
        if (len <= 0) break;
        strtok(cmd, "\n"); // 去除換行符
        printf("Received command: %s\n", cmd);

        pthread_mutex_lock(&lock); // 上鎖以保護 client_sockets 陣列
        for (int i = 0; i < num_clients; i++) {
            if (client_sockets[i] != 0) {
                dprintf(client_sockets[i], "%s\n", cmd); // 向所有 clients 廣播指令
            }
        }
        pthread_mutex_unlock(&lock);
    }

    close(connfd);
    pthread_mutex_lock(&lock);
    for (int i = 0; i < num_clients; i++) { // 移除斷線的 client
        if (client_sockets[i] == connfd) {
            client_sockets[i] = 0;
            break;
        }
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    listen(sockfd, 5);

    printf("Server listening on port %d\n", PORT);

    while (1) {
        socklen_t len = sizeof(cli);
        connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
        if (connfd < 0) {
            continue;
        }
        printf("Connected to client: %s\n", inet_ntoa(cli.sin_addr));

        pthread_mutex_lock(&lock);
        if (num_clients < MAX_CLIENTS) {
            client_sockets[num_clients++] = connfd;
            pthread_t tid;
            pthread_create(&tid, NULL, client_handler, (void *)&connfd);
        }
        pthread_mutex_unlock(&lock);
    }

    return 0;
}
