#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

int main(){
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(9877);
    bind(socketfd, (struct sockaddr*)&servaddr, sizeof(struct sockaddr_in));
    listen(socketfd, 20);
    
    struct sockaddr_in cliaddr;
    socklen_t clilen = sizeof(cliaddr);
    int connfd;
    char str[] = "hello!\n";
    int count = 0;
    while(true){
        connfd = accept(socketfd, (struct sockaddr*)&cliaddr, &clilen);
        count++;
        printf("connected: %d\n", count);
        write(connfd, str, sizeof(str));
        close(connfd);
    }
    close(socketfd);

    return 0;
}