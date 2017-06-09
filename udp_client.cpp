#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#define SERVPORT 1106
#define CLIPORT 1107
#define MAXLINE 1024

int main(){
    int socket_fd;
    struct sockaddr_in client_addr, server_addr, recv_addr;
    bzero(&client_addr, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(CLIPORT);
    client_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVPORT);
    server_addr.sin_addr.s_addr = INADDR_BROADCAST;
    
    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    bind(socket_fd, (struct sockaddr *)&client_addr, sizeof(client_addr));

    int optval = 1;
    setsockopt(socket_fd, SOL_SOCKET, SO_BROADCAST, &optval, sizeof(optval));

    char message[MAXLINE];
    printf("input message:\n");
    scanf("%s", message);
    sendto(socket_fd, message, strlen(message), 0, (struct sockaddr *)&server_addr, sizeof(client_addr));
    socklen_t len;
    recvfrom(socket_fd, message, MAXLINE, 0, (struct sockaddr*)&recv_addr, &len);
    printf("%s\n", message);
    printf("message from:%s\n", inet_ntoa(recv_addr.sin_addr));
    return 0;
}