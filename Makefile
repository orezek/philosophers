# Define the compiler
CC = gcc

# Define the flags
CFLAGS = -Wall -Wextra -Werror -O3 -pthread

# Define the source files
SRCS = main.c init_simulation.c fork_utils.c init_resources.c forks.c time_functions.c clean_allocs.c control_thread.c init_philosophers.c thread_states.c thread_execution.c

# Define the header files
HEADERS = philos.h

# Define the output executable
OUT = philo

# Define the object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(OUT)

# Rule to build the executable
$(OUT): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to build object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJS) $(OUT)

# Phony targets
.PHONY: all clean
