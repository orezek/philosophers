CC = gcc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread
SRCDIR = ./src
OBJDIR = ./obj

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
       $(SRCDIR)/utils.c \

# Adjust the object files path transformation
OBJS = $(patsubst %.c, $(OBJDIR)/%.o, $(notdir $(SRCS)))
DEPS = philos.h

# Rules for compiling source files to object files
$(OBJDIR)/main.o: main.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJDIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o philo

# Create the object directory if it does not exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -f $(OBJDIR)/*.o philo

re: clean all

.PHONY: all clean re
