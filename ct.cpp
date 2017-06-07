#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(){
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) printf("sockfd wrong!\n");

    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(9877);
    if(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
        printf("connect wrong!\n");

    char buf[40];
    if(read(sockfd, buf, sizeof(buf)-1) < 0)
        printf("read wrong!\n");
    printf("%s", buf);
    close(sockfd);
    return 0;
}