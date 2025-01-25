// Functions for socket setup (e.g., create_socket, bind_socket)
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int create_socket(int domain, int type, int protocol)
{
    int sockfd = socket(domain, type, protocol);
    if (sockfd < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
    {
        perror("setsockopt failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    return sockfd;
}

void bind_socket(int sockfd, struct sockaddr *addr, socklen_t addr_len, int port)
{
    if (bind(sockfd, addr, addr_len) < 0)
    {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
}
