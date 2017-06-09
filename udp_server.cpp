#include<stdio.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/ioctl.h>
#include<unistd.h>
#define SERVPORT 1106
#define MAXLINE 1024

int main(){
    int socket_fd;
    struct sockaddr_in server_addr, client_addr;

    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERVPORT);

    bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    int n;
    socklen_t len;
    char message[MAXLINE];

    while(true){
        len = sizeof(client_addr);
        bzero(message, sizeof(message));
        recvfrom(socket_fd, message, MAXLINE, 0, (struct sockaddr*)&client_addr, &len);
        printf("%s\n", message);
        printf("%s\n", inet_ntoa(client_addr.sin_addr));
        sendto(socket_fd, inet_ntoa(client_addr.sin_addr), 16, 0, (struct sockaddr*)&client_addr, len);
    }
    return 0;
}