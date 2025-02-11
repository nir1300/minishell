# Define variables
NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Paths to PIPEX and includes
PIPEX_DIR = pipex
PIPEX = $(PIPEX_DIR)/pipex
INCLUDES = -I $(PIPEX_DIR) -I .

# Source files
SRC = heredoc.c
OBJ = $(SRC:.c=.o)

# Compilation rules
all: $(NAME)

$(PIPEX):
	make -C $(PIPEX_DIR)

$(NAME): $(OBJ) $(PIPEX)
	$(CC) $(CFLAGS) $(OBJ) -g -L$(PIPEX_DIR) -Llibft -lft -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -g -c $< -o $@

clean:
	make clean -C $(PIPEX_DIR)
	rm -f $(OBJ)

fclean: clean
	make fclean -C $(PIPEX_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
