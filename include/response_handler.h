#ifndef RESPONSE_HANDLER_H
#define RESPONSE_HANDLER_H

void send_response(int client_socket, int status_code, const char *content_type, const char *body);
void send_file_header(int client_socket, const char *content_type, long content_length);
void send_file_chunked(int client_socket, const char *path);

#endif
