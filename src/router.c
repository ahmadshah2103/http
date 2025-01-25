#include "router.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ROUTES 100

// Route struct for defining routes/endpoints
typedef struct {
    char method[10];
    char path[100];
    route_handler_t handler;
} Route;

static Route routes[MAX_ROUTES];
static int route_count = 0;

void init_router() {
    route_count = 0;
}

void register_route(const char *method, const char *path, route_handler_t handler) {
    if (route_count >= MAX_ROUTES) {
        fprintf(stderr, "Max route limit reached\n");
        return;
    }
    strncpy(routes[route_count].method, method, sizeof(routes[route_count].method));
    strncpy(routes[route_count].path, path, sizeof(routes[route_count].path));
    routes[route_count].handler = handler;
    route_count++;
}

route_handler_t find_route(const char *method, const char *path) {
    for (int i = 0; i < route_count; i++) {
        if (strcmp(routes[i].method, method) == 0 && strcmp(routes[i].path, path) == 0) {
            return routes[i].handler;
        }
    }
    return NULL; // No matching route
}
