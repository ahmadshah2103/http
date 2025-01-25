# Variables
CC = gcc
CFLAGS = -Iinclude -Wall
PORT = 8080
TARGET = server
SRCS = ./src/server.c ./src/socket_utils.c ./src/response_handler.c ./src/handlers.c ./src/router.c ./src/request_parser.c
OBJS = $(SRCS:.c=.o)

# Build target
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

# Compile object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean compiled files
clean:
	rm -f $(OBJS) $(TARGET)

# Run the server (builds and runs the server)
run: $(TARGET)
	./$(TARGET) $(PORT)

# Stop the server if already running (using port)
stop_server:
	@echo "Checking if server is running on port $(PORT)..."
	@pid=$(lsof -t -i :$(PORT)); \
	if [ -n "$$pid" ]; then \
		echo "Server is running with PID $$pid. Stopping it..."; \
		kill $$pid; \
		sleep 1; \
	else \
		echo "No server process found on port $(PORT)."; \
	fi

# Watch for changes and rebuild/restart automatically
watch:
	@echo "Watching for file changes..."
	# Stop the previous server if it's running
	@$(MAKE) stop_server
	# Build and run the server whenever files change
	@ls src/*.c include/*.h | entr -r $(MAKE) run