# HTTP Server

This project implements an HTTP v1.1 server that can handle `GET` request and serve static pages. It utilizes sockets for the client-server request-response handling.

## Features

## How to Run

1. Build the project using:
   ```bash
   make
   ```
2. Run the project:
   ```bash
   ./server
   ```
3. Test using `curl`:

   ```bash
   curl http://localhost:8080/
   ```

   Or the following endpoints can be open in the browser as well:

   - `GET /`
   - `GET /hello`
   - `GET /redis-basics`
   - `GET /vpc-exemplified`

   The server runs on port 8080 by default but can be changed by passing the port number in the arguments while running the server.

### Running in development mode

To run in development mode:

    make watch

## Project Structure

```
.
├── Makefile
├── README.md
├── server
├── include
│   ├── handlers.h
│   ├── request_parser.h
│   ├── response_handler.h
│   ├── router.h
│   ├── server.h
│   └── socket_utils.h
├── src
│   ├── handlers.c
│   ├── handlers.o
│   ├── request_parser.c
│   ├── request_parser.o
│   ├── response_handler.c
│   ├── response_handler.o
│   ├── router.c
│   ├── router.o
│   ├── server.c
│   ├── server.o
│   ├── socket_utils.c
│   └── socket_utils.o
└── static
    ├── redis-basics.html
    └── vpc.html
```
