# Compiler
CC = cc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror

# Directories
SRC_DIR = ./src
OBJ_DIR = ./obj
INC_DIR = ./includes

# Source files
SRCS = main.c \
       $(SRC_DIR)/clean_allocs.c \
       $(SRC_DIR)/control_thread.c \
       $(SRC_DIR)/forks.c \
       $(SRC_DIR)/fork_utils.c \
       $(SRC_DIR)/init_mutex.c \
       $(SRC_DIR)/init_philosophers.c \
       $(SRC_DIR)/init_resources.c \
       $(SRC_DIR)/init_simulation.c \
       $(SRC_DIR)/thread_execution.c \
       $(SRC_DIR)/thread_states.c \
       $(SRC_DIR)/time_functions.c

# Object files
OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(SRCS)))

# Executable
NAME = philo

# Include directories
INCLUDES = -I$(INC_DIR)

# Rules
all: fclean $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
