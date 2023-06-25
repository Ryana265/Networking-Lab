// UDP Client
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int main() {
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent* server;
    char buffer[256];

    portno = 1234;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Error opening socket");
        exit(1);
    }

    server = gethostbyname("localhost");
    if (server == NULL) {
        fprintf(stderr, "Error, no such host\n");
        exit(1);
    }

    bzero((char*) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char*) server->h_addr, (char*) &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    printf("Enter a message: ");
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);

    n = sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
    if (n < 0) {
        perror("Error writing to socket");
        exit(1);
    }

    bzero(buffer, 256);
    n = recvfrom(sockfd, buffer, 255, 0, NULL, NULL);
    if (n < 0) {
        perror("Error reading from socket");
        exit(1);
    }

    printf("Server response: %s\n", buffer);

    close(sockfd);
    return 0;
}

