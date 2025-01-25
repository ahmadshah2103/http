#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "response_handler.h"

// Send response headers
void send_file_header(int client_socket, const char *content_type, long content_length)
{
    char header[1024];
    snprintf(header, sizeof(header),
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: %s\r\n"
             "Content-Length: %ld\r\n"
             "Connection: close\r\n\r\n",
             content_type, content_length);
    write(client_socket, header, strlen(header));
}

// Send file content in chunks
void send_file_chunked(int client_socket, const char *path)
{
    struct stat file_stat;
    int file_descriptor;
    ssize_t bytes_read;
    size_t chunk_size = 4096;
    char buffer[chunk_size];

    // Check if the file exists
    if (stat(path, &file_stat) == -1)
    {
        send_response(client_socket, 404, "text/html", "<html><body><h1>404 Not Found</h1></body></html>");
        return;
    }

    // Open the file
    file_descriptor = open(path, O_RDONLY);
    if (file_descriptor == -1)
    {
        send_response(client_socket, 500, "text/html", "<html><body><h1>500 Internal Server Error</h1></body></html>");
        return;
    }

    // Send the headers first
    send_file_header(client_socket, "text/html", file_stat.st_size);

    // Send file content in chunks
    while ((bytes_read = read(file_descriptor, buffer, chunk_size)) > 0)
    {
        write(client_socket, buffer, bytes_read);
    }

    close(file_descriptor);
}

// Send simple HTTP response 
void send_response(int client_socket, int status_code, const char *content_type, const char *body)
{
    if (content_type == NULL || body == NULL)
    {
        // Handle error for NULL content_type or body
        return;
    }

    char header[8192]; // Increased size for larger responses
    char status_message[1024];

    // Set status message based on the status code
    switch (status_code)
    {
    case 200:
        strcpy(status_message, "OK");
        break;
    case 404:
        strcpy(status_message, "Not Found");
        break;
    case 500:
        strcpy(status_message, "Internal Server Error");
        break;
    default:
        strcpy(status_message, "Unknown Status Code");
    }

    // Safely format the response
    sprintf(header,
            "HTTP/1.1 %d %s\r\n"
            "Content-Type: %s\r\n"
            "Content-Length: %ld\r\n"
            "Access-Control-Allow-Origin: *\r\n\r\n",
            status_code, status_message, content_type, strlen(body));

    // // Send headers
    send(client_socket, header, strlen(header), 0);

    // Send body (file content or error page)
    send(client_socket, body, strlen(body), 0);
}
