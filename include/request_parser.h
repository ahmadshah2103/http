#ifndef REQUEST_PARSER_H
#define REQUEST_PARSER_H

void receive_request(int client_socket, char *request);
void parse_request(const char *request, char *method, char *path);

#endif
