// UDP Server
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    int sockfd, portno, n;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Error opening socket");
        exit(1);
    }

    bzero((char*) &serv_addr, sizeof(serv_addr));
    portno = 1234;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error on binding");
        exit(1);
    }

    clilen = sizeof(cli_addr);

    bzero(buffer, 256);
    n = recvfrom(sockfd, buffer, 255, 0, (struct sockaddr*) &cli_addr, &clilen);
    if (n < 0) {
        perror("Error reading from socket");
        exit(1);
    }

    printf("Message from client: %s\n", buffer);

    n = sendto(sockfd, "Server acknowledges your message", 30, 0, (struct sockaddr*) &cli_addr, clilen);
    if (n < 0) {
        perror("Error writing to socket");
        exit(1);
    }

    close(sockfd);
    return 0;
}
