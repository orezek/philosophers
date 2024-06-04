CC = gcc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread
SRCDIR = ./src
OBJDIR = ./obj

# List of source files
SRCS = main.c \
       $(SRCDIR)/init_resources.c \
       $(SRCDIR)/fork_utils.c \
       $(SRCDIR)/init_mutex.c \
       $(SRCDIR)/thread_execution.c \
       $(SRCDIR)/control_thread.c \
       $(SRCDIR)/thread_states.c \
       $(SRCDIR)/time_functions.c \
       $(SRCDIR)/clean_allocs.c \
       $(SRCDIR)/init_simulation.c \
       $(SRCDIR)/init_philosophers.c \
       $(SRCDIR)/forks.c \
       $(SRCDIR)/input_parser.c \
       $(SRCDIR)/utils.c

# Transform source files to object files
OBJS = $(patsubst %.c, $(OBJDIR)/%.o, $(notdir $(SRCS)))
DEPS = philos.h

# Default target
all: $(OBJDIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o philo

# Rule for creating the object directory
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Rule for compiling main.c
$(OBJDIR)/main.o: main.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule for compiling source files in SRCDIR
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove object files and the executable
clean:
	rm -f $(OBJDIR)/*.o philo

# Full clean rule
fclean: clean
	rm -f philo

# Rebuild rule
re: fclean all

.PHONY: all clean re
