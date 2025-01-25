#ifndef SOCKET_UTILS_H
#define SOCKET_UTILS_H

#include <sys/socket.h>
#include <netinet/in.h>

int create_socket(int domain, int type, int protocol);
void bind_socket(int sockfd, struct sockaddr *addr, socklen_t addr_len, int port);

#endif
