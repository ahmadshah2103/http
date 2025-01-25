#include "request_parser.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>

void receive_request(int client_socket, char *request)
{
    int bytes_read = recv(client_socket, request, 4096, 0);
    if (bytes_read < 0)
    {
        perror("Failed to read from client");
        close(client_socket);
        return;
    }
    else if (bytes_read == 0)
    {
        fprintf(stderr, "Client disconnected\n");
        close(client_socket);
        return;
    }
    request[bytes_read] = '\0';
}

void parse_request(const char *request, char *method, char *path)
{
    // Ensure input pointers are valid
    if (request == NULL || method == NULL || path == NULL)
    {
        fprintf(stderr, "Error: Null pointer passed to parse_request\n");
        return;
    }

    // Parse the method and path from the request
    if (sscanf(request, "%s %s", method, path) != 2)
    {
        fprintf(stderr, "Error: Failed to parse HTTP method and path\n");
        method[0] = '\0';
        path[0] = '\0';
        return;
    }
}
