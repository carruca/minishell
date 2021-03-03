NAME = minishell

SRC_DIR = ./src/
OBJ_DIR = ./obj/
LIBFT_DIR = ./libft/

SRC = main.c
OBJ = $(SRC:.c=.o)
INC = -I. -I $(LIBFT_DIR)
LIBFT = -L $(LIBFT_DIR) -lft

CC = gcc
WFLAGS = -Wall -Wextra -Werror
MAKE = make
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(WFLAGS) $(INC) $(LIBFT) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(WFLAGS) -c -o $@ $<

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(OBJ)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
