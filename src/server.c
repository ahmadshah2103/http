#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include "socket_utils.h"
#include "response_handler.h"
#include "request_parser.h"
#include "router.h"
#include "handlers.h"

// Constants for server configuration
#define BACKLOG 10

int main(int argc, char *argv[])
{
    int PORT = 8080;
    if (argc > 1)
    {
        PORT = atoi(argv[1]);
    }

    struct sockaddr_in client_addr, server_addr;
    socklen_t client_len = sizeof(client_addr);
    char request[4096] = {0}, method[10], path[100];

    // Create server socket
    int server_socket = create_socket(AF_INET, SOCK_STREAM, 0);

    // Set up server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind and listen to the socket
    bind_socket(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr), PORT);
    listen(server_socket, BACKLOG);
    printf("Server listening on port %d...\n", PORT);

    // Define routes
    init_router();
    register_route("GET", "/", handle_root);
    register_route("GET", "/hello", handle_hello);
    register_route("GET", "/redis-basics", handle_redis_basics);
    register_route("GET", "/vpc-exemplified", handle_vpc_exemplified);

    // Accept client connections
    while (1)
    {

        int client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
        if (client_socket < 0)
        {
            perror("Failed to accept connection");
            continue;
        }
        printf("Request received at: %s\n", inet_ntoa(client_addr.sin_addr));

        // Handle HTTP request and send response
        receive_request(client_socket, request);
        parse_request(request, method, path);
        if (strcmp(path, "/favicon.ico") == 0)
        {
            printf("Ignoring favicon request\n");
            send_response(client_socket, 404, "text/plain", "Favicon not found");
        }
        else
        {
            route_handler_t handler = find_route(method, path);
            if (handler != NULL)
            {
                handler(client_socket);
            }
            else
            {
                handle_404(client_socket);
            }
        }
        
        // Close client socket after handling request
        close(client_socket);
    }

    // Close server socket
    close(server_socket);

    return 0;
}
