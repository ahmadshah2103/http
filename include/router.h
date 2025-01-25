#ifndef ROUTER_H
#define ROUTER_H

typedef void (*route_handler_t)(int);

void init_router();
void register_route(const char *method, const char *path, route_handler_t handler);
route_handler_t find_route(const char *method, const char *path);

#endif
