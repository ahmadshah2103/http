#ifndef HANDLERS_H
#define HANDLERS_H

void handle_root(int client_socket);
void handle_hello(int client_socket);
void handle_redis_basics(int client_socket);
void handle_vpc_exemplified(int client_socket);
void handle_404(int client_socket);

#endif
