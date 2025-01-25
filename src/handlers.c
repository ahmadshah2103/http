#include "response_handler.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Simple handlers 
void handle_root(int client_socket)
{
    const char *body = "<h1>Welcome to the HTTP Server</h1>";
    send_response(client_socket, 200, "text/html", body);
}

void handle_hello(int client_socket)
{
    const char *body = "<h1>Hello, World!</h1>";
    send_response(client_socket, 200, "text/html", body);
}

// Static file handlers
void handle_redis_basics(int client_socket)
{
    const char *path = "./static/redis-basics.html";
    send_file_chunked(client_socket, path);
}

void handle_vpc_exemplified(int client_socket)
{
    const char *path = "./static/vpc.html";
    send_file_chunked(client_socket, path);
}

// Fallback handlers
void handle_404(int client_socket)
{
    const char *body = "<h1>404 Not Found</h1>";
    send_response(client_socket, 404, "text/html", body);
}